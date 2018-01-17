#include <mos6502.h>

static int rti(mos6502_t *cpu)
{
    // I move to the first value from the stack
    cpu->sp++;
    // I pull the first value and I put it to the flags
    cpu->flags = cpu->read8(cpu, 0x0100 + cpu->sp);
    // I move to the second value
    cpu->sp++;
    // I save the second value (program counter) into a variable
    unsigned short prev_pc = cpu->read16(cpu, 0x0100 + cpu->sp);
    cpu->sp++;
    // I jump to previous program counter
    cpu->pc = prev_pc;

    return 6;
}

void rti_init(mos6502_t *cpu) 
{
    cpu->op_codes[0x40] = rti;
}