#include <mos6502.h>

int asl_accumulator(mos6502_t *cpu){
    char a = cpu->a;
    //Gets the 7th bit and puts it in the carry.
    M6502_C(cpu, (a >> 7) & 1);
    
    M6502_Z(cpu, cpu->a == 0);
    
    cpu->a = a << 1;

    return 2;
}

int asl_zero_page(mos6502_t *cpu){
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);
    
    char v = value;
    //Gets the 7th bit and puts it in the carry.
    M6502_C(cpu, (v >> 7) & 1);
    
    M6502_Z(cpu, cpu->a == 0);
    
    cpu->write8(cpu, address, value << 1);

    return 5;
}

int asl_zero_page_x(mos6502_t *cpu){
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);
    
    char v = value;
    //Gets the 7th bit and puts it in the carry.
    M6502_C(cpu, (v >> 7) & 1);
    
    M6502_Z(cpu, cpu->a == 0);
    
    cpu->write8(cpu, address + cpu->x, value << 1);

    return 6;
}

int asl_absolute(mos6502_t *cpu){
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);
    
    char v = value;
    //Gets the 7th bit and puts it in the carry.
    M6502_C(cpu, (v >> 7) & 1);
    
    M6502_Z(cpu, cpu->a == 0);
    
    cpu->write8(cpu, address, value << 1);

    return 6;
}

int asl_absolute_x(mos6502_t *cpu){
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;

    unsigned short page = address + cpu->x;
    unsigned char value = cpu->read8(cpu, page);
    
    char v = value;
    //Gets the 7th bit and puts it in the carry.
    M6502_C(cpu, (v >> 7) & 1);
    
    M6502_Z(cpu, cpu->a == 0);
    
    cpu->write8(cpu, page, value << 1);

    return 7;
}

void asl_init(mos6502_t *cpu){
    cpu->op_codes[0x0A] = asl_accumulator;
    cpu->op_codes[0x06] = asl_zero_page;
    cpu->op_codes[0x16] = asl_zero_page_x;
    cpu->op_codes[0x0E] = asl_absolute;
    cpu->op_codes[0x1E] = asl_absolute_x;
}