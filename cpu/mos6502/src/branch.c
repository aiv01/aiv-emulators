#include <mos6502.h>

static int branch_on_plus(mos6502_t* cpu) // BPL
{
    int delta = cpu->pc;
    char src = cpu->read8(cpu, cpu->pc++);
    delta += src;
    if(!NEGATIVE_READ(cpu))
    {
        cpu->pc = (unsigned short)delta;
        return 2;
    }
    return 3;
}

static int branch_on_minus(mos6502_t* cpu) //BMI
{
    int delta = cpu->pc;
    char src = cpu->read8(cpu, cpu->pc++);
    delta += src;
    if(NEGATIVE_READ(cpu))
    {
        cpu->pc = (unsigned short)delta;
        return 2;
    }
    return 3;
}

static int branch_on_not_equal(mos6502_t* cpu) //BNE
{
    int delta = cpu->pc;
    char src = cpu->read8(cpu, cpu->pc++);
    delta += src;
    if(!ZERO_READ(cpu))
    {
        cpu->pc = (unsigned short)delta;
        return 2;
    }
    return 3;
}

static int branch_on_equal(mos6502_t* cpu) //BEQ
{
    int delta = cpu->pc;
    char src = cpu->read8(cpu, cpu->pc++);
    delta += src;
    if(ZERO_READ(cpu))
    {
        cpu->pc = (unsigned short)delta;
        return 2;
    }
    return 3;
}

static int branch_on_overflow_clear(mos6502_t* cpu) //BVC
{
    int delta = cpu->pc;
    char src = cpu->read8(cpu, cpu->pc++);
    delta += src;
    if(!OVERFL_READ(cpu))
    {
        cpu->pc = (unsigned short)delta;
        return 2;
    }
    return 3;
}

static int branch_on_overflow_set(mos6502_t* cpu) //BVS
{
    int delta = cpu->pc;
    char src = cpu->read8(cpu, cpu->pc++);
    delta += src;
    if(OVERFL_READ(cpu))
    {
        cpu->pc = (unsigned short)delta;
        return 2;
    }
    return 3;
}

static int branch_on_carry_clear(mos6502_t* cpu) //BCC
{
    int delta = cpu->pc;
    char src = cpu->read8(cpu, cpu->pc++);
    delta += src;
    if(!CARRY_READ(cpu))
    {
        cpu->pc = (unsigned short)delta;
        return 2;
    }
    return 3;
}

static int branch_on_carry_set(mos6502_t* cpu) //BCS
{
    int delta = cpu->pc;
    char src = cpu->read8(cpu, cpu->pc++);
    delta += src;
    if(CARRY_READ(cpu))
    {
        cpu->pc = (unsigned short)delta;
        return 2;
    }
    return 3;
}

void branch_init(mos6502_t* cpu)
{
    cpu->op_codes[0x10] = branch_on_plus;
    cpu->op_codes[0x30] = branch_on_minus;
    cpu->op_codes[0x50] = branch_on_overflow_clear;
    cpu->op_codes[0x70] = branch_on_overflow_set;
    cpu->op_codes[0x90] = branch_on_carry_clear;
    cpu->op_codes[0xB0] = branch_on_carry_set;
    cpu->op_codes[0xD0] = branch_on_not_equal;
    cpu->op_codes[0xF0] = branch_on_equal;
}