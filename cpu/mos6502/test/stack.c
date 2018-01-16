#include "test.h"
#include <stdio.h>

static int test_pha_green()
{
    unsigned char rom[512];

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.sp = 0xFF;

    rom[0] = 0x48;

    cpu.a = 6;

    int ticks = mos6502_tick(&cpu);

    // Check if value is correct on the stack
    assert_is_equal(rom[0x01FF], 6);
    // Check if stack pointer has been decremented
    assert_is_equal(cpu.sp, 0xFE);
    // Check if processor ticks are correct
    assert_is_equal(ticks, 3);

    return 0;
}

static int test_pha_red()
{
    unsigned char rom[512];

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.sp = 0xFF;

    rom[0] = 0x48;

    cpu.a = 6;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(rom[0x01FF], 7);
    assert_is_not_equal(cpu.sp, 0xFC);
    assert_is_not_equal(ticks, 4);
    
    return 0;
}

static int test_php_green()
{
    unsigned char rom[512];

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.sp = 0xFF;

    rom[0] = 0x08;

    cpu.flags = 0x80;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(rom[0x01FF], 0x80);
    assert_is_equal(cpu.sp, 0xFE);
    assert_is_equal(ticks, 3);

    return 0;
}

static int test_php_red()
{
    unsigned char rom[512];

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.sp = 0xFF;

    rom[0] = 0x08;

    cpu.flags = 0x80;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(rom[0x01FF], 0x40);
    assert_is_not_equal(cpu.sp, 0xFC);
    assert_is_not_equal(ticks, 4);

    return 0;
}

static int test_pla_green()
{
    unsigned char rom[512];

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.sp = 0xFF;

    rom[0] = 0x48; // Push accumulator to stack

    cpu.a = 6;

    mos6502_tick(&cpu);

    rom[1] = 0x68; // Pull from stack

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(cpu.a, 6);
    assert_is_equal(cpu.sp, 0xFF);
    assert_is_equal(is_set_bit_0(cpu.flags), 0);
    assert_is_equal(is_set_bit_1(cpu.flags), 0);
    assert_is_equal(ticks, 4);

    return 0;
}

static int test_pla_red()
{
    unsigned char rom[512];

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.sp = 0xFF;

    rom[0] = 0x48;

    cpu.a = 6;

    mos6502_tick(&cpu);

    rom[1] = 0x68;

    int ticks = mos6502_tick(&cpu);
    
    assert_is_not_equal(cpu.a, 7);
    assert_is_not_equal(cpu.sp, 0xFE);
    assert_is_not_equal(is_set_bit_0(cpu.flags), 1);
    assert_is_not_equal(is_set_bit_1(cpu.flags), 1);
    assert_is_not_equal(ticks, 5);

    return 0;
}

static int test_plp_green()
{
    unsigned char rom[512];

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.sp = 0xFF;

    rom[0] = 0x08; // Push flags to stack

    cpu.flags = 0x80;

    mos6502_tick(&cpu);

    rom[1] = 0x68; // Pull from stack

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(cpu.sp, 0xFF);
    assert_is_equal(cpu.flags, 0x80);
    assert_is_equal(ticks, 4);

    return 0;
}

static int test_plp_red()
{
    unsigned char rom[512];

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.sp = 0xFF;

    rom[0] = 0x08; // Push flags to stack

    cpu.flags = 0xC0;

    mos6502_tick(&cpu);

    rom[1] = 0x68; // Pull from stack

    cpu.sp++;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(cpu.sp, 0xFE);
    assert_is_not_equal(cpu.flags, 0x80);
    assert_is_not_equal(ticks, 5);

    return 0;
}

int test_all_stack()
{
    test(test_pha_green);
    test(test_pha_red);
    test(test_php_green);
    test(test_php_red);
    test(test_pla_green);
    test(test_pla_red);
    test(test_plp_green);
    test(test_plp_red);

    return 0;
}