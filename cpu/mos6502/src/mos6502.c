#include <mos6502.h>
#include <stdlib.h>
#include <string.h>

int mos6502_tick(mos6502_t *cpu) 
{
    unsigned char op_code = cpu->read8(cpu, cpu->pc++);
    
    if (cpu->op_codes[op_code] != NULL)
    {
        return cpu->op_codes[op_code](cpu);
    }
    return -1;
}

void mos6502_init(mos6502_t *cpu)
{
    memset(cpu, 0, sizeof(mos6502_t));
    cpu->sp = 0xFF;
    and_init(cpu);
    jump_init(cpu);
    cmp_init(cpu);
    cpx_init(cpu);
    cpy_init(cpu);
    nop_init(cpu);
    adc_init(cpu);
    ora_init(cpu);
    eor_init(cpu);
    sbc_init(cpu);
    inc_init(cpu);
    dec_init(cpu);
    lsr_init(cpu);
    asl_init(cpu);
    ldx_init(cpu);
    transfert_init(cpu);
    inx_init(cpu);
    iny_init(cpu);
    dex_init(cpu);
    dey_init(cpu);
    branch_init(cpu);
    sta_init(cpu);
    stx_init(cpu);
    sty_init(cpu);
    jsr_init(cpu);
    rts_init(cpu);
    ldy_init(cpu);
    stack_init(cpu);
    lda_init(cpu);
    rti_init(cpu);
    flags_init(cpu);
}

unsigned char mos6502_ram_read8(mos6502_t *cpu, unsigned short address)
{
    unsigned char *ptr = cpu->data;
    return ptr[address];
}

unsigned short mos6502_ram_read16(mos6502_t *cpu, unsigned short address)
{
    unsigned short low_byte = cpu->read8(cpu, address);
    unsigned short high_byte = cpu->read8(cpu, address + 1);
    // invert (little endian)
    return (high_byte << 8 | low_byte);
}

void mos6502_ram_write8(mos6502_t *cpu, unsigned short address, unsigned char value)
{
    unsigned char *ptr = cpu->data;
    ptr[address] = value;
}

void mos6502_ram_write16(mos6502_t *cpu, unsigned short address, unsigned short value)
{
    unsigned char low_byte = value & 0x00ff;
    unsigned char high_byte = value >> 8;
    cpu->write8(cpu, address, low_byte);
    cpu->write8(cpu, address + 1, high_byte);
}

void mos6502_add_test_full_mapping(mos6502_t *cpu, void *buffer)
{
    cpu->data = buffer;
    cpu->read8 = mos6502_ram_read8;
    cpu->write8 = mos6502_ram_write8;
    cpu->read16 = mos6502_ram_read16;
    cpu->write16 = mos6502_ram_write16;
}
