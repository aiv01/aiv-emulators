#include <mos6502.h>

static int ldx_immediate(mos6502_t *cpu) {
  
    unsigned char value = cpu->read8(cpu,cpu->pc++);
    cpu->x = value;  

    M6502_Z(cpu, cpu->x == 0);
    M6502_S(cpu, cpu->x >> 7);

    return 2;
}

static int ldx_zero_page(mos6502_t *cpu) {

    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);
    cpu->x = value;

    M6502_Z(cpu, cpu->x == 0);
    M6502_S(cpu, cpu->x >> 7);

    return 3;
}

static int ldx_zero_page_y(mos6502_t *cpu) {

    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->y);
    cpu->x = value;

    M6502_Z(cpu, cpu->x == 0);
    M6502_S(cpu, cpu->x >> 7);

    return 4;
}

static int ldx_absolute(mos6502_t *cpu) {

   unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);
    cpu->x = value;

    M6502_Z(cpu, cpu->x == 0);
    M6502_S(cpu, cpu->x >> 7);

    return 4;
}

static int ldx_absolute_y(mos6502_t *cpu) {

    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned short page = address + cpu->y;
    unsigned char value = cpu->read8(cpu, page);
    cpu->x = value;

    M6502_Z(cpu, cpu->x == 0);
    M6502_S(cpu, cpu->x >> 7);

    if (page >> 8 == address >> 8)
        return 4;
    return 5;
}

void ldx_init(mos6502_t *cpu) {
    cpu->op_codes[0xA2] = ldx_immediate;
    cpu->op_codes[0xA6] = ldx_zero_page;
    cpu->op_codes[0xB6] = ldx_zero_page_y;
    cpu->op_codes[0xAE] = ldx_absolute;
    cpu->op_codes[0xBE] = ldx_absolute_y;
}
