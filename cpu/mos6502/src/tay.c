#include <mos6502.h>

static int tay(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->y &= address + cpu-> a;
    return 2;
}