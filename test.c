//
//  test.c
//  Changmin's library
//
//  Created by ï¿½Ö°ï¿½Ã¢ï¿½ï¿½ on 2020/11/09.
//  Copyright 2020 ï¿½Ö°ï¿½Ã¢ï¿½ï¿½. All rights reserved.
//
#include "test.h"

int Wordlen = 16;

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
    printf(" #< bigint Addition > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    fmpz_t x, y, z, cal, zero;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_init(cal);
    fmpz_init(zero);

    fmpz_zero(zero);  //zero¸¦ 0À¸·Î ¼³Á¤. 

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, Wordlen);

        ADD_zxy(&dst, src1, src2);

        fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen);
        fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen);

        fmpz_add(z, x, y);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, dst->wordlen);


        if ((fmpz_equal(z, cal) != 1)) // ï¿½ï¿½ï¿½ï¿½ï¿? trueï¿½Ï¶ï¿½1 ï¿½ï¿½ï¿½ï¿½
            break; // ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? while ï¿½ï¿½ï¿½ï¿½

        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src1, 10);
        printf("B = ");  bi_show(src2, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(z); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    fmpz_clear(cal);
}

void SUB_test()
{
    printf(" #< bigint Subtraction > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    fmpz_t x, y, z, cal, zero;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_init(cal);
    fmpz_init(zero);

    fmpz_zero(zero);

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 16);
        bi_gen_rand(&src2, NON_NEGATIVE, 16);
        //printf("src1=");
        //bi_show(src1,16);
        //printf("src2=");
        //bi_show(src2,16);

        //printf("dst=");
        SUB_zxy(&dst, src1, src2);  

        //bi_show(dst,16);
        fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen);
        fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen);
        
        fmpz_sub(z, x, y);
        //fmpz_print(z);
        //printf("\n");    

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, dst->wordlen);
        //printf("cal=");
        //fmpz_print(cal);

        if(NEGATIVE==get_sign(dst))
            fmpz_sub(cal,zero,cal);  
        //printf("\n");  
        //printf("-cal=");  
        //fmpz_print(cal);

        //fmpz_set_si(cal, (mp_limb_signed_t)dst);
       
        //fmpz_print(cal);

        if ((fmpz_equal(z, cal) != 1)) // °°Àº °æ¿ì 1 
            break; // ´Ù¸£¸é Á¾·á

        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src1, 10);
        printf("B = ");  bi_show(src2, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(z); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    fmpz_clear(cal);
    fmpz_clear(zero);
}

void MUL_test()
{
    printf("\n");
    printf(" #< bigint Multiplication > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    fmpz_t x, y, z, cal;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_init(cal);

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, Wordlen);
        
        MUL_zxy(&dst, src1, src2);

        fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen);
        fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen);

        fmpz_mul(z, x, y);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, dst->wordlen);


        if ((fmpz_equal(z, cal) != 1)) 
            break; // ´Ù¸£¸é Á¾·á

        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src1, 10);
        printf("B = ");  bi_show(src2, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(z); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    fmpz_clear(cal);
}

void Karatsuba_test()
{
    printf("\n < bigint KARA Multiplication > \n");

    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    fmpz_t x, y, z, cal;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_init(cal);

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, Wordlen);

        KaratsubaMUL(&dst, src1, src2);

        fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen);
        fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen);

        fmpz_mul(z, x, y);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, dst->wordlen);


        if ((fmpz_equal(z, cal) != 1)) // °°Àº°ªÀÎ°æ¿ì 1Ãâ·ÂµÊ
            break; // °°Áö ¾ÊÀ¸¸é Áï½ÃÁ¾·á

        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src1, 10);
        printf("B = ");  bi_show(src2, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(z); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    fmpz_clear(cal);
}

void SQU_test()
{
    printf("\n #< bigint Squaring > \n");
    bigint* src = NULL;
    bigint* dst = NULL;

    fmpz_t x, y, z, cal;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_init(cal);
    //FLINT °ö¼ÀÀÇ ÀÔ·Â¿¡ °°Àº°ªÀ» ³Ö´Â°ÍÀ¸·Î Á¦°öÀ» °ËÁõ

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, NON_NEGATIVE, Wordlen);
        SQU_zxx(&dst, src);

        fmpz_set_ui_array(x, (const mp_limb_t*)src->a, src->wordlen);
        fmpz_set_ui_array(y, (const mp_limb_t*)src->a, src->wordlen);

        fmpz_mul(z, x, y);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, dst->wordlen);


        if ((fmpz_equal(z, cal) != 1)) // ï¿½ï¿½ï¿½ï¿½ï¿? trueï¿½Ï¶ï¿½1 ï¿½ï¿½ï¿½ï¿½
            break; // ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? while ï¿½ï¿½ï¿½ï¿½

        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(z); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src);
    bi_delete(&dst);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    fmpz_clear(cal);
}


