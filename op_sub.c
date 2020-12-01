//  
//  op_sub.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"

/*****SUB_1word_zxy(A, b, B)*****************
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

void SUB_1word_zxy(word* dst, int* carry, const word* src1, const word* src2)    // src1과 src2, carry를 입력받아 1word에 대한 뺄셈의 절댓값을 출력
{
    *dst = (*src1) - (*carry);

    if (*src1 < *carry)
        *carry = 1;
    else
        *carry = 0;

    if (*dst < *src2)
        *carry = *carry + 1;

    *dst = *dst - *src2;

}

/********SUBC(A, B)***A ≥ B > 0*******************
Input: A = [Wn?1, Wn), B = [Wm?1, Wm), (A ≥ B > 0),
Output: A ? B = C∈ [0, Wn)
1: Bj ← 0 for j = m, m + 1, . . . , n ? 1
2: b ← 0
3: for j = 0 to n ? 1 do
4:       b, Cj ← SUBAbB(Aj, b, Bj)
5: end for
6: l ← min{j : Cn?1 = Cn?2 = · · · = Cj = 0}
7: return  C
*******************************/

void SUBC(bigint** dst, const bigint* src1, const bigint* src2)    // src1>src2로 입력받아 둘의 차를 dst에 저장
{
    int new_wordlen = get_wordlen(src1);
    int y_wordlen = get_wordlen(src2);

    bi_new(dst, new_wordlen, NON_NEGATIVE);  //z는 src1, src2중 긴길이로 우선 할당

    bigint* temp = NULL;
    bi_assign(&temp, src2); //src2를 변형해야 하는 경우 

    int carry = 0;
    //bi_show(temp, 16);
    if (get_wordlen(src1) != get_wordlen(temp))     // src1, src2 길이 다르면
    {
        temp->wordlen = new_wordlen;
        temp->a = (word*)realloc(temp->a, sizeof(word) * new_wordlen);       // scr2 재할당
        //bi_show(temp, 16);
        //printf("=\n");
        for (int i = new_wordlen; i > y_wordlen; i--)
            temp->a[i - 1] = 0;

        //bi_show(temp, 16);
        //printf("=\n");
    }
    for (int i = 0; i < new_wordlen; i++)
    {
        SUB_1word_zxy(&(*dst)->a[i], &carry, &src1->a[i], &temp->a[i]);
    }
    bi_refine(*dst);
    bi_delete(&temp);
}

/*********SUB_zxy(A, B) **************
Input: A, B ∈ Z
Output: A ? B ∈ Z
1: if A = 0 then              |   13: return ?SUBC(B, A)
2:      return ?B             |   14: end if
3: end if                     |   15: if 0 > A ≥ B then
4: if B = 0 then              |   16:     return SUBC(|B|, |A|)
5:      return A              |   17: else if 0 > B > A then
6: end if                     |   18:     return ?SUBC(|A|, |B|)
7: if A = B then              |   19: end if
8:      return 0              |   20: if A > 0 and B < 0 then
9: end if                     |   21:     return ADD_zxy(A, |B|)
10: if 0 < B ≤ A then        |   22: else .
11:     return SUBC(A, B)     |   23:     return ?ADD_zxy(|A|, B)
12: else if 0 < A < B then    |   24: end if

****************************/

void SUB_zxy(bigint** dst, const bigint* src1, const bigint* src2)   //src1 과 src2를 비교하여 subc로 이동시키는 함수
{
    bigint* temp = NULL;
    if(bi_is_zero(src1) == TRUE && bi_is_zero(src2) == TRUE)
    {
        bi_set_zero(dst);
    }
    else if (TRUE == bi_is_zero(src1))  //  src1=0
    {
        bi_assign(dst, src2); // bigint 구조체를 복사하는 함수
        flip_sign(*dst);
        //printf("#src1=0\n");
    }
    else if (TRUE == bi_is_zero(src2)) //  src2=0
    {
        bi_assign(dst, src1);
        //printf("#src2=0\n");
    }
    else if (0 == bi_compare(src1, src2)) //  src1=src2
    {
        bi_set_zero(dst);
        //printf("#src2=src1\n");

    }
    else if ((1 == bi_compare(src1, src2)) && (src2->sign == NON_NEGATIVE))  //  src1>src2>0
    {
        //printf("#src1>src2>0\n");
        SUBC(dst, src1, src2);
    }
    else if ((-1 == bi_compare(src1, src2)) && (src1->sign == NON_NEGATIVE))  // src2>src1>0
    {
        //printf("#src2>src1>0\n");
        SUBC(dst, src2, src1);
        flip_sign(*dst);
    }
    else if ((1 == bi_compare(src1, src2)) && (src1->sign == NEGATIVE))      // 0>src1>src2
    {
        //printf("#0>src1>src2\n");
        SUBC(dst, src2, src1);
    }
    else if ((-1 == bi_compare(src1, src2)) && (src2->sign == NEGATIVE))   //   0>src2>src1
    {
        //printf("# 0>src2>src1\n");
        SUBC(dst, src1, src2);
        flip_sign(*dst);
    }
    else if ((src1->sign == NON_NEGATIVE) && (src2->sign == NEGATIVE))    //  src1>0>src2
    {
        //printf("# src1>0>src2\n");
        bi_assign(&temp, src2);
        flip_sign(temp);
        ADD_zxy(dst, src1, temp);
        //flip_sign(src2);
        //ADD_zxy(dst, src1, src2); // *수정*
        //flip_sign(src2);
    }
    else                           // src2>0>src1
    {
        //printf("#else\n");
        bi_assign(&temp,src1);
        flip_sign(temp);
        ADD_zxy(dst, temp, src2);
        //flip_sign(src1);
        //ADD_zxy(dst, src1, src2); // *수정*
        //flip_sign(src1);
        flip_sign(*dst);
    }
    bi_delete(&temp);
}

void SUB_zzy(bigint** dst, const bigint* src)
{
    bigint* temp = NULL;
    bi_assign(&temp, *dst);
    bi_delete(dst);
    SUB_zxy(dst, temp, src);
    bi_delete(&temp);
}
