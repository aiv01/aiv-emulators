#include <mos6502.h>
#include <stdio.h>

static int cpy_immediate(mos6502_t* cpu)
{
    unsigned char value = cpu->read8(cpu, cpu->pc++); //read value

    M6502_Z(cpu, cpu->y == value);
    M6502_S(cpu, (cpu->y-value) >> 7);
    M6502_C(cpu, cpu->y >= value);

    return 2;
}
static int cpy_zero_page(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, cpu->y == value);
    M6502_S(cpu, (cpu->y-value) >> 7);
    M6502_C(cpu, cpu->y >= value);

    return 3;
}
static int cpy_absolute(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, cpu->y == value);
    M6502_S(cpu, (cpu->y-value) >> 7);
    M6502_C(cpu, cpu->y >= value);

    return 4;
}
void cpy_init(mos6502_t *cpu) {
    cpu->op_codes[0xc0] = cpy_immediate;
    cpu->op_codes[0xc4] = cpy_zero_page;
    cpu->op_codes[0xcc] = cpy_absolute;
}