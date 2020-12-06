//
//  main.c
//  Changmin's library
//
//  Created by √÷∞≠√¢πŒ on 2020/12/06.
//  Copyright 2020 √÷∞≠√¢πŒ. All rights reserved.
//

//README

#include <stdio.h>
#include "changmin_library.h"


int main()
{
    srand((unsigned int)time(NULL));
    welcome();
    //BASIC_test(); 
    COMPARE_test();
    SHIFT_test();
    REDUCTION_test();
      
    ADD_test(); 
    SUB_test(); 
    MUL_test();  
    Karatsuba_test(); 
    SQU_test(); 
    KaratsubaSQU_test(); 

    //NAIVE_div_test();    
    BinaryLongDiv_test(); 
    DIV_test(); 
    
    MODExp_L2R_test(); 
    MODExp_R2L_test(); 
    MODExp_Montgomery_test(); 

     // for (int i = 4; i <= 12; i=i+4)
     // {   
     //      printf("==================================\n");
     //      printf("wordlen = %d\n",i); 
     //      ADD_FLINTvsCM(i); 
     //      SUB_FLINTvsCM(i); 
     //      MUL_FLINTvsCM(i); 
     //      DIV_FLINTvsCM(i); 
     //      EXPMOD_FLINTvsCM(i); 
     
     //      Kara_flag(i); 
     //      MULvsKara(i); 
     //      MULvsSQU(i);    
     //      SQUvsKara(i); 
     //      BINARYLONGvsMULTIDIV(i);
     //      //NAIVEvsBINARYLONGvsMULTIDIV(i); 
     // }
    return 0;
}