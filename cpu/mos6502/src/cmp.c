#include <mos6502.h>
#include <stdio.h>

static int cmp_immediate(mos6502_t* cpu)
{
    unsigned char value = cpu->read8(cpu, cpu->pc++); //read value

    M6502_Z(cpu, cpu->a == value);
    M6502_S(cpu, (cpu->a-value) >> 7);
    M6502_C(cpu, cpu->a >= value);

    return 2;
}

static int cmp_zero_page(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, cpu->a == value);
    M6502_S(cpu, (cpu->a-value) >> 7);
    M6502_C(cpu, cpu->a >= value);

    return 3;
}

static int cmp_zero_page_x(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);

    M6502_Z(cpu, cpu->a == value);
    M6502_S(cpu, (cpu->a-value) >> 7);
    M6502_C(cpu, cpu->a >= value);

    return 4;
}

static int cmp_absolute(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, cpu->a == value);
    M6502_S(cpu, (cpu->a-value) >> 7);
    M6502_C(cpu, cpu->a >= value);

    return 4;
}

static int cmp_absolute_x(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->x;
    unsigned char value = cpu->read8(cpu, page);

    M6502_Z(cpu, cpu->a == value);
    M6502_S(cpu, (cpu->a-value) >> 7);
    M6502_C(cpu, cpu->a >= value);

    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

static int cmp_absolute_y(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->y;
    unsigned char value = cpu->read8(cpu, page);

    M6502_Z(cpu, cpu->a == value);
    M6502_S(cpu, (cpu->a-value) >> 7);
    M6502_C(cpu, cpu->a >= value);

    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

static int cmp_indirect_x(mos6502_t *cpu) {
    unsigned short zp_address = cpu->read16(cpu, cpu->pc++);
    
    unsigned short page = zp_address + cpu->x;
    
    unsigned short address = cpu->read16(cpu, page);
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, cpu->a == value);
    M6502_S(cpu, (cpu->a-value) >> 7);
    M6502_C(cpu, cpu->a >= value);


    return 6;
}

static int cmp_indirect_y(mos6502_t *cpu) {
    unsigned short zp_address = cpu->read16(cpu, cpu->pc++);

    unsigned short address = cpu->read16(cpu, zp_address);

    unsigned short page = address + cpu->y;
    
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, cpu->a == value);
    M6502_S(cpu, (cpu->a-value) >> 7);
    M6502_C(cpu, cpu->a >= value);

    if (page >> 8 == address >> 8)
        return 5;
    return 6;
}

void cmp_init(mos6502_t *cpu) {
    cpu->op_codes[0xc9] = cmp_immediate;
    cpu->op_codes[0xc5] = cmp_zero_page;
    cpu->op_codes[0xd5] = cmp_zero_page_x;
    cpu->op_codes[0xcd] = cmp_absolute;
    cpu->op_codes[0xdd] = cmp_absolute_x;
    cpu->op_codes[0xd9] = cmp_absolute_y;
    cpu->op_codes[0xc1] = cmp_indirect_x;
    cpu->op_codes[0xd1] = cmp_indirect_y;
}
