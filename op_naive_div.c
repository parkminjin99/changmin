//  
//  op_naive_div.c
//  Changmin's library
//  
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
//  
#include "operation.h"
/*********************** Naive Division **********************
 ���� �ƴ� �� ���� A, B�� ���� �� Q, ������ R�� ã�� ���� �⺻���� ������ �˰����̴�. 
 A = BQ + R (0 <= R < B)
 B = 0�� ���� ������ ���ǵ��� �ʾ� INVALID�� ��ȯ�Ѵ�.
 A < B�� ��쿡�� Q = 0, R = A�� �ȴ�.
 B = 1�� ��쿡�� Q = A, R = 0�� �ȴ�.
 ����ڴ� NaiveDiv�Լ��� ����Ͽ� ���� �⺻���� ������ �˰��� ����� �����ϴ�.
 (���� �ڵ�) NaiveDiv(&Q, &R, A, B);
*************************************************************/

/***************** NaiveDiv(Q, R, A, B) : ���� �⺻���� ������ �˰���  **********************
Input: A, B �� Z such that A >= 0 and B >= 0
Output: INVALID or (Q, R) such that A = B*Q + R (0 <= R < B)
1: if B <= 0 then             |   10: (Q,R) �� (0,A)
2:      return INVALID        |   11: while R >= B do
3: end if                     |   12:       (Q, R) �� (Q+1,R-B)
4: if A < B then              |   13: end while
5:      return (0,A)          |   14:     return (Q,R)
6: end if                    
7: if B = 1 then             
8:      return (A,0)
9: end if
****************************************************************************************/
int NaiveDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2)
{
    if(get_sign(src2) == NEGATIVE || bi_is_zero(src2) == TRUE) // src2 <= 0�� ��� INVALID
        return INVALID;
    if(bi_compare(src1,src2) == -1)     // src1 < src2
    {
        bi_set_zero(Q);
        bi_assign(R, src1);
        return VALID;
    }
    if(bi_is_one(src2) == TRUE)         // src2 = 1
    {
        bi_assign(Q, src1);
        bi_set_zero(R);
        return VALID;
    }
    bigint* ONE = NULL;
    bi_set_one(&ONE); 
    bi_set_zero(Q);         // Q = 0
    bi_assign(R,src1);      // R = src1
    while(bi_compare(*R,src2) != -1)    // R < B�� ������ ������ R = R-B, Q = Q+1
    {
        ADD_zzy(Q, ONE);
        SUB_zzy(R, src2);
    }
    return VALID;
}
