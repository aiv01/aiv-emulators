#include "test.h"
#include <stdio.h>

static int test_stx_zero_page()
{
    fprintf(stdout,"passato");
    unsigned int rom = 0x86;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, &rom);

    //cpu.a = 0xaf;
    //cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);
    fprintf(stdout,"passato");

    assert_is_equal(ticks, 3); // fallisce
    fprintf(stdout,"passato");
    assert_is_equal(cpu.sp, cpu.x);

    return 0;
}

static int test_stx_zero_page_y()
{
    unsigned int rom = 0x96;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, &rom);

    //cpu.a = 0xaf;
    //cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.sp, cpu.x);

    return 0;
}

static int test_stx_absolute()
{
    unsigned int rom = 0x8E;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, &rom);

    //cpu.a = 0xaf;
    //cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.sp, cpu.x);

    return 0;
}

int test_all_stx()
{
    test(test_stx_zero_page);
    test(test_stx_zero_page_y);
    test(test_stx_absolute);
      
    return 0;
}