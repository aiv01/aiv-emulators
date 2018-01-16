#include <stdio.h>
#include <stdlib.h>
#include <mos6502.h>

#define assert_is_equal(a, b) if (a != b) return -1;
#define assert_is_zero(a) if (a != 0) return -1;
#define assert_is_not_zero(a) if (a == 0) return -1;
#define assert_is_not_equal(a, b) if (a == b) return -1;

#define test(f) if (f())\
{\
    fprintf(stderr, "TEST FAILED: " #f "() file: " __FILE__ " line: %d\n", __LINE__);\
    exit(1);\
}\
else {\
    fprintf(stdout, "TEST OK: " #f "()\n");\
}

