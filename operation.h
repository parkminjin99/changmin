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

//========================���꿡�� ����ڰ� ������ ����ϴ� �Լ� LIST =========================
//----------------------------------Addition----------------------------------------------
void ADD_zxy(bigint** dst, const bigint* src1, const bigint* src2);                             // ������ �� ���� src1, src2�� ���� > dst�� ���� 
void ADD_zzy(bigint** dst, const bigint* src);                                                  // ������ �� ���� src, dst�� ���� > dst�� ���� 
//-------------------------------Subtraction----------------------------------------------
void SUB_zxy(bigint** dst, const bigint* src1, const bigint* src2);                             // ������ �� ���� src1���� src2���� ����  > dst�� ���� 
void SUB_zzy(bigint** dst, const bigint* src);                                                  // ������ �� ���� dst���� src���� ����  > dst�� ���� 
//------------------------Multiplication + (KaratsubaMul)---------------------------------
void MUL_zxy(bigint** dst, const bigint* src1, const bigint* src2);                             // ������ �� ���� src1, src2�� ���� > dst�� ���� 
void MUL_zzy(bigint** dst, const bigint* src);                                                  // ������ �� ���� src, dst�� ���� > dst�� ���� 
void KaratsubaMUL(bigint** dst, const bigint* src1, const bigint* src2);                        // �������� KARA_FLAG�� �̿��ϴ� karatsuba ����.
//------------------------------Squaring + (KaratsubaSqu)---------------------------------
void SQU_zxx(bigint** dst, const bigint* src);                                                  // ������ ���� src�� ���� > dst�� ����
void KaratsubaSQU(bigint** dst, const bigint* src);                                             // �������� KARA_FLAG�� �̿��ϴ� karatsuba ����.
//-----------------------------------Division(3 types)------------------------------------
int NaiveDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2);                               // ���� �⺻���� ������ �˰��� (src1 = src2*Q + R�� �����ϴ� Q, R ����)
int BinaryLongDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2);                          // ���� �� ������ �˰��� (src1 = src2*Q + R�� �����ϴ� Q, R ����)
int DIV(bigint** Q, bigint** R, const bigint* src1, const bigint* src2);                        // ���� ���� ���� �� ������ �˰��� (src1 = src2*Q + R�� �����ϴ� Q, R ����)
//------------------------Modular Exponentiation(3 types)---------------------------------
void MODExp_L2R(bigint** dst, const bigint* base, const bigint* power, const bigint* M);        // left to right ����� �̿��� modular exponentiation.
void MODExp_R2L(bigint** dst, const bigint* base, const bigint* power, const bigint* M);        // right to left ����� �̿��� modular exponentiation.
void MODExp_Montgomery(bigint** dst, const bigint* base, const bigint* power, const bigint* M); // Montgomery ladder ����� �̿��� modular exponentiation.
//============================================================================================



//=========================���� �Լ��� �����ϴ� ���� �Լ�=========================================
void left_shift(bigint* x, int r);      // bigint x�� r��Ʈ��ŭ �������� shift�ϴ� �Լ�
void right_shift(bigint* x, int r);     // bigint x�� r��Ʈ��ŭ ���������� shift�ϴ� �Լ�
void reduction_2_r(bigint* x, int r);   // bigint x�� x mod 2^r�� ����ϴ� �Լ�
void ADD_1word_zxyc(word* dst, word* carry, const word* src1, const word* src2);                // src1, src2, carry�� �Է¹޾� 1word�� ���� ���� > dst�� ���� 
void ADD_1word_zzyc(word* dst, word* carry, const word* src);                                   // src, dst, carry�� �Է¹޾� 1word�� ���� ���� > dst�� ���� 
void ADDC(bigint** dst, const bigint* src1, const bigint* src2);                                // ������ ��ȣ�� �� ���� src1, src2�� ���� > dst�� ���� 
void SUB_1word_zxy(word* dst, int* carry, const word* src1, const word* src2);                  // src1, src2, carry�� �Է¹޾� 1word�� ���� ������ ���� > dst�� ���� 
void SUBC(bigint** dst, const bigint* src1, const bigint* src2);                                // �� ���� src1, src2 (src1>src2)�� ���� > dst�� ����
void MUL_1word_zxy(word* dst, const word* src1, const word* src2);                              // src1, src2�� �Է¹޾� 1word�� ���� ���� > dst�� ���� 
void schoolbook_MULC(bigint** dst, const bigint* src1, const bigint* src2);                     // ������ ��ȣ�� �� ���� src1, src2�� ���� > dst�� ����
void KaratsubaMUL_Flag(bigint** dst, const bigint* src1, const bigint* src2, const int flag);   // �׶����� ������ FLAG�� �̿��ϴ� karatsuba ����.
void SQUC_1Word_zxx(word* dst, const word* src);                                                // src�� �Է¹޾� 1word�� ���� ���� > dst�� ���� 
void schoolbook_SQUC(bigint** dst, const bigint* src);                                          // 0,-1,1�� �ƴ� ���� src�� ���� > dst�� ���� 
void KaratsubaSQU_Flag(bigint** dst, const bigint* src, const int flag);                        // �׶����� ������ FLAG�� �̿��ϴ� karatsuba ����.
void BinaryLongDiv_2word(word* Q, const word* src11, const word* src10, const word* src2);      // ���� �� ������ �˰��� (src1�� 2word�� ���, src1 = src2*Q + R�� �����ϴ� Q ����)
void DIVCC(word* Q, bigint** R, const bigint* src1, const bigint* src2);                        // 0 < src2 <= src1 < src2*W�� MSB(src2)=1�� �����ϴ� src1,src2�� ������ �˰��� (src1 = src2*Q + R�� �����ϴ� Q, R ����)
void DIVC(word* Q, bigint** R, const bigint* src1, const bigint* src2, const int k);            // 0 <= src1 < src2*W�� �����ϴ� src1,src2�� ������ �˰��� (src1 = src2*Q + R�� �����ϴ� Q, R ����)
//====================================================================================================
#endif /* operation_h */