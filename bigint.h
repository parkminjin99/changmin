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

#include "changmin_library.h"

#define NON_NEGATIVE 0
#define NEGATIVE 1

#define SUCCESS 0
#define FAIL 1

#define TRUE 0
#define FALSE 1

#define VALID 0
#define INVALID 1


void bi_sage_show(const bigint* x, const int base);                 // bigint 구조체에 저장된 값을 sage형식에 맞게 원하는 진수로 출력하는 함수
void bi_show(const bigint* x, const int base);                      // bigint 구조체에 저장된 값을 원하는 진수로 출력하는 함수
void bi_delete(bigint** x);                                         // bigint 구조체의 메모리를 해제하는 함수
int bi_new(bigint** x, int wordlen, int sign);                      // bigint 구조체 메모리 동적할당 함수
int bi_refine(bigint* x);                                           // bigint 구조체 안의 배열에서 0인 상위의 워드를 삭제하는 함수
void bi_zeroize(bigint* x);                                         // bigint 안의 배열을 0으로 초기화하는 함수
void bi_assign(bigint** y, const bigint* x);                        // bigint 구조체를 복사하는 함수
void bi_gen_rand(bigint** x, int sign, int wordlen);                // bigint 구조체를 임의로 생성하는 함수.
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);   // a와 sign 정보를 struct에 저장하기.
void bi_set_by_string(bigint** x, int sign, char* str, word base);  // 문자열로 되어있는 수를 구조체에 입력하는 함수.

int get_wordlen(const bigint* x);                                   // bigint 구조체의 word길이를 나타내는 함수
int get_bitlen(const bigint* x);                                    // bigint 구조체의 bit길이를 나타내는 함수
int get_jth_bit(const bigint* x, const int j);                      // bigint 구조체의 하위 j번째 bit를 나타내는 함수
int get_sign(const bigint* x);                                      // bigint 구조체의 부호를 나타내는 함수
void flip_sign(bigint* x);                                          // bigint 구조체의 부호를 바꾸는 함수

void bi_set_one(bigint** x);                                        // bigint 구조체를 1로 설정하는 함수
void bi_set_zero(bigint** x);                                       // bigint 구조체를 0으로 설정하는 함수
int bi_is_minus_one(const bigint* x);                               // bigint 구조체가 -1인지 확인하는 함수
int bi_is_one(const bigint* x);                                     // bigint 구조체가 1인지 확인하는 함수
int bi_is_zero(const bigint* x);                                    // bigint 구조체가 0인지 확인하는 함수

int bi_compareABS(const bigint* src1, const bigint* src2);          // 두 bigint의 절댓값을 비교하는 함수
int bi_compare(const bigint* src1, const bigint* src2);             // 두 bigint를 비교하는 함수

#endif /* bigint_h */