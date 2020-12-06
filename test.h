#pragma once
//
//  test.h
//  Changmin's library
//
//  Created by √÷∞≠√¢πŒ on 2020/11/09.
//  Copyright 2020 √÷∞≠√¢πŒ. All rights reserved.
//

#ifndef test_h
#define test_h

#include "changmin_library.h"

void BASIC_test();              //bi_set_by_array(), bi_gen_rand(), 
void COMPARE_test();            //bi_compare()
void SHIFT_test();              //left_shift(), right_shift()
void REDUCTION_test();          //reduction_2_r()

void ADD_test();                //ADD_zxy()
void SUB_test();                //SUB_zxy()
void MUL_test();                //MUL_zxy() 
void Karatsuba_test();          //KaratsubaMUL()
  
void SQU_test();                //SQU_zxx()
void KaratsubaSQU_test();       //KaratsubaSQU()

void NAIVE_div_test();          //NaiveDiv()
void BinaryLongDiv_test();      //BinaryLongDiv()
void DIV_test();                //DIV()

void MODExp_L2R_test();         //MODExp_L2R()
void MODExp_R2L_test();         //MODExp_R2L()
void MODExp_Montgomery_test();  //MODExp_Montgomery

#endif /* test_h */