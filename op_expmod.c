//  
//  op_expmod.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/12/06.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"

/***********************************************************************************************
x^n mod N 에 대한 연산을 진행하는 함수이다. 

각각의 함수는 (bigint** R, const bigint* base, const bigint* power, const int modn)를 입력으로 받는다.
이때 R은 출력되는 값으로, 각 함수 내부에서 값을 만들게 된다. 
base는 x에 해당하는 값으로, 만들어진 값을 입력받는다. 
power는 n에 해당하는 값으로, 만들어진 값을 입력받는다. 
modn은 N에 해당하는 값으로, 만들어진 값을 입력받는다.
지수승 연산은 다음의 3가지 알고리듬이 존재한다.
    - Left to Right (MODExp_L2R)
    - Right to Left (MODExp_R2L)
    - Montgomery    (MODExp_Montgomery)
(예제 코드) MODExp_L2R(&dst, base, power, M);
(예제 코드) MODExp_R2L(&dst, base, power, M);
(예제 코드) MODExp_Montgomery(&dst, base, power, M);
**************************************************************************************************/

/***************** MODExp_L2R *******************
Input: x and n
Output: x^n
--------------------------------------------------
1: t ← 1
2: for i ← l - 1 downto 0 do
3:      t ← t^2
4:      t ← tx^ni
5: end for
6: return t
**************************************************/

void MODExp_L2R(bigint** dst, const bigint* base, const bigint* power, const bigint* M)
{
    bigint* t = NULL;           //pseudo code상의 t
    bigint* tmp1 = NULL;        // t^2를 저장할 변수
    bigint* tmp2 = NULL;        // tx^ni를 저장할 함수  
    bigint* Q = NULL;
    bigint* R = NULL;
    int ni;                     //지수 n의 하위 i번째 비트

    bi_set_one(&t);                   // t를 1로 설정
    int len = get_wordlen(power);     // 지수의 wordlen 

    for (int j = (len * WORD_BITLEN) - 1; j >= 0; j--)
    {
        SQU_zxx(&tmp1, t);                //t^2를 tmp1에 저장 
        ni = get_jth_bit(power, j);   //지수의 i번째 비트 확인
        if (ni == 1)                  //i번째 비트가 1인경우 base를 곱한 후 t갱신 
        {
            MUL_zxy(&tmp2, tmp1, base);
            bi_assign(&t, tmp2);
        }
        else                          //i번째 비트가 0인경우 그대로 t 갱신
        {
            bi_assign(&t, tmp1);
        }
        DIV(&Q, &R, t, M);      //단계가 끝날때마다 mod M 진행
        bi_assign(&t, R);

        
    }
    bi_assign(dst, t);                  //마지막 결과 dst에 할당
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
1: t0, t1 ← 1, x
2: for i ← 0 to l - 1 do
3:      t0 ← t0*t1^ni
4:      t1 ← t1^2
5: end for
6: return t0
********************************************/

void MODExp_R2L(bigint** dst, const bigint* base, const bigint* power, const bigint* M)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* tmp1 = NULL;            //t0*t1 저장할 변수
    bigint* tmp2 = NULL;            //t1^2 저장할 변수
    bigint* Q = NULL;               //Mod과정에서 필요한변수
    bigint* R = NULL;               //mod과정에서 필요
    int ni;                         //지수의 i번째 비트 저장

    bi_set_one(&t0);                //t0를 1로 설정
    bi_assign(&t1, base);           //t1를 base 로 설정

    int len = get_wordlen(power);   //지수의 wordlen 확인

    for (int j = 0; j < len * WORD_BITLEN; j++)
    {
        ni = get_jth_bit(power, j);  //지수의 하위 i번째 비트 확인
        if (ni == 1)                 //i번째 비트가 1이면 to*t1진행, 아니면 그대로
        {
            MUL_zxy(&tmp1, t0, t1);
            bi_assign(&t0, tmp1);
        }
        SQU_zxx(&tmp2, t1);               //t1^2를 tmp2에 저장
        bi_assign(&t1, tmp2);

        DIV(&Q, &R, t0, M);            //단계마다 t0 mod 진행. 
        bi_assign(&t0, R);             //R이 mod 결과     

        DIV(&Q, &R, t1, M);             //단계마다 t1 mod 진행.
        bi_assign(&t1, R);              //R이 mod 결과
        
    }
    bi_assign(dst, t0);             //최종결과 dst로 입력.
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
1: t0,t1 ←1,x
2: for i ← l - 1 downto 0 do
3:      t_{1-n_i} ← t0 × t1
4:      t_{n_i} ← t^2_{n_i}
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

    bi_set_one(&t0);                 //t0를 1로 설정
    bi_assign(&t1, base);            //t1을 x로 설정

    int len = get_wordlen(power);    // 지수의 워드길이 확인
    for (int j = (len * WORD_BITLEN) - 1; j >= 0; j--)
    {
        ni = get_jth_bit(power, j);
        if (ni == 1)                //지수 bit가 1이면 t0*t1을 t0로, t1은 제곱
        {
            MUL_zxy(&tmp1, t0, t1);  
            bi_assign(&t0, tmp1);
            SQU_zxx(&tmp2, t1);
            bi_assign(&t1, tmp2);
        }
        else                        //지수 bit가 0이면 t0*t1을 t1로,  t0는 제곱
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
    bi_assign(dst, t0);  // 최종결과
    bi_delete(&t0);
    bi_delete(&t1);
    bi_delete(&R);
    bi_delete(&Q);
    bi_delete(&tmp1);
    bi_delete(&tmp2);
}