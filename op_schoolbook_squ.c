//  
//  op_schoolbook_squ.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"
/******************* Schoolbook SQU *******************
 schoolbook방식으로 구현한 제곱연산이다.
 사용자는 SQU함수만을 사용하여 schoolbook방식의 제곱 사용이 가능하다.
 (예제 코드) SQU(&dst, src);
******************************************************/

/************** SQUC_1Word_zxx(A) : word 1개의 제곱연산  *********************
Input: A = (-W, W)
Output: C = A^2 = [0,W^2)
1: A1, A0 ← |A| >> (w/2), |A| mod 2^(w/2)     
2: C1, C0 ← A1*A1, A0*A0         
3: C ← (C1 << w) + C0               
4: T ← A0*A1           
5: T ← T << ((w/2) + 1)              
6: C ← C + T      
7: return C 
********************************************************************/
void SQUC_1Word_zxx(word* dst, const word* src)
{
    word A[2], temp, carry = 0;
    A[1] = (*src)>>(WORD_BITLEN/2);
    A[0] = (*src)&HALF_WORDBIT;

    temp = A[0]*A[1];
    dst[1] = A[1]*A[1];
    dst[0] = A[0]*A[0];

    word temp1 = temp << (WORD_BITLEN/2+1);
    word temp2 = temp >> (WORD_BITLEN/2-1);
    ADD_1word_zzyc(&dst[0], &carry, &temp1);
    ADD_1word_zzyc(&dst[1], &carry, &temp2);
}

/************** schoolbook_SQUC(A) : 0,-1,1이 아닌 정수 A의 제곱  *********************
Input: A = [Wn-1, Wn)
Output: C = A^2 = [0,W2n)
1: C1, C2 ← 0                       |   8:          T2 ← T2 << (i+j)w      
2: for j = 0 to t-1 do              |   9:          C2 ← ADD(C2, T2)
3:      T1 ← Aj*Aj                  |   10:      end for
4:      T1 ← T1 << 2jw              |   11: end for
5:      C1 ← T1 + C1                |   12: C2 ← C2 << 1
6:      for i = j+1 to t-1 do       |   13: return ADD(C1,C2)
7:          T2 ← AjAi  
***********************************************************************************/
void schoolbook_SQUC(bigint** dst, const bigint* src)
{
    word temp[2];
    int i, j, t = get_wordlen(src);
    bigint* temp_bigint = NULL;
    bi_new(&temp_bigint, 2*t, NON_NEGATIVE);
    bigint* C0 = NULL;
    bigint* C1 = NULL;
    bi_new(&C0, 2*t, NON_NEGATIVE);
    bi_new(&C1, 2*t, NON_NEGATIVE);
    for ( i = 0; i < t; i++)
    {
        SQUC_1Word_zxx(temp, &src->a[i]);
        temp_bigint->a[2*i] = temp[0];  
        temp_bigint->a[2*i+1] = temp[1];
        ADD_zzy(&C0, temp_bigint);
        array_init(temp_bigint->a + 2*i, 2);
        for ( j = i+1; j < t; j++)
        {
            MUL_1word_zxy(temp, &src->a[i], &src->a[j]);
            temp_bigint->a[i+j] = temp[0];  
            temp_bigint->a[i+j+1] = temp[1];
            ADD_zzy(&C1, temp_bigint);
            array_init(temp_bigint->a + i+j, 2);
        } 
    }
    left_shift(C1,1);
    ADD_zxy(dst, C0, C1);
    
    bi_delete(&temp_bigint);
    bi_delete(&C0);
    bi_delete(&C1);
}

/******************* SQU(A) : 임의의 정수 A의 제곱  *********************
Input: A = [Wn-1, Wn)
Output: C = A^2 = [0,W2n)
1: if A = 0 or A = 1 or A = -1 then
2:      return |A|                       
3: end if             
4: return SQUC(A)                    
********************************************************************/
void SQU_zxx(bigint** dst, const bigint* src)
{
    if(bi_is_zero(src) == TRUE || bi_is_minus_one(src) == TRUE || bi_is_one(src) == TRUE)
    {  // src = 0, src = -1, src = 1인 경우 
        bi_assign(dst,src);
        (*dst)->sign = NON_NEGATIVE;
    } 
    else
        schoolbook_SQUC(dst,src);
}
