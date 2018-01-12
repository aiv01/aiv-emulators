#include "test.h"

int test_all_and();
int test_all_nop();
int test_all_ora();
int test_all_eor();
int test_all_inc();
int test_all_dec();
int test_all_transfert_test();
int test_all_branch();

int main(int argc, char *argv[])
{
    test_all_and();
    test_all_nop();
    test_all_ora();
    test_all_eor();
    test_all_inc();
    test_all_dec();
    test_all_transfert_test();
    test_all_branch();
    fprintf(stdout, "ALL TESTS PASSED\n");
}
