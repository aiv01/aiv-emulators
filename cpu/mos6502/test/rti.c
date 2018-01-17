#include "test.h"

static int test_rti_green()
{
    unsigned char rom[512] = { 0x08, 0x40 };
    
    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);
    
    cpu.pc = 0;
    cpu.sp = 0xFF;

    // Push program counter to the stack
    cpu.sp--;
    cpu.write16(&cpu, 0x0100 + cpu.sp, 0x6666);
    cpu.sp--;

    // Push flags to the stack
    cpu.flags = 0x40;

    mos6502_tick(&cpu);
    
    // Return to interrupt (read flags then pc)

    int ticks = mos6502_tick(&cpu);

    assert_is_equal(ticks, 6);
    assert_is_equal(cpu.pc, 0x6666);
    assert_is_equal(cpu.flags, 0x40);
    assert_is_equal(cpu.sp, 0xFF);

    return 0;
}

static int test_rti_red()
{
    unsigned char rom[512] = { 0x08, 0x40 };
    
    mos6502_t cpu;
    mos6502_init(&cpu);
    mos6502_add_test_full_mapping(&cpu, rom);
    
    cpu.pc = 0;
    cpu.sp = 0xFF;

    // Push program counter to the stack
    cpu.sp--;
    cpu.write16(&cpu, 0x0100 + cpu.sp, 0x6666);
    cpu.sp--;

    // Push flags to the stack
    cpu.flags = 0x40;

    mos6502_tick(&cpu);
    
    // Return to interrupt (read flags then pc)

    int ticks = mos6502_tick(&cpu);

    assert_is_not_equal(ticks, 7);
    assert_is_not_equal(cpu.pc, 0x66FF);
    assert_is_not_equal(cpu.flags, 0x48);
    assert_is_not_equal(cpu.sp, 0xFE);

    return 0;
}

int test_all_rti()
{
    test(test_rti_green);
    test(test_rti_red);

    return 0;
}
