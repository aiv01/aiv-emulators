#include "test.h"
#include <stdio.h>

static int test_sty_zero_page()
{
    unsigned char rom[] = {0x84, 0x01};


    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, &rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    unsigned char address = cpu.read8(&cpu,0x01);
    assert_is_equal(address, cpu.y);

    return 0;
}

static int test_sty_zero_page_x()
{
    unsigned char rom[] = {0x94, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, &rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);

    unsigned char address = cpu.read8(&cpu,0x01);
    
    assert_is_equal(address, cpu.y);

    return 0;
}

static int test_sty_absolute()
{
    unsigned char rom[] = {0x8C, 0x01,0x00};    

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, &rom);

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    unsigned char address = cpu.read8(&cpu,0x01);    
    assert_is_equal(address, cpu.y);

    return 0;
}

int test_all_sty()
{
    test(test_sty_zero_page);
    test(test_sty_zero_page_x);
    test(test_sty_absolute);
      
    return 0;
}