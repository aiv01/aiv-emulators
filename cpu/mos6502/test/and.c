#include "test.h"
#include <string.h>

static int test_and_immediate()
{
    unsigned char rom[] = {0x29, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 2);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 1);

    return 0;
}

static int test_and_zero_page()
{
    unsigned char rom[] = {0x25, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 3);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 1);

    return 0;
}

static int test_and_zero_page_x()
{
    unsigned char rom[] = {0x35, 0x01, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0x1);

    return 0;
}

static int test_and_absolute()
{
    unsigned char rom[] = {0x2d, 0x03, 0x00, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0x1);

    return 0;
}

static int test_and_absolute_x()
{
    unsigned char rom[] = {0x3d, 0x03, 0x00, 0x00, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0x1);

    return 0;
}

static int test_and_absolute_x_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x3d;
    rom[1] = 0xff;
    rom[256] = 0x01;
 
    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0x1);

    return 0;
}

static int test_and_absolute_y()
{
    unsigned char rom[] = {0x39, 0x03, 0x00, 0x01, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 4);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0x1);

    return 0;
}

static int test_and_absolute_y_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x39;
    rom[1] = 0xff;
    rom[256] = 0x01;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 3);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0x1);

    return 0;
}

static int test_and_indirect_x()
{
    unsigned char rom[] = {0x21, 0x02, 0x00, 0x05, 0x00, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.x = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0x1);

    return 0;
}

static int test_and_indirect_y()
{
    unsigned char rom[] = {0x31, 0x02, 0x04, 0x00, 0x00, 0x01};

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 5);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0x1);

    return 0;
}

static int test_and_indirect_y_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x31;
    rom[1] = 0x02;
    rom[2] = 0xff;
    rom[256] = 0x01;

    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);

    cpu.a = 0xaf;
    cpu.y = 0x01;
    cpu.pc = 0;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 2);
    assert_is_zero(cpu.flags >> 7);
    assert_is_zero(((cpu.flags >> 1) & 0x01));
    assert_is_equal(cpu.a, 0x1);

    return 0;
}

int test_all_and()
{
    test(test_and_immediate);
    test(test_and_zero_page);
    test(test_and_zero_page_x);
    test(test_and_absolute);
    test(test_and_absolute_x);
    test(test_and_absolute_x_boundary);
    test(test_and_absolute_y);
    test(test_and_absolute_y_boundary);
    test(test_and_indirect_x);
    test(test_and_indirect_y);
    test(test_and_indirect_y_boundary);
    return 0;
}