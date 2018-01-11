#include "test.h"

static int test_nop_green()
{
    unsigned char rom[] = {0xea};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 1);
    return 0;
}

static int test_nop_red()
{
    unsigned char rom[] = {0xea};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_not_equal(cpu.pc, 2);
    return 0;
}

int test_all_nop()
{
    test(test_nop_green);
    test(test_nop_red);
    return 0;
}