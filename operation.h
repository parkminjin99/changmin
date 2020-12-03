#pragma once
//
//  operation.h
//  Changmin's library
//
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
//

#ifndef operation_h
#define operation_h

#include "changmin_library.h"

#define max(x,y)( (x)>(y)?(x):(y) )
#define min(x,y)( (x)<(y)?(x):(y) )
#define get_j_th_bit(x,j) ((x>>j)&0x1)


void left_shift(bigint* x, int r);      // bigint x�� r��Ʈ��ŭ �������� shift�ϴ� �Լ�
void right_shift(bigint* x, int r);     // bigint x�� r��Ʈ��ŭ ���������� shift�ϴ� �Լ�
void reduction_2_r(bigint* x, int r);   // bigint x�� x mod 2^r�� ����ϴ� �Լ�

void ADD_1word_zxyc(word* dst, word* carry, const word* src1, const word* src2);
void ADD_1word_zzyc(word* dst, word* carry, const word* src);
void ADDC(bigint** dst, const bigint* src1, const bigint* src2);
void ADD_zxy(bigint** dst, const bigint* src1, const bigint* src2);
void ADD_zzy(bigint** dst, const bigint* src);

void SUB_1word_zxy(word* dst, int* carry, const word* src1, const word* src2);    // src1�� src2, carry�� �Է¹޾� 1word�� ���� ������ ������ ���
void SUBC(bigint** dst, const bigint* src1, const bigint* src2);     //src1>src2�� �Է¹޾� ���� ���� dst�� ����
void SUB_zxy(bigint** dst, const bigint* src1, const bigint* src2);  //src1�� src2�� ���Ͽ� subc�� �̵���Ű�� �Լ�
void SUB_zzy(bigint** dst, const bigint* src);                       //dst-src�� dst�� �Է��ϴ� �Լ�.

void KaratsubaMUL(bigint** dst, const bigint* src1, const bigint* src2); //�������� KARA_FLAG�� �̿��ϴ� karatsuba ����.
void KaratsubaMUL_Flag(bigint** dst, const bigint* src1, const bigint* src2, const int flag);  //�׶����� ������ FLAG�� �̿��ϴ� karatsuba ����.

void MUL_1word_zxy(word* dst, const word* src1, const word* src2);  
void schoolbook_MULC(bigint** dst, const bigint* src1, const bigint* src2);
void MUL_zxy(bigint** dst, const bigint* src1, const bigint* src2);
void MUL_zzy(bigint** dst, const bigint* src);

void SQUC_1Word_zxx(word* dst, const word* src);
void SQUC(bigint** dst, const bigint* src);
void SQU_zxx(bigint** dst, const bigint* src);

void KaratsubaSQU(bigint** dst, const bigint* src);                         //�������� KARA_FLAG�� �̿��ϴ� karatsuba ����.
void KaratsubaSQU_Flag(bigint** dst, const bigint* src, const int flag);    //�׶����� ������ FLAG�� �̿��ϴ� karatsuba ����.

int NaiveDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2);      
int BinaryLongDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2);
void BinaryLongDiv_2word(word* Q, const word* src11, const word* src10, const word* src2);
void DIVCC(word* Q, bigint** R, const bigint* src1, const bigint* src2); 
void DIVC(word* Q, bigint** R, const bigint* src1, const bigint* src2, const int k);
int DIV(bigint** Q, bigint** R, const bigint* src1, const bigint* src2);

void MODExp_L2R(bigint** dst, const bigint* base, const bigint* power, const bigint* M); //left to right ����� �̿��� modular exponentiation.
void MODExp_R2L(bigint** dst, const bigint* base, const bigint* power, const bigint* M); //right to left ����� �̿��� modular exponentiation.
void MODExp_Montgomery(bigint** dst, const bigint* base, const bigint* power, const bigint* M); //Montgomery ladder ����� �̿��� modular exponentiation.

#endif /* operation_h */