void KaratsubaSQU_test()
{
    printf("\n #< bigint karatsuba Squaring > \n");
    bigint* src = NULL;
    bigint* dst = NULL;

    fmpz_t x, y, z, cal;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_init(cal);
    //FLINT °ö¼ÀÀÇ ÀÔ·Â¿¡ °°Àº°ªÀ» ³Ö´Â°ÍÀ¸·Î Á¦°öÀ» °ËÁõ
    
    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, NON_NEGATIVE, Wordlen);
        KaratsubaSQU(&dst, src);

        fmpz_set_ui_array(x, (const mp_limb_t*)src->a, src->wordlen);
        fmpz_set_ui_array(y, (const mp_limb_t*)src->a, src->wordlen);

        fmpz_mul(z, x, y);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, dst->wordlen);


        if ((fmpz_equal(z, cal) != 1)) // ï¿½ï¿½ï¿½ï¿½ï¿? trueï¿½Ï¶ï¿½1 ï¿½ï¿½ï¿½ï¿½
            break; // ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? while ï¿½ï¿½ï¿½ï¿½

        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(z); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src);
    bi_delete(&dst);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    fmpz_clear(cal);
}

void NAIVE_div_test()
{
    printf(" < bigint BinaryLongDiv > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;

    fmpz_t f, s, g, h, calq, calr;
    fmpz_init(f);
    fmpz_init(s);
    fmpz_init(g);
    fmpz_init(h);
    fmpz_init(calq);
    fmpz_init(calr);

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 2 * Wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, Wordlen);
        while (VALID != NaiveDiv(&dstQ, &dstR, src1, src2))
        {
            bi_gen_rand(&src1, NON_NEGATIVE, 2 * Wordlen);
            bi_gen_rand(&src2, NON_NEGATIVE, Wordlen);
        }

        fmpz_set_ui_array(g, (const mp_limb_t*)src1->a, 2 * Wordlen);
        fmpz_set_ui_array(h, (const mp_limb_t*)src2->a, Wordlen);

        // bi_set_one(&dstQ);   // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?

        fmpz_fdiv_qr(f, s, g, h);

        fmpz_set_ui_array(calq, (const mp_limb_t*)dstQ->a, dstQ->wordlen);
        fmpz_set_ui_array(calr, (const mp_limb_t*)dstR->a, dstR->wordlen);

        if ((fmpz_equal(f, calq) != 1) || (fmpz_equal(s, calr) != 1)) // ï¿½ï¿½ï¿½ï¿½ï¿? trueï¿½Ï¶ï¿½1 ï¿½ï¿½ï¿½ï¿½
            break; // ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? while ï¿½ï¿½ï¿½ï¿½
        cnt++;
        if (0 == (cnt % (MAX_COUNT / 100)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src1, 10);
        printf("B = ");  bi_show(src2, 10);
        printf("calQ = ");  bi_show(dstQ, 10);
        printf("calR = ");  bi_show(dstR, 10);
        printf("realQ = ");   fmpz_print(f); printf("\n");
        printf("realR = ");   fmpz_print(s); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dstQ);
    bi_delete(&dstR);

    fmpz_clear(f);
    fmpz_clear(s);
    fmpz_clear(g);
    fmpz_clear(h);
    fmpz_clear(calq);
    fmpz_clear(calr);
}

