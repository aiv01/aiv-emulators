#include "test.h"

static int test_dec_page_zero()
{
    unsigned char rom[] = {0xC6, 0x02, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_not_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(rom[2], 0);

    return 0;
}
static int test_dec_zero_page_x()
{
    unsigned char rom[] = {0xD6, 0x02, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_not_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(rom[2], 0);

    return 0;
}
static int test_dec_absolute()
{
    unsigned char rom[] = {0xCE, 0x03, 0x00, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7);
    assert_is_not_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(rom[3], 0);

    return 0;
}
static int test_dec_absolute_x()
{
    //il primo è l'opcode, poi i 2 sono gli indirizzi e il quarto è il
    unsigned char rom[] = {0xDE, 0x03, 0x00, 0x01};


    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 7);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7);
    assert_is_not_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(rom[3], 0);

    return 0;
}

int test_all_dec()
{
    test(test_dec_page_zero);
    test(test_dec_zero_page_x);
    test(test_dec_absolute);
    test(test_dec_absolute_x);
    return 0;
}
