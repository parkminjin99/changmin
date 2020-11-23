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
    word arr[5] = { 0x1234567890abcdef, 0x1234567890abcdef, 0x1234567890abcdef, 0x1234567890abcdef, 0x1234567890abcdef };
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
    int cnt = 0;
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, 5);
        bi_gen_rand(&src2, rand()%2, 5);
        printf("comA = " );       bi_sage_show(src1, 16);    printf("\n");
        printf("comB = " );       bi_sage_show(src2, 16);    printf("\n");
        if (1 == bi_compare(src1, src2))                printf("print(comA > comB)\n");
        else if (0 == bi_compare(src1, src2))           printf("print(comA  == comB)\n");
        else                                            printf("print(comA  < comB)\n");
        bi_delete(&src1);
        bi_delete(&src2);
        cnt++;
    }
}

void SHIFT_test()
{
    printf("\n");
    bigint* Lshift = NULL;
    bigint* Rshift = NULL;
    int cnt = 0;
    //printf(" < bigint left shift >\n");
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&Lshift, NON_NEGATIVE, 15);
        printf("Lshift = " );             bi_sage_show(Lshift, 16);     printf("\n");
        int lshift = rand()%(10*WORD_BITLEN);
        left_shift(Lshift, lshift);
        printf("print(Lshift << %d == ", lshift);       bi_sage_show(Lshift, 16);   printf(")\n");
        bi_delete(&Lshift);
        cnt++;
    }
    
    cnt = 0;
    //printf(" < bigint right shift >\n");
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&Rshift, NON_NEGATIVE, 15);
        printf("Rshift = 0x");             bi_sage_show(Rshift, 16);     printf("\n");
        int rshift = rand()%(5*WORD_BITLEN);
        right_shift(Rshift, rshift);
        printf("print(Rshift >> %d == ",rshift);       bi_sage_show(Rshift, 16);   printf(")\n");
        bi_delete(&Rshift); 
        cnt++;
    }
}   

void REDUCTION_test()
{
    printf("\n");
    //printf(" < bigint reduction 2^r(a mod 2^r) >\n");
    bigint* A = NULL;
    int cnt = 0;
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&A, NON_NEGATIVE, 10);
        printf("A = 0x");               bi_sage_show(A, 16);     printf("\n");
        int r = rand() % 10;
        reduction_2_r(A, r);
        printf("print(A %% 2^%d == ", r);     bi_sage_show(A, 16);   printf(")\n");
        bi_delete(&A);
        cnt++;
    }
}

void ADD_test()
{
    printf("\n");
    //printf(" < bigint Addition > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    int cnt = 0;
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, rand() % 10);
        bi_gen_rand(&src2, rand()%2, rand() % 10);
        printf("addA = ");       bi_sage_show(src1, 16);    printf("\n");
        printf("addB = ");       bi_sage_show(src2, 16);    printf("\n");
        ADD(&dst, src1, src2);
        printf("print(addA + addB == ");       bi_sage_show(dst, 16);    printf(")\n");

        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
}

void ADD2_test()
{
    printf("\n");
    //printf(" < bigint Addition > \n");
    bigint* src = NULL;
    bigint* dst = NULL;
    int cnt = 0;
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand()%2, rand() % 10);
        bi_gen_rand(&dst, rand()%2, rand() % 10);
        printf("addA = ");       bi_sage_show(src, 16);    printf("\n");
        printf("dst = ");        bi_sage_show(dst, 16);    printf("\n");
        ADD2(&dst, src);
        printf("print(addA + dst == ");       bi_sage_show(dst, 16);    printf(")\n");

        bi_delete(&src);
        bi_delete(&dst);
        cnt++;
    }
}

void SUB_test()
{
    printf("\n");
    //printf(" < bigint Subtraction > \n")
    bigint* src1 = NULL;  // x-y에서 x
    bigint* src2 = NULL;  // x-y에서 y
    bigint* dst = NULL;  // x-y
    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, rand() % 10);
        bi_gen_rand(&src2, rand()%2, rand() % 10);
        printf("subA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("subB = ");          bi_sage_show(src2, 16);    printf("\n");

        SUB(&dst, src1, src2);   // m-n
        printf("print(subA - subB == ");      bi_sage_show(dst, 16);    printf(")\n");

        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
}

void MUL_test()
{
    printf("\n");
    //printf(" < bigint Multiplication > \n");
    bigint* src1 = NULL;    // x*y에서 x
    bigint* src2 = NULL;    // x*y에서 y
    bigint* dst = NULL;     // x*y
    int cnt = 0;
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, 10);
        bi_gen_rand(&src2, rand()%2, 10);
        printf("mulA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("mulB = ");          bi_sage_show(src2, 16);    printf("\n");

        MUL(&dst, src1, src2);   
        printf("print(mulA * mulB == ");      bi_sage_show(dst, 16);    printf(")\n");

        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
}

