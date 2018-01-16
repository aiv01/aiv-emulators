#include "test.h"

static int test_ldx_immediate()
{
    unsigned char rom[] = {0xA2, 0x10};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.x, 0x10);
    return 0;
}

static int test_ldx_zero_page()
{
    unsigned char rom[] = {0xA6, 0x01};
 
     mos6502_t cpu;
     mos6502_init(&cpu);
     mos6502_add_test_full_mapping(&cpu, rom);
 
     cpu.pc = 0;
 
     int ticks = mos6502_tick(&cpu);
 
     assert_is_equal(ticks, 3);
     assert_is_equal(cpu.pc, 2);
     assert_is_equal(cpu.x, 0x01);
 
     return 0;
}

static int test_ldx_zero_page_y()
 {
     unsigned char rom[] = {0xB6, 0x01, 0xFE};
 
     mos6502_t cpu;
     mos6502_init(&cpu);
     mos6502_add_test_full_mapping(&cpu, rom);
 
     cpu.pc = 0;
     cpu.y = 1;
     int ticks = mos6502_tick(&cpu);
 
     assert_is_equal(ticks, 4);
     assert_is_equal(cpu.pc, 2);
     assert_is_equal(cpu.x, 0xFE);
 
     return 0;
}


static int test_ldx_absolute()
 {
     unsigned char rom[] = {0xAE, 0x03, 0x00, 0x5F};
 
     mos6502_t cpu;
     mos6502_init(&cpu);
     mos6502_add_test_full_mapping(&cpu, rom);
 
     cpu.pc = 0;
 
     int ticks = mos6502_tick(&cpu);
 
     assert_is_equal(ticks, 4);
     assert_is_equal(cpu.pc, 3);
     assert_is_equal(cpu.x, 0x5F);
 
     return 0;
 }
 
 static int test_ldx_absolute_y()
 {
     unsigned char rom[] = {0xBE, 0x02, 0x00, 0xFF, 0xAA, 0xB5};
 
     mos6502_t cpu;
     mos6502_init(&cpu);
     mos6502_add_test_full_mapping(&cpu, rom);
 
     cpu.pc = 0;
     cpu.y = 3;
 
     int ticks = mos6502_tick(&cpu);
 
     assert_is_equal(ticks, 4);
     assert_is_equal(cpu.pc, 3);
     assert_is_equal(cpu.x, 0xB5);
 
     return 0;
}


int test_all_ldx()
{
    test(test_ldx_immediate);
    test(test_ldx_zero_page);
    test(test_ldx_zero_page_y);
    test(test_ldx_absolute);
    test(test_ldx_absolute_y);
    return 0;
}
