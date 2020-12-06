//  
//  op_expmod.c
//  Changmin's library
//  
//  Created by �ְ�â�� on 2020/12/06.
//  Copyright 2020 �ְ�â��. All rights reserved.
//  
#include "operation.h"

/***********************************************************************************************
x^n mod N �� ���� ������ �����ϴ� �Լ��̴�. 

������ �Լ��� (bigint** R, const bigint* base, const bigint* power, const int modn)�� �Է����� �޴´�.
�̶� R�� ��µǴ� ������, �� �Լ� ���ο��� ���� ����� �ȴ�. 
base�� x�� �ش��ϴ� ������, ������� ���� �Է¹޴´�. 
power�� n�� �ش��ϴ� ������, ������� ���� �Է¹޴´�. 
modn�� N�� �ش��ϴ� ������, ������� ���� �Է¹޴´�.
������ ������ ������ 3���� �˰����� �����Ѵ�.
    - Left to Right (MODExp_L2R)
    - Right to Left (MODExp_R2L)
    - Montgomery    (MODExp_Montgomery)
(���� �ڵ�) MODExp_L2R(&dst, base, power, M);
(���� �ڵ�) MODExp_R2L(&dst, base, power, M);
(���� �ڵ�) MODExp_Montgomery(&dst, base, power, M);
**************************************************************************************************/

/***************** MODExp_L2R *******************
Input: x and n
Output: x^n
--------------------------------------------------
1: t �� 1
2: for i �� l - 1 downto 0 do
3:      t �� t^2
4:      t �� tx^ni
5: end for
6: return t
**************************************************/

void MODExp_L2R(bigint** dst, const bigint* base, const bigint* power, const bigint* M)
{
    bigint* t = NULL;           //pseudo code���� t
    bigint* tmp1 = NULL;        // t^2�� ������ ����
    bigint* tmp2 = NULL;        // tx^ni�� ������ �Լ�  
    bigint* Q = NULL;
    bigint* R = NULL;
    int ni;                     //���� n�� ���� i��° ��Ʈ

    bi_set_one(&t);                   // t�� 1�� ����
    int len = get_wordlen(power);     // ������ wordlen 

    for (int j = (len * WORD_BITLEN) - 1; j >= 0; j--)
    {
        SQU_zxx(&tmp1, t);                //t^2�� tmp1�� ���� 
        ni = get_jth_bit(power, j);   //������ i��° ��Ʈ Ȯ��
        if (ni == 1)                  //i��° ��Ʈ�� 1�ΰ�� base�� ���� �� t���� 
        {
            MUL_zxy(&tmp2, tmp1, base);
            bi_assign(&t, tmp2);
        }
        else                          //i��° ��Ʈ�� 0�ΰ�� �״�� t ����
        {
            bi_assign(&t, tmp1);
        }
        DIV(&Q, &R, t, M);      //�ܰ谡 ���������� mod M ����
        bi_assign(&t, R);

        
    }
    bi_assign(dst, t);                  //������ ��� dst�� �Ҵ�
    bi_delete(&Q);
    bi_delete(&R);
    bi_delete(&tmp1);             
    bi_delete(&tmp2);
    bi_delete(&t);

}

/*************** MODExp_R2L ***************
Input: x and n
Output: x^n
-----------------------------------------
1: t0, t1 �� 1, x
2: for i �� 0 to l - 1 do
3:      t0 �� t0*t1^ni
4:      t1 �� t1^2
5: end for
6: return t0
********************************************/

void MODExp_R2L(bigint** dst, const bigint* base, const bigint* power, const bigint* M)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* tmp1 = NULL;            //t0*t1 ������ ����
    bigint* tmp2 = NULL;            //t1^2 ������ ����
    bigint* Q = NULL;               //Mod�������� �ʿ��Ѻ���
    bigint* R = NULL;               //mod�������� �ʿ�
    int ni;                         //������ i��° ��Ʈ ����

    bi_set_one(&t0);                //t0�� 1�� ����
    bi_assign(&t1, base);           //t1�� base �� ����

    int len = get_wordlen(power);   //������ wordlen Ȯ��

    for (int j = 0; j < len * WORD_BITLEN; j++)
    {
        ni = get_jth_bit(power, j);  //������ ���� i��° ��Ʈ Ȯ��
        if (ni == 1)                 //i��° ��Ʈ�� 1�̸� to*t1����, �ƴϸ� �״��
        {
            MUL_zxy(&tmp1, t0, t1);
            bi_assign(&t0, tmp1);
        }
        SQU_zxx(&tmp2, t1);               //t1^2�� tmp2�� ����
        bi_assign(&t1, tmp2);

        DIV(&Q, &R, t0, M);            //�ܰ踶�� t0 mod ����. 
        bi_assign(&t0, R);             //R�� mod ���     

        DIV(&Q, &R, t1, M);             //�ܰ踶�� t1 mod ����.
        bi_assign(&t1, R);              //R�� mod ���
        
    }
    bi_assign(dst, t0);             //������� dst�� �Է�.
    bi_delete(&R);
    bi_delete(&Q);
    bi_delete(&tmp1);
    bi_delete(&tmp2);
    bi_delete(&t0);
    bi_delete(&t1);

}

/************** MODExp_Montgomery ****************
Input: x and n 
Output: x^n
--------------------------------------------------
1: t0,t1 ��1,x
2: for i �� l - 1 downto 0 do
3:      t_{1-n_i} �� t0 �� t1
4:      t_{n_i} �� t^2_{n_i}
5: end for 
6: return t0
*************************************************/

void MODExp_Montgomery(bigint** dst, const bigint* base, const bigint* power, const bigint* M)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* tmp1 = NULL;
    bigint* tmp2 = NULL;
    bigint* Q = NULL;
    bigint* R = NULL;
    int ni;

    bi_set_one(&t0);                 //t0�� 1�� ����
    bi_assign(&t1, base);            //t1�� x�� ����

    int len = get_wordlen(power);    // ������ ������� Ȯ��
    for (int j = (len * WORD_BITLEN) - 1; j >= 0; j--)
    {
        ni = get_jth_bit(power, j);
        if (ni == 1)                //���� bit�� 1�̸� t0*t1�� t0��, t1�� ����
        {
            MUL_zxy(&tmp1, t0, t1);  
            bi_assign(&t0, tmp1);
            SQU_zxx(&tmp2, t1);
            bi_assign(&t1, tmp2);
        }
        else                        //���� bit�� 0�̸� t0*t1�� t1��,  t0�� ����
        {
            MUL_zxy(&tmp1, t0, t1);
            bi_assign(&t1, tmp1);
            SQU_zxx(&tmp2, t0);
            bi_assign(&t0, tmp2);
        }

        DIV(&Q, &R, t0, M);  // mod M
        bi_assign(&t0, R);
    
        DIV(&Q, &R, t1, M);  // mod M
        bi_assign(&t1, R);
    }
    bi_assign(dst, t0);  // �������
    bi_delete(&t0);
    bi_delete(&t1);
    bi_delete(&R);
    bi_delete(&Q);
    bi_delete(&tmp1);
    bi_delete(&tmp2);
}