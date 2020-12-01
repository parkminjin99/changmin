//
//  test.c
//  Changmin's library
//
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//
#include "test.h"

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
    printf("\n #< bigint compare > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    int cnt = 0;
    printf("while(True):\n");
    printf("    case=0\n");
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, 5);
        bi_gen_rand(&src2, rand()%2, 5);
        printf("    comA = " );       bi_sage_show(src1, 16);    printf("\n");
        printf("    comB = " );       bi_sage_show(src2, 16);    printf("\n");
        if (1 == bi_compare(src1, src2)) 
        { 
            printf("    if comA<=comB:\n");
            printf("        print( 'False!!')\n");
            printf("        break\n");
        }
        else if (0 == bi_compare(src1, src2)) 
        { 
            printf("    if comA!=comB:\n");
            printf("        print( 'False!!')\n");
            printf("        break\n");

        }
        else
        {
            printf("    if comA>=comB:\n");
            printf("        print( 'False!!')\n");
            printf("        break\n");;
        }
        bi_delete(&src1);
        bi_delete(&src2);
        cnt++;
        printf("    case=case+1\n");

    }
    
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n",MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case A = ',end='')\n");
    printf("    print(comA)\n");
    printf("    print('error case B = ',end='')\n");
    printf("    print(comB)\n");

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
        bi_gen_rand(&Lshift, NON_NEGATIVE, rand()%30);
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
        bi_gen_rand(&Rshift, NON_NEGATIVE, rand()%30);
        printf("Rshift = ");             bi_sage_show(Rshift, 16);     printf("\n");
        int rshift = rand()%(10*WORD_BITLEN);
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

    printf("while(True):\n");
    printf("    case=0\n");
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&A, NON_NEGATIVE, rand()%30);
        printf("    A = ");          bi_sage_show(A, 16);    printf("\n");
        int r = rand() % 10;
        reduction_2_r(A, r);
        printf("    cal = ");    bi_sage_show(A, 16);    printf("\n");
        printf("    if A %% 2^%%d != cal:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");
        printf("    case=case+1\n");
        bi_delete(&A);
        cnt++;
    }
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case A = ',end='')\n");
    printf("    print(A)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(A %% 2^%%d)\n");
}

void ADD_test()
{
    //printf(" < bigint Addition > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    int cnt = 0;

    printf("while(True):\n");
    printf("    case=0\n");
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, rand() % 20);
        bi_gen_rand(&src2, rand()%2, rand() % 20);
        printf("    addA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("    addB = ");          bi_sage_show(src2, 16);    printf("\n");
        ADD_zxy(&dst, src1, src2);   
        printf("    cal = ");    bi_sage_show(dst, 16);    printf("\n");
        printf("    if addA + addB != cal:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");
        printf("    case=case+1\n");
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case addA = ',end='')\n");
    printf("    print(addA)\n");
    printf("    print('error case addB = ',end='')\n");
    printf("    print(addB)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(addA + addB)\n");
}

void SUB_test()
{
    printf("\n");
    //printf(" < bigint Subtraction > \n")
    bigint* src1 = NULL;  // x-y에서 x
    bigint* src2 = NULL;  // x-y에서 y
    bigint* dst = NULL;  // x-y
    int cnt = 0;

    printf("while(True):\n");
    printf("    case=0\n");
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, rand() % 20);
        bi_gen_rand(&src2, rand()%2, rand() % 20);
        printf("    subA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("    subB = ");          bi_sage_show(src2, 16);    printf("\n");
        SUB_zxy(&dst, src1, src2);   
        printf("    cal = ");    bi_sage_show(dst, 16);    printf("\n");
        printf("    if subA - subB != cal:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");
        printf("    case=case+1\n");
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case subA = ',end='')\n");
    printf("    print(subA)\n");
    printf("    print('error case subB = ',end='')\n");
    printf("    print(subB)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(subA - subB)\n");
}

