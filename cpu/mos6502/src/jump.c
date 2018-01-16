#include <mos6502.h>

static int jump_absolute(mos6502_t *cpu) 
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    cpu->pc = address;
    return 3;
}
 
/*
static int jump_indirect(mos6502_t *cpu) 
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    cpu->pc += address;
    return 5;
}
*/

static int jump_indirect(mos6502_t *cpu) 
{
    unsigned short indirect_address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short address = cpu->read16(cpu, indirect_address);

    cpu->pc = address;
    return 5;
}

void jump_init(mos6502_t *cpu) 
{
    cpu->op_codes[0x4C] = jump_absolute;
    cpu->op_codes[0x6C] = jump_indirect;
}
