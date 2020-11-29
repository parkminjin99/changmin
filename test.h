#pragma once
//
//  test.h
//  Changmin's library
//
//  Created by ÃÖ°­Ã¢¹Î on 2020/11/09.
//  Copyright 2020 ÃÖ°­Ã¢¹Î. All rights reserved.
//

#ifndef test_h
#define test_h

#define MAX_COUNT 100000 // ¹Ýº¹¼öÇà È½¼ö 

void COMPARE_test();
void SHIFT_test();
void REDUCTION_test();

void ADD_test(); // 0 
void ADD2_test();
void SUB_test(); // 0
void MUL_test(); // 0
void Karatsuba_test(); // x
 
void SQU_test(); // x
void SQUCKaratsuba_test();

void NAIVE_div_test();
void Binary_Long_Div_test();
void DIV_test(); // 0

void L2R_test(); // 0
void R2L_test(); 
void Montgomery_test();

#endif /* test_h */