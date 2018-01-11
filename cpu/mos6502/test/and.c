#include "test.h"

static int test_and_immediate()
{
    unsigned char rom[] = {0x29, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 1);

    return 0;
}

static int test_and_zero_page()
{
    unsigned char rom[] = {0x25, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 1);

    return 0;
}

int test_all_and()
{
    test(test_and_immediate);
    test(test_and_zero_page);
    return 0;
}