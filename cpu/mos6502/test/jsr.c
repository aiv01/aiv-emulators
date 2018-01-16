#include "test.h"

static int test_jsr()
{
    unsigned char rom[1024] = {0x20, 0x00, 0xFF};

    // 6502 init
    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);
    cpu.pc = 0;
    
    assert_is_equal(cpu.sp, 0xFF);

    // read second and third bytes of rom
    unsigned short expected_pc = cpu.read16(&cpu, 1);
    unsigned char expected_sp = cpu.sp - 2;

    int ticks = mos6502_tick(&cpu);
    
    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, expected_pc);
    assert_is_equal(cpu.sp, expected_sp);

    return 0;
}

int test_all_jsr()
{
    test(test_jsr);
    return 0;
}