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
      
    // ADD_test();
    // SUB_test();
    // MUL_test();
    // Karatsuba_test();
    // SQU_test();
    // SQUCKaratsuba_test();

    //NAIVE_div_test();
    // BinaryLongDiv_test();
    // DIV_test();
    
    // L2R_test();
    // R2L_test();
    // Montgomery_test();

    // ADD_FLINTvsCM();
    // SUB_FLINTvsCM();
    // MUL_FLINTvsCM();
    Kara_flag();
    MULvsKara();
    MULvsSQU();

    //SQUvsKara();
    //NAIVEvsBINARYLONGvsMULTIDIV();
    //DIV_FLINTvsCM();
    //FLINT_tri();
    //EXPMOD_FLINTvsCM();
    //EXPMOD_test();

    return 0;
}