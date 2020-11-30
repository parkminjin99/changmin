//  
//  op_expmod.c
//  Changmin's library
//  
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
//  
#include "operation.h"

/*****===================================
������ �Լ��� x^n mod N �� ���� ������ �����ϴ� �Լ��̴�.

������ �Լ��� (bigint** R, const bigint* base, const bigint* power, const int modn)�� �Է����� �޴´�.
�̶� R�� ��µǴ� ������, �� �Լ� ���ο��� ���� ����� �ȴ�.
base�� x�� �ش��ϴ� ������, ������� ���� �Է¹޴´�.
power�� n�� �ش��ϴ� ������, ������� ���� �Է¹޴´�.
modn�� N�� �ش��ϴ� ������, ������� ���� �Է¹޴´�.
������ ������ ������ 3���� �˰����� �����Ѵ�.
    - Left to Right (L2R)
    - Right to Left (R2L)
    - Montgomery
*********************************/

/***********L2R*************
Input: x and n
Output: x^n
1: t �� 1
2: for i �� l ? 1 downto 0 do
3:      t �� t^2
4:      t �� tx^ni
5: end for
6: return t
**************************/

void L2R(bigint** R, const bigint* base, const bigint* power, const int modn)
{
    bigint* t = NULL;           //pseudo code���� t
    bigint* tmp1 = NULL;        // t^2�� ������ ����
    bigint* tmp2 = NULL;        // tx^ni�� ������ ����  

    int ni;                     //������ i��° ��Ʈ ����

    bi_set_one(&t);                   // t�� 1�� ����
    int len = get_wordlen(power);     // ������ wordlen Ȯ��

    for (int j = (len * WORD_BITLEN) - 1; j >= 0; j--)
    {
        SQU(&tmp1, t);                //t^2�� tmp1�� ���� 
        ni = get_jth_bit(power, j);   //������ i��° ��Ʈ Ȯ��
        if (ni == 1)                  //i��°�� 1�̸� base�� ������ t�� ���� 
        {
            MUL(&tmp2, tmp1, base);
            bi_delete(&t);
            bi_assign(&t, tmp2);
        }
        else                          //i��°�� 0�̸� �״�� t ����
        {
            bi_delete(&t);
            bi_assign(&t, tmp1);
        }
        reduction_2_r(t, modn);       //�ܰ谡 ���������� modN ����

        bi_delete(&tmp1);             //�ܰ� ���� tmp�� ����.
        bi_delete(&tmp2);
    }
    bi_assign(R, t);                  //������ ����� �Ҵ�
    bi_delete(&t);

}

/*********R2L************
Input: x and n
Output: x^n
---------------------------
1: t0, t1 �� 1, x
2: for i �� 0 to l ? 1 do
3:      t0 �� t0*t1^ni
4:      t1 �� t1^2
5: end for
6: return t0
***********************/

void R2L(bigint** R, const bigint* base, const bigint* power, const int modn)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* tmp1 = NULL;            //t0*t1 ������ ���� 
    bigint* tmp2 = NULL;            //t1^2 ������ ����
    int ni;                         //������ i��° ��Ʈ ����

    bi_set_one(&t0);                //t0�� 1�� ����
    bi_assign(&t1, base);           //t1�� x�� ����

    int len = get_wordlen(power);   //������ wordlen Ȯ��

    for (int j = 0; j < len * WORD_BITLEN; j++)
    {
        ni = get_jth_bit(power, j);  //������ i��° ��Ʈ Ȯ�� 
        if (ni == 1)                 //i��° ��Ʈ�� 1�̸� to*t1�� ���� �ƴϸ� �״��
        {
            MUL(&tmp1, t0, t1);
            bi_delete(&t0);
            bi_assign(&t0, tmp1);
        }
        SQU(&tmp2, t1);               //t1^2�� tmp2�� ����
        bi_delete(&t1);
        bi_assign(&t1, tmp2);

        reduction_2_r(t0, modn);       //�ܰ谡 ���������� modN
        reduction_2_r(t1, modn);

        bi_delete(&tmp1);
        bi_delete(&tmp2);
    }
    bi_assign(R, t0);
    bi_delete(&t0);
    bi_delete(&t1);

}

void Montgomery(bigint** R, const bigint* base, const bigint* power, const int modn)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* tmp1 = NULL;
    bigint* tmp2 = NULL;
    int ni;

    bi_set_one(&t0);     //t0�� 1�� ����
    bi_assign(&t1, base);  //t1�� x�� ����

    int len = get_wordlen(power);
    for (int j = (len * WORD_BITLEN) - 1; j >= 0; j--)
    {
        ni = get_jth_bit(power, j);
        if (ni == 1)
        {
            MUL(&tmp1, t0, t1);
            bi_delete(&t0);
            bi_assign(&t0, tmp1);
            SQU(&tmp2, t1);
            bi_delete(&t1);
            bi_assign(&t1, tmp2);
        }
        else
        {
            MUL(&tmp1, t0, t1);
            bi_delete(&t1);
            bi_assign(&t1, tmp1);
            SQU(&tmp2, t0);
            bi_delete(&t0);
            bi_assign(&t0, tmp2);
        }

        reduction_2_r(t0, modn);
        reduction_2_r(t1, modn);

        bi_delete(&tmp1);
        bi_delete(&tmp2);
    }
    bi_assign(R, t0);
    bi_delete(&t0);
    bi_delete(&t1);

}