#include <test.h>

static int test_decrement_y()
{
    unsigned char rom = 0x88;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, &rom);

    cpu.y = 6;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.y, 5);

    return 0;
}

int test_all_dey()
{
    test(test_decrement_y);
    return 0;
}
