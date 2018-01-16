#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mos6502.h>

static int ERROR_LINE = 0;
#define assert_is_equal(a, b) if (a != b) { ERROR_LINE = __LINE__; return -1; }
#define assert_is_zero(a) if (a != 0) { ERROR_LINE = __LINE__; return -1; }
#define assert_is_not_zero(a) if (a == 0) { ERROR_LINE = __LINE__; return -1; }
#define assert_is_not_equal(a, b) if (a == b) { ERROR_LINE = __LINE__; return -1; }

#define test(f) if (f())\
{\
    fprintf(stderr, "TEST FAILED: " #f "() file: " __FILE__ " line: %d\n", ERROR_LINE);\
    exit(1);\
}\
else {\
    fprintf(stdout, "TEST OK: " #f "()\n");\
}

#define is_set_bit_0(a) ((a & 0x01) == 0x01)
#define is_set_bit_1(a) ((a & 0x02) == 0x02)
#define is_set_bit_2(a) ((a & 0x04) == 0x04)
#define is_set_bit_3(a) ((a & 0x08) == 0x08)

#define is_set_bit_4(a) ((a & 0x10) == 0x10)
#define is_set_bit_5(a) ((a & 0x20) == 0x20)
#define is_set_bit_6(a) ((a & 0x40) == 0x40)
#define is_set_bit_7(a) ((a & 0x80) == 0x80)

#endif