void MUL_test()
{
    printf("\n");
    //printf(" < bigint Multiplication > \n");
    bigint* src1 = NULL;    // x*y에서 x
    bigint* src2 = NULL;    // x*y에서 y
    bigint* dst = NULL;     // x*y
    int cnt = 0;

    printf("while(True):\n");
    printf("    case=0\n");
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, rand()%20);
        bi_gen_rand(&src2, rand()%2, rand()%20);
        printf("    mulA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("    mulB = ");          bi_sage_show(src2, 16);    printf("\n");
        MUL_zxy(&dst, src1, src2);   
        printf("    cal = ");    bi_sage_show(dst, 16);    printf("\n");
        printf("    if mulA * mulB != cal:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");
        printf("    case=case+1\n");
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case mulA = ',end='')\n");
    printf("    print(mulA)\n");
    printf("    print('error case mulB = ',end='')\n");
    printf("    print(mulB)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(mulA * mulB)\n");
}

void Karatsuba_test()
{
    //printf("\n < bigint KARA Multiplication > \n");

    bigint* src1 = NULL;    // x*y에서 x
    bigint* src2 = NULL;    // x*y에서 y
    bigint* dst = NULL;     // x*y
    int cnt = 0;

    printf("while(True):\n");
    printf("    case=0\n");
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, rand()%20);
        bi_gen_rand(&src2, NON_NEGATIVE, rand()%20);
        printf("    mulA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("    mulB = ");          bi_sage_show(src2, 16);    printf("\n");
        KaratsubaMUL(&dst, src1, src2);
        printf("    cal = ");    bi_sage_show(dst, 16);    printf("\n");
        printf("    if mulA * mulB != cal:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");
        printf("    case=case+1\n");
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case mulA = ',end='')\n");
    printf("    print(mulA)\n");
    printf("    print('error case mulB = ',end='')\n");
    printf("    print(mulB)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(mulA * mulB)\n");
}

void SQU_test()
{
    printf("\n");
    printf(" #< bigint Squaring > \n");
    bigint* src = NULL;
    bigint* dst = NULL;
    int cnt = 0;

    printf("while(True):\n");
    printf("    case=0\n");
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand() % 2, rand() % 10);
        printf("    squcA = ");          bi_sage_show(src, 16);    printf("\n");
        SQU_zxx(&dst, src);
        printf("    cal = ");    bi_sage_show(dst, 16);    printf("\n");
        printf("    if squcA * squcA != cal:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");
        bi_delete(&src);
        bi_delete(&dst);
        cnt++;
        printf("    case=case+1\n");
    }
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case squcA = ',end='')\n");
    printf("    print(squcA)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(squcA * squcA)\n");
}

void SQUCKaratsuba_test()
{
    printf("\n");
    printf(" #< bigint karatsuba Squaring > \n");
    bigint* src = NULL;
    bigint* dst = NULL;
    int cnt = 0;
    int flag = 2;

    printf("while(True):\n");
    printf("    case=0\n");

    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand() % 2, rand() % 9);
        printf("    squcA = ");          bi_sage_show(src, 16);    printf("\n");
        SQUCKaratsuba(&dst, src, flag);
        printf("    cal = ");    bi_sage_show(dst, 16);    printf("\n");
        printf("    if squcA * squcA != cal:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");
        bi_delete(&src);
        bi_delete(&dst);
        cnt++;
        printf("    case=case+1\n");
    }
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case squcA = ',end='')\n");
    printf("    print(squcA)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(squcA * squcA)\n");
}

