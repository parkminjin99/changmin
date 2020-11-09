#pragma once
//
//  operation.h
//  Changmin's library
//
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//

#ifndef operation_h
#define operation_h

#include <stdio.h>
#include "bigint.h"
#include "array.h"

#define max(x,y)( (x)>(y)?(x):(y) )


void left_shift(bigint* x, int r);      // bigint x를 r비트만큼 왼쪽으로 shift하는 함수
void right_shift(bigint* x, int r);     // bigint x를 r비트만큼 오른쪽으로 shift하는 함수
void reduction_2_r(bigint* x, int r);   // bigint x의 x mod 2^r를 출력하는 함수

void ADD_ABc(word* dst, word* carry, const word* src1, const word* src2);
void ADDC(bigint** dst, const bigint* src1, const bigint* src2);
void ADDC2(bigint* dst, const bigint* src);
void ADD(bigint** dst, const bigint* src1, const bigint* src2);
void subABS(word* dst, int* carry, const word src1, const word src2);
void subc(bigint** z, bigint* x, bigint* y);
void SUB(bigint** z, bigint* x, bigint* y);

void MUL_1Word(word* dst, const word* src1, const word* src2);
void MULC(bigint** dst, const bigint* src1, const bigint* src2);
void MUL(bigint** dst, const bigint* src1, const bigint* src2);

void SQUC_1Word(word* dst, const word* src);
void SQUC(bigint** dst, const bigint* src);
void SQU(bigint** dst, const bigint* src);

#endif /* operation_h */