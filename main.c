//
//  main.c
//  Changmin's library
//
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//

//README

#include <stdio.h>
#include "changmin_library.h"

int main(int argc, const char* argv[])
{
    srand((unsigned int)time(NULL));
    //BASIC_test(); // sage로 확인하지 않음 

    //COMPARE_test();
    //SHIFT_test();
    //REDUCTION_test();

    //ADD_test();
    //ADD2_test();
    //SUB_test();
    //MUL_test();
    //Karatsuba_test();
    //SQU_test();
    //LDA_2word_test();
    DIV_test();
    return 0;
}