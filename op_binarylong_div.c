//  
//  op_binarylong_div.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"

int BinaryLongDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2)
{ 
    if(get_sign(src2) == NEGATIVE || bi_is_zero(src2) == TRUE)
        return INVALID; 
    bigint* temp = NULL; 
    bi_set_zero(R); // R = 0
    int i, n = get_wordlen(src1)*WORD_BITLEN;
    bi_new(Q,n,NON_NEGATIVE);
    for ( i = n-1; i >= 0; i--)
    {
        left_shift(*R,1);
        (*R)->a[0] |= get_jth_bit(src1,i); // R = 2*R + src1의 i번째 원소
        if(bi_compare(*R,src2) != -1) // R >= src2
        {
            bi_new(&temp,(i/WORD_BITLEN)+1,NON_NEGATIVE);
            temp->a[get_wordlen(temp)-1] ^= (word)1<<(i%WORD_BITLEN); // temp = 1<<(i%WORD_BITLEN)
            ADD_zzy(Q,temp); // Q += temp
            SUB_zzy(R,src2); // R -= src2
            bi_delete(&temp);
        }
    }
    return VALID;
}