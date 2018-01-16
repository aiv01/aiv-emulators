#include <mos6502.h>

static int sta_zero_page(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    cpu->write8(cpu,address,cpu->a);

    return 3;
}

static int sta_zero_page_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    cpu->write8(cpu,address + cpu->x,cpu->a);
    
    return 4;
}

static int sta_absolute(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    cpu->write8(cpu,address,cpu->a);

    return 4;
}

static int sta_absolute_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    cpu->write8(cpu,address + cpu->x,cpu->a);

    return 5;
}

static int sta_absolute_y(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    cpu->write8(cpu,address + cpu->y,cpu->a);

    return 5;
}

static int sta_indirect_x(mos6502_t *cpu)
{
    unsigned short zp_address = cpu->read16(cpu, cpu->pc++);
    unsigned short page = zp_address + cpu->x;
    unsigned short address = cpu->read16(cpu, page);
    cpu->write8(cpu,address,cpu->a);

    return 6;
}

static int sta_indirect_y(mos6502_t *cpu)
{
    unsigned short zp_address = cpu->read8(cpu, cpu->pc++);
    unsigned short page = zp_address + cpu->y;
    unsigned short address = cpu->read16(cpu, page);
    cpu->write8(cpu,address,cpu->a);
    
    return 6;
}

void sta_init(mos6502_t *cpu) {
    cpu->op_codes[0x85] = sta_zero_page;
    cpu->op_codes[0x95] = sta_zero_page_x;
    cpu->op_codes[0x8D] = sta_absolute;
    cpu->op_codes[0x9D] = sta_absolute_x;
    cpu->op_codes[0x99] = sta_absolute_y;
    cpu->op_codes[0x81] = sta_indirect_x;
    cpu->op_codes[0x91] = sta_indirect_y;
}