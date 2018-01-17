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

//cpu Flags
#define FLAG_NEGATIVE   0x80
#define FLAG_OVERFLOW   0x20
#define FLAG_BREAK      0x10
#define FLAG_DECIMAL    0x08
#define FLAG_INTERRUPT  0x04
#define FLAG_ZERO       0x02
#define FLAG_CARRY      0x01

//set flags
#define SET_BIT_NEGATIVE(cpu, b)\
if(b)\
{\
    cpu->flags |= FLAG_NEGATIVE;\
}\
else\
{\
    cpu->flags &= (~FLAG_NEGATIVE);\
}

#define SET_BIT_OVERFLOW(cpu, b)\
if(b)\
{\
    cpu->flags |= FLAG_OVERFLOW;\
}\
else\
{\
    cpu->flags &= (~FLAG_OVERFLOW);\
}

#define SET_BIT_BREAK(cpu, b)\
if(b)\
{\
    cpu->flags |= FLAG_BREAK;\
}\
else\
{\
    cpu->flags &= (~FLAG_BREAK);\
}

#define SET_BIT_DECIMAL(cpu, b)\
if(b)\
{\
    cpu->flags |= FLAG_DECIMAL;\
}\
else\
{\
    cpu->flags &= (~FLAG_DECIMAL);\
}

#define SET_BIT_INTERRUPT(cpu, b)\
if(b)\
{\
    cpu->flags |= FLAG_INTERRUPT;\
}\
else\
{\
    cpu->flags &= (~FLAG_INTERRUPT);\
}

#define SET_BIT_ZERO(cpu, b)\
if(b)\
{\
    cpu->flags |= FLAG_ZERO;\
}\
else\
{\
    cpu->flags &= (~FLAG_ZERO);\
}

#define SET_BIT_CARRY(cpu, b)\
if(b)\
{\
    cpu->flags |= FLAG_CARRY;\
}\
else\
{\
    cpu->flags &= (~FLAG_CARRY);\
}

//Read flags
#define NEGATIVE_READ(cpu)  (cpu->flags & FLAG_NEGATIVE)
#define OVERFL_READ(cpu)    (cpu->flags & FLAG_OVERFLOW)
#define BRK_READ(cpu)       (cpu->flags & FLAG_BREAK)
#define DECIM_READ(cpu)     (cpu->flags & FLAG_DECIMAL)
#define INTERR_READ(cpu)    (cpu->flags & FLAG_INTERRUPT)
#define ZERO_READ(cpu)      (cpu->flags & FLAG_ZERO)
#define CARRY_READ(cpu)     (cpu->flags & FLAG_CARRY)

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
void sbc_init(mos6502_t *);
void inc_init(mos6502_t *);
void dec_init(mos6502_t *);
void lsr_init(mos6502_t *);
void asl_init(mos6502_t *);
void ldx_init(mos6502_t *);
void transfert_init(mos6502_t *);
void branch_init(mos6502_t* );
void sta_init(mos6502_t *);
void stx_init(mos6502_t *);
void sty_init(mos6502_t *);
void jsr_init(mos6502_t *);
void rts_init(mos6502_t *);
void ldy_init(mos6502_t *);
void stack_init(mos6502_t *);
void lda_init(mos6502_t *);
void rti_init(mos6502_t *);
void inx_init(mos6502_t *);
void iny_init(mos6502_t *);
void dex_init(mos6502_t *);
void dey_init(mos6502_t *);
void flags_init(mos6502_t*);