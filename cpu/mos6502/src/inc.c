#include <mos6502.h>

static int inc_zero_page(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);
    value++;
    cpu->write8(cpu, address, value);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    return 5;
}

static int inc_zero_page_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);
    value++;
    cpu->write8(cpu, address, value);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    return 6;
}

static int inc_absolute(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);
    value++;
    cpu->write8(cpu, address, value);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    return 6;
}

static int inc_absolute_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->x;
    unsigned char value = cpu->read8(cpu, page);
    value++;
    cpu->write8(cpu, address, value);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    return 7;
}

void inc_init(mos6502_t *cpu)
{
    cpu->op_codes[0xE6] = inc_zero_page;
    cpu->op_codes[0xF6] = inc_zero_page_x;
    cpu->op_codes[0xEE] = inc_absolute;
    cpu->op_codes[0xFE] = inc_absolute_x;
}