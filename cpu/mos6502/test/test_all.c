#include "test.h"

int test_all_and();
int test_all_jump();
int test_all_cmp();
int test_all_cpx();
int test_all_cpy();
int test_all_asl();
int test_all_nop();
int test_all_adc();
int test_all_ora();
int test_all_eor();
int test_all_sbc();
int test_all_inc();
int test_all_dec();
int test_all_ldx();
int test_all_transfert_test();
int test_all_sta();
int test_all_stx();
int test_all_sty();
int test_all_jsr();
int test_all_rts();
int test_all_ldy();
int test_all_stack();
int test_all_lda();

int main(int argc, char *argv[])
{
    test_all_and();
    test_all_jump();
    test_all_cmp();
    test_all_cpx();
    test_all_cpy();
    test_all_nop();
    test_all_adc();
    test_all_ora();
    test_all_eor();
    test_all_sbc();
    test_all_inc();
    test_all_dec();
    test_all_asl();
    test_all_ldx();
    test_all_transfert_test();
<<<<<<< HEAD
    test_all_inx();
    test_all_iny();
    test_all_dex();
    test_all_dey();
=======
    test_all_sta();
    test_all_stx();
    test_all_sty();
    test_all_jsr();
    test_all_rts();
    test_all_ldy();
    test_all_stack();
    test_all_lda();
>>>>>>> 8f3e8e5c506cadd6b6684c2d1ad6f5cc8d34b70e
    fprintf(stdout, "ALL TESTS PASSED\n");
}
