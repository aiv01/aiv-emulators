#include "test.h"
#include <stdio.h>

static int test_sta_zero_page()
{
    unsigned char rom[] = {0x85, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    unsigned char address = cpu.read8(&cpu,0x01);
    
    assert_is_equal(address, cpu.a);

    return 0;
}

static int test_sta_zero_page_x()
{
    unsigned char rom[] = {0x95,0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    unsigned char address = cpu.read8(&cpu,0x01);
    
    assert_is_equal(address, cpu.a);

    return 0;
}

static int test_sta_absolute()
{
    unsigned char rom[] = {0x8D,0x01,0x00};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    
    unsigned char address = cpu.read8(&cpu,0x01);
    
    assert_is_equal(address, cpu.a);

    return 0;
}

static int test_sta_absolute_x()
{
    unsigned char rom[] = {0x9D,0x01, 0x00};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    unsigned char address = cpu.read8(&cpu,0x01);
    
    assert_is_equal(address, cpu.a);

    return 0;
}

static int test_sta_absolute_y()
{
    unsigned char rom[] = {0x99,0x01, 0x00};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    unsigned char address = cpu.read8(&cpu,0x01);
    
    assert_is_equal(address, cpu.a);

    return 0;
}

static int test_sta_indirect_x()
{
    unsigned char rom[] = {0x81,0x01, 0x00};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    unsigned char address = cpu.read8(&cpu,0x01);
    
    assert_is_equal(address, cpu.a);

    return 0;
}

static int test_sta_indirect_y()
{
    unsigned char rom[] = {0x91,0x01, 0x00};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    unsigned char address = cpu.read8(&cpu,0x01);
    
    assert_is_equal(address, cpu.a);

    return 0;
}

int test_all_sta()
{
    test(test_sta_zero_page);
    test(test_sta_zero_page_x);
    test(test_sta_absolute);
    test(test_sta_absolute_x);
    test(test_sta_absolute_y);
    test(test_sta_indirect_x);
    test(test_sta_indirect_y);
      
    return 0;
}