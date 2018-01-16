#include <mos6502.h>

static int stx_zero_page(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    cpu->write8(cpu,address,cpu->x);

    return 3;
}

static int stx_zero_page_y(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    cpu->write8(cpu,address + cpu->y,cpu->x);
    
    return 4;
}

static int stx_absolute(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    cpu->write8(cpu,address,cpu->x);

    return 4;
}

void stx_init(mos6502_t *cpu) 
{
    cpu->op_codes[0x86] = stx_zero_page;
    cpu->op_codes[0x96] = stx_zero_page_y;
    cpu->op_codes[0x8E] = stx_absolute;
}