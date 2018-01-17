#include <test.h>

static int test_clear_carry()
{
    unsigned char rom[] = { 0x18 }; //first byte points to the opcode

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    //Counting machine clocks
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);              //expecting 2 ticks
    assert_is_zero(((cpu.flags) & 0x01));   //flag is carry, checking it's clear, expecting 0

    return 0;
}

static int test_set_carry()
{
    unsigned char rom[] = { 0x38 }; //first byte points to the opcode

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    //Counting machine clocks
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);                  //expecting 2 ticks
    assert_is_not_zero(((cpu.flags) & 0x01));   //flag is carry, checking it's set, expecting 1

    return 0;
}

static int test_clear_interrupt()
{
    unsigned char rom[] = { 0x58 }; //first byte points to the opcode

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    //Counting machine clocks
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);                      //expecting 2 ticks
    assert_is_zero(((cpu.flags >> 2) & 0x01));      //flag is interrupt, checking it's clear, expecting 0

    return 0;
}

static int test_set_interrupt()
{
    unsigned char rom[] = { 0x78 }; //first byte points to the opcode

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    //Counting machine clocks
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);                          //expecting 2 ticks
    assert_is_not_zero(((cpu.flags >> 2) & 0x01));      //flag is interrupt, checking it's set, expecting 1

    return 0;
}

static int test_clear_overflow()
{
    unsigned char rom[] = { 0xB8 }; //first byte points to the opcode

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    //Counting machine clocks
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);                      //expecting 2 ticks
    assert_is_zero(((cpu.flags >> 5) & 0x01));      //flag is overflow, checking it's clear, expecting 0

    return 0;
}

static int test_clear_decimal()
{
    unsigned char rom[] = { 0xD8 };     //first byte points to the opcode

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    //Counting machine clocks
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);                      //expecting 2 ticks
    assert_is_zero(((cpu.flags >> 3) & 0x01));      //flag is decimal, checking it's clear, expecting 0

    return 0;
}

static int test_set_decimal()
{
    unsigned char rom[] = { 0xF8 };     //first byte points to the opcode

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    //Counting machine clocks
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);                          //expecting 2 ticks
    assert_is_not_zero(((cpu.flags >> 3) & 0x01));      //flag is decimal, checking it's set, expecting 1

    return 0;
}

int test_all_flags()
{
    test(test_clear_carry);
    test(test_set_carry);
    test(test_clear_interrupt);
    test(test_set_interrupt);
    test(test_clear_overflow);
    test(test_clear_decimal);
    test(test_set_decimal);
    return 0;
}