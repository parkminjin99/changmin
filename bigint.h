#pragma once
//
//  bigint.h
//  Changmin's library
//
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//

#ifndef bigint_h
#define bigint_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WORD_BITLEN 8

#if WORD_BITLEN == 64
typedef unsigned long long word;
#define HALF_WORDBIT 0x00000000ffffffff
#define BITMASK 0xffffffffffffffff
#elif WORD_BITLEN == 32
typedef unsigned int word;
#define HALF_WORDBIT 0x0000ffff
#define BITMASK 0xffffffff
#else // WORD_BITLEN == 8
typedef unsigned char word;
#define HALF_WORDBIT 0x0f
#define BITMASK 0xff
#endif

#define NON_NEGATIVE 0
#define NEGATIVE 1

#define SUCCESS 2
#define FAIL -2

#define TRUE 3
#define FALSE -3

#define VALID 4
#define INVALID -4

typedef struct {
    int sign;
    int wordlen;
    word* a;
} bigint;
void bi_sage_show(const bigint* x, const int base);
void bi_show(const bigint* x, const int base);
void bi_delete(bigint** x);                                     // bigint 구조체의 메모리를 해제하는 함수
int bi_new(bigint** x, int wordlen, int sign);                  // bigint 구조체 메모리 동적할당 함수
int bi_refine(bigint* x);                                       // bigint 구조체 안의 배열에서 0인 상위의 워드를 삭제하는 함수
void bi_zeroize(bigint* x);                                     // bigint 안의 배열을 0으로 초기화하는 함수
void bi_assign(bigint** y, const bigint* x);                    // bigint 구조체를 복사하는 함수
void bi_gen_rand(bigint** x, int sign, int wordlen);
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);  // a와 sign 정보를 struct에 저장하기.
void bi_set_by_string(bigint** x, int sign, char* str, word base);

int get_wordlen(const bigint* x);
int get_bitlen(const bigint* x);
int get_jth_bit(const bigint* x, const int j);
int get_sign(const bigint* x);
void flip_sign(bigint* x);

void bi_set_one(bigint** x);
void bi_set_zero(bigint** x);
int bi_is_minus_one(const bigint* x);
int bi_is_one(const bigint* x);
int bi_is_zero(const bigint* x);

int bi_compareABS(const bigint* src1, const bigint* src2);      // 두 bigint의 절댓값을 비교하는 함수
int bi_compare(const bigint* src1, const bigint* src2);         // 두 bigint를 비교하는 함수

#endif /* bigint_h */