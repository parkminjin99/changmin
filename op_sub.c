//  
//  op_sub.c
//  Changmin's library
//  
//  Created by ÃÖ°­Ã¢¹Î on 2020/11/09.
//  Copyright 2020 ÃÖ°­Ã¢¹Î. All rights reserved.
//  
#include "operation.h"

/*********************
 1word»çÀÌ¿¡ A ¡Ã B > 0 ÀÏ¶§, »¬¼ÀÀ» ÁøÇàÇÏ´Â ÇÔ¼öÀÌ´Ù. 
 pseudo code´Â ´ÙÀ½°ú °°´Ù
 ******SUB_1word_zxy(A, b, B)*****************
Input: A, B (1 word), b ¡ô {0, 1}
Output: b ¡ô {0, 1}, C ¡ô (1 word) such that A - B = -bW + C
------------------------------------------------------------------
1: C ¡ç A - b
2: if A < b then
3:      b ¡ç 1
4: else
5:      b ¡ç 0
6: end if
7: if C < B then
8:      b ¡ç b + 1
9: end if
10: C ¡ç C - B
11: return b, C
**********************/

void SUB_1word_zxy(word* dst, int* carry, const word* src1, const word* src2)    // src1°ú src2, carry¸¦ ÀÔ·Â¹Þ¾Æ 1word¿¡ ´ëÇÑ Àý´ñ°ª Ãâ·Â
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
/************************************
A ¡Ã B > 0 ¿¡ ´ëÇØ  A - B¸¦ Ãâ·ÂÇÏ´Â ÇÔ¼öÀÌ´Ù. 
°á°ú´Â Ç×»ó ¾ç¼ö°¡ µÇ°í, °á°ú´Â bigintÀÇ ÁÖ¼Ò¸¦ ÀÔ·Â¹Þ¾Æ ÁøÇàÇÑ´Ù. 
´ÙÀ½ÀÇ ÇØ´ç °úÁ¤ÀÇ pseudo codeÀÌ´Ù.

*******SUBC(A, B)***A ¡Ã B > 0*******************
Input: A = [Wn-1, Wn), B = [Wm-1, Wm), (A ¡Ã B > 0),
Output: A - B = C¡ô [0, Wn)
1: Bj ¡ç 0 for j = m, m + 1, . . . , n - 1
2: b ¡ç 0
3: for j = 0 to n - 1 do
4:       b, Cj ¡ç SUBAbB(Aj, b, Bj)
5: end for
6: l ¡ç min{j : Cn-1 = Cn-2 = ¡¤ ¡¤ ¡¤ = Cj = 0}
7: return  C
*******************************/

void SUBC(bigint** dst, const bigint* src1, const bigint* src2)     // src1>src2·Î ÀÔ·Â¹Þ¾Æ µÑÀÇ Â÷¸¦ dst¿¡ ÀúÀå
{
    int new_wordlen = get_wordlen(src1);
    int y_wordlen = get_wordlen(src2);

    bi_new(dst, new_wordlen, NON_NEGATIVE);//z´Â src1, src2Áß ±ä±æÀÌ·Î ¿ì¼± ÇÒ´ç

    bigint* temp = NULL;
    bi_assign(&temp, src2); //src2¸¦ º¯ÇüÇØ¾ß ÇÏ´Â °æ¿ì 

    int carry = 0;
    if (get_wordlen(src1) != get_wordlen(temp))     // src1, src2 ±æÀÌ ´Ù¸£¸é
    {
        temp->wordlen = new_wordlen;
        temp->a = (word*)realloc(temp->a, sizeof(word) * new_wordlen);       // scr2 ÀçÇÒ´ç
   
        for (int i = new_wordlen; i > y_wordlen; i--)
            temp->a[i - 1] = 0;

    }
    for (int i = 0; i < new_wordlen; i++)
    {
        SUB_1word_zxy(&(*dst)->a[i], &carry, &src1->a[i], &temp->a[i]);
    }
    bi_refine(*dst);
    bi_delete(&temp);
}

/*********SUB_zxy(A, B) **************
Input: A, B ï¿½ï¿½ Z
Output: A ? B ï¿½ï¿½ Z
1: if A = 0 then              |   13: return ?SUBC(B, A)
2:      return ?B             |   14: end if
3: end if                     |   15: if 0 > A ï¿½ï¿½ B then
4: if B = 0 then              |   16:     return SUBC(|B|, |A|)
5:      return A              |   17: else if 0 > B > A then
6: end if                     |   18:     return ?SUBC(|A|, |B|)
7: if A = B then              |   19: end if
8:      return 0              |   20: if A > 0 and B < 0 then
9: end if                     |   21:     return ADD_zxy(A, |B|)
10: if 0 < B ï¿½ï¿½ A then        |   22: else .
11:     return SUBC(A, B)     |   23:     return ?ADD_zxy(|A|, B)
12: else if 0 < A < B then    |   24: end if

****************************/

void SUB_zxy(bigint** dst, const bigint* src1, const bigint* src2)   //src1 ï¿½ï¿½ src2ï¿½ï¿½ ï¿½ï¿½ï¿½Ï¿ï¿½ subcï¿½ï¿½ ï¿½Ìµï¿½ï¿½ï¿½Å°ï¿½ï¿½ ï¿½Ô¼ï¿½
{
    bigint* temp = NULL;
    if(bi_is_zero(src1) == TRUE && bi_is_zero(src2) == TRUE)
    {
        bi_set_zero(dst);
    }
    else if (TRUE == bi_is_zero(src1))  //  src1=0
    {
        bi_assign(dst, src2); // bigint ï¿½ï¿½ï¿½ï¿½Ã¼ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½ ï¿½Ô¼ï¿½
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
        //ADD_zxy(dst, src1, src2); // *ï¿½ï¿½ï¿½ï¿½*
        //flip_sign(src2);
    }
    else                           // src2>0>src1
    {
        //printf("#else\n");
        bi_assign(&temp,src1);
        flip_sign(temp);
        ADD_zxy(dst, temp, src2);
        //flip_sign(src1);
        //ADD_zxy(dst, src1, src2); // *ï¿½ï¿½ï¿½ï¿½*
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
