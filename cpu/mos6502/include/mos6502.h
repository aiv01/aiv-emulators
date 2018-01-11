typedef struct mos6502 {
    unsigned char a;
    unsigned char x;
    unsigned char y;
    unsigned char flags;
    unsigned char sp;
    unsigned short pc;

    unsigned char read8(mos6502_t*, unsigned short);
    unsigned short read16(mos6502_t*, unsigned short);
    void write8(mos6502_t*, unsigned short, unsigned char);
    void write16(mos6502_t*, unsigned short, unsigned short);

    int (*op_codes[256])(mos6502_t*);
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