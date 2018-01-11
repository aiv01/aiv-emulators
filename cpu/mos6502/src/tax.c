#include <mos6502.h>

static int tax(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->x &= address + cpu-> a;
    return 2;
}    