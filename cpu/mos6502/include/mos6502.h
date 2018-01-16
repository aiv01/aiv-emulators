typedef struct mos6502 {
    unsigned char a;
    unsigned char x;
    unsigned char y;
    unsigned char flags;
    unsigned char sp;
    unsigned short pc;

    unsigned char (*read8)(struct mos6502 *, unsigned short);
    unsigned short (*read16)(struct mos6502 *, unsigned short);
    void (*write8)(struct mos6502 *, unsigned short, unsigned char);
    void (*write16)(struct mos6502 *, unsigned short, unsigned short);

    int (*op_codes[256])(struct mos6502 *);

    void *data;
} mos6502_t;

//Defines the bit sign
#define M6502_S(cpu, b) \
if (b) \
{\
    cpu->flags |= 0x80;\
}\
else\
{\
    cpu->flags &= 0x7F;\
}

#define M6502_V(cpu, b) \
if (b) \
{\
    cpu->flags |= 0x40;\
}\
else\
{\
    cpu->flags &= 0xBF;\
}

#define M6502_Z(cpu, b) \
if (b) \
{\
    cpu->flags |= 0x02;\
}\
else\
{\
    cpu->flags &= 0xFD;\
}

#define M6502_C(cpu, b) \
if (b) \
{\
    cpu->flags |= 0x01;\
}\
else\
{\
    cpu->flags &= 0xFE;\
}

void mos6502_init(mos6502_t *);
int mos6502_tick(mos6502_t *);
void mos6502_add_test_full_mapping(mos6502_t *, void *);

void and_init(mos6502_t *);
void jump_init(mos6502_t*);
void nop_init(mos6502_t *);
void cmp_init(mos6502_t *);
void cpx_init(mos6502_t *);
void cpy_init(mos6502_t *);
void nop_init(mos6502_t *);
void adc_init(mos6502_t *);
void ora_init(mos6502_t *);
void eor_init(mos6502_t *);
void inc_init(mos6502_t *);
void dec_init(mos6502_t *);
void asl_init(mos6502_t *);
void transfert_init(mos6502_t *);
void ldy_init(mos6502_t *);
void lda_init(mos6502_t *);
