//
//  main.c
//  Changmin's library
//
//  Created by ÃÖ°­Ã¢¹Î on 2020/11/09.
//  Copyright 2020 ÃÖ°­Ã¢¹Î. All rights reserved.
//

//README

#include <stdio.h>
#include "changmin_library.h"

int main(int argc, const char* argv[])
{
    srand((unsigned int)time(NULL));
    //BASIC_test(); // sageï¿½ï¿½ È®ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ 

    // COMPARE_test();
    // SHIFT_test();
    //REDUCTION_test();
      
    //ADD_test(); //0
    //SUB_test(); //0
    //MUL_test();  //0
    //Karatsuba_test(); //0
    //SQU_test(); //0
    //KaratsubaSQU_test(); //0

    NAIVE_div_test();    
    //BinaryLongDiv_test(); //o
    //DIV_test(); // o
    
    //MODExp_L2R_test(); //o
    //MODExp_R2L_test(); //0
    //MODExp_Montgomery_test(); //0

    // for (int i = 8;i<=100;i=i+4)
    // {   
    //     printf("\n==================================\n");
    //     printf("wordlen = %d\n",i); 
    //     //ADD_FLINTvsCM(i); //0
    //     //SUB_FLINTvsCM(i); //0 
    //     //MUL_FLINTvsCM(i); //0 
    //     Kara_flag(i); //0
    //     MULvsKara(i); //0
    //     MULvsSQU(i);    //0
    //     SQUvsKara(i); //0
    //     BINARYLONGvsMULTIDIV(i);
    //     //NAIVEvsBINARYLONGvsMULTIDIV(); 
    //     //DIV_FLINTvsCM(i); //0
    //     //EXPMOD_FLINTvsCM(i); //0
    // }
    return 0;
}