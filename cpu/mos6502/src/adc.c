#include "../include/mos6502.h"

static int adc_immediate_ORI(mos6502_t *cpu) {
    unsigned char value = cpu->read8(cpu, cpu->pc++);
    char carryValue = cpu->flags &= 0x01;        //C flag è in posizione 0. quindi AND con 1 per trovare il valore
    
    short result = cpu->a + value + carryValue;  //uso short nel caso fosse > 255

    char newCarryValue;
    char overflowValue;                          //Note: overflow in this case is equal of Carry. When a Carry is set, basically there is Overflow also.
    if (result > 255) {
        result = result - 255;                   //Roll around 255 and Set Carry Flag
        newCarryValue = 1;    
        overflowValue = 1;
    } else {
       newCarryValue = 0;                        //Clear Carry Flag
       overflowValue = 0;    
    }

    cpu->a = (char)result;
    M6502_S(cpu, cpu->a >> 7);
    M6502_V(cpu, overflowValue);
    M6502_Z(cpu, cpu->a == 0);
    M6502_C(cpu, newCarryValue);
    return 2;
}

static int adc_immediate(mos6502_t *cpu) {
    unsigned char value = cpu->read8(cpu, cpu->pc++);

    char carryValue = cpu->flags &= 0x01;        //C flag è in posizione 0. quindi AND con 1 per trovare il valore
    unsigned short shortSum = value + cpu->a + carryValue;
    
    M6502_Z(cpu, !(shortSum & 0xFF));
    M6502_S(cpu, shortSum & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ shortSum) & 0x80));     // Overflow calculated as Two complement representation
    M6502_C(cpu, shortSum > 0xFF);
    cpu->a = shortSum & 0xFF;                     //To assign a value between [0, 255]
    return 2;
}

static int adc_zeropage(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);

    char carryValue = cpu->flags &= 0x01;        //C flag è in posizione 0. quindi AND con 1 per trovare il valore
    unsigned short shortSum = value + cpu->a + carryValue;
    
    M6502_Z(cpu, !(shortSum & 0xFF));
    M6502_S(cpu, shortSum & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ shortSum) & 0x80));     // Overflow calculated as Two complement representation
    M6502_C(cpu, shortSum > 0xFF);
    cpu->a = shortSum & 0xFF;                     //To assign a value between [0, 255]
    return 3;
}

// Zero Page,X   ADC $44,X     $75  2   4
static int adc_zeropagex(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);

    char carryValue = cpu->flags &= 0x01;        //C flag è in posizione 0. quindi AND con 1 per trovare il valore
    unsigned short shortSum = value + cpu->a + carryValue;
    
    M6502_Z(cpu, !(shortSum & 0xFF));
    M6502_S(cpu, shortSum & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ shortSum) & 0x80));     // Overflow calculated as Two complement representation
    M6502_C(cpu, shortSum > 0xFF);
    cpu->a = shortSum & 0xFF;                     //To assign a value between [0, 255]
    return 4;
}

// Absolute      ADC $4400     $6D  3   4
static int adc_absolute(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);

    char carryValue = cpu->flags &= 0x01;        //C flag è in posizione 0. quindi AND con 1 per trovare il valore
    unsigned short shortSum = value + cpu->a + carryValue;
    
    M6502_Z(cpu, !(shortSum & 0xFF));
    M6502_S(cpu, shortSum & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ shortSum) & 0x80));     // Overflow calculated as Two complement representation
    M6502_C(cpu, shortSum > 0xFF);
    cpu->a = shortSum & 0xFF;                     //To assign a value between [0, 255]
    return 4;
}

// Absolute,X    ADC $4400,X   $7D  3   4+
static int adc_absolutex(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned short addressX = address + cpu->x;
    unsigned char value = cpu->read8(cpu, addressX);

    char carryValue = cpu->flags &= 0x01;        //C flag è in posizione 0. quindi AND con 1 per trovare il valore
    unsigned short shortSum = value + cpu->a + carryValue;
    
    M6502_Z(cpu, !(shortSum & 0xFF));
    M6502_S(cpu, shortSum & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ shortSum) & 0x80));     // Overflow calculated as Two complement representation
    M6502_C(cpu, shortSum > 0xFF);
    cpu->a = shortSum & 0xFF;                     //To assign a value between [0, 255]
    
    char pageAddr = address >> 8;                 // I primi 8 bit rappresentano la Page.
    char pageAddrX = addressX >> 8;               // Quindi shift a destra di 8 per compararle.
    if (pageAddr == pageAddrX) return 4;          // Se sono su pagine diverse allora l'accesso costa un tick in più
    else return 5; 
}

