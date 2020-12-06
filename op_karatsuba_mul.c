//  
//  op_karatsuba_mul.c
//  Changmin's library
//  
//  Created by �ְ�â�� on 2020/12/06.
//  Copyright 2020 �ְ�â��. All rights reserved.
//  
#include "operation.h"
/*************************** KaratsubaMUL ***************************************
 schoolbook ������ ���� ������ karatsubaMUL�� flag�� �̿��Ͽ� ������ ���ȭ�Ѵ�.
 ������ flag�� ���� ���� �ӵ��� �޶����Ƿ� ����ڰ� ���������� kara_flag�� �����Ͽ� ������ �����Ҽ��ְ�,
 ������ flag�� �����ϱ����� KaratsubaMUL_Flag �Լ��� �̿��ؼ� test.c ���Ͽ��� ������ �����Ѵ�. 
 ���� ����ڴ� karatsubaMUL�Լ����� ����Ͽ� karatsuba���� ����� �����ϴ�.
(���� �ڵ�) KaratsubaMUL(&dst, src1, src2);
********************************************************************************
Input: A,B
Output: C=AB
---------------------------------------------------------------------------------
1: procedure (KaratsubaMUL(A, B))
2:      if flag �� min(WordLen(A), WordLen(B)) then
3:           return MUL(A, B)
4:      end if
5:      l �� (max(WordLen(A), WordLen(B)) + 1) �� 1
6:      A1,A0 ��A��lw,Amod2lw
7:      B1,B0 ��B��lw,Bmod2lw
8:      T1,T0 �� MULCKaratsuba(A1,B1),MULCKaratsuba(A0,B0)
9:      R��(T1 ��2lw)+T0
10:     S1,S0 ��SUB(A0,A1),SUB(B1,B0)
11:     S �� (-1)Sign(S1)-Sign(S2)MULCKaratsuba(|S1|, |S0|)
12:     S �� ADD(S, T1)
13:     S �� ADD(S, T0)
14:     S �� S �� lw
15:     R �� ADD(R, S)
16:     return R
17: end procedure
*********************************************************************************/

void KaratsubaMUL(bigint** dst, const bigint* src1, const bigint* src2)   
{
    KaratsubaMUL_Flag(dst, src1, src2, KARA_FLAG);   //flag�� ���������� ������ �� ���.
}

void KaratsubaMUL_Flag(bigint** dst, const bigint* src1, const bigint* src2, const int flag)
{
    int temp = min(get_wordlen(src1), get_wordlen(src2));
    if (flag >= temp)  // ���� ���̺��� wordlen�� �۾����� �Ϲ� mul
    {
        MUL_zxy(dst, src1, src2);
        return;
    }
    int l;
    bigint* aco0 = NULL;    //a ���� ����
    bigint* aco1 = NULL;    //a ���� ����
    bigint* bco0 = NULL;    //b ���� ����
    bigint* bco1 = NULL;    //b ���� ����
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* tco1 = NULL;
    bigint* R = NULL;
    bigint* S0 = NULL;
    bigint* S1 = NULL;
    bigint* S = NULL;

    l = (max(get_wordlen(src1), get_wordlen(src2)) + 1) >> 1;    // ��ü ���� ���ݸ�ŭ�� ������ ���� l �������
    bi_assign(&aco0, src1);         bi_assign(&aco1, src1);       // a�� �ΰ� ��ߵǼ� 2���� �Ҵ�
    bi_assign(&bco0, src2);         bi_assign(&bco1, src2);       //b�� �ΰ� ��ߵǼ� 2���� �Ҵ�

    right_shift(aco1, l * WORD_BITLEN);     reduction_2_r(aco0, l * WORD_BITLEN); // ������ a�� ���� shift�� reduct(a1, a0 �����)
    right_shift(bco1, l * WORD_BITLEN);     reduction_2_r(bco0, l * WORD_BITLEN);  // ������ B�� ���� shift�� reduct(b1,b0 �����)

    KaratsubaMUL_Flag(&t1, aco1, bco1, flag); //a1,b1���� karatsuba �ؼ� t1����
    KaratsubaMUL_Flag(&t0, aco0, bco0, flag); //a0,b0�� karatsuba �ؼ� t0����

    bi_assign(&tco1, t1);  // t1�� �ٽ� ����ؼ� �켱 ����
    left_shift(tco1, 2 * l * WORD_BITLEN); // tco1 << 2lw

    ADD_zxy(&R, tco1, t0); //tco1�� t0 ���Ͽ� R ���� 
    SUB_zxy(&S1, aco0, aco1); // a0�� a1�� ���� s1�� �Ҵ�
    SUB_zxy(&S0, bco1, bco0);  // b0�� b1 ���� s0�� �Ҵ�

    int temp1 = get_sign(S1), temp0 = get_sign(S0); //s�� ��ȣ ������ ����

    if (get_sign(S1) == NEGATIVE)
        flip_sign(S1);
    if (get_sign(S0) == NEGATIVE)
        flip_sign(S0);
        
    KaratsubaMUL_Flag(&S, S1, S0, flag);
    if (temp1 != temp0)
        flip_sign(S);

    ADD_zzy(&S, t1);                      //  s�� t1�� ���� s��
    ADD_zzy(&S, t0);                      //  s�� t0�� ���� s��
    left_shift(S, l * WORD_BITLEN);    //  s shift
    ADD_zxy(dst, R, S);                    //  r�� s���� dst��

    //*************** ����ߴ� ����ü �Ҵ� ����.
    bi_delete(&aco0);
    bi_delete(&aco1);
    bi_delete(&bco0);
    bi_delete(&bco1);
    bi_delete(&t0);
    bi_delete(&t1);
    bi_delete(&R);
    bi_delete(&S0);
    bi_delete(&S1);
    bi_delete(&S);
    bi_delete(&tco1);
}