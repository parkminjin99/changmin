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
#define min(x,y)( (x)<(y)?(x):(y) )
#define get_j_th_bit(x,j) ((x>>j)&0x1)


void left_shift(bigint* x, int r);      // bigint x를 r비트만큼 왼쪽으로 shift하는 함수
void right_shift(bigint* x, int r);     // bigint x를 r비트만큼 오른쪽으로 shift하는 함수
void reduction_2_r(bigint* x, int r);   // bigint x의 x mod 2^r를 출력하는 함수

void ADD_ABc(word* dst, word* carry, const word* src1, const word* src2);
void ADDC(bigint** dst, const bigint* src1, const bigint* src2);
//void ADDC2(bigint* dst, const bigint* src);
void ADD(bigint** dst, const bigint* src1, const bigint* src2);
void ADD2(bigint** dst, const bigint* src);

void subABS(word* dst, int* carry, const word* src1, const word* src2);    // src1과 src2, carry를 입력받아 1word에 대한 뺄셈의 절댓값을 출력
void subc(bigint** dst, const bigint* src1, const bigint* src2);    // src1>src2로 입력받아 둘의 차를 dst에 저장
void SUB(bigint** dst, const bigint* src1, const bigint* src2);   //src1 과 src2를 비교하여 subc로 이동시키는 함수
void Karatsuba(bigint** dst, const bigint* src1, const bigint* src2, const int flag);

void MUL_1Word(word* dst, const word* src1, const word* src2);
void MULC(bigint** dst, const bigint* src1, const bigint* src2);
void MUL(bigint** dst, const bigint* src1, const bigint* src2);

void SQUC_1Word(word* dst, const word* src);
void SQUC(bigint** dst, const bigint* src);
void SQU(bigint** dst, const bigint* src);
void SQUCKaratsuba(bigint** dst, const bigint* src, const int flag);

void LDA_2word(word* Q, const word* src11, const word* src10, const word* src2);
void DIVCC(word* Q, bigint** R, const bigint* src1, const bigint* src2);
void DIVC(word* Q, bigint** R, const bigint* src1, const bigint* src2);
int DIV(bigint** Q, bigint** R, const bigint* src1, const bigint* src2);

void L2R(bigint** R, const bigint* base, const bigint* power, const int modn);
void R2L(bigint** R, const bigint* base, const bigint* power, const int modn);
void Montgomery(bigint** R, const bigint* base, const bigint* power, const int modn);

#endif /* operation_h */