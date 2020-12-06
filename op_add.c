//  
//  op_add.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//  

#include "operation.h"
/******************* Additino *******************
 두 bigint를 입력하여 덧셈을 진행하는 함수이다. 
 사용자는 ADD_zxy ADD_zzy함수만을 사용하여 뺄셈이 가능하다.
 (예제 코드) ADD_zxy(&dst, src1, src2);  ADD_zzy(&dst, dst, src1);
******************************************************/
/***** ADD_1word_zxyc(A, b, B) :  *****************
Input: A, B (1 word), b ∈ {0, 1}
Output: b ∈ {0, 1}, C ∈ (1 word) such that A ? B = ?bW + C
------------------------------------------------------------------
1: C ← A - b
2: if A < b then
3:      b ← 1
4: else
5:      b ← 0
6: end if
7: if C < B then
8:      b ← b + 1
9: end if
10: C ← C - B
11: return b, C
**********************/
void ADD_1word_zxyc(word* dst, word* carry, const word* src1, const word* src2)
{
    word new_carry = 0;
    *dst = (*src1) + (*src2);
    if (*dst < *src1)           // carry 발생
        new_carry = 1;
    *dst += *carry;
    if (*dst < *carry)          // carry 발생
        new_carry += 1;
    *carry = new_carry;
}

void ADD_1word_zzyc(word* dst, word* carry, const word* src)
{
    word new_carry = 0;
    *dst += *src;
    if (*dst < *src)            // carry 발생
        new_carry = 1;
    *dst += *carry;
    if (*dst < *carry)          // carry 발생
        new_carry += 1;
    *carry = new_carry;
}

/************** ADDC(A, B) : 동일한 부호의 두 정수 덧셈  *********************
Input: A = [Wn-1, Wn), B = [Wm-1, Wm)
Output: A + B ∈ Z
1: Bj ← 0 for j = m, m+1,..., n-1   |   7: if A < 0 and B > 0 then 
2: carry = 0                        |   8:     return SUB_zxy(B,|A|)
3: for j = 0 to n-1 do              |   9: end if
4:      carry, Cj ← ADD_1word_zxyc()       |   10: if WordLen(A) >= WordLen(B) then
5: end for                          |   11:     return ADDC(A,B)
6: Cn ← carry                       |   12: else
********************************************************************/
void ADDC(bigint** dst, const bigint* src1, const bigint* src2)
{
    int i, src1Len = get_wordlen(src1), src2Len = get_wordlen(src2);

    bi_new(dst, src1Len + 1, get_sign(src1));
    word carry = 0; // carry
    for (i = 0; i < src2Len; i++)
        ADD_1word_zxyc(&(*dst)->a[i], &carry, &src1->a[i], &src2->a[i]); // 1워드 덧셈

    for (i = src2Len; i < src1Len; i++)  
    {
        (*dst)->a[i] = src1->a[i] + carry;
        if ((*dst)->a[i] < carry && carry == 1) // carry 발생
            carry = 1;
        else
            carry = 0;
    }
    (*dst)->a[i] = carry;
    bi_refine(*dst);
}

/************************* ADD_zxy(A, B) ****************************
Input: A, B ∈ Z
Output: A + B ∈ Z
1: if A = 0 then              |   10: if A < 0 and B > 0 then 
2:      return B              |   11:     return SUB_zxy(B,|A|)
3: end if                     |   12: end if
4: if B = 0 then              |   13: if WordLen(A) >= WordLen(B) then
5:      return A              |   14:     return ADDC(A,B)
6: end if                     |   15: else
7: if A > 0 and B < 0 then    |   16:     return ADDC(B,A)
8:      return SUB_zxy(A,|B|)     |   17: end if
9: end if                     |  
********************************************************************/
void ADD_zxy(bigint** dst, const bigint* src1, const bigint* src2)
{
    bigint* temp = NULL;
    if (bi_is_zero(src1) == TRUE) // src1 = 0
        bi_assign(dst, src2);
    else if (bi_is_zero(src2) == TRUE) // src2 = 0
        bi_assign(dst, src1);
    else if ((get_sign(src1) == NON_NEGATIVE) && (get_sign(src2) == NEGATIVE)) // src1 >= 0, src2 < 0
    {
        bi_assign(&temp,src2);
        flip_sign(temp);
        SUB_zxy(dst, src1, temp);
    }
    else if ((get_sign(src1) == NEGATIVE) && (get_sign(src2) == NON_NEGATIVE)) // src1 < 0, src2 >= 0
    {
        bi_assign(&temp,src1);
        flip_sign(temp);
        SUB_zxy(dst, src2, temp);
    }
    else if (get_wordlen(src1) >= get_wordlen(src2))
        ADDC(dst, src1, src2);
    else 
        ADDC(dst, src2, src1);
    bi_delete(&temp);
}

void ADD_zzy(bigint** dst, const bigint* src)
{
    bigint* temp = NULL;
    bi_assign(&temp, *dst);
    ADD_zxy(dst, temp, src);
    bi_delete(&temp);
}