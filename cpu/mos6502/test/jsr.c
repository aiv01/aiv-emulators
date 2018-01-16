#include "test.h"

static int test_jsr()
{
    unsigned char rom[512] = {0x20, 0x00, 0xFF};
    memset(rom + 3, 0, 512-3);

    // 6502 init
    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);
    cpu.pc = 0;
    cpu.sp = 0xff;
    

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.sp, 0xfd);
    assert_is_equal(cpu.pc, 0xff00);

    // read value just pushed in the stack
    unsigned short pushed_pc = cpu.read16(&cpu, 0x0100 + cpu.sp + 1);
    assert_is_equal(pushed_pc, 0x0002);

    return 0;
}

int test_all_jsr()
{
    test(test_jsr);
    return 0;
}
