#include "test.h"

static int test_jump_absolute()
{
    unsigned char rom[] = {0x4C, 0x04, 0x00, 0x00, 0x45};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_equal(cpu.pc, 0x04);

    return 0;
}

static int test_jump_indirect()
{
    unsigned char rom[] = {0x6C, 0x04, 0x00, 0x00, 0x45, 0x00};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 0x45);

    return 0;
}

int test_all_jump()
{
    test(test_jump_absolute);
    test(test_jump_indirect);
    return 0;
}