//  
//  op_karatsuba_squ.c
//  Changmin's library
//  
//  Created by 占쌍곤옙창占쏙옙 on 2020/11/09.
//  Copyright 2020 占쌍곤옙창占쏙옙. All rights reserved.
//  
#include "operation.h"
/*************KaratsubaSQU*************
 schoolbook 제곱의 발전 형태인 karatsubaSQU은 flag를 이용하여 제곱을 고속화한다.
 하지만 flag에 따라 연산 속도가 달라지므로 사용자가 전역변수인 kara_flag를 설정하여 과정을 진행할수있고,
 최적의 flag를 제안하기위해 KaratsubaSQU_Flag 함수를 이용해서  실험을 진행한다. 
 따라서 사용자는 karatsubaSQU함수만을 사용하여 karatsuba제곱 사용이 가능하다.
****************************************
Input: A 
Output: C = A^2 
1: procedure (KaratsubaSQU(A))
2:      if f lag ≥ WordLen(A) then
3:          return SQUC(A)
4:      end if
5:      l ← (WordLen(A)+1)≫1
6:      A1,A0 ← |A| ≫ lw,|A| mod 2lw
7:      T1, T0 ← KaratsubaSQU(A1), KaratsubaSQU(A0)
8:      R←(T1 ≪2lw)+T0
9:      S ← KaratsubaMUL(A1, A0)
10:     S ← S≪(lw+1)
11:     R ← ADDC(R, S)
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
        SQU_zxx(dst, src);          // 설정한 flag보다 작아지면 schoolbook squ
        return;
    }
    int l = (get_wordlen(src) + 1) >> 1;  

    bigint* A1 = NULL;      //A의 상위 반
    bigint* A0 = NULL;      //A의 하위 반
    bigint* t1 = NULL;      
    bigint* t0 = NULL;
    bigint* R = NULL;
    bigint* S = NULL;

    bi_assign(&A1, src);     //A를 2번 사용하므로 2개 복사
    bi_assign(&A0, src);
    right_shift(A1, l * WORD_BITLEN);  reduction_2_r(A0, l * WORD_BITLEN);   //복사한 A를 shift, reduction하여 A1,A0생성

    KaratsubaSQU(&t1, A1);   // A1 karatsubaSQU
    KaratsubaSQU(&t0, A0);   // A0 karatsubaSQU

    left_shift(t1, 2 * l * WORD_BITLEN);  // t1을 leftshift
    ADD_zxy(&R, t1, t0);                  // t1+t0 를 R에 저장
    KaratsubaMUL(&S, A1, A0);             // A1,A0 MUL

    left_shift(S, l * WORD_BITLEN + 1);   // S leftshift
    ADD_zxy(dst, R, S);                   //R+S를 최종 결과로

    bi_delete(&A1);
    bi_delete(&A0);
    bi_delete(&t1);
    bi_delete(&t0);
    bi_delete(&R);
    bi_delete(&S);

}