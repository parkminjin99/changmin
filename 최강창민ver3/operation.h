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

#include <stdio.h>
#include "bigint.h"
#include "array.h"

#define max(x,y)( (x)>(y)?(x):(y) )


void left_shift(bigint* x, int r);      // bigint x�� r��Ʈ��ŭ �������� shift�ϴ� �Լ�
void right_shift(bigint* x, int r);     // bigint x�� r��Ʈ��ŭ ���������� shift�ϴ� �Լ�
void reduction_2_r(bigint* x, int r);   // bigint x�� x mod 2^r�� ����ϴ� �Լ�

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