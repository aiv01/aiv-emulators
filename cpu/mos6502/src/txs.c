#include <mos6502.h>

static int txs(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->sp &= address + cpu->x;
    return 2;
}