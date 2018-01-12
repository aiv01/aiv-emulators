#include <mos6502.h>

static int ora_immediate(mos6502_t *cpu) {
    unsigned char value = cpu->read8(cpu, cpu->pc++);
    cpu->a |= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 2;
}

static int ora_zero_page(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);
    cpu->a |= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 3;
}

static int ora_zero_page_x(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);
    cpu->a |= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 4;
}

static int ora_absolute(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);
    cpu->a |= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 4;
}

static int ora_absolute_x(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->x;
    unsigned char value = cpu->read8(cpu, page);
    cpu->a |= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);


    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

static int ora_absolute_y(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->y;
    unsigned char value = cpu->read8(cpu, page);
    cpu->a |= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);


    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

static int ora_indirect_x(mos6502_t *cpu) {
    unsigned short zp_address = cpu->read16(cpu, cpu->pc++);

    unsigned short page = zp_address + cpu->x;
    unsigned short address = cpu->read16(cpu, page);

    unsigned char value = cpu->read8(cpu, address);
    cpu->a |= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    return 6;
}

static int ora_indirect_y(mos6502_t *cpu) {
    unsigned short zp_address = cpu->read8(cpu, cpu->pc++);

    unsigned short address = cpu->read16(cpu, zp_address);

    unsigned short page = address + cpu->y;
    unsigned char value = cpu->read8(cpu, page);
    cpu->a |= value;

    M6502_Z(cpu, cpu->a == 0);
    M6502_S(cpu, cpu->a >> 7);

    if (page >> 8 == address >> 8)
        return 5;
    return 6;
}

void ora_init(mos6502_t *cpu) {
    cpu->op_codes[0x09] = ora_immediate;
    cpu->op_codes[0x05] = ora_zero_page;
    cpu->op_codes[0x15] = ora_zero_page_x;
    cpu->op_codes[0x0D] = ora_absolute;
    cpu->op_codes[0x1D] = ora_absolute_x;
    cpu->op_codes[0x19] = ora_absolute_y;
    cpu->op_codes[0x01] = ora_indirect_x;
    cpu->op_codes[0x11] = ora_indirect_y;
}
