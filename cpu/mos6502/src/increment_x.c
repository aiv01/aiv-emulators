#include <mos6502.h>

static int inx(mos6502_t *cpu)
{
    cpu->x++;

    M6502_Z(cpu, cpu->x == 0);
    M6502_S(cpu, cpu->x >> 7);

    return 2;
}
void inx_init(mos6502_t *cpu)
{
    cpu->op_codes[0xE8] = inx;
}