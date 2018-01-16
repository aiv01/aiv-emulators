#include <mos6502.h>
#include <stdio.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

static int lsr_accumulator(mos6502_t* cpu)
{
    int v = CHECK_BIT(cpu->a,0);
    cpu->a = cpu->a >> 1;
    
    M6502_C(cpu,v); //carry
    M6502_S(cpu,v);//sign
    if(v == 1)
        cpu->a |= 0x80; //first bit on the left 1

    M6502_Z(cpu,cpu->a == 0);//is zero
        
    return 2;
}
static int lsr_zero_page(mos6502_t* cpu)
{
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);

    int v = CHECK_BIT(value,0);
    value = value >> 1;
    M6502_C(cpu,v); //carry
    M6502_S(cpu,v);//sign
    if(v == 1)
        value |= 0x80; //first bit on the left 1

    cpu->write8(cpu,address,value);
    M6502_Z(cpu,value == 0);
    return 5;
}
static int lsr_zero_page_x(mos6502_t* cpu)
{
     unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);

    int v = CHECK_BIT(value,0);
    value = value >> 1;
    M6502_C(cpu,v); //carry
    M6502_S(cpu,v);//sign
    M6502_C(cpu,v); //set carry bit
    if(v == 1)
        value |= 0x80; //first bit on the left 1

    M6502_Z(cpu,value == 0);
    cpu->write8(cpu,address + cpu->x,value);

    return 6;
}
static int lsr_absolute(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);

    int v = CHECK_BIT(value,0);
    value = value >> 1;
    M6502_C(cpu,v);//carry
    M6502_S(cpu,v);//sign
    
    if(v == 1)
        value |= 0x80; //first bit on the left 1

    M6502_Z(cpu,value == 0); //zero
    cpu->write8(cpu,address,value);
    
    return 6;
}
static int lsr_absolute_x(mos6502_t *cpu)
{
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address + cpu->x);

    int v = CHECK_BIT(value,0);
    value = value >> 1;
    M6502_C(cpu,v);
    M6502_S(cpu,v);//sign
    
    if(v == 1)
        value |= 0x80; //first bit on the left 1

    M6502_Z(cpu,value == 0); //zero
    cpu->write8(cpu,address + cpu->x,value);
    
    return 6;
}
void lsr_init(mos6502_t *cpu) {
    cpu->op_codes[0x4a] = lsr_accumulator;
    cpu->op_codes[0x46] = lsr_zero_page;
    cpu->op_codes[0x56] = lsr_zero_page_x;
    cpu->op_codes[0x4e] = lsr_absolute;
    cpu->op_codes[0x5e] = lsr_absolute_x;
    // cpu->op_codes[0xd9] = cmp_absolute_y;
    // cpu->op_codes[0xc1] = cmp_indirect_x;
    // cpu->op_codes[0xd1] = cmp_indirect_y;
}