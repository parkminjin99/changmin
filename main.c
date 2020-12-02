//
//  main.c
//  Changmin's library
//
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
//

//README

#include <stdio.h>
#include "changmin_library.h"

int main(int argc, const char* argv[])
{
    srand((unsigned int)time(NULL));
    //BASIC_test(); // sage�� Ȯ������ ���� 

    // COMPARE_test();
    // SHIFT_test();
    //REDUCTION_test();
      
    ADD_test(); //0
    SUB_test(); //0
    MUL_test();  //0
    Karatsuba_test(); //0
    SQU_test(); //0
    KaratsubaSQU_test(); //0

    //NAIVE_div_test();    //너무 느려서 검증 못해봄
    BinaryLongDiv_test(); //o
    DIV_test(); // o
    
    //MODExp_L2R_test(); //o
    //MODExp_R2L_test(); //0
    //MODExp_Montgomery_test(); //0

     ADD_FLINTvsCM(); //0
     SUB_FLINTvsCM(); //0 
     MUL_FLINTvsCM(); //0 
     Kara_flag(); //0
    // MULvsKara(); //0
    //MULvsSQU();    //0

    //SQUvsKara(); //0
    //NAIVEvsBINARYLONGvsMULTIDIV(); //너무느려
    //DIV_FLINTvsCM(); //0
    //EXPMOD_FLINTvsCM(); //0
    //EXPMOD_test(); 

    return 0;
}