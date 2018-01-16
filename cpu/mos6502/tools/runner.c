#include <mos6502.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usage()
{
    fprintf(stdout, "runner <bin> [offset] [address]\n");
}

int main(int argc, char *argv[])
{
    int offset = 0;
    int address_to_monitor = 0;
    if (argc < 2)
    {
        usage();
        fprintf(stderr, "you need to specify a binary file\n");
        return -1;
    }

    char *filename = argv[1];
    if (argc > 2)
    {
        offset = atoi(argv[2]);
        if (offset > 0xffff)
        {
            fprintf(stderr, "invalid offset\n");
            return -1;
        }
    }

    if (argc > 3)
    {
        address_to_monitor = atoi(argv[3]);
        if (address_to_monitor > 0xffff)
        {
            fprintf(stderr, "invalid address to monitor\n");
            return -1;
        }
    }

#ifndef _WIN32
    FILE *f = fopen(filename, "rb");
#else
    FILE *f = NULL;
    fopen_s(&f, filename, "rb");
#endif
    if (!f)
    {
        fprintf(stderr, "unable to open file %s\n", filename);
        return -1;
    }

    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);

    if (file_size > 65536)
    {
        fprintf(stderr, "binary image can be at most 65536 bytes\n");
        fclose(f);
        return -1;
    }

    char *data = malloc(65536);
    if (!data)
    {
        fprintf(stderr, "unable to allocate memory\n");
        fclose(f);
        return -1;
    }
    memset(data, 0, 65536);

    fseek(f, 0, SEEK_SET);

    if (fread(data, 1, file_size, f) != file_size)
    {
        fprintf(stderr, "error while reading binary image\n");
        fclose(f);
	free(data);
        return -1;
    }

    fclose(f);

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, data);

    cpu.sp = 0xFF;
    cpu.pc = offset;

    unsigned long long ticks_counter = 0;
    for(;;)
    {
        int ticks = mos6502_tick(&cpu);
        if (ticks < 0)
            break;
        ticks_counter+=ticks;
        fprintf(stdout, "[$%04X] A=$%02X X=$%02X Y=$%02X Flags=$%02X SP=$%02X value at address $%04X = $%02X\n",
            cpu.pc,
            cpu.a,
            cpu.x,
            cpu.y,
            cpu.flags,
            cpu.sp,
            address_to_monitor,
            (unsigned char )data[address_to_monitor]
        );
    }

    fprintf(stdout, "program exited after %llu ticks\n", ticks_counter);

    free(data);

    return 0;
}
