#include "test.h"


//CPX IMMEDIATE
static int test_cpx_immediate()
{
    unsigned char rom[] = {0xe0, 0x40};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.x = 0x40;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}

static int test_cpx_zero_page()
{
    unsigned char rom[] = {0xe4, 0x02,0x40};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.x = 0x40;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_equal(cpu.pc, 2);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}

static int test_cpx_absolute()
{
    unsigned char rom[] = {0xec, 0x03,0x00,0x10};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.x = 0x10;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    
    assert_is_equal(cpu.pc, 3);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}


int test_all_cpx()
{
    test(test_cpx_immediate);
    test(test_cpx_zero_page);
    test(test_cpx_absolute);
    return 0;
}