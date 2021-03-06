#include <mos6502.h>

static int iny(mos6502_t *cpu)
{
    cpu->y++;

    M6502_Z(cpu, cpu->y == 0);
    M6502_S(cpu, cpu->y >> 7);

    return 2;
}
void iny_init(mos6502_t *cpu)
{
    cpu->op_codes[0xC8] = iny;
}