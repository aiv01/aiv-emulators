#include "test.h"
#include <string.h>

static int test_asl_accumulator()
{
    unsigned char rom[] = {0x0A};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x55;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_zero(is_set_bit_0(cpu.flags));
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAA);

    return 0;
}

static int test_asl_zero_page()
{
    unsigned char rom[] = {0x06, 0x02, 0x55};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(is_set_bit_0(cpu.flags));
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAF);
    assert_is_equal(cpu.read8(&cpu, 0x02), 0xAA);

    return 0;
}

static int test_asl_zero_page_x()
{
    unsigned char rom[] = {0x16, 0x02, 0x00, 0x55};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(is_set_bit_0(cpu.flags));
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAF);
    printf("%d\n", cpu.read8(&cpu, 0x03));
    assert_is_equal(cpu.read8(&cpu, 0x03), 0xAA);

    return 0;
}

static int test_asl_absolute()
{
    unsigned char rom[] = {0x0E, 0x03, 0x00, 0x56};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(is_set_bit_0(cpu.flags));
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAF);
    assert_is_equal(cpu.read8(&cpu, 0x03), 0xAC);

    return 0;
}

static int test_asl_absolute_x()
{
    unsigned char rom[] = {0x1E, 0x02, 0x00, 0x57};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 7);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(is_set_bit_0(cpu.flags));
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAF);
    assert_is_equal(cpu.read8(&cpu, 0x03), 0xAE);

    return 0;
}

int test_all_asl()
{
    test(test_asl_accumulator);
    test(test_asl_zero_page);
    test(test_asl_zero_page_x);
    test(test_asl_absolute);
    test(test_asl_absolute_x);
    return 0;
}