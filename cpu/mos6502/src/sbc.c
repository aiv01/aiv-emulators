#include "../include/mos6502.h"

// *********************************
// ******* COMMON FUNCTIONS ********
// *********************************

// Calculation of the SBC and related FLAGS impacted.
// Reused from all the SBC variants
static void compute_sbc_and_flags(mos6502_t *cpu, unsigned char value) {
    /*  HEX Reference:
        $00 to $7F represents 0 to 127 
        $80 to $FF represents -128 to -1
    */
    unsigned char carry_value = cpu->flags &= 0x01;                                 // C flag is at position 0. AND by 1 to find the value
    unsigned short sub_as_short = cpu->a - value - carry_value;
    M6502_Z(cpu, !(sub_as_short & 0xFF));
    M6502_S(cpu, sub_as_short & 0x80);
	M6502_V(cpu, !((cpu->a ^ value) & 0x80) && ((cpu->a ^ sub_as_short) & 0x80));   // Overflow calculated as Two complement representation
    M6502_C(cpu, sub_as_short > 0xFF);                                                
    cpu->a = sub_as_short & 0xFF;                                                   // To assign a value between [0, 255]
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
// Immediate     SBC #$44      $E9  2   2
static int sbc_immediate(mos6502_t *cpu) {
    unsigned char value = cpu->read8(cpu, cpu->pc++);
    compute_sbc_and_flags(cpu, value);
    return 2;
}

// Zero Page     SBC $44       $E5  2   3
static int sbc_zero_page(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address);
    compute_sbc_and_flags(cpu, value);
    return 3;
}

// Zero Page,X   SBC $44,X     $F5  2   4
static int sbc_zero_page_x(mos6502_t *cpu) {
    unsigned short address = cpu->read8(cpu, cpu->pc++);
    unsigned char value = cpu->read8(cpu, address + cpu->x);
    compute_sbc_and_flags(cpu, value);
    return 4;
}

// Absolute      SBC $4400     $ED  3   4
static int sbc_absolute(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned char value = cpu->read8(cpu, address);
    compute_sbc_and_flags(cpu, value);
    return 4;
}

// Absolute,X    SBC $4400,X   $FD  3   4+
static int sbc_absolute_x(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned short address_x = address + cpu->x;
    unsigned char value = cpu->read8(cpu, address_x);
    compute_sbc_and_flags(cpu, value);
    return is_in_same_page_addr(address, address_x) ? 4 : 5;
}

// Absolute,Y    SBC $4400,Y   $F9  3   4+
static int sbc_absolute_y(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    cpu->pc++;
    unsigned short address_y = address + cpu->y;
    unsigned char value = cpu->read8(cpu, address_y);
    compute_sbc_and_flags(cpu, value);
    return is_in_same_page_addr(address, address_y) ? 4 : 5;
}

// Indirect,X    SBC ($44,X)   $E1  2   6
static int sbc_indirect_x(mos6502_t *cpu) {
    unsigned short address = cpu->read16(cpu, cpu->pc++);
    unsigned short address_x = cpu->read16(cpu, address + cpu->x);
    unsigned char value = cpu->read8(cpu, address_x);
    compute_sbc_and_flags(cpu, value);
    return 6;
}

// Indirect,Y    SBC ($44),Y   $F1  2   5+
static int sbc_indirect_y(mos6502_t *cpu) {
    unsigned short address_zp_pointer = cpu->read8(cpu, cpu->pc++);
    unsigned short address = cpu->read16(cpu, address_zp_pointer);
    unsigned short address_y = address + cpu->y;
    unsigned char value = cpu->read8(cpu, address_y);
    compute_sbc_and_flags(cpu, value);
    return is_in_same_page_addr(address, address_y) ? 5 : 6;
}

void sbc_init(mos6502_t *cpu) {
    cpu->op_codes[0xE9] = sbc_immediate;
    cpu->op_codes[0xE5] = sbc_zero_page;
    cpu->op_codes[0xF5] = sbc_zero_page_x;
    cpu->op_codes[0xED] = sbc_absolute;
    cpu->op_codes[0xFD] = sbc_absolute_x;
    cpu->op_codes[0xF9] = sbc_absolute_y;
    cpu->op_codes[0xE1] = sbc_indirect_x;
    cpu->op_codes[0xF1] = sbc_indirect_y;
}
