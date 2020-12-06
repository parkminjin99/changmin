//  
//  op_div.c
//  Changmin's library
//  
//  Created by �ְ�â�� on 2020/12/06.
//  Copyright 2020 �ְ�â��. All rights reserved.
//  
#include "operation.h"
/***************************************************************************
 ������ �Լ�
 src1, src2 �� �Է��Ͽ� Q = src1/src2, R = src1%src2�� ����ϴ� �Լ��̴�.
 ����ڰ� �� bigint�� �������� �����Ҷ��� DIV�Լ��� bigint�� �Է��Ѵ�.
 DIV�Լ��� ���ǿ� ���� DIVC�Լ��� ����Ѵ�.
 DIVC�Լ������� DIVCC�Լ��� ����Ѵ�.
 DIVCC�Լ������� pseudo code�� Line 8�� ���꿡�� BinaryLongDiv_2word�Լ��� ����Ѵ�.
 (���� �ڵ�) DIV(&Q, &R, src1, src2);
***************************************************************************/

/******* binary Long Division Algorithm (2-word version) : 2word�� src1�� 1 word�� src2�� ������ �Լ�  *************
Input: A=A1W+A0,B(A1,A0 ��[0,W)
Output: Q such that A=BQ+R (0��R<B)
---------------------------------------------------------------------------------------------------------------
1: (Q,R)��(0,A1) 
2: for j = w-1 downto 0 do
3:      if R �� 2^(w-1) then
4:          (Q,R)��(Q + 2j, 2R + aj - B)
5:      else
6:          R �� 2R + aj
7:          if R �� B then
8:              (Q, R) �� (Q + 2j, R - B) 
9:          end if
10:     end if
11: end for
12: return Q
**************************************************************************************************************/
void BinaryLongDiv_2word(word* Q, const word* src11, const word* src10, const word* src2) // Q�� 1����, src1�� 2����, src2�� 1����
{
    int i;
    word R = *src11;
    *Q = 0;
    for ( i = WORD_BITLEN-1; i >= 0; i--)
    {
        if(R >= (word)1<<(WORD_BITLEN-1))   //R�� ��Ʈ���̰� WORD_BITLEN-1 �̻��ΰ��.
        {
            *Q += (word)1<<i;               //Q����
            R = (R<<1) + get_j_th_bit(*src10,i) - (*src2);
        }
        else
        {
            R = (R<<1) + get_j_th_bit(*src10,i);    //R����
            if(R >= *src2)                          // ���� Q�� �Ѿ�� �� Ȯ��
            {
                *Q += (word)1<<i;
                R -= (*src2);
            }
        }
    }
}


/******************************** DIVCC ***********************************
Input: A, B 
Output: (Q, R) such that A = BQ + R (0 �� R < B, Q �� [0, W)).
---------------------------------------------------------------------------
1: if n = m then
2:      Q ��A_{m-1}/B_{m-1}
3: end if
4: if n = m + 1 then
5:      if A_m = B_{m-1} then
6:          Q �� W ? 1
7:      else 
8:          Q �� (A_{m}W + A_{m-1}) / B_{m-1}
9:      end if
10: end if
11: R �� A - BQ 
12: while R < 0 do 
13:     (Q, R) �� (Q - 1, R + B)
14: end while
15: return (Q, R)
******************************************************************************/
void DIVCC(word* Q, bigint** R, const bigint* src1, const bigint* src2)
{
    bigint* temp = NULL;
    int src1Len = get_wordlen(src1), src2Len = get_wordlen(src2);
    *Q = 0;
    if(src1Len == src2Len)    // ������̰� ���� ���
        *Q = src1->a[src2Len-1]/src2->a[src2Len-1];
    else            // src1Len == src2Len+1
    {
        if(src1->a[src2Len] == src2->a[src2Len-1])
            *Q = BITMASK;
        else
            BinaryLongDiv_2word(Q, &src1->a[src2Len], &src1->a[src2Len-1], &src2->a[src2Len-1]);
    }
    bi_new(&temp, 1, NON_NEGATIVE);
    temp->a[0] = *Q;
    MUL_zzy(&temp, src2);       // temp = src2*Q

    SUB_zxy(R, src1, temp);     // R = src1 - src2*Q
    while(get_sign(*R) == NEGATIVE) // R < 0
    {
        (*Q)--;
        ADD_zzy(R,src2);   // R=R+src2
    }
    bi_delete(&temp);
}

/******************************* DIVC *********************************
Input: A , B 
Output: (Q, R) such that A = BQ + R (0 �� R < B, Q �� [0, W))
-----------------------------------------------------------------------
1: if A < B then
2:      return (0, A)
3: end if
4: Compute k �� Z��0 such that 2^k*B_{m-1} �� [2w-1, 2w)
5: A0, B0 �� 2^k*A, 2^k*B
6: Q0, R0 �� DIVCC(A0, B0)
7: Q, R �� Q0, 2^{-k}*R0
8: return (Q, R)
**********************************************************************/
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
    bi_assign(&src1_temp, src1);    //shift�� ���� �Ҵ�
    bi_assign(&src2_temp, src2);    //shift�� ���� �Ҵ�
    left_shift(src1_temp, k);       // src1_temp = src1 << k
    left_shift(src2_temp, k);       // src2_temp = src2 << k

    DIVCC(Q, R, src1_temp, src2_temp); 
    right_shift(*R,k);              // Q = Q, R = R >> k

    bi_delete(&src1_temp);
    bi_delete(&src2_temp);
}

/******************************** DIV ***********************************
Input: A , B 
Output: (Q, R) such that A = BQ + R (0 �� R < B, Q_j �� [0, W)).
-----------------------------------------------------------------------
1: if B �� 0 then
2:      return INVALID
3: end if
4: if A < B then
5:      return (0, A)
6: end if
7: (Q, R) �� (0, 0) 
8: for i = n - 1 downto 0 do
9:      R �� RW + A_i
10: (Q_i, R) �� DIVC(R, B) 
11: end for
12: return (Q, R)
***************************************************************************/
int DIV(bigint** Q, bigint** R, const bigint* src1, const bigint* src2)
{
    bigint* temp = NULL;
    if(bi_is_zero(src2) == TRUE || get_sign(src2) == NEGATIVE) // src2 < 0 �Ǵ� 
        return INVALID;                     //������ �������� ����
    if(bi_compare(src1,src2) == -1)         // src1 < src2
    {
        bi_set_zero(Q);
        bi_assign(R,src1);                  // ���� 0 �������� src1
        return VALID;
    }

    int k = 0, src1Len = get_wordlen(src1), src2Len = get_wordlen(src2);   // �������� wordlen����
    while(1)
    {
        word mask = src2->a[src2Len-1]>>(WORD_BITLEN-1-k);
        if((mask & 0x1) == 0x1)
            break;                      //mask�� 1�� �ڸ� ã��
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