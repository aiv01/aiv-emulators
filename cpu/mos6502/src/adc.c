#include "../include/mos6502.h"

// *********************************
// ******* COMMON FUNCTIONS ********
// *********************************

// Calculation of the ADC and related FLAGS impacted.
// Reused from all the ADC variants
static void compute_adc_and_flags(mos6502_t *cpu, unsigned char value) {
    /*  HEX Reference:
        $00 to $7F represents 0 to 127 
        $80 to $FF represents -128 to -1
    */
    unsigned char carry_value = cpu->flags &= 0x01;                                 //C flag is at position 0. AND by 1 to find the value
    unsigned short sum_as_short = value + cpu->a + carry_value;
    M6502_Z(cpu, !(sum_as_short & 0xFF));
    M6502_S(cpu, sum_as_short & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ sum_as_short) & 0x80));   // Overflow calculated as Two complement representation
    M6502_C(cpu, sum_as_short > 0xFF);                                                
    cpu->a = sum_as_short & 0xFF;                                                   //To assign a value between [0, 255]
}

static unsigned char is_in_same_page_addr(unsigned short addr_1, unsigned short addr_2) {
    char page_addr_1 = addr_1 >> 8;                    // First 8 bit represent the Page.
    char page_addr_2 = addr_2 >> 8;                    // Then Right Shifting by 8 to compare pages.
    if (page_addr_1 == page_addr_2) return 1;          // If pages are equal return 1 (TRUE)
    else return 0;                                     // else return 0 (FALSE)
}

// *********************************
// *** VARIANTS IMPLEMENTATION *****
// *********************************
//Immediate     ADC #$44      OPCODE: $69  LEN: 2   TIM: 2
static int adc_immediate(mos6502_t *cpu) {
    unsigned char value = cpu->read8(cpu, cpu->pc++);
    compute_adc_and_flags(cpu, value);
    return 2;
}

//Zero Page     ADC $44       OPCODE: $65  LEN: 2   TIM: 3
static int adc_zero_page(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);
    compute_adc_and_flags(cpu, value);
    return 3;
}

//Zero Page,X   ADC $44,X     OPCODE: $75  LEN: 2   TIM:4
static int adc_zero_page_x(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);
    compute_adc_and_flags(cpu, value);
    return 4;
}

//Absolute      ADC $4400     OPCODE: $6D  LEN: 3   TIM: 4
static int adc_absolute(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);
    compute_adc_and_flags(cpu, value);
    return 4;
}

//Absolute,X    ADC $4400,X   OPCODE: $7D  LEN: 3   TIM: 4+
static int adc_absolute_x(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned short address_x = address + cpu->x;
    unsigned char value = cpu->read8(cpu, address_x);
    compute_adc_and_flags(cpu, value);
    return is_in_same_page_addr(address, address_x) ? 4 : 5;
}

//Absolute,Y    ADC $4400,Y   OPCODE: $79  LEN: 3   TIM: 4+
static int adc_absolute_y(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned short address_y = address + cpu->y;
    unsigned char value = cpu->read8(cpu, address_y);
    compute_adc_and_flags(cpu, value);
    return is_in_same_page_addr(address, address_y) ? 4 : 5;
}

//Indirect,X    ADC ($44,X)   OPCODE: $61  LEN: 2   TIM: 6
static int adc_indirect_x(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    unsigned short address_x = cpu->read16(cpu, address + cpu->x);
    unsigned char value = cpu->read8(cpu, address_x);
    compute_adc_and_flags(cpu, value);
    return 6;
}

//Indirect,Y    ADC ($44),Y   OPCODE: $71  LEN: 2   TIM: 5+
static int adc_indirect_y(mos6502_t *cpu) {
    unsigned short address_zp_pointer = cpu->read8(cpu, cpu->pc++);
    unsigned short address = cpu->read16(cpu, address_zp_pointer);
    unsigned short address_y = address + cpu->y;
    unsigned char value = cpu->read8(cpu, address_y);
    compute_adc_and_flags(cpu, value);
    return is_in_same_page_addr(address, address_y) ? 5 : 6;
}

// Setup ADC Variants in the CPU
void adc_init(mos6502_t *cpu) {
    cpu->op_codes[0x69] = adc_immediate;
    cpu->op_codes[0x65] = adc_zero_page;
    cpu->op_codes[0x75] = adc_zero_page_x;
    cpu->op_codes[0x6D] = adc_absolute;
    cpu->op_codes[0x7D] = adc_absolute_x;
    cpu->op_codes[0x79] = adc_absolute_y;
    cpu->op_codes[0x61] = adc_indirect_x;
    cpu->op_codes[0x71] = adc_indirect_y;
}