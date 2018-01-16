#include <mos6502.h>

static int sty_zero_page(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    cpu->write8(cpu,address,cpu->y);

    return 3;
}

static int sty_zero_page_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    cpu->write8(cpu,address + cpu->x,cpu->y);
    
    return 4;
}

static int sty_absolute(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    cpu->write8(cpu,address,cpu->y);
    
    return 4;
}

void sty_init(mos6502_t *cpu) 
{
    cpu->op_codes[0x84] = sty_zero_page;
    cpu->op_codes[0x94] = sty_zero_page_x;
    cpu->op_codes[0x8C] = sty_absolute;
}