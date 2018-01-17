#include <test.h>

static int test_decrement_x()
{
    unsigned char rom = 0xCA;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, &rom);

    cpu.x = 3;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.x, 2);

    return 0;
}

int test_all_dex()
{
    test(test_decrement_x);
    return 0;
}
