#include "test.h"
#include <stdio.h>
#include <string.h>

static int test_sbc_immediate_case1()
{
    unsigned char rom[] = {0xE9, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

static int test_sbc_immediate_case2()
{
    unsigned char rom[] = {0xE9, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x7F;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);             //S) Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01));  //V) Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));  //Z) Zero
    assert_is_zero((cpu.flags & 0x01));         //C) Carry
    assert_is_equal(cpu.a, 0x7E);
                                         
    return 0;
}

static int test_sbc_immediate_case3()
{
    unsigned char rom[] = {0xE9, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xFF;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_not_zero(cpu.flags >> 7);         //S) Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01));  //V) Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));  //Z) Zero
    assert_is_zero((cpu.flags & 0x01));         //C) Carry
    assert_is_equal(cpu.a, 0xFE);
    return 0;
}

static int test_sbc_zero_page_case1()
{
    unsigned char rom[] = {0xE5, 0x02, 0x01};   //Zero Page Address pointer = 0x02  point to Value = 0x01

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_equal(cpu.pc, 2);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

static int test_sbc_zero_page_x_case1_case1()
{
    unsigned char rom[] = {0xF5, 0x02, 0x00, 0x01};   

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 2);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

static int test_sbc_absolute_case1()
{
    unsigned char rom[] = {0xED, 0x03, 0x00, 0x01};   

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

static int test_sbc_absolute_x_case1()
{
    unsigned char rom[] = {0xFD, 0x02, 0x00, 0x01};   

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

static int test_sbc_absolute_x_case2()
{
    unsigned char rom[257];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0xFD;   //OPCODE
    rom[1] = 0xFF;   //ADDRESS Zero Page at limit 255
    rom[256] = 0x01; //VALUE POINTED in Page One by X offset =1

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 3);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

static int test_sbc_absolute_y_case1()
{
    unsigned char rom[] = {0xF9, 0x02, 0x00, 0x01};   

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

static int test_sbc_indirect_x_case1()
{
    
    unsigned char rom[6];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0xE1;   //OPCODE
    rom[1] = 0x02;   //ADDRESS OPERAND $0002
    rom[2] = 0x00;   
    rom[3] = 0x05;   //FINAL ADDRESS $0005 pointed by ADDRESS OPERAND + X OFFSET 
    rom[4] = 0x00;   
    rom[5] = 0x01;   //VALUE POINTED by FINAL ADDRESS

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

static int test_sbc_indirect_y_case1()
{
    unsigned char rom[6];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0xF1;   //OPCODE
    rom[1] = 0x02;   //ADDRESS OPERAND $02
    rom[2] = 0x03;   //FINAL ADDRESS $0003 pointed by ADDRESS OPERAND 
    rom[3] = 0x00;      
    rom[4] = 0x01;   //VALUE POINTED by FINAL ADDRESS

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 2);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

static int test_sbc_indirect_y_case2()
{
    unsigned char rom[257];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0xF1;      //OPCODE
    rom[1] = 0x02;      //ADDRESS OPERAND $02
    rom[2] = 0xFF;      //INDIRECT ADDRESS $00FF pointed by ADDRESS OPERAND 
    rom[3] = 0x00;   
    rom[256] = 0x01;    //VALUE POINTED by FINAL ADDRESS

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_not_zero(cpu.flags >> 7);             //Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01));  //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));      //Zero
    assert_is_not_zero((cpu.flags & 0x01));         //Carry
    assert_is_equal(cpu.a, 0xff);

    return 0;
}

int test_all_sbc()
{
    test(test_sbc_immediate_case1);
    test(test_sbc_immediate_case2);
    test(test_sbc_immediate_case3);
    test(test_sbc_zero_page_case1);
    test(test_sbc_zero_page_x_case1_case1);
    test(test_sbc_absolute_case1);
    test(test_sbc_absolute_x_case1);
    test(test_sbc_absolute_x_case2);
    test(test_sbc_absolute_y_case1);
    test(test_sbc_indirect_x_case1);
    test(test_sbc_indirect_y_case1);
    test(test_sbc_indirect_y_case2);
    return 0;
}
