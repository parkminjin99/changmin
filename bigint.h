#pragma once
//  
//  bigint.h
//  Changmin's library
//  
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
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


void bi_sage_show(const bigint* x, const int base);                 // bigint ����ü�� ����� ���� sage���Ŀ� �°� ���ϴ� ������ ����ϴ� �Լ�
void bi_show(const bigint* x, const int base);                      // bigint ����ü�� ����� ���� ���ϴ� ������ ����ϴ� �Լ�
void bi_delete(bigint** x);                                         // bigint ����ü�� �޸𸮸� �����ϴ� �Լ�
int bi_new(bigint** x, int wordlen, int sign);                      // bigint ����ü �޸� �����Ҵ� �Լ�
int bi_refine(bigint* x);                                           // bigint ����ü ���� �迭���� 0�� ������ ���带 �����ϴ� �Լ�
void bi_zeroize(bigint* x);                                         // bigint ���� �迭�� 0���� �ʱ�ȭ�ϴ� �Լ�
void bi_assign(bigint** y, const bigint* x);                        // bigint ����ü�� �����ϴ� �Լ�
void bi_gen_rand(bigint** x, int sign, int wordlen);                // bigint ����ü�� ���Ƿ� �����ϴ� �Լ�.
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen);   // a�� sign ������ struct�� �����ϱ�.
void bi_set_by_string(bigint** x, int sign, char* str, word base);  // ���ڿ��� �Ǿ��ִ� ���� ����ü�� �Է��ϴ� �Լ�.

int get_wordlen(const bigint* x);                                   // bigint ����ü�� word���̸� ��Ÿ���� �Լ�
int get_bitlen(const bigint* x);                                    // bigint ����ü�� bit���̸� ��Ÿ���� �Լ�
int get_jth_bit(const bigint* x, const int j);                      // bigint ����ü�� ���� j��° bit�� ��Ÿ���� �Լ�
int get_sign(const bigint* x);                                      // bigint ����ü�� ��ȣ�� ��Ÿ���� �Լ�
void flip_sign(bigint* x);                                          // bigint ����ü�� ��ȣ�� �ٲٴ� �Լ�

void bi_set_one(bigint** x);                                        // bigint ����ü�� 1�� �����ϴ� �Լ�
void bi_set_zero(bigint** x);                                       // bigint ����ü�� 0���� �����ϴ� �Լ�
int bi_is_minus_one(const bigint* x);                               // bigint ����ü�� -1���� Ȯ���ϴ� �Լ�
int bi_is_one(const bigint* x);                                     // bigint ����ü�� 1���� Ȯ���ϴ� �Լ�
int bi_is_zero(const bigint* x);                                    // bigint ����ü�� 0���� Ȯ���ϴ� �Լ�

int bi_compareABS(const bigint* src1, const bigint* src2);          // �� bigint�� ������ ���ϴ� �Լ�
int bi_compare(const bigint* src1, const bigint* src2);             // �� bigint�� ���ϴ� �Լ�

#endif /* bigint_h */