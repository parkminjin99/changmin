//  
//  op_karatsuba_squ.c
//  Changmin's library
//  
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
//  
#include "operation.h"
/*************KaratsubaSQU*************
 schoolbook ������ ���� ������ karatsubaSQU�� flag�� �̿��Ͽ� ������ ���ȭ�Ѵ�.
 ������ flag�� ���� ���� �ӵ��� �޶����Ƿ� ����ڰ� ���������� kara_flag�� �����Ͽ� ������ �����Ҽ��ְ�,
 ������ flag�� �����ϱ����� KaratsubaSQU_Flag �Լ��� �̿��ؼ�  ������ �����Ѵ�. 
 ���� ����ڴ� karatsubaSQU�Լ����� ����Ͽ� karatsuba���� ����� �����ϴ�.
****************************************
Input: A 
Output: C = A^2 
1: procedure (KaratsubaSQU(A))
2:      if f lag �� WordLen(A) then
3:          return SQUC(A)
4:      end if
5:      l �� (WordLen(A)+1)��1
6:      A1,A0 �� |A| �� lw,|A| mod 2lw
7:      T1, T0 �� KaratsubaSQU(A1), KaratsubaSQU(A0)
8:      R��(T1 ��2lw)+T0
9:      S �� KaratsubaMUL(A1, A0)
10:     S �� S��(lw+1)
11:     R �� ADDC(R, S)
12:     return R
13: end procedure
**************************************/

void KaratsubaSQU(bigint** dst, const bigint* src)
{
    KaratsubaSQU_Flag(dst, src, KARA_FLAG);
}

void KaratsubaSQU_Flag(bigint** dst, const bigint* src, const int flag)
{
    if (flag >= get_wordlen(src))
    {
        SQU_zxx(dst, src);          // ������ flag���� �۾����� schoolbook squ
        return;
    }
    int l = (get_wordlen(src) + 1) >> 1;  

    bigint* A1 = NULL;      //A�� ���� ��
    bigint* A0 = NULL;      //A�� ���� ��
    bigint* t1 = NULL;      
    bigint* t0 = NULL;
    bigint* R = NULL;
    bigint* S = NULL;

    bi_assign(&A1, src);     //A�� 2�� ����ϹǷ� 2�� ����
    bi_assign(&A0, src);
    right_shift(A1, l * WORD_BITLEN);  reduction_2_r(A0, l * WORD_BITLEN);   //������ A�� shift, reduction�Ͽ� A1,A0����

    KaratsubaSQU(&t1, A1);   // A1 karatsubaSQU
    KaratsubaSQU(&t0, A0);   // A0 karatsubaSQU

    left_shift(t1, 2 * l * WORD_BITLEN);  // t1�� leftshift
    ADD_zxy(&R, t1, t0);                  // t1+t0 �� R�� ����
    KaratsubaMUL(&S, A1, A0);             // A1,A0 MUL

    left_shift(S, l * WORD_BITLEN + 1);   // S leftshift
    ADD_zxy(dst, R, S);                   //R+S�� ���� �����

    bi_delete(&A1);
    bi_delete(&A0);
    bi_delete(&t1);
    bi_delete(&t0);
    bi_delete(&R);
    bi_delete(&S);

}