//Absolute,Y    ADC $4400,Y   $79  3   4+
static int adc_absolutey(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned short addressY = address + cpu->y;
    unsigned char value = cpu->read8(cpu, addressY);

    char carryValue = cpu->flags &= 0x01;        //C flag è in posizione 0. quindi AND con 1 per trovare il valore
    unsigned short shortSum = value + cpu->a + carryValue;
    
    M6502_Z(cpu, !(shortSum & 0xFF));
    M6502_S(cpu, shortSum & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ shortSum) & 0x80));     // Overflow calculated as Two complement representation
    M6502_C(cpu, shortSum > 0xFF);
    cpu->a = shortSum & 0xFF;                     //To assign a value between [0, 255]
    
    char pageAddr = address >> 8;                 // I primi 8 bit rappresentano la Page.
    char pageAddrX = addressY >> 8;               // Quindi shift a destra di 8 per compararle.
    if (pageAddr == pageAddrX) return 4;          // Se sono su pagine diverse allora l'accesso costa un tick in più
    else return 5; 
}

// Indirect,X    ADC ($44,X)   $61  2   6
static int adc_indirectx(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    unsigned short finalAddress = cpu->read16(cpu, address + cpu->x);
    unsigned char value = cpu->read8(cpu, finalAddress);

    char carryValue = cpu->flags &= 0x01;        //C flag è in posizione 0. quindi AND con 1 per trovare il valore
    unsigned short shortSum = value + cpu->a + carryValue;
    
    M6502_Z(cpu, !(shortSum & 0xFF));
    M6502_S(cpu, shortSum & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ shortSum) & 0x80));     // Overflow calculated as Two complement representation
    M6502_C(cpu, shortSum > 0xFF);
    cpu->a = shortSum & 0xFF;                     //To assign a value between [0, 255]
    
    return 6;
}

//Indirect,Y    ADC ($44),Y   $71  2   5+
static int adc_indirecty(mos6502_t *cpu) {
    unsigned short addressZP = cpu->read8(cpu, cpu->pc++);             //ZeroPage Address is just 8 bit    
    unsigned short address = cpu->read16(cpu, addressZP);
    unsigned short addressY = address + cpu->y;
    unsigned char value = cpu->read8(cpu, addressY);

    char carryValue = cpu->flags &= 0x01;        //C flag è in posizione 0. quindi AND con 1 per trovare il valore
    unsigned short shortSum = value + cpu->a + carryValue;
    
    M6502_Z(cpu, !(shortSum & 0xFF));
    M6502_S(cpu, shortSum & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ shortSum) & 0x80));     // Overflow calculated as Two complement representation
    M6502_C(cpu, shortSum > 0xFF);
    cpu->a = shortSum & 0xFF;                     //To assign a value between [0, 255]
    
    char pageAddr = address >> 8;                 // I primi 8 bit rappresentano la Page.
    char pageAddrY = addressY >> 8;               // Quindi shift a destra di 8 per compararle.
    if (pageAddr == pageAddrY) return 5;          // Se sono su pagine diverse allora l'accesso costa un tick in più
    else return 6; 
}


void adc_init(mos6502_t *cpu) {
    cpu->op_codes[0x69] = adc_immediate;
    cpu->op_codes[0x65] = adc_zeropage;
    cpu->op_codes[0x75] = adc_zeropagex;
    cpu->op_codes[0x6D] = adc_absolute;
    cpu->op_codes[0x7D] = adc_absolutex;
    cpu->op_codes[0x79] = adc_absolutey;
    cpu->op_codes[0x61] = adc_indirectx;
    cpu->op_codes[0x71] = adc_indirecty;
}