#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
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

#endif