#include <mos6502.h>


static int lda_immediate(mos6502_t *cpu)
{
    unsigned char value = cpu->read8(cpu, cpu->pc++);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->a = value;

    return 2;
}

static int lda_zero_page(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->a = value;

    return 3;
}

static int lda_zero_page_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->a = value;

    return 4;
}

static int lda_absolute(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->a = value;

    return 4;
}

static int lda_absolute_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->x;
    unsigned char value = cpu->read8(cpu, page);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->a = value;

    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

static int lda_absolute_y(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->y;
    unsigned char value = cpu->read8(cpu, page);

    M6502_Z(cpu, value == 0);
    M6502_S(cpu, value >> 7);

    cpu->a = value;

    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

static int lda_indirect_x(mos6502_t *cpu)
{
     unsigned short zp_address = cpu->read16(cpu, cpu->pc++);
     cpu->pc++;

    unsigned short page = zp_address + cpu->x;
    unsigned short address = cpu->read16(cpu, page);

    unsigned char value = cpu->read8(cpu, address);
    cpu->a = value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 6;
}

static int lda_indirect_y(mos6502_t *cpu)
{
     unsigned short zp_address = cpu->read16(cpu, cpu->pc++);
     cpu->pc++;

    unsigned short page = zp_address + cpu->y;
    unsigned short address = cpu->read16(cpu, page);

    unsigned char value = cpu->read8(cpu, address);
    cpu->a = value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 6;
}

void lda_init(mos6502_t *cpu)
{
    cpu->op_codes[0xA9] = lda_immediate;
    cpu->op_codes[0xA5] = lda_zero_page;
    cpu->op_codes[0xB5] = lda_zero_page_x;
    cpu->op_codes[0xAD] = lda_absolute;
    cpu->op_codes[0xBD] = lda_absolute_x;
    cpu->op_codes[0xB9] = lda_absolute_y; 
    cpu->op_codes[0xA1] = lda_indirect_x;
    cpu->op_codes[0xB1] = lda_indirect_y;   
}
