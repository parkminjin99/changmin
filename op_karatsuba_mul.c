//  
//  op_karatsuba_mul.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"

void KaratsubaMUL(bigint** dst, const bigint* src1, const bigint* src2)
{
    KaratsubaMUL_Flag(dst, src1, src2, KARA_FLAG);
}

void KaratsubaMUL_Flag(bigint** dst, const bigint* src1, const bigint* src2, const int flag)
{
    int temp = min(get_wordlen(src1), get_wordlen(src2));
    if (flag >= temp)  // 설정 길이보다 wordlen이 작아지면 일반 mul
    {
        MUL_zxy(dst, src1, src2);
        return;
    }
    int l;
    bigint* aco0 = NULL;    //a 하위 절반
    bigint* aco1 = NULL;    //a 상위 절반
    bigint* bco0 = NULL;    //b 하위 절반
    bigint* bco1 = NULL;    //b 상위 절반
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* tco1 = NULL;
    bigint* R = NULL;
    bigint* S0 = NULL;
    bigint* S1 = NULL;
    bigint* S = NULL;

    l = (max(get_wordlen(src1), get_wordlen(src2)) + 1) >> 1;    // 전체 길이 절반만큼씩 나누기 위해 l 계산으로
    bi_assign(&aco0, src1);         bi_assign(&aco1, src1);    // a를 두개 써야되서 2개로 할당
    bi_assign(&bco0, src2);         bi_assign(&bco1, src2);       //b를 두개 써야되서 2개로 할당

    right_shift(aco1, l * WORD_BITLEN);     reduction_2_r(aco0, l * WORD_BITLEN); // 복사한 a를 각각 shift랑 reduct(a1, a0 만들기)
    right_shift(bco1, l * WORD_BITLEN);     reduction_2_r(bco0, l * WORD_BITLEN);  // 복사한 B를 각각 shift랑 reduct(b1,b0 만들기)

    KaratsubaMUL_Flag(&t1, aco1, bco1, flag); //a1,b1으로 karatsuba 해서 t1생성
    KaratsubaMUL_Flag(&t0, aco0, bco0, flag); //a0,b0로 karatsuba 해서 t0생성

    bi_assign(&tco1, t1);  // t1을 다시 써야해서 우선 복사
    left_shift(tco1, 2 * l * WORD_BITLEN); // tco1 << 2lw

    ADD_zxy(&R, tco1, t0); //tco1과 t0 더하여 R 생성 
    SUB_zxy(&S1, aco0, aco1); // a0와 a1을 빼서 s1에 할당
    SUB_zxy(&S0, bco1, bco0);  // b0와 b1 빼서 s0에 할당

    int temp1 = get_sign(S1), temp0 = get_sign(S0); //s의 부호 결정을 위함

    if (get_sign(S1) == NEGATIVE)
        flip_sign(S1);
    if (get_sign(S0) == NEGATIVE)
        flip_sign(S0);
        
    KaratsubaMUL_Flag(&S, S1, S0, flag);
    if (temp1 != temp0)
        flip_sign(S);

    ADD_zzy(&S, t1);                      //  s와 t1의 합을 s로
    ADD_zzy(&S, t0);                      //  s와 t0의 합을 s로
    left_shift(S, l * WORD_BITLEN);    //  s shift
    ADD_zxy(dst, R, S);                    //  r과 s합을 dst로

    //*************** 사용했던 구조체 할당 해제.
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