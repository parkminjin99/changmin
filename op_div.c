//  
//  op_div.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"

void BinaryLongDiv_2word(word* Q, const word* src11, const word* src10, const word* src2) // Q는 1워드, src1은 2워드, src2은 1워드
{
    int i;
    word R = *src11;
    *Q = 0;
    for ( i = WORD_BITLEN-1; i >= 0; i--)
    {
        if(R >= (word)1<<(WORD_BITLEN-1))
        {
            *Q += (word)1<<i;
            R = (R<<1) + get_j_th_bit(*src10,i) - (*src2);
        }
        else
        {
            R = (R<<1) + get_j_th_bit(*src10,i);
            if(R >= *src2)
            {
                *Q += (word)1<<i;
                R -= (*src2);
            }
        }
    }
}

void DIVCC(word* Q, bigint** R, const bigint* src1, const bigint* src2)
{
    bigint* temp = NULL;
    int src1Len = get_wordlen(src1), src2Len = get_wordlen(src2);
    *Q = 0;
    if(src1Len == src2Len)
        *Q = src1->a[src2Len-1]/src2->a[src2Len-1];
    else // src1Len == src2Len+1
    {
        if(src1->a[src2Len] == src2->a[src2Len-1])
            *Q = BITMASK;
        else
            BinaryLongDiv_2word(Q, &src1->a[src2Len], &src1->a[src2Len-1], &src2->a[src2Len-1]);
    }
    bi_new(&temp, 1, NON_NEGATIVE);
    temp->a[0] = *Q;
    MUL_zzy(&temp, src2); // temp = src2*Q

    SUB_zxy(R, src1, temp);  // R = src1 - src2*Q
    while(get_sign(*R) == NEGATIVE) // R < 0
    {
        (*Q)--;
        ADD_zzy(R,src2);
    }
    bi_delete(&temp);
}

void DIVC(word* Q, bigint** R, const bigint* src1, const bigint* src2, const int k)
{
    if(bi_compare(src1,src2) == -1) // src1 < src2
    {
        *Q = 0;
        bi_assign(R, src1);
        return;
    }
    bigint* src1_temp = NULL;
    bigint* src2_temp = NULL;
    bi_assign(&src1_temp, src1);
    bi_assign(&src2_temp, src2);
    left_shift(src1_temp, k); // src1_temp = src1 << k
    left_shift(src2_temp, k); // src2_temp = src2 << k

    DIVCC(Q, R, src1_temp, src2_temp); 
    right_shift(*R,k); // Q = Q, R = R >> k

    bi_delete(&src1_temp);
    bi_delete(&src2_temp);
}

int DIV(bigint** Q, bigint** R, const bigint* src1, const bigint* src2)
{
    bigint* temp = NULL;
    if(bi_is_zero(src2) == TRUE || get_sign(src2) == NEGATIVE) // src2 < 0 또는 
        return INVALID;
    if(bi_compare(src1,src2) == -1) // src1 < src2
    {
        bi_set_zero(Q);
        bi_assign(R,src1);
        return VALID;
    }

    int k = 0, src1Len = get_wordlen(src1), src2Len = get_wordlen(src2);
    while(1)
    {
        word mask = src2->a[src2Len-1]>>(WORD_BITLEN-1-k);
        if((mask & 0x1) == 0x1)
            break;
        k++;
    }

    bi_new(Q, src1Len, get_sign(src1)); // Q = 0
    bi_set_zero(R); // R = 0 
    int i;
    for ( i = src1Len - 1; i >= 0; i--)
    {
        left_shift(*R,WORD_BITLEN);
        (*R)->a[0] = src1->a[i]; // R = RW + src1->a[i] 
        bi_assign(&temp, *R); // temp = R
        DIVC(&(*Q)->a[i], R, temp, src2, k);
        bi_delete(&temp);
    }
    bi_refine(*Q);
    return VALID;
}