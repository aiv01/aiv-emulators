#include "test.h"
#include <stdio.h>
#include <string.h>

/* CASE2: Adding 1 to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_immediate_case1()
{
    unsigned char rom[] = {0x69, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

/* CASE2: Adding 1 to accumulator A = 127
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 128  [10000001]
 *           FLAGS:   S V Z C
 *                    1 1 0 0
*/
static int test_adc_immediate_case2()
{
    unsigned char rom[] = {0x69, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x7F;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_not_zero(cpu.flags >> 7);            //S) Sign
    assert_is_not_zero(((cpu.flags >> 6) & 0x01)); //V) Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01));     //Z) Zero
    assert_is_zero((cpu.flags & 0x01));            //C) Carry
    assert_is_equal(cpu.a, 128);
                                         //$00 to $7F represents 0 to 127 and $80 to $FF represents -128 to -1
    return 0;
}

/* CASE3: Adding 1 to accumulator A = 255
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 0   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 1 1
*/
static int test_adc_immediate_case3()
{
    unsigned char rom[] = {0x69, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xFF;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);                //S) Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01));     //V) Overflow
    assert_is_not_zero(((cpu.flags >> 1) & 0x01)); //Z) Zero
    assert_is_not_zero((cpu.flags & 0x01));        //C) Carry
    assert_is_equal(cpu.a, 0);
                                         //$00 to $7F represents 0 to 127 and $80 to $FF represents -128 to -1
    return 0;
}

/* CASE:  Adding 1 (read from address at page0) to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_zeropage_case1()
{
    unsigned char rom[] = {0x65, 0x02, 0x01};   //Zero Page Address pointer = 0x02  point to Value = 0x01

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

/* CASE:  Adding 1 (read from address at page0 + X offset = 1) to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_zeropagex_case1()
{
    //Zero Page Address pointer = 0x02 + X offset (0x01) point to Value = 0x01 
    // 0x00 used just for padding
    unsigned char rom[] = {0x75, 0x02, 0x00, 0x01};   

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

/* CASE:  Adding 1 (read from absolute address) to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_absolute_case1()
{
    //Absolute Address pointer = 0x0300 (16bit address) point to Value = 0x01 
    unsigned char rom[] = {0x6D, 0x03, 0x00, 0x01};   

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

/* CASE:  Adding 1 (read from absolute address + X offset staying in the same page) to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_absolutex_case1()
{
    //Absolute Address pointer 0x0200 (16bit address) + X=1 point to Value = 0x01 
    unsigned char rom[] = {0x7D, 0x02, 0x00, 0x01};   

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

/* CASE:  Adding 1 (read from absolute address + X offset goes in DIFFERENT page) to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_absolutex_case2()
{
    
    unsigned char rom[257];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x7D;   //OPCODE
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
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

/* CASE:  Adding 1 (read from absolute address + Y offset staying in the same page) to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_absolutey_case1()
{
    //Absolute Address pointer 0x0200 (16bit address) + Y=1 point to Value = 0x01 
    unsigned char rom[] = {0x79, 0x02, 0x00, 0x01};   

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

/* CASE:  Adding 1 (read from indirect address of Address Operand + X offset) to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_indirectx_case1()
{
    
    unsigned char rom[6];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x61;   //OPCODE
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
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

/* CASE:  Adding 1 (read from indirect address of Address Operand and after adding Y offset and staying in the same page) to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_indirecty_case1()
{
    unsigned char rom[6];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x71;   //OPCODE
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
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

/* CASE:  Adding 1 (read from indirect address of Address Operand and after adding Y offset
          going in a DIFFERENT page) to accumulator A = 0
 *        With FLAGS: S V Z C
 *                    0 0 0 0
 *        EXPECTED:   
 *                    76543210
 *           A = 1   [00000001]
 *           FLAGS:   S V Z C
 *                    0 0 0 0
*/
static int test_adc_indirecty_case2()
{
    unsigned char rom[257];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x71;   //OPCODE
    rom[1] = 0x02;   //ADDRESS OPERAND $02
    rom[2] = 0xFF;   //INDIRECT ADDRESS $00FF pointed by ADDRESS OPERAND 
    rom[3] = 0x00;   
    rom[256] = 0x01;   //VALUE POINTED by FINAL ADDRESS

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0x00;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);
    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7); //Sign
    assert_is_zero(((cpu.flags >> 6) & 0x01)); //Overflow
    assert_is_zero(((cpu.flags >> 1) & 0x01)); //Zero
    assert_is_zero((cpu.flags & 0x01)); //Carry
    assert_is_equal(cpu.a, 1);

    return 0;
}

int test_all_adc()
{
    test(test_adc_immediate_case1);
    test(test_adc_immediate_case2);
    test(test_adc_immediate_case3);
    test(test_adc_zeropage_case1);
    test(test_adc_zeropagex_case1);
    test(test_adc_absolute_case1);
    test(test_adc_absolutex_case1);
    test(test_adc_absolutex_case2);
    test(test_adc_absolutey_case1);
    test(test_adc_indirectx_case1);
    test(test_adc_indirecty_case1);
    test(test_adc_indirecty_case2);
    return 0;
}