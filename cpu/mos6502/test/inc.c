#include "test.h"

static int test_inc_page_zero()
{
    unsigned char rom[] = {0xE6, 0x02, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(rom[1], 2);

    return 0;
}
static int test_inc_zero_page_x()
{
    unsigned char rom[] = {0xF6, 0x02, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(rom[1], 2);

    return 0;
}
static int test_inc_absolute()
{
    unsigned char rom[] = {0xEE, 0x03, 0x00, 0x01};


    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(rom[3], 2);

    return 0;
}
static int test_inc_absolute_x()
{
    unsigned char rom[] = {0xFE, 0x03, 0x00, 0x01};


    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 7);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(rom[3], 2);

    return 0;
}

int test_all_inc()
{
    test(test_inc_page_zero);
    test(test_inc_zero_page_x);
    test(test_inc_absolute);
    test(test_inc_absolute_x);
    return 0;
}
