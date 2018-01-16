#include <mos6502.h>

static int pha(mos6502_t *cpu) 
{
    cpu->write8(cpu, 0x0100 + cpu->sp, cpu->a);
    cpu->sp--;
    
    return 3;
}

static int php(mos6502_t *cpu) 
{
    cpu->write8(cpu, 0x0100 + cpu->sp, cpu->flags);
    cpu->sp--;

    return 3;
}

static int pla(mos6502_t *cpu) 
{
    cpu->sp++;
    cpu->a = cpu->read8(cpu, 0x0100 + cpu->sp);

    M6502_S(cpu, cpu->a >> 7);
    M6502_Z(cpu, cpu->a == 0);

    return 4;
}

static int plp(mos6502_t *cpu) 
{
    cpu->sp++;
    cpu->flags = cpu->read8(cpu, 0x0100 + cpu->sp);

    return 4;
}

void stack_init(mos6502_t *cpu) 
{
    cpu->op_codes[0x48] = pha;
    cpu->op_codes[0x08] = php;
    cpu->op_codes[0x68] = pla;
    cpu->op_codes[0x28] = plp;
}