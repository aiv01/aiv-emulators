#include <mos6502.h>

static int txa(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->a &= address + cpu-> y;
    return 2;
}