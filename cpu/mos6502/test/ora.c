#include "test.h"
#include <string.h>

static int test_ora_immediate()
{
    unsigned char rom[] = {0x09, 0x01};

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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_zero_page()
{
    unsigned char rom[] = {0x05, 0x01};

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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_zero_page_x()
{
    unsigned char rom[] = {0x15, 0x01, 0x01};

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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_absolute()
{
    unsigned char rom[] = {0x0D, 0x03, 0x00, 0x01};

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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_absolute_x()
{
    unsigned char rom[] = {0x1D, 0x03, 0x00, 0x00, 0x01};

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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_absolute_x_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x1D;
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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_absolute_y()
{
    unsigned char rom[] = {0x19, 0x03, 0x00, 0x01, 0x01};

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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_absolute_y_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x19;
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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_indirect_x()
{
    unsigned char rom[] = {0x01, 0x02, 0x00, 0x05, 0x00, 0x01};

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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_indirect_y()
{
    unsigned char rom[] = {0x11, 0x02, 0x04, 0x00, 0x00, 0x01};

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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

static int test_ora_indirect_y_boundary()
{
    unsigned char rom[258];
    memset(rom, 0, sizeof(rom));
    rom[0] = 0x11;
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
    assert_is_equal(cpu.a, 0xAF);

    return 0;
}

int test_all_ora()
{
    test(test_ora_immediate);
    test(test_ora_zero_page);
    test(test_ora_zero_page_x);
    test(test_ora_absolute);
    test(test_ora_absolute_x);
    test(test_ora_absolute_x_boundary);
    test(test_ora_absolute_y);
    test(test_ora_absolute_y_boundary);
    test(test_ora_indirect_x);
    test(test_ora_indirect_y);
    test(test_ora_indirect_y_boundary);
    return 0;
}
