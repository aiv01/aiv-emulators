#include <mos6502.h>

static int tsx(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->x &= address + cpu->sp;
    return 2;
}