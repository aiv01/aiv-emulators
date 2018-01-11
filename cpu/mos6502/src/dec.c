#include <mos6502.h>

static int dec_zero_page(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);
    value--;
    cpu->write8(cpu, address, value);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    return 5;
}

static int dec_zero_page_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);
    value--;
    cpu->write8(cpu, address, value);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    return 6;
}

static int dec_absolute(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);
    value--;
    cpu->write8(cpu, address, value);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    return 3;
}

static int dec_absolute_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->x;
    unsigned char value = cpu->read8(cpu, page);
    value--;
    cpu->write8(cpu, address, value);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    return 7;
}

void dec_init(mos6502_t *cpu)
{
    cpu->op_codes[0xC6] = dec_zero_page;
    cpu->op_codes[0xD6] = dec_zero_page_x;
    cpu->op_codes[0xCE] = dec_absolute;
    cpu->op_codes[0xDE] = dec_absolute_x;
}