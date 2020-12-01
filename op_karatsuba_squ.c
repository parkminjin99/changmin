//  
//  op_karatsuba_squ.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"
void SQUCKaratsuba(bigint** dst, const bigint* src, const int flag)
{
    if (flag >= get_wordlen(src))
    {
        SQU_zxx(dst, src);
        return;
    }
    int l = (get_wordlen(src) + 1) >> 1;

    bigint* A1 = NULL;
    bigint* A0 = NULL;
    bigint* t1 = NULL;
    bigint* t0 = NULL;
    bigint* R = NULL;
    bigint* S = NULL;

    bi_assign(&A1, src);
    bi_assign(&A0, src);
    right_shift(A1, l * WORD_BITLEN);  reduction_2_r(A0, l * WORD_BITLEN);   //A1은 상위비트, A0는 하위 LW

    SQUCKaratsuba(&t1, A1, flag);
    SQUCKaratsuba(&t0, A0, flag);

    left_shift(t1, 2 * l * WORD_BITLEN);
    ADD_zxy(&R, t1, t0);

    KaratsubaMUL(&S, A1, A0);

    left_shift(S, l * WORD_BITLEN + 1);
    ADD_zxy(dst, R, S);

    bi_delete(&A1);
    bi_delete(&A0);
    bi_delete(&t1);
    bi_delete(&t0);
    bi_delete(&R);
    bi_delete(&S);

}