void BinaryLongDiv_test()
{
    //printf(" < bigint BinaryLongDiv > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;

    fmpz_t f, s, g, h, calq, calr;
    fmpz_init(f);
    fmpz_init(s);
    fmpz_init(g);
    fmpz_init(h);
    fmpz_init(calq);
    fmpz_init(calr);

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 2 * Wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, Wordlen);
        while (VALID != BinaryLongDiv(&dstQ, &dstR, src1, src2))
        {
            bi_gen_rand(&src1, NON_NEGATIVE, 2 * Wordlen);
            bi_gen_rand(&src2, NON_NEGATIVE, Wordlen);
        }

        fmpz_set_ui_array(g, (const mp_limb_t*)src1->a, 2 * Wordlen);
        fmpz_set_ui_array(h, (const mp_limb_t*)src2->a, Wordlen);

        // bi_set_one(&dstQ);   // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?

        fmpz_fdiv_qr(f, s, g, h);

        fmpz_set_ui_array(calq, (const mp_limb_t*)dstQ->a, dstQ->wordlen);
        fmpz_set_ui_array(calr, (const mp_limb_t*)dstR->a, dstR->wordlen);

        if ((fmpz_equal(f, calq) != 1) || (fmpz_equal(s, calr) != 1)) // ï¿½ï¿½ï¿½ï¿½ï¿? trueï¿½Ï¶ï¿½1 ï¿½ï¿½ï¿½ï¿½
            break; // ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? while ï¿½ï¿½ï¿½ï¿½
        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src1, 10);
        printf("B = ");  bi_show(src2, 10);
        printf("calQ = ");  bi_show(dstQ, 10);
        printf("calR = ");  bi_show(dstR, 10);
        printf("realQ = ");   fmpz_print(f); printf("\n");
        printf("realR = ");   fmpz_print(s); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dstQ);
    bi_delete(&dstR);

    fmpz_clear(f);
    fmpz_clear(s);
    fmpz_clear(g);
    fmpz_clear(h);
    fmpz_clear(calq);
    fmpz_clear(calr);

}

void DIV_test()
{
    printf(" < bigint Multi-precision_DIV > \n");
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;

    fmpz_t f, s, g, h, calq, calr;
    fmpz_init(f);
    fmpz_init(s);
    fmpz_init(g);
    fmpz_init(h);
    fmpz_init(calq);
    fmpz_init(calr);

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 2 * Wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, Wordlen);
        
        while (VALID != DIV(&dstQ, &dstR, src1, src2))
        {
            bi_gen_rand(&src1, NON_NEGATIVE, 2 * Wordlen);
            bi_gen_rand(&src2, NON_NEGATIVE, Wordlen);
        }

        fmpz_set_ui_array(g, (const mp_limb_t*)src1->a, 2 * Wordlen);
        fmpz_set_ui_array(h, (const mp_limb_t*)src2->a, Wordlen);

        // bi_set_one(&dstQ);   // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?

        fmpz_fdiv_qr(f, s, g, h);

        fmpz_set_ui_array(calq, (const mp_limb_t*)dstQ->a, dstQ->wordlen);
        fmpz_set_ui_array(calr, (const mp_limb_t*)dstR->a, dstR->wordlen);

        if ((fmpz_equal(f, calq) != 1) || (fmpz_equal(s, calr) != 1)) // ï¿½ï¿½ï¿½ï¿½ï¿? trueï¿½Ï¶ï¿½1 ï¿½ï¿½ï¿½ï¿½
            break; // ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? while ï¿½ï¿½ï¿½ï¿½
        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src1, 10);
        printf("B = ");  bi_show(src2, 10);
        printf("calQ = ");  bi_show(dstQ, 10);
        printf("calR = ");  bi_show(dstR, 10);
        printf("realQ = ");   fmpz_print(f); printf("\n");
        printf("realR = ");   fmpz_print(s); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dstQ);
    bi_delete(&dstR);

    fmpz_clear(f);
    fmpz_clear(s);
    fmpz_clear(g);
    fmpz_clear(h);
    fmpz_clear(calq);
    fmpz_clear(calr);

}


void MODExp_L2R_test()
{
    printf("\n #< bignum MODExp_L2R > \n");
    bigint* base = NULL;
    bigint* power = NULL;
    bigint* dst = NULL;
    bigint* M = NULL;

    fmpz_t f, g, e, m, cal;
    fmpz_init(f);
    fmpz_init(g);
    fmpz_init(e);
    fmpz_init(m);
    fmpz_init(cal);

    int cnt = 0;

    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&base, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&power, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&M, NON_NEGATIVE, Wordlen);
        while (!bi_is_zero(M))
            bi_gen_rand(&M, NON_NEGATIVE, Wordlen);

        MODExp_L2R(&dst, base, power, M);

        fmpz_set_ui_array(g, (const mp_limb_t*)base->a, Wordlen); // x = src1
        fmpz_set_ui_array(e, (const mp_limb_t*)power->a, Wordlen); // y = src2
        fmpz_set_ui_array(m, (const mp_limb_t*)M->a, Wordlen); // y = src2

        fmpz_powm(f, g, e, m);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, dst->wordlen);

        if ((fmpz_equal(f, cal) != 1)) // ï¿½ï¿½ï¿½ï¿½ï¿? trueï¿½Ï¶ï¿½1 ï¿½ï¿½ï¿½ï¿½
            break; // ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? while ï¿½ï¿½ï¿½ï¿½
        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");

    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("base = ");  bi_show(base, 10);
        printf("power = ");  bi_show(power, 10);
        printf("M = ");  bi_show(M, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(f); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    bi_delete(&base);
    bi_delete(&power);
    bi_delete(&dst);
    bi_delete(&M);
    
    fmpz_clear(f);
    fmpz_clear(g);
    fmpz_clear(e);
    fmpz_clear(m);
}


