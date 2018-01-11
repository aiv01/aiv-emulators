#include "test.h"

int test_all_and();
int test_all_nop();
int test_all_inc();
int test_all_dec();

int main(int argc, char *argv[])
{
    test_all_and();
    test_all_nop();
    test_all_inc();
    test_all_dec();
    fprintf(stdout, "ALL TESTS PASSED\n");
}