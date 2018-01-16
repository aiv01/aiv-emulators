#include "test.h"


//CMP IMMEDIATE
static int test_cmp_immediate()
{
    unsigned char rom[] = {0xc9, 0x40};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x40;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}
static int test_cmp_immediate_red_light()
{
    unsigned char rom[] = {0xc9, 0x40};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x30;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    
    assert_is_equal(is_set_bit_1(cpu.flags),0); //z check expected 1 (are equal)
    
    assert_is_equal(is_set_bit_7(cpu.flags),1); // s check expected 1 (have sign)
    
    assert_is_equal(is_set_bit_0(cpu.flags),0); //c a is less
    
    return 0;
}

//CMP ZERO PAGE
static int test_cmp_zero_page()
{
    unsigned char rom[] = {0xc5, 0x02,0x40};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x40;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_equal(cpu.pc, 2);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}

//CMP ZERO PAGE X
static int test_cmp_zero_page_x()
{
    unsigned char rom[] = {0xd5, 0x00,0x20};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x20;
    cpu.x = 0x02;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 2);

    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}

//CMP ABSOLUTE
static int test_cmp_absolute()
{
    unsigned char rom[] = {0xcd, 0x03,0x00,0x10};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x10;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}

//CMP ABSOLUTE X
static int test_cmp_absolute_x()
{
    unsigned char rom[] = {0xdd, 0x03,0x00,0x10,0x05};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.x = 0x01;
    cpu.a = 0x05;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}
static int test_cmp_absolute_x_next_page()
{
    unsigned char rom[258];
    rom[0] = 0xdd;
    rom[1] = 0xff;
    rom[2] = 0x00; //255
    rom[257] = 0x05;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.x = 0x02;
    cpu.a = 0x05;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 3);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}
static int test_cmp_absolute_x_next_page_not_equal()
{
    unsigned char rom[258];
    rom[0] = 0xdd;
    rom[1] = 0xff;
    rom[2] = 0xff; //255
    rom[257] = 0x25;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.x = 0x03;
    cpu.a = 0x05;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 3);
    
    assert_is_equal(is_set_bit_1(cpu.flags),0); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),1); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),0); //c check (is >=)
    
    return 0;
}

//CMP ABSOLUTE Y
static int test_cmp_absolute_y()
{
    unsigned char rom[] = {0xd9, 0x03,0x00,0x10,0x25};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.y = 0x01;
    cpu.a = 0x25;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}
static int test_cmp_absolute_y_not_equal()
{
    unsigned char rom[] = {0xd9, 0x03,0x00,0x10,0x25};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.y = 0x01;
    cpu.a = 0x35;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    
    assert_is_equal(is_set_bit_1(cpu.flags),0); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    
    return 0;
}

static int test_cmp_indirect_x()
{
    unsigned char rom[] = {0xc1,0x03,0x00,0x03,0x00};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.x = 0x00;
    cpu.a = 0x03;
    int ticks = mos6502_tick(&cpu);
    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    return 0;
}

static int test_cmp_indirect_y()
{
    unsigned char rom[] = {0xd1,0x03,0x00,0x03,0x00};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.y = 0x00;
    cpu.a = 0x03;
    int ticks = mos6502_tick(&cpu);
    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 2);
    
    assert_is_equal(is_set_bit_1(cpu.flags),1); //z check expected 1 (are equal)
    assert_is_equal(is_set_bit_7(cpu.flags),0); // s check expected 0 (have sign)
    assert_is_equal(is_set_bit_0(cpu.flags),1); //c check (is >=)
    return 0;
}


int test_all_cmp()
{
    test(test_cmp_immediate);
    test(test_cmp_immediate_red_light);

    test(test_cmp_zero_page);
    test(test_cmp_zero_page_x);
    test(test_cmp_absolute);
    test(test_cmp_absolute_x);
    test(test_cmp_absolute_x_next_page);
    test(test_cmp_absolute_x_next_page_not_equal);
    test(test_cmp_absolute_y);
    test(test_cmp_absolute_y_not_equal);
    test(test_cmp_indirect_x);
    test(test_cmp_indirect_y);
    return 0;
}