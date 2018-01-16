#include "test.h"
#include "string.h"
static int test_ldy_immediate()
{
    unsigned char rom[] = {0xA0, 0x10};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.y, 0x10);

    return 0;
}

static int test_ldy_zero_page()
{
    unsigned char rom[] = {0xA4, 0x02, 0xFF};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.y, 0xFF);

    return 0;
}

static int test_ldy_zero_page_x()
{
    unsigned char rom[] = {0xB4, 0x01, 0xFE};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;
    cpu.x = 1;
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.y, 0xFE);

    return 0;
}

static int test_ldy_absolute()
{
    unsigned char rom[] = {0xAC, 0x03, 0x00, 0x5F};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.y, 0x5F);

    return 0;
}

static int test_ldy_absolute_x()
{
    unsigned char rom[] = {0xBC, 0x02, 0x00, 0xFF, 0xAA, 0xB5};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;
    cpu.x = 3;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.y, 0xB5);

    return 0;
}
static int test_ldy_absolute_x_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0xBC;
    rom[1] = 0xFF;
    rom[256] = 0xFB;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;
    cpu.x = 1;
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.y, 0xFB);

    return 0;
}
int test_all_ldy()
{
    test(test_ldy_immediate);
    test(test_ldy_zero_page);
    test(test_ldy_zero_page_x);
    test(test_ldy_absolute);
    test(test_ldy_absolute_x);
    test(test_ldy_absolute_x_boundary);
    return 0;
}