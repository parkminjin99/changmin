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

    //COMPARE_test();
    //SHIFT_test();
    //REDUCTION_test();

    //ADD_test();
    //SUB_test();
    MUL_test();
    //Karatsuba_test();
    //SQU_test();
    return 0;
}