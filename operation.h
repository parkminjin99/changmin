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

#include "changmin_library.h"

#define max(x,y)( (x)>(y)?(x):(y) )
#define min(x,y)( (x)<(y)?(x):(y) )
#define get_j_th_bit(x,j) ((x>>j)&0x1)


void left_shift(bigint* x, int r);      // bigint x를 r비트만큼 왼쪽으로 shift하는 함수
void right_shift(bigint* x, int r);     // bigint x를 r비트만큼 오른쪽으로 shift하는 함수
void reduction_2_r(bigint* x, int r);   // bigint x의 x mod 2^r를 출력하는 함수

void ADD_1word_zxyc(word* dst, word* carry, const word* src1, const word* src2);
void ADD_1word_zzyc(word* dst, word* carry, const word* src);
void ADDC(bigint** dst, const bigint* src1, const bigint* src2);
void ADD_zxy(bigint** dst, const bigint* src1, const bigint* src2);
void ADD_zzy(bigint** dst, const bigint* src);

void SUB_1word_zxy(word* dst, int* carry, const word* src1, const word* src2);    // src1과 src2, carry를 입력받아 1word에 대한 뺄셈의 절댓값을 출력
void SUBC(bigint** dst, const bigint* src1, const bigint* src2);     //src1>src2로 입력받아 둘의 차를 dst에 저장
void SUB_zxy(bigint** dst, const bigint* src1, const bigint* src2);  //src1과 src2를 비교하여 subc로 이동시키는 함수
void SUB_zzy(bigint** dst, const bigint* src);                       //dst-src를 dst에 입력하는 함수.

void KaratsubaMUL(bigint** dst, const bigint* src1, const bigint* src2); //전역변수 KARA_FLAG를 이용하는 karatsuba 곱셈.
void KaratsubaMUL_Flag(bigint** dst, const bigint* src1, const bigint* src2, const int flag);  //그때마다 설정한 FLAG를 이용하는 karatsuba 곱셈.

void MUL_1word_zxy(word* dst, const word* src1, const word* src2);  
void schoolbook_MULC(bigint** dst, const bigint* src1, const bigint* src2);
void MUL_zxy(bigint** dst, const bigint* src1, const bigint* src2);
void MUL_zzy(bigint** dst, const bigint* src);

void SQUC_1Word_zxx(word* dst, const word* src);
void SQUC(bigint** dst, const bigint* src);
void SQU_zxx(bigint** dst, const bigint* src);

void KaratsubaSQU(bigint** dst, const bigint* src);                         //전역변수 KARA_FLAG를 이용하는 karatsuba 제곱.
void KaratsubaSQU_Flag(bigint** dst, const bigint* src, const int flag);    //그때마다 설정한 FLAG를 이용하는 karatsuba 제곱.

int NaiveDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2);      
int BinaryLongDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2);
void BinaryLongDiv_2word(word* Q, const word* src11, const word* src10, const word* src2);
void DIVCC(word* Q, bigint** R, const bigint* src1, const bigint* src2); 
void DIVC(word* Q, bigint** R, const bigint* src1, const bigint* src2, const int k);
int DIV(bigint** Q, bigint** R, const bigint* src1, const bigint* src2);

void MODExp_L2R(bigint** dst, const bigint* base, const bigint* power, const bigint* M); //left to right 방법을 이용한 modular exponentiation.
void MODExp_R2L(bigint** dst, const bigint* base, const bigint* power, const bigint* M); //right to left 방법을 이용한 modular exponentiation.
void MODExp_Montgomery(bigint** dst, const bigint* base, const bigint* power, const bigint* M); //Montgomery ladder 방법을 이용한 modular exponentiation.

#endif /* operation_h */