void MODExp_R2L_test()
{
    printf("\n #< bignum MODExp_R2L > \n");
    bigint* base = NULL;
    bigint* power = NULL;
    bigint* dst = NULL;
    bigint* M = NULL;

    fmpz_t f, g, e, m, cal;
    fmpz_init(f);
    fmpz_init(g);
    fmpz_init(e);
    fmpz_init(m);
    fmpz_init(cal);

    int cnt = 0;

    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&base, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&power, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&M, NON_NEGATIVE, Wordlen);
        while (!bi_is_zero(M))
            bi_gen_rand(&M, NON_NEGATIVE, Wordlen);

        MODExp_R2L(&dst, base, power, M);

        fmpz_set_ui_array(g, (const mp_limb_t*)base->a, Wordlen); // x = src1
        fmpz_set_ui_array(e, (const mp_limb_t*)power->a, Wordlen); // y = src2
        fmpz_set_ui_array(m, (const mp_limb_t*)M->a, Wordlen); // y = src2

        fmpz_powm(f, g, e, m);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, dst->wordlen);

        if ((fmpz_equal(f, cal) != 1)) // ï¿½ï¿½ï¿½ï¿½ï¿? trueï¿½Ï¶ï¿½1 ï¿½ï¿½ï¿½ï¿½
            break; // ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? while ï¿½ï¿½ï¿½ï¿½
        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");

    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("base = ");  bi_show(base, 10);
        printf("power = ");  bi_show(power, 10);
        printf("M = ");  bi_show(M, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(f); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    bi_delete(&base);
    bi_delete(&power);
    bi_delete(&dst);
    bi_delete(&M);

    fmpz_clear(f);
    fmpz_clear(g);
    fmpz_clear(e);
    fmpz_clear(m);
}

void MODExp_Montgomery_test()
{
    printf("\n #< bignum MODExp_Montgomery > \n");
    bigint* base = NULL;
    bigint* power = NULL;
    bigint* dst = NULL;
    bigint* M = NULL;

    fmpz_t f, g, e, m, cal;
    fmpz_init(f);
    fmpz_init(g);
    fmpz_init(e);
    fmpz_init(m);
    fmpz_init(cal);

    int cnt = 0;

    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&base, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&power, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&M, NON_NEGATIVE, Wordlen);
        while (!bi_is_zero(M))
            bi_gen_rand(&M, NON_NEGATIVE, Wordlen);

        MODExp_Montgomery(&dst, base, power, M);

        fmpz_set_ui_array(g, (const mp_limb_t*)base->a, Wordlen); // x = src1
        fmpz_set_ui_array(e, (const mp_limb_t*)power->a, Wordlen); // y = src2
        fmpz_set_ui_array(m, (const mp_limb_t*)M->a, Wordlen); // y = src2

        fmpz_powm(f, g, e, m);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, dst->wordlen);

        if ((fmpz_equal(f, cal) != 1)) // ï¿½ï¿½ï¿½ï¿½ï¿? trueï¿½Ï¶ï¿½1 ï¿½ï¿½ï¿½ï¿½
            break; // ï¿½Ù¸ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿? while ï¿½ï¿½ï¿½ï¿½
        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");

    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("base = ");  bi_show(base, 10);
        printf("power = ");  bi_show(power, 10);
        printf("M = ");  bi_show(M, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(f); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    bi_delete(&base);
    bi_delete(&power);
    bi_delete(&dst);
    bi_delete(&M);

    fmpz_clear(f);
    fmpz_clear(g);
    fmpz_clear(e);
    fmpz_clear(m);    
}
