#include "test.h"


int test_all_and();
int test_all_cmp();
int test_all_cpx();
int test_all_cpy();
 

int main(int argc, char *argv[])
{
    test_all_and();
    test_all_cmp();
    test_all_cpx();
    test_all_cpy();
    fprintf(stdout, "ALL TESTS PASSED\n");
}