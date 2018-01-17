#include "test.h"

////////////////////BEQ and BNE///////////////
static int test_branch_equal_green() //BEQ
{
    unsigned char rom[] = {0xF0, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);
    
    cpu.flags = FLAG_ZERO;       //set ZERO_BIT to 1
    cpu.pc = 0;                 //setup pc to 0

    int ticks = mos6502_tick(&cpu);  

    assert_is_equal(ticks, 3);
    assert_is_not_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.pc, 3);

    return 0;
}

static int test_branch_equal_red() //BEQ
{
    unsigned char rom[] = {0xF0, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags &= FLAG_ZERO;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(ticks, 3);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.pc, 2);

    return 0;
}

static int test_branch_not_equal_green() //BNE
{
    unsigned char rom[] = {0xD0, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags &= FLAG_ZERO;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.pc, 3);

    return 0;
}

static int test_branch_not_equal_red() //BNE
{
    unsigned char rom[] = {0xD0, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags = FLAG_ZERO;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(ticks, 3);
    assert_is_not_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.pc, 2);

    return 0;
}

////////////////////BCS and BCC///////////////
static int test_branch_carry_set_green() //BCS
{
    unsigned char rom[] = {0xB0, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags = FLAG_CARRY;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_not_zero(((cpu.flags) & 0x01));
    assert_is_equal(cpu.pc, 3);

    return 0;
}

static int test_branch_carry_set_red() //BCS
{
    unsigned char rom[] = {0xB0, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags &= FLAG_CARRY;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(ticks, 3);
    assert_is_zero(((cpu.flags) & 0x01));
    assert_is_equal(cpu.pc, 2);

    return 0;
}

static int test_branch_carry_clear_green() //BCC
{
    unsigned char rom[] = {0x90, 0x03, 0x03};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags &= FLAG_CARRY;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_zero(((cpu.flags) & 0x01));
    assert_is_equal(cpu.pc, 5);

    return 0;
}

static int test_branch_carry_clear_red() //BCC
{
    unsigned char rom[] = {0x90, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags = FLAG_CARRY;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(ticks, 3);
    assert_is_not_zero(((cpu.flags) & 0x01));
    assert_is_equal(cpu.pc, 2);

    return 0;
}

////////////////////BVS and BVC///////////////
static int test_branch_overflow_set_green() //BVS
{
    unsigned char rom[] = {0x70, 0x02};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags = FLAG_OVERFLOW;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_not_zero(((cpu.flags >> 5) & 0x01));
    assert_is_equal(cpu.pc, 4);

    return 0;
}

static int test_branch_overflow_set_red() //BVS
{
    unsigned char rom[] = {0x70, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags &= FLAG_OVERFLOW;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(ticks, 3);
    assert_is_zero(((cpu.flags >> 5) & 0x01));
    assert_is_equal(cpu.pc, 2);

    return 0;
}

static int test_branch_overflow_clear_green() //BVC
{
    unsigned char rom[] = {0x50, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags &= FLAG_OVERFLOW;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_zero(((cpu.flags >> 5) & 0x01));
    assert_is_equal(cpu.pc, 3);

    return 0;
}

static int test_branch_overflow_clear_red() //BVC
{
    unsigned char rom[] = {0x50, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags = FLAG_OVERFLOW;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_not_zero(((cpu.flags >> 5) & 0x01));
    assert_is_equal(cpu.pc, 2);

    return 0;
}

////////////////////BPL and BMI///////////////
static int test_branch_on_minus_green() //BMI
{
    unsigned char rom[] = {0x30, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags = FLAG_NEGATIVE;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_not_zero(((cpu.flags >> 7) & 0x01));
    assert_is_equal(cpu.pc, 3);

    return 0;
}

static int test_branch_on_minus_red() //BMI
{
    unsigned char rom[] = {0x30, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags &= FLAG_NEGATIVE;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(ticks, 3);
    assert_is_zero(((cpu.flags >> 7) & 0x01));
    assert_is_equal(cpu.pc, 2);

    return 0;
}

static int test_branch_on_plus_green() //BPL
{
    unsigned char rom[] = {0x10, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.flags &= FLAG_NEGATIVE;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_zero(((cpu.flags >> 7) & 0x01));
    assert_is_equal(cpu.pc, 3);

    return 0;
}

static int test_branch_on_plus_red() //BPL
{
    unsigned char rom[] = {0x10, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    //set current NEGATIVE flag to 1
    cpu.flags = FLAG_NEGATIVE;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(ticks, 3);
    assert_is_not_zero(((cpu.flags >> 7) & 0x01));
    assert_is_equal(cpu.pc, 2);

    return 0;
}
//end of tests methods

int test_all_branch()
{
    test(test_branch_equal_green);
    test(test_branch_equal_red)
    test(test_branch_not_equal_green);
    test(test_branch_not_equal_red);
    test(test_branch_carry_set_green);
    test(test_branch_carry_set_red);
    test(test_branch_carry_clear_green);
    test(test_branch_carry_clear_red);
    test(test_branch_overflow_set_green);
    test(test_branch_overflow_set_red);
    test(test_branch_overflow_clear_green);
    test(test_branch_overflow_clear_red);
    test(test_branch_on_minus_green);
    test(test_branch_on_minus_red);
    test(test_branch_on_plus_green);
    test(test_branch_on_plus_red);
    return 0;
}