void NAIVE_div_test()
{
    printf("\n");
    printf(" #< bigint NAIVE Division Algo > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;
    int cnt = 0;
    printf("while(True):\n");
    printf("    case=0\n");
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 3);
        bi_gen_rand(&src2, NON_NEGATIVE, rand() % 3);
        printf("    divA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("    divB = ");          bi_sage_show(src2, 16);    printf("\n");
        if (INVALID == NaiveDiv(&dstQ, &dstR, src1, src2))
            continue;
        printf("    Q = ");     bi_sage_show(dstQ, 16);     printf("\n");
        printf("    R = ");     bi_sage_show(dstR, 16);     printf("\n");
        printf("    if divB*Q+R != divA:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
        cnt++;
        printf("    case=case+1\n");
    }

    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case divA = ',end='')\n");
    printf("    print(divA)\n");
    printf("    print('error case divB = ',end='')\n");
    printf("    print(divB)\n");
    printf("    print('error case cal Q = ',end='')\n");
    printf("    print(Q)\n");
    printf("    print('error case cal R = ',end='')\n");
    printf("    print(R)\n");
    printf("    print('error case real Q= ',end='')\n");
    printf("    print(divA//divB)\n");
    printf("    print('error case real R= ',end='')\n");
    printf("    print(divA%%divB)\n");
}

void BinaryLongDiv_test()
{
    printf("\n");
    printf(" #< bigint Long Division Algo > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;
    int cnt = 0;
    printf("while(True):\n");
    printf("    case=0\n");

    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 10);
        bi_gen_rand(&src2, NON_NEGATIVE, rand() % 5);
        printf("    divA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("    divB = ");          bi_sage_show(src2, 16);    printf("\n");
        if (INVALID == BinaryLongDiv(&dstQ, &dstR, src1, src2))
            continue;
        printf("    Q = ");     bi_sage_show(dstQ, 16);     printf("\n");
        printf("    R = ");     bi_sage_show(dstR, 16);     printf("\n");

        printf("    if divB*Q+R != divA:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");

        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
        cnt++;
        printf("    case=case+1\n");

    }
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case divA = ',end='')\n");
    printf("    print(divA)\n");
    printf("    print('error case divB = ',end='')\n");
    printf("    print(divB)\n");
    printf("    print('error case cal Q = ',end='')\n");
    printf("    print(Q)\n");
    printf("    print('error case cal R = ',end='')\n");
    printf("    print(R)\n");
    printf("    print('error case real Q= ',end='')\n");
    printf("    print(divA//divB)\n");
    printf("    print('error case real R= ',end='')\n");
    printf("    print(divA%%divB)\n");
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

    printf("while(True):\n");
    printf("    case=0\n");

    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 4);
        bi_gen_rand(&src2, NON_NEGATIVE, 2);
        printf("    divA = ");          bi_sage_show(src1, 16);    printf("\n");
        printf("    divB = ");          bi_sage_show(src2, 16);    printf("\n");
        if (INVALID == DIV(&dstQ, &dstR, src1, src2))
        {
            bi_delete(&src1);
            bi_delete(&src2);
            continue;
        }

        printf("    Q = ");     bi_sage_show(dstQ, 16);     printf("\n");
        printf("    R = ");     bi_sage_show(dstR, 16);     printf("\n");

        printf("    if divB*Q+R != divA:\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");

        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
        cnt++;
        printf("    case=case+1\n");
    }
    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case divA = ',end='')\n");
    printf("    print(divA)\n");
    printf("    print('error case divB = ',end='')\n");
    printf("    print(divB)\n");
    printf("    print('error case cal Q = ',end='')\n");
    printf("    print(Q)\n");
    printf("    print('error case cal R = ',end='')\n");
    printf("    print(R)\n");
    printf("    print('error case real Q= ',end='')\n");
    printf("    print(divA//divB)\n");
    printf("    print('error case real R= ',end='')\n");
    printf("    print(divA%%divB)\n");
}


void L2R_test()
{
    printf("\n #< bignum L2R > \n");
    bigint* base = NULL;
    bigint* power = NULL;
    bigint* dst = NULL;
    int cnt = 0;
    int modn = 50;
    printf("def exp(base, power,mod): \n");
    printf("   t = [1, base]\n");
    printf("   e = power.bits()\n");
    printf("   for i in range(len(e) - 1, -1, -1): \n");
    printf("       t[1- e[i]] = (t[0] * t[1])%%(2**mod) \n");
    printf("       t[e[i]] = (t[e[i]]^2)%%(2**mod) \n");
    printf("   return t[0]\n \n");

    printf("while(True):\n");
    printf("    case=0\n");
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&base, NON_NEGATIVE, 11);
        bi_gen_rand(&power, NON_NEGATIVE, 20);

        printf("    base = ");          bi_sage_show(base, 16);    printf("\n");
        printf("    power = ");          bi_sage_show(power, 16);    printf("\n");
        printf("    modn = %d \n", modn);
        L2R(&dst, base, power, modn);
        printf("    cal = ");            bi_sage_show(dst, 16);    printf("\n");

        printf("    if cal != exp(base, power,modn):\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");

        bi_delete(&base);
        bi_delete(&power);
        bi_delete(&dst);
        cnt++;
        printf("    case=case+1\n");
    }

    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case base = ',end='')\n");
    printf("    print(base)\n");
    printf("    print('error case power = ',end='')\n");
    printf("    print(power)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(exp(base, power,modn))\n");
}


void R2L_test()
{
    printf("\n #< bignum R2L > \n");
    bigint* base = NULL;
    bigint* power = NULL;
    bigint* dst = NULL;
    int cnt = 0;
    int modn = 50;
    printf("def exp(base, power,mod): \n");
    printf("   t = [1, base]\n");
    printf("   e = power.bits()\n");
    printf("   for i in range(len(e) - 1, -1, -1): \n");
    printf("       t[1- e[i]] = (t[0] * t[1])%%(2**mod) \n");
    printf("       t[e[i]] = (t[e[i]]^2)%%(2**mod) \n");
    printf("   return t[0]\n \n");

    printf("while(True):\n");
    printf("    case=0\n");
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&base, NON_NEGATIVE, 11);
        bi_gen_rand(&power, NON_NEGATIVE, 20);

        printf("    base = ");          bi_sage_show(base, 16);    printf("\n");
        printf("    power = ");          bi_sage_show(power, 16);    printf("\n");
        printf("    modn = %d \n", modn);
        R2L(&dst, base, power, modn);
        printf("    cal = ");            bi_sage_show(dst, 16);    printf("\n");

        printf("    if cal != exp(base, power,modn):\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");

        bi_delete(&base);
        bi_delete(&power);
        bi_delete(&dst);
        cnt++;
        printf("    case=case+1\n");
    }

    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case base = ',end='')\n");
    printf("    print(base)\n");
    printf("    print('error case power = ',end='')\n");
    printf("    print(power)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(exp(base, power,modn))\n");
}

void Montgomery_test()
{
    printf("\n #< bignum Montgomery > \n");
    bigint* base = NULL;
    bigint* power = NULL;
    bigint* dst = NULL;
    int cnt = 0;
    int modn = 50;
    printf("def exp(base, power,mod): \n");
    printf("   t = [1, base]\n");
    printf("   e = power.bits()\n");
    printf("   for i in range(len(e) - 1, -1, -1): \n");
    printf("       t[1- e[i]] = (t[0] * t[1])%%(2**mod) \n");
    printf("       t[e[i]] = (t[e[i]]^2)%%(2**mod) \n");
    printf("   return t[0]\n \n");

    printf("while(True):\n");
    printf("    case=0\n");
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&base, NON_NEGATIVE, 11);
        bi_gen_rand(&power, NON_NEGATIVE, 20);

        printf("    base = ");          bi_sage_show(base, 16);    printf("\n");
        printf("    power = ");          bi_sage_show(power, 16);    printf("\n");
        printf("    modn = %d \n", modn);
        Montgomery(&dst, base, power, modn);
        printf("    cal = ");            bi_sage_show(dst, 16);    printf("\n");

        printf("    if cal != exp(base, power,modn):\n");
        printf("        print( 'False!!')\n");
        printf("        break\n");

        bi_delete(&base);
        bi_delete(&power);
        bi_delete(&dst);
        cnt++;
        printf("    case=case+1\n");
    }

    printf("    print('true!!')\n");
    printf("    break\n");
    printf("\nif case!=%d:\n", MAX_COUNT);
    printf("    print('error in ',end='')\n");
    printf("    print(case+1)\n");
    printf("    print('error case base = ',end='')\n");
    printf("    print(base)\n");
    printf("    print('error case power = ',end='')\n");
    printf("    print(power)\n");
    printf("    print('error case cal = ',end='')\n");
    printf("    print(cal)\n");
    printf("    print('error case real = ',end='')\n");
    printf("    print(exp(base, power,modn))\n");
    
}
