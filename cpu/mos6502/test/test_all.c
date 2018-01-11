#include "test.h"


int test_all_and();
int test_all_nop();

int main(int argc, char *argv[])
{
    test_all_and();
    test_all_nop();
    fprintf(stdout, "ALL TESTS PASSED\n");
}