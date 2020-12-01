//  
//  op_naive_div.c
//  Changmin's library
//  
//  Created by √÷∞≠√¢πŒ on 2020/11/09.
//  Copyright 2020 √÷∞≠√¢πŒ. All rights reserved.
//  
#include "operation.h"


int NaiveDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2)
{
    if(get_sign(src2) == NEGATIVE || bi_is_zero(src2) == TRUE)
        return INVALID;
    if(bi_compare(src1,src2) == -1) // src1 < src2
    {
        bi_set_zero(Q);
        bi_assign(R, src1);
        return VALID;
    }
    if(bi_is_one(src2) == TRUE) // src2 = 1
    {
        bi_assign(Q, src1);
        bi_set_zero(R);
        return VALID;
    }
    bigint* ONE = NULL;
    bi_set_one(&ONE);
    bi_set_zero(Q);
    bi_assign(R,src1);
    while(bi_compare(*R,src2) != -1)
    {
        ADD_zzy(Q, ONE);
        SUB_zzy(R, src2);
        //bi_show(*R,16);
    }
    return VALID;
}
