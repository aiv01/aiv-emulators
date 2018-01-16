#include <mos6502.h>

// MODE:  Absolute
// HEX:   $20
// LEN:   3
// TIM:   6
// FLAGS: None

static int jsr(mos6502_t *cpu)
{
    // read sub-routine address
    unsigned short sr_address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    // push 2 bytes on the stack for the return address
    cpu->write16(cpu, --cpu->sp, cpu->pc);
    cpu->sp--;
    
    // jump to sub-routine address
    cpu->pc = sr_address;
    return 6;
}

void jsr_init(mos6502_t *cpu) 
{
    cpu->op_codes[0x20] = jsr;
}