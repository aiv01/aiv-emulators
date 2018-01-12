#include <mos6502.h>

static int nop(mos6502_t *cpu) {
    return 2;
}

void nop_init(mos6502_t *cpu) {
    cpu->op_codes[0xea] = nop;
}