void Karatsuba_test()
{
    //printf("\n < bigint KARA Multiplication > \n");

    bigint* src1 = NULL;    // x*y에서 x
    bigint* src2 = NULL;    // x*y에서 y
    bigint* dst = NULL;     // x*y
    int flag = 2;
    int cnt = 0;

    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 20);
        bi_gen_rand(&src2, NON_NEGATIVE, 20);
        printf("mulA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("mulB = ");          bi_sage_show(src2, 16);    printf("\n");

        Karatsuba(&dst, src1, src2, 2);
        printf("print(mulA * mulB == ");      bi_sage_show(dst, 16);    printf(")\n");

        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
}

void SQU_test()
{
    printf("\n");
    //printf(" < bigint Squaring > \n");
    bigint* src = NULL;    
    bigint* dst = NULL;     
    int cnt = 0;
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand()%2, rand() % 10);
        printf("squcA = ");          bi_sage_show(src, 16);    printf("\n");
        SQU(&dst, src);   
        printf("print(squcA * squcA == ");      bi_sage_show(dst, 16);    printf(")\n");
        bi_delete(&src);
        bi_delete(&dst);
        cnt++;
    }
}

void SQUCKaratsuba_test()
{
    printf("\n");
    //printf(" < bigint Squaring > \n");
    bigint* src = NULL;
    bigint* dst = NULL;
    int cnt = 0;
    int flag = 2;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand() % 2, rand() % 9);
        printf("squcA = ");          bi_sage_show(src, 16);    printf("\n");
        SQUCKaratsuba(&dst, src, flag);
        printf("print(squcA * squcA == ");      bi_sage_show(dst, 16);    printf(")\n");
        bi_delete(&src);
        bi_delete(&dst);
        cnt++;
    }
}

void LDA_2word_test()
{
    printf("\n");
    //printf(" < bigint Squaring > \n");  
    int cnt = 0;
    while(cnt < 500)
    {
        //bi_gen_rand(&src1, NON_NEGATIVE, rand() % 10);
        //bi_gen_rand(&src2, NON_NEGATIVE, rand() % 10);
        //bi_set_by_string(&src1,NON_NEGATIVE,"888cd3a33724e9200e",16);
        //bi_set_by_string(&src2,NON_NEGATIVE,"22b7",16);
        //printf("divA = ");          bi_sage_show(src1, 16);    printf("\n");
        //printf("divB = ");          bi_sage_show(src2, 16);    printf("\n");
        word a1 = rand()&BITMASK;     word a0 = rand()&BITMASK;
        word b = rand()&BITMASK;
        //word a1 = 0x0e;     word a0 = 0xd4;
        //word b = 0xfe;
        word Q = 0;
        if(a1 >= b)
            continue;
        if(a1 == 0)
            continue;
        printf("divA = 0x");      printf("%02x%02x\n",a1,a0);
        printf("divB = 0x");      printf("%02x\n",b);
        LDA_2word(&Q,&a1,&a0,&b);
        printf("print(divA//divB == 0x");     printf("%02x",Q);     printf(")\n");
        //printf("print(divA%%divB == ");     bi_sage_show(dstR, 16);     printf(")\n");
        cnt++;
    }
}

void DIV_test()
{
    printf("\n");
    //printf(" < bigint Squaring > \n");
    bigint* src1 = NULL;  
    bigint* src2 = NULL;  
    bigint* dstQ = NULL;
    bigint* dstR = NULL;     
    int cnt = 0;
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 4);
        bi_gen_rand(&src2, NON_NEGATIVE, rand()%2);
        //bi_set_by_string(&src1,NON_NEGATIVE,"3073ec6bc652e5f4bbc73481cd202525582a6e6a",16);
        //bi_set_by_string(&src2,NON_NEGATIVE,"275c1ea70fb49e10b9348c3b2a766b3d",16);
        printf("divA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("divB = ");          bi_sage_show(src2, 16);    printf("\n");
        if(INVALID == DIV(&dstQ, &dstR, src1, src2))
            continue;
        printf("print(divA//divB == ");     bi_sage_show(dstQ, 16);     printf(")\n");
        printf("print(divA%%divB == ");     bi_sage_show(dstR, 16);     printf(")\n");
        //printf("print(divA == ");       bi_sage_show(dstQ, 16);    
        //printf(" * ");                  bi_sage_show(src2, 16);
        //printf(" + ");                  bi_sage_show(dstR, 16);    printf(")\n");
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
        cnt++;
    }
    // 88 8c d3 a3 37 24 e9 20 0e
}