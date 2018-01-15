#include <mos6502.h>
static int ldy_immediate(mos6502_t *cpu)
{
    unsigned char value = cpu->read8(cpu, cpu->pc++);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->y = value;

    return 2;
}

static int ldy_zero_page(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->y = value;

    return 3;
}

static int ldy_zero_page_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->y = value;

    return 4;
}

static int ldy_absolute(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->y = value;

    return 4;
}

static int ldy_absolute_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->x;
    unsigned char value = cpu->read8(cpu, page);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->y = value;

    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

void ldy_init(mos6502_t *cpu)
{
    cpu->op_codes[0xA0] = ldy_immediate;
    cpu->op_codes[0xA4] = ldy_zero_page;
    cpu->op_codes[0xB4] = ldy_zero_page_x;
    cpu->op_codes[0xAC] = ldy_absolute;
    cpu->op_codes[0xBC] = ldy_absolute_x;
}