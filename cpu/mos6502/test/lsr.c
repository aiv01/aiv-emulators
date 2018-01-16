#include "test.h"


static int test_lsr_accumulator()
{
    unsigned char rom[] = {0x4a, 0x40};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x01;
    
    int ticks = mos6502_tick(&cpu);
    
    assert_is_equal(cpu.a, 0x80); //first bit on the left on
    assert_is_equal(ticks,2);
    assert_is_equal(cpu.pc,1);
    assert_is_equal(is_set_bit_0(cpu.flags),1); //carry
    assert_is_equal(is_set_bit_1(cpu.flags),0); //zero
    assert_is_equal(is_set_bit_7(cpu.flags),1); //sign
    
    return 0;
}
static int test_lsr_accumulator_red_light()
{
    unsigned char rom[] = {0x4a, 0x40};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x02;
    
    int ticks = mos6502_tick(&cpu);
    
    assert_is_equal(cpu.a, 0x01); //first bit on the left on
    assert_is_equal(ticks,2);
    assert_is_equal(cpu.pc,1);
    assert_is_equal(is_set_bit_0(cpu.flags),0); //carry
    assert_is_equal(is_set_bit_1(cpu.flags),0); //zero
    assert_is_equal(is_set_bit_7(cpu.flags),0); //sign
    return 0;
}
static int test_lsr_accumulator_is_zero()
{
    unsigned char rom[] = {0x4a, 0x40};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    
    int ticks = mos6502_tick(&cpu);
    
    assert_is_equal(cpu.a, 0x00); //first bit on the left on
    assert_is_equal(ticks,2);
    assert_is_equal(cpu.pc,1);
    assert_is_equal(is_set_bit_0(cpu.flags),0); //carry
    assert_is_equal(is_set_bit_1(cpu.flags),1); //zero
    assert_is_equal(is_set_bit_7(cpu.flags),0); //sign
    return 0;
}

static int test_lsr_zero_page()
{
    unsigned char rom[] = {0x46, 0x03,0x50,0x03,0x20,0x4a};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);
    
    assert_is_equal(rom[3], 0x81); //first bit on the left on
    assert_is_equal(ticks,5);
    assert_is_equal(cpu.pc,2);
    assert_is_equal(is_set_bit_0(cpu.flags),1); //carry
    assert_is_equal(is_set_bit_1(cpu.flags),0); //zero
    assert_is_equal(is_set_bit_7(cpu.flags),1); //sign
    return 0;
}

static int test_lsr_zero_page_x()
{
    unsigned char rom[] = {0x56, 0x03,0x50,0x03,0x20,0x04};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.x = 2;
    int ticks = mos6502_tick(&cpu);
    
    assert_is_equal(rom[5], 0x02); //first bit on the left on
    assert_is_equal(ticks,6);
    assert_is_equal(cpu.pc,2);
    assert_is_equal(is_set_bit_0(cpu.flags),0);
    assert_is_equal(is_set_bit_1(cpu.flags),0); //zero
    assert_is_equal(is_set_bit_7(cpu.flags),0); //sign
    return 0;
}

static int test_lsr_absolute()
{
    unsigned char rom[300];
    rom[0] = 0x4e;
    rom[1] = 0x10;
    rom[2] = 0x01;
    rom[272] = 0x01;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    int ticks = mos6502_tick(&cpu);
    
    assert_is_equal(rom[272], 0x80); //first bit on the left on
    assert_is_equal(ticks,6);
    assert_is_equal(cpu.pc,3);
    assert_is_equal(is_set_bit_0(cpu.flags),1);
    assert_is_equal(is_set_bit_1(cpu.flags),0); //zero
    assert_is_equal(is_set_bit_7(cpu.flags),1); //sign
    return 0;
}
static int test_lsr_absolute_x()
{
    unsigned char rom[300];
    rom[0] = 0x5e;
    rom[1] = 0x10;
    rom[2] = 0x01;
    rom[274] = 0x01;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.x = 2;

    int ticks = mos6502_tick(&cpu);
    
    assert_is_equal(rom[274], 0x80); //first bit on the left on
    assert_is_equal(ticks,6);
    assert_is_equal(cpu.pc,3);
    assert_is_equal(is_set_bit_0(cpu.flags),1);
    assert_is_equal(is_set_bit_1(cpu.flags),0); //zero
    assert_is_equal(is_set_bit_7(cpu.flags),1); //sign
    return 0;
}
int test_all_lsr()
{
    test(test_lsr_accumulator);
    test(test_lsr_accumulator_red_light);
    test(test_lsr_accumulator_is_zero);
    test(test_lsr_zero_page);
    test(test_lsr_zero_page_x);
    test(test_lsr_absolute);
    test(test_lsr_absolute_x);
    return 0;
}