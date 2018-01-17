#include <mos6502.h>

static int clear_carry(mos6502_t* cpu)
{
    SET_BIT_CARRY(cpu, 0);
    return 2;
}

static int set_carry(mos6502_t* cpu)
{
    SET_BIT_CARRY(cpu, 1);
    return 2;
}

static int clear_interrupt(mos6502_t* cpu)
{
    SET_BIT_INTERRUPT(cpu, 0);
    return 2;
}

static int set_interrupt(mos6502_t* cpu)
{
    SET_BIT_INTERRUPT(cpu, 1);
    return 2;
}

static int clear_overflow(mos6502_t* cpu)
{
    SET_BIT_OVERFLOW(cpu, 0);
    return 2;
}

static int clear_decimal(mos6502_t* cpu)
{
    SET_BIT_DECIMAL(cpu, 0);
    return 2;
}

static int set_decimal(mos6502_t* cpu)
{
    SET_BIT_DECIMAL(cpu, 1);
    return 2;
}

void flags_init(mos6502_t* cpu)
{
    cpu->op_codes[0x18] = clear_carry;
    cpu->op_codes[0x38] = set_carry;
    cpu->op_codes[0x58] = clear_interrupt;
    cpu->op_codes[0x78] = set_interrupt;
    cpu->op_codes[0xB8] = clear_overflow;
    cpu->op_codes[0xD8] = clear_decimal;
    cpu->op_codes[0xF8] = set_decimal;
}