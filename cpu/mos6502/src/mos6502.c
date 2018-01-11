#include <mos6502.h>
#include <stdlib.h>
#include <string.h>

int mos6502_tick(mos6502_t *cpu) {
    unsigned char op_code = cpu->read8(cpu, cpu->pc++);
    
    if (cpu->op_codes[op_code] != NULL){
        return cpu->op_codes[op_code](cpu);
    }
    return -1;
}

void mos6502_init(mos6502_t *cpu){
    memset(cpu, 0, sizeof(mos6502_t));
    and_init(cpu);
}