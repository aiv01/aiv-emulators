#include "test.h"
#include <string.h>

static int test_eor_immediate()
{
    unsigned char rom[] = {0x49, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_zero_page()
{
    unsigned char rom[] = {0x45, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_zero_page_x()
{
    unsigned char rom[] = {0x55, 0x01, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_absolute()
{
    unsigned char rom[] = {0x4D, 0x03, 0x00, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_absolute_x()
{
    unsigned char rom[] = {0x5D, 0x03, 0x00, 0x00, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_absolute_x_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x5D;
    rom[1] = 0xFF;
    rom[256] = 0x01;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_absolute_y()
{
    unsigned char rom[] = {0x59, 0x03, 0x00, 0x01, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_absolute_y_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x59;
    rom[1] = 0xFF;
    rom[256] = 0x01;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 3);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_indirect_x()
{
    unsigned char rom[] = {0x41, 0x02, 0x00, 0x05, 0x00, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_indirect_y()
{
    unsigned char rom[] = {0x51, 0x02, 0x04, 0x00, 0x00, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

static int test_eor_indirect_y_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x51;
    rom[1] = 0x02;
    rom[2] = 0xFF;
    rom[256] = 0x01;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xAF;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_equal(cpu.flags >> 7, 1);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0xAE);

    return 0;
}

int test_all_eor()
{
    test(test_eor_immediate);
    test(test_eor_zero_page);
    test(test_eor_zero_page_x);
    test(test_eor_absolute);
    test(test_eor_absolute_x);
    test(test_eor_absolute_x_boundary);
    test(test_eor_absolute_y);
    test(test_eor_absolute_y_boundary);
    test(test_eor_indirect_x);
    test(test_eor_indirect_y);
    test(test_eor_indirect_y_boundary);
    return 0;
}
