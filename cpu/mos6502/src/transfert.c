#include <mos6502.h>

static int txa(mos6502_t *cpu)
{  
    cpu->a = cpu->x;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);
    
    return 2;
}

static int tax(mos6502_t *cpu)
{  
    cpu->x = cpu->a;

    M6502_Z(cpu, cpu->x == 0);
    M6502_S(cpu, cpu->x >> 7);

    return 2;
}

static int tya(mos6502_t *cpu)
{  
    cpu->a = cpu-> y;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 2;
}

static int tay(mos6502_t *cpu)
{  
    cpu->y = cpu->a;

    M6502_Z(cpu, cpu->y == 0);
    M6502_S(cpu, cpu->y >> 7);

    return 2;
}

static int txs(mos6502_t *cpu)
{  
    cpu->sp = cpu->x;

    return 2;
}

static int tsx(mos6502_t *cpu)
{  
    cpu->x = cpu->sp;

    M6502_Z(cpu, cpu->x == 0);
    M6502_S(cpu, cpu->x >> 7);

    return 2;
}

void transfert_init(mos6502_t *cpu) 
{
    cpu->op_codes[0x8A] = txa;
    cpu->op_codes[0xAA] = tax;
    cpu->op_codes[0x98] = tya;
    cpu->op_codes[0xA8] = tay;
    cpu->op_codes[0x9A] = txs;
    cpu->op_codes[0xBA] = tsx;
}