#include <mos6502.h>

static int and_immediate(mos6502_t *cpu) {
    unsigned char value = cpu->read8(cpu, cpu->pc++);
    cpu->a &= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 2;
}

static int and_zero_page(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);
    cpu->a &= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 3;
}

static int and_zero_page_x(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);
    cpu->a &= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 4;
}

static int and_absolute(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);
    cpu->a &= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 4;
}

static int and_absolute_x(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->x;
    unsigned char value = cpu->read8(cpu, page);
    cpu->a &= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

static int and_absolute_y(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->y;
    unsigned char value = cpu->read8(cpu, page);
    cpu->a &= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

static int and_indirect_x(mos6502_t *cpu) {
    unsigned short zp_address = cpu->read8(cpu, cpu->pc++);

    unsigned short page = zp_address + cpu->x;
    unsigned short address = cpu->read16(cpu, page);

    unsigned char value = cpu->read8(cpu, address);
    cpu->a &= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 6;
}

static int and_indirect_y(mos6502_t *cpu) {
    unsigned short zp_address = cpu->read8(cpu, cpu->pc++);

    unsigned short address = cpu->read16(cpu, zp_address);

    unsigned short page = address + cpu->y;
    unsigned char value = cpu->read8(cpu, page);
    cpu->a &= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    if (page >> 8 == address >> 8)
        return 5;
    return 6;
}

void and_init(mos6502_t *cpu) {
    cpu->op_codes[0x29] = and_immediate;
    cpu->op_codes[0x25] = and_zero_page;
    cpu->op_codes[0x35] = and_zero_page_x;
    cpu->op_codes[0x2D] = and_absolute;
    cpu->op_codes[0x3D] = and_absolute_x;
    cpu->op_codes[0x39] = and_absolute_y;
    cpu->op_codes[0x21] = and_indirect_x;
    cpu->op_codes[0x31] = and_indirect_y;
}