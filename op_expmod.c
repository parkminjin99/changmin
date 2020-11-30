//  
//  op_expmod.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"

/*****===================================
다음의 함수는 x^n mod N 에 대한 연산을 진행하는 함수이다.

각각의 함수는 (bigint** R, const bigint* base, const bigint* power, const int modn)를 입력으로 받는다.
이때 R은 출력되는 값으로, 각 함수 내부에서 값을 만들게 된다.
base는 x에 해당하는 값으로, 만들어진 값을 입력받는다.
power는 n에 해당하는 값으로, 만들어진 값을 입력받는다.
modn은 N에 해당하는 값으로, 만들어진 값을 입력받는다.
지수승 연산은 다음의 3가지 알고리듬이 존재한다.
    - Left to Right (L2R)
    - Right to Left (R2L)
    - Montgomery
*********************************/

/***********L2R*************
Input: x and n
Output: x^n
1: t ← 1
2: for i ← l ? 1 downto 0 do
3:      t ← t^2
4:      t ← tx^ni
5: end for
6: return t
**************************/

void L2R(bigint** R, const bigint* base, const bigint* power, const int modn)
{
    bigint* t = NULL;           //pseudo code상의 t
    bigint* tmp1 = NULL;        // t^2를 저장할 변수
    bigint* tmp2 = NULL;        // tx^ni를 저장할 변수  

    int ni;                     //지수의 i번째 비트 저장

    bi_set_one(&t);                   // t를 1로 설정
    int len = get_wordlen(power);     // 지수의 wordlen 확인

    for (int j = (len * WORD_BITLEN) - 1; j >= 0; j--)
    {
        SQU(&tmp1, t);                //t^2를 tmp1에 저장 
        ni = get_jth_bit(power, j);   //지수의 i번째 비트 확인
        if (ni == 1)                  //i번째가 1이면 base를 곱한후 t로 갱신 
        {
            MUL(&tmp2, tmp1, base);
            bi_delete(&t);
            bi_assign(&t, tmp2);
        }
        else                          //i번째가 0이면 그대로 t 갱신
        {
            bi_delete(&t);
            bi_assign(&t, tmp1);
        }
        reduction_2_r(t, modn);       //단계가 끝날때마다 modN 진행

        bi_delete(&tmp1);             //단계 마다 tmp들 삭제.
        bi_delete(&tmp2);
    }
    bi_assign(R, t);                  //마지막 결과를 할당
    bi_delete(&t);

}

/*********R2L************
Input: x and n
Output: x^n
---------------------------
1: t0, t1 ← 1, x
2: for i ← 0 to l ? 1 do
3:      t0 ← t0*t1^ni
4:      t1 ← t1^2
5: end for
6: return t0
***********************/

void R2L(bigint** R, const bigint* base, const bigint* power, const int modn)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* tmp1 = NULL;            //t0*t1 저장할 변수 
    bigint* tmp2 = NULL;            //t1^2 저장할 변수
    int ni;                         //지수의 i번째 비트 저장

    bi_set_one(&t0);                //t0를 1로 설정
    bi_assign(&t1, base);           //t1을 x로 설정

    int len = get_wordlen(power);   //지수의 wordlen 확인

    for (int j = 0; j < len * WORD_BITLEN; j++)
    {
        ni = get_jth_bit(power, j);  //지수의 i번째 비트 확인 
        if (ni == 1)                 //i번째 비트가 1이면 to*t1을 진행 아니면 그대로
        {
            MUL(&tmp1, t0, t1);
            bi_delete(&t0);
            bi_assign(&t0, tmp1);
        }
        SQU(&tmp2, t1);               //t1^2를 tmp2에 저장
        bi_delete(&t1);
        bi_assign(&t1, tmp2);

        reduction_2_r(t0, modn);       //단계가 끝날때마다 modN
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

    bi_set_one(&t0);     //t0를 1로 설정
    bi_assign(&t1, base);  //t1을 x로 설정

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