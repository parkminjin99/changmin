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

//========================연산에서 사용자가 실제로 사용하는 함수 LIST =========================
//----------------------------------Addition----------------------------------------------
void ADD_zxy(bigint** dst, const bigint* src1, const bigint* src2);                             // 임의의 두 정수 src1, src2의 덧셈 > dst에 저장 
void ADD_zzy(bigint** dst, const bigint* src);                                                  // 임의의 두 정수 src, dst의 덧셈 > dst에 저장 
//-------------------------------Subtraction----------------------------------------------
void SUB_zxy(bigint** dst, const bigint* src1, const bigint* src2);                             // 임의의 두 정수 src1에서 src2로의 뺄셈  > dst에 저장 
void SUB_zzy(bigint** dst, const bigint* src);                                                  // 임의의 두 정수 dst에서 src로의 뺄셈  > dst에 저장 
//------------------------Multiplication + (KaratsubaMul)---------------------------------
void MUL_zxy(bigint** dst, const bigint* src1, const bigint* src2);                             // 임의의 두 정수 src1, src2의 곱셈 > dst에 저장 
void MUL_zzy(bigint** dst, const bigint* src);                                                  // 임의의 두 정수 src, dst의 곱셈 > dst에 저장 
void KaratsubaMUL(bigint** dst, const bigint* src1, const bigint* src2);                        // 전역변수 KARA_FLAG를 이용하는 karatsuba 곱셈.
//------------------------------Squaring + (KaratsubaSqu)---------------------------------
void SQU_zxx(bigint** dst, const bigint* src);                                                  // 임의의 정수 src의 제곱 > dst에 저장
void KaratsubaSQU(bigint** dst, const bigint* src);                                             // 전역변수 KARA_FLAG를 이용하는 karatsuba 제곱.
//-----------------------------------Division(3 types)------------------------------------
int NaiveDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2);                               // 가장 기본적인 나눗셈 알고리듬 (src1 = src2*Q + R을 만족하는 Q, R 저장)
int BinaryLongDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2);                          // 이진 긴 나눗셈 알고리듬 (src1 = src2*Q + R을 만족하는 Q, R 저장)
int DIV(bigint** Q, bigint** R, const bigint* src1, const bigint* src2);                        // 다중 워드 단위 긴 나눗셈 알고리듬 (src1 = src2*Q + R을 만족하는 Q, R 저장)
//------------------------Modular Exponentiation(3 types)---------------------------------
void MODExp_L2R(bigint** dst, const bigint* base, const bigint* power, const bigint* M);        // left to right 방법을 이용한 modular exponentiation.
void MODExp_R2L(bigint** dst, const bigint* base, const bigint* power, const bigint* M);        // right to left 방법을 이용한 modular exponentiation.
void MODExp_Montgomery(bigint** dst, const bigint* base, const bigint* power, const bigint* M); // Montgomery ladder 방법을 이용한 modular exponentiation.
//============================================================================================



//=========================위의 함수를 구성하는 하위 함수=========================================
void left_shift(bigint* x, int r);      // bigint x를 r비트만큼 왼쪽으로 shift하는 함수
void right_shift(bigint* x, int r);     // bigint x를 r비트만큼 오른쪽으로 shift하는 함수
void reduction_2_r(bigint* x, int r);   // bigint x의 x mod 2^r를 출력하는 함수
void ADD_1word_zxyc(word* dst, word* carry, const word* src1, const word* src2);                // src1, src2, carry를 입력받아 1word에 대한 덧셈 > dst에 저장 
void ADD_1word_zzyc(word* dst, word* carry, const word* src);                                   // src, dst, carry를 입력받아 1word에 대한 덧셈 > dst에 저장 
void ADDC(bigint** dst, const bigint* src1, const bigint* src2);                                // 동일한 부호의 두 정수 src1, src2의 덧셈 > dst에 저장 
void SUB_1word_zxy(word* dst, int* carry, const word* src1, const word* src2);                  // src1, src2, carry를 입력받아 1word에 대한 뺄셈의 절댓값 > dst에 저장 
void SUBC(bigint** dst, const bigint* src1, const bigint* src2);                                // 두 정수 src1, src2 (src1>src2)의 뺄셈 > dst에 저장
void MUL_1word_zxy(word* dst, const word* src1, const word* src2);                              // src1, src2를 입력받아 1word에 대한 곱셈 > dst에 저장 
void schoolbook_MULC(bigint** dst, const bigint* src1, const bigint* src2);                     // 동일한 부호의 두 정수 src1, src2의 곱셈 > dst에 저장
void KaratsubaMUL_Flag(bigint** dst, const bigint* src1, const bigint* src2, const int flag);   // 그때마다 설정한 FLAG를 이용하는 karatsuba 곱셈.
void SQUC_1Word_zxx(word* dst, const word* src);                                                // src를 입력받아 1word에 대한 제곱 > dst에 저장 
void schoolbook_SQUC(bigint** dst, const bigint* src);                                          // 0,-1,1이 아닌 정수 src의 제곱 > dst에 저장 
void KaratsubaSQU_Flag(bigint** dst, const bigint* src, const int flag);                        // 그때마다 설정한 FLAG를 이용하는 karatsuba 제곱.
void BinaryLongDiv_2word(word* Q, const word* src11, const word* src10, const word* src2);      // 이진 긴 나눗셈 알고리듬 (src1이 2word인 경우, src1 = src2*Q + R을 만족하는 Q 저장)
void DIVCC(word* Q, bigint** R, const bigint* src1, const bigint* src2);                        // 0 < src2 <= src1 < src2*W와 MSB(src2)=1을 만족하는 src1,src2의 나눗셈 알고리듬 (src1 = src2*Q + R을 만족하는 Q, R 저장)
void DIVC(word* Q, bigint** R, const bigint* src1, const bigint* src2, const int k);            // 0 <= src1 < src2*W를 만족하는 src1,src2의 나눗셈 알고리듬 (src1 = src2*Q + R을 만족하는 Q, R 저장)
//====================================================================================================
#endif /* operation_h */