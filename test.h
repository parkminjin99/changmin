#pragma once
//
//  test.h
//  Changmin's library
//
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
//

#ifndef test_h
#define test_h

#include "changmin_library.h"

void COMPARE_test();            
void SHIFT_test();
void REDUCTION_test();

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