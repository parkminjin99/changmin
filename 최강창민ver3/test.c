//
//  test.c
//  Changmin's library
//
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//

#include "changmin_library.h"
void BASIC_test()
{
    bigint* x = NULL;
    bigint* y = NULL;
#if WORD_BITLEN == 64
    word arr[5] = { 0x1234567890abcdef, 0x1234567890abcdef, 0x1234567890abcdef, 0x1234567890abcdef, 0x1234567890abcdef }
    bi_set_by_array(&x, NON_NEGATIVE, arr, 5);
    printf("bigint x = ");       bi_show(x, 16);
    bi_gen_rand(&y, NON_NEGATIVE, 5);
    printf("random bigint y = ");       bi_show(y, 16);
#elif WORD_BITLEN == 32
    word arr[5] = { 0x12345678, 0x90abcdef, 0x12345678, 0x90abcdef, 0x12345678 };
    bi_set_by_array(&x, NON_NEGATIVE, arr, 5);
    printf("bigint x = ");       bi_show(x, 16);
    bi_gen_rand(&y, NON_NEGATIVE, 5);
    printf("random bigint y = ");       bi_show(y, 16);
#else // WORD_BITLEN == 8
    word arr[5] = { 0x90,0x78,0x56,0x34,0x12 };
    bi_set_by_array(&x, NON_NEGATIVE, arr, 5);
    printf("bigint x = ");       bi_show(x, 16);
    bi_gen_rand(&y, NON_NEGATIVE, 5);
    printf("random bigint y = ");       bi_show(y, 16);
#endif
    bigint* a = NULL;
    bigint* b = NULL;
    bigint* b_copy = NULL;
    char chr2[100] = "0101010101010101010101010101010101010101";
    char chr16[100] = "123456789abcdef0";

    printf("\nstring A = \"%s\"\n", chr2);
    bi_set_by_string(&a, NON_NEGATIVE, chr2, 2);
    printf("A -> bigint a = ");      bi_show(a, 2);

    printf("\nstring B = \"%s\"\n", chr16);
    bi_set_by_string(&b, NON_NEGATIVE, chr16, 16);
    printf("B -> bigint b = ");     bi_show(b, 16);

    bi_assign(&b_copy, b);
    printf("bigint b's copy = ");   bi_show(b_copy, 16);

    bi_delete(&x);
    bi_delete(&y);
    bi_delete(&a);
    bi_delete(&b);
    bi_delete(&b_copy);
}

void COMPARE_test()
{
    printf("\n");
    //printf(" < bigint compare > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, 5);
    bi_gen_rand(&src2, NON_NEGATIVE, 5);
    printf("comA = 0x" );             bi_show(src1, 16);
    printf("comB = 0x" );             bi_show(src2, 16);
    if (1 == bi_compare(src1, src2))                printf("print(comA > comB)\n");
    else if (0 == bi_compare(src1, src2))           printf("print(comA  == comB)\n");
    else                                            printf("print(comA  < comB)\n");
    bi_delete(&src1);
    bi_delete(&src2);
}

void SHIFT_test()
{
    printf("\n");
    bigint* Lshift = NULL;
    bigint* Rshift = NULL;
    bi_gen_rand(&Lshift, NON_NEGATIVE, 5);
    bi_gen_rand(&Rshift, NON_NEGATIVE, 5);
    //printf(" < bigint left shift >\n");
    printf("Lshift = 0x" );             bi_show(Lshift, 16);
    int lshift = rand()%(10*WORD_BITLEN);
    //int lshift = 16;
    left_shift(Lshift, lshift);
    printf("print(Lshift << %d == ",lshift);       bi_sage_show(Lshift, 16);

    //printf(" < bigint right shift >\n");
    printf("Rshift = 0x");             bi_show(Rshift, 16);
    int rshift = rand()%(5*WORD_BITLEN);
    right_shift(Rshift, rshift);
    printf("print(Rshift >> %d == ",rshift);       bi_sage_show(Rshift, 16);

    bi_delete(&Lshift);
    bi_delete(&Rshift); 
}

void REDUCTION_test()
{
    printf("\n");
    //printf(" < bigint reduction 2^r(a mod 2^r) >\n");
    bigint* A = NULL;
    bi_gen_rand(&A, NON_NEGATIVE, 10);
    printf("A = 0x");               bi_show(A, 16);
    int r = rand() % 10;
    reduction_2_r(A, r);
    printf("print(A %% 2^%d == ", r);     bi_sage_show(A, 16);
    bi_delete(&A);
}

void ADD_test()
{
    printf("\n");
    //printf(" < bigint Addition > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, rand() % 10);
    bi_gen_rand(&src2, NON_NEGATIVE, rand() % 10);
    printf("addA = 0x");       bi_show(src1, 16);
    printf("addB = 0x");       bi_show(src2, 16);
    ADD(&dst, src1, src2);
    printf("print(addA + addB == ");       bi_sage_show(dst, 16);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
}

void SUB_test()
{
    printf("\n");
    //printf(" < bigint Subtraction > \n")
    bigint* src1 = NULL;  // x-y에서 x
    bigint* src2 = NULL;  // x-y에서 y
    bigint* dst = NULL;  // x-y
    bi_gen_rand(&src1, NON_NEGATIVE, rand() % 5);
    bi_gen_rand(&src2, NON_NEGATIVE, rand() % 5);
    printf("subA = 0x");          bi_show(src1, 16);
    printf("subB = 0x");          bi_show(src2, 16);

    SUB(&dst, src1, src2);   // m-n
    printf("print(subA - subB == ");      bi_sage_show(dst, 16);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
}

void MUL_test()
{
    printf("\n");
    //printf(" < bigint Multiplication > \n");
    bigint* src1 = NULL;    // x*y에서 x
    bigint* src2 = NULL;    // x*y에서 y
    bigint* dst = NULL;     // x*y

    bi_gen_rand(&src1, NON_NEGATIVE, 4);
    bi_gen_rand(&src2, NON_NEGATIVE, 4);
    printf("mulA = 0x");          bi_show(src1, 16);
    printf("mulB = 0x");          bi_show(src2, 16);

    MUL(&dst, src1, src2);   
    printf("print(mulA * mulB == ");      bi_sage_show(dst, 16);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
}

void SQUC_test()
{
    printf("\n");
    printf(" < bigint Squaring > \n");
    bigint* src1 = NULL;    // x*y에서 x
    bigint* src2 = NULL;    // x*y에서 y
    bigint* dst = NULL;     // x*y

    bi_gen_rand(&src1, NON_NEGATIVE, 4);
    bi_gen_rand(&src2, NON_NEGATIVE, 4);
    printf("mulA = 0x");          bi_show(src1, 16);
    printf("mulB = 0x");          bi_show(src2, 16);

    MUL(&dst, src1, src2);   
    printf("print(mulA * mulB == ");      bi_sage_show(dst, 16);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
}