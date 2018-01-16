#include "test.h"
#include "string.h"

static int test_lda_immediate()
{
    unsigned char rom[] = {0xA9, 0x10};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.a, 0x10);

    return 0;
}

static int test_lda_zero_page()
{
    unsigned char rom[] = {0xA5, 0x02, 0xFF};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.a, 0xFF);

    return 0;
}

static int test_lda_zero_page_x()
{
    unsigned char rom[] = {0xB5, 0x01, 0xFE};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;
    cpu.x = 1;
    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.a, 0xFE);

    return 0;
}

static int test_lda_absolute()
{
    unsigned char rom[] = {0xAD, 0x03, 0x00, 0x5F};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.a, 0x5F);

    return 0;
}

static int test_lda_absolute_x()
{
    unsigned char rom[] = {0xBD, 0x02, 0x00, 0xFF, 0xAA, 0xB5};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.pc = 0;
    cpu.x = 3;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.a, 0xB5);

    return 0;
}
static int test_lda_absolute_x_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0xBD;
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
    assert_is_equal(cpu.a, 0xFB);

    return 0;
}
int test_all_lda()
{
    test(test_lda_immediate);
    test(test_lda_zero_page);
    test(test_lda_zero_page_x);
    test(test_lda_absolute);
    test(test_lda_absolute_x);
    test(test_lda_absolute_x_boundary);
    return 0;
}
