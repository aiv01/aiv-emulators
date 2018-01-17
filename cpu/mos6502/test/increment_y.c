#include <test.h>

static int test_increment_y()
{
    unsigned char rom = 0xC8;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, &rom);

    cpu.y = 1;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.y, 2);

    return 0;
}

int test_all_iny()
{
    test(test_increment_y);
    return 0;
}
