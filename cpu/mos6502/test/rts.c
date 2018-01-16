#include "test.h"

static int test_rts()
{
    unsigned char rom[1024] = {0x60};

    // 6502 init
    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);
    cpu.pc = 0;
    cpu.sp = 0xFF;
    
    // push an address on the stack
    cpu.sp--;
    cpu.write16(&cpu, 0x0100 + cpu.sp, 0xffaa);
    cpu.sp--;

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 0xffab);
    assert_is_equal(cpu.sp, 0xFF);

    return 0;
}

int test_all_rts()
{
    test(test_rts);
    return 0;
}
