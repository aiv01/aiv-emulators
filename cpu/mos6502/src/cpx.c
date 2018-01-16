#include <mos6502.h>
#include <stdio.h>

static int cpx_immediate(mos6502_t* cpu)
{
    unsigned char value = cpu->read8(cpu, cpu->pc++); //read value

    M6502_Z(cpu, cpu->x == value);
    M6502_S(cpu, (cpu->x-value) >> 7);
    M6502_C(cpu, cpu->x >= value);

    return 2;
}

static int cpx_zero_page(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, cpu->x == value);
    M6502_S(cpu, (cpu->x-value) >> 7);
    M6502_C(cpu, cpu->x >= value);

    return 3;
}

static int cpx_absolute(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);

    M6502_Z(cpu, cpu->x == value);
    M6502_S(cpu, (cpu->x-value) >> 7);
    M6502_C(cpu, cpu->x >= value);

    return 4;
}

void cpx_init(mos6502_t *cpu) {
    cpu->op_codes[0xe0] = cpx_immediate;
    cpu->op_codes[0xe4] = cpx_zero_page;
    cpu->op_codes[0xec] = cpx_absolute;
}