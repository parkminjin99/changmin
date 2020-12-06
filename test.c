//
//  test.c
//  Changmin's library
//
//  Created by ÃÖ°­Ã¢¹Î on 2020/11/09.
//  Copyright 2020 ÃÖ°­Ã¢¹Î. All rights reserved.
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

// 
void COMPARE_test()
{
    printf("\n< bigint compare > \n");
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
    printf(" < bigint Addition > \n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dst[2];         dst[0] = dst[1] = NULL;
    int flag;

    fmpz_t x, y, z[2], cal0, cal1, zero;
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(z[0]);        fmpz_init(z[1]);
    fmpz_init(cal0);        fmpz_init(cal1);
    fmpz_init(zero);
    fmpz_zero(zero);  //zero¸¦ 0À¸·Î ¼³Á¤. 

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        if(cnt < MAX_COUNT/4) // src[0] = 0, src[1] >= 0
        {
            bi_set_zero(&src[0]);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
            //bi_show(src[0], 16);    bi_show(src2[0], 16);
        }
        else if(cnt < ((MAX_COUNT/4) * 2))
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }
        else if(cnt < ((MAX_COUNT/4)*3))
        {   
            bi_gen_rand(&src[0], NON_NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else
        {
            bi_gen_rand(&src[0], NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }

        ADD_zxy(&dst[0], src[0], src[1]);
        ADD_zxy(&dst[1], src[1], src[0]);
        if(0==cnt%(MAX_COUNT/4))
            printf("case : %d\n",cnt%(MAX_COUNT/4)+1);
        printf("\n=======\n");
        printf("src1 : ");  bi_sage_show(src[0],16); printf("\n");
        printf("src2 : ");  bi_sage_show(src[1],16); printf("\n");
        printf("dst  : ");  bi_sage_show(dst[0],16); printf("\n");
        printf("\n--------\n");
        printf("src1 : ");  bi_sage_show(src[1],16); printf("\n");
        printf("src2 : ");  bi_sage_show(src[0],16); printf("\n");
        printf("dst  : ");  bi_sage_show(dst[1],16); printf("\n");
        
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src[0]))  fmpz_sub(x,zero,x); 
        if(NEGATIVE == get_sign(src[1]))  fmpz_sub(y,zero,y); 

        fmpz_add(z[0], x, y);
        fmpz_add(z[1], y, x);
        fmpz_set_ui_array(cal0, (const mp_limb_t*)dst[0]->a, (dst[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(cal1, (const mp_limb_t*)dst[1]->a, (dst[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        
        if(NEGATIVE == get_sign(dst[0]))  fmpz_sub(cal0,zero,cal0); 
        if(NEGATIVE == get_sign(dst[1]))  fmpz_sub(cal1,zero,cal1); 

        if ((fmpz_equal(z[0], cal0) != 1)){flag = 0;  break;}
        if ((fmpz_equal(z[1], cal1) != 1)){flag = 1;  break;}
        
        cnt++;
        if (0 == (cnt % (MAX_COUNT / 10)))
            printf(".");
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    { 
        // flag = 0 -> src0, src1 
        // flag = 1 -> src1, src0
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("cal = ");       bi_show(dst[flag], 16);
        printf("real = ");      fmpz_print(z[flag]);        printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src[0]);         bi_delete(&src[1]);
    bi_delete(&dst[0]);         bi_delete(&dst[1]);
    fmpz_clear(x);              fmpz_clear(y);
    fmpz_clear(z[0]);           fmpz_clear(z[1]);
    fmpz_clear(cal0);           fmpz_clear(cal1);
}

void SUB_test()
{
    printf(" < bigint Subtraction > \n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dst[2];         dst[0] = dst[1] = NULL;
    int flag;

    fmpz_t x, y, z[2], cal0, cal1, zero;
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(z[0]);        fmpz_init(z[1]);
    fmpz_init(cal0);        fmpz_init(cal1);
    fmpz_init(zero);        fmpz_zero(zero); //zero¸¦ 0À¸·Î ¼³Á¤. 

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        if(cnt < MAX_COUNT/5)
        {
            bi_gen_rand(&src[0], NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else if(cnt < (MAX_COUNT/5)*2)
        {
            bi_set_zero(&src[0]);
            bi_gen_rand(&src[1], rand()%2, Wordlen);
        }
        else if(cnt < (MAX_COUNT/5)*3) // src[0] = src[1]
        {
            bi_gen_rand(&src[0], rand()%2, Wordlen);
            bi_assign(&src[1], src[0]);
        }
        else if(cnt < (MAX_COUNT/5)*4)
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else
        {
            bi_gen_rand(&src[0], NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }
        
        SUB_zxy(&dst[0], src[0], src[1]);  
        SUB_zxy(&dst[1], src[1], src[0]); 
        if(0==cnt%(MAX_COUNT/5))
            printf("case : %d\n",cnt%(MAX_COUNT/4)+1);
        printf("\n=======\n");
        printf("src1 : ");  bi_sage_show(src[0],16); printf("\n");
        printf("src2 : ");  bi_sage_show(src[1],16); printf("\n");
        printf("dst  : ");  bi_sage_show(dst[0],16); printf("\n");
        printf("\n--------\n");
        printf("src1 : ");  bi_sage_show(src[1],16); printf("\n");
        printf("src2 : ");  bi_sage_show(src[0],16); printf("\n");
        printf("dst  : ");  bi_sage_show(dst[1],16); printf("\n"); 
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src[0]))  fmpz_sub(x,zero,x); 
        if(NEGATIVE == get_sign(src[1]))  fmpz_sub(y,zero,y); 

        fmpz_sub(z[0], x, y);
        fmpz_sub(z[1], y, x);
        fmpz_set_ui_array(cal0, (const mp_limb_t*)dst[0]->a, (dst[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(cal1, (const mp_limb_t*)dst[1]->a, (dst[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        
        if(NEGATIVE == get_sign(dst[0]))  fmpz_sub(cal0,zero,cal0); 
        if(NEGATIVE == get_sign(dst[1]))  fmpz_sub(cal1,zero,cal1); 

        if ((fmpz_equal(z[0], cal0) != 1)){flag = 0;  break;}
        if ((fmpz_equal(z[1], cal1) != 1)){flag = 1;  break;}

        cnt++;
    }
    if (cnt != MAX_COUNT)
    {
        // flag = 0 -> src0, src1 
        // flag = 1 -> src1, src0
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("cal = ");       bi_show(dst[flag], 16);
        printf("real = ");      fmpz_print(z[flag]);        printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src[0]);         bi_delete(&src[1]);
    bi_delete(&dst[0]);         bi_delete(&dst[1]);
    fmpz_clear(x);              fmpz_clear(y);
    fmpz_clear(z[0]);           fmpz_clear(z[1]);
    fmpz_clear(cal0);           fmpz_clear(cal1);
}

void MUL_test()
{
    printf(" < bigint Multiplication > \n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dst[2];         dst[0] = dst[1] = NULL;
    int flag;

    fmpz_t x, y, z[2], cal0, cal1, zero;
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(z[0]);        fmpz_init(z[1]);
    fmpz_init(cal0);        fmpz_init(cal1);
    fmpz_init(zero);        fmpz_zero(zero); //zero¸¦ 0À¸·Î ¼³Á¤. 

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        if(cnt < MAX_COUNT/4) // src[0] = 0, src[1] >= 0
        {
            bi_set_zero(&src[0]);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else if(cnt < ((MAX_COUNT/4) * 2))
        {
            bi_set_one(&src[0]);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }
        else if(cnt < ((MAX_COUNT/4)*3))
        {   
            bi_set_minus_one(&src[0]);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else
        {
            bi_gen_rand(&src[0], NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }
        
        MUL_zxy(&dst[0], src[0], src[1]);
        MUL_zxy(&dst[1], src[1], src[0]);
        if(0==cnt%(MAX_COUNT/4))
            printf("case : %d\n",cnt%(MAX_COUNT/4)+1);
        printf("\n=======\n");
        printf("src1 : ");  bi_sage_show(src[0],16); printf("\n");
        printf("src2 : ");  bi_sage_show(src[1],16); printf("\n");
        printf("dst  : ");  bi_sage_show(dst[0],16); printf("\n");
        printf("\n--------\n");
        printf("src1 : ");  bi_sage_show(src[1],16); printf("\n");
        printf("src2 : ");  bi_sage_show(src[0],16); printf("\n");
        printf("dst  : ");  bi_sage_show(dst[1],16); printf("\n");
        
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src[0]))  fmpz_sub(x,zero,x); 
        if(NEGATIVE == get_sign(src[1]))  fmpz_sub(y,zero,y); 

        fmpz_mul(z[0], x, y);
        fmpz_mul(z[1], y, x);

        fmpz_set_ui_array(cal0, (const mp_limb_t*)dst[0]->a, (dst[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(cal1, (const mp_limb_t*)dst[1]->a, (dst[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(dst[0]))  fmpz_sub(cal0,zero,cal0); 
        if(NEGATIVE == get_sign(dst[1]))  fmpz_sub(cal1,zero,cal1); 

        if ((fmpz_equal(z[0], cal0) != 1)){flag = 0;  break;}
        if ((fmpz_equal(z[1], cal1) != 1)){flag = 1;  break;}

        cnt++;
    }
    printf("\n");
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("cal = ");       bi_show(dst[flag], 16);
        printf("real = ");      fmpz_print(z[flag]);        printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src[0]);         bi_delete(&src[1]);
    bi_delete(&dst[0]);         bi_delete(&dst[1]);
    fmpz_clear(x);              fmpz_clear(y);
    fmpz_clear(z[0]);           fmpz_clear(z[1]);
    fmpz_clear(cal0);           fmpz_clear(cal1);
}

void Karatsuba_test()
{
    printf("\n< bigint KARA Multiplication >\n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dst[2];         dst[0] = dst[1] = NULL;
    int flag;

    fmpz_t x, y, z[2], cal0, cal1, zero;
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(z[0]);        fmpz_init(z[1]);
    fmpz_init(cal0);        fmpz_init(cal1);
    fmpz_init(zero);        fmpz_zero(zero); //zero¸¦ 0À¸·Î ¼³Á¤.       

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src[0], rand()%2, Wordlen);
        bi_gen_rand(&src[1], rand()%2, Wordlen);

        KaratsubaMUL(&dst[0], src[0], src[1]);
        KaratsubaMUL(&dst[1], src[1], src[0]);
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src[0]))  fmpz_sub(x,zero,x); 
        if(NEGATIVE == get_sign(src[1]))  fmpz_sub(y,zero,y); 

        fmpz_mul(z[0], x, y);
        fmpz_mul(z[1], y, x);
        fmpz_set_ui_array(cal0, (const mp_limb_t*)dst[0]->a, (dst[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(cal1, (const mp_limb_t*)dst[1]->a, (dst[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(dst[0]))  fmpz_sub(cal0,zero,cal0); 
        if(NEGATIVE == get_sign(dst[1]))  fmpz_sub(cal1,zero,cal1); 

        if ((fmpz_equal(z[0], cal0) != 1)){flag = 0;  break;}
        if ((fmpz_equal(z[1], cal1) != 1)){flag = 1;  break;}
        cnt++;
    }
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("cal = ");       bi_show(dst[flag], 16);
        printf("real = ");      fmpz_print(z[flag]);        printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src[0]);         bi_delete(&src[1]);
    bi_delete(&dst[0]);         bi_delete(&dst[1]);
    fmpz_clear(x);              fmpz_clear(y);
    fmpz_clear(z[0]);           fmpz_clear(z[1]);
    fmpz_clear(cal0);           fmpz_clear(cal1);
}

void SQU_test() //FLINT °ö¼ÀÀÇ ÀÔ·Â¿¡ °°Àº°ªÀ» ³Ö´Â°ÍÀ¸·Î Á¦°öÀ» °ËÁõ
{
    printf("\n< bigint Squaring > \n");
    bigint* src = NULL;
    bigint* dst = NULL;

    fmpz_t x, z, cal, zero;
    fmpz_init(x);           fmpz_init(z);           fmpz_init(cal);
    fmpz_init(zero);        fmpz_zero(zero); //zero¸¦ 0À¸·Î ¼³Á¤. 
    
    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        if(cnt < MAX_COUNT/4)
            bi_set_zero(&src);
        else if(cnt < (MAX_COUNT/4)*2)
            bi_set_one(&src);
        else if(cnt < (MAX_COUNT/4)*3)
            bi_set_minus_one(&src);
        else
            bi_gen_rand(&src, rand()%2, Wordlen);

        SQU_zxx(&dst, src);

        if(0==cnt%(MAX_COUNT/4))
            printf("case : %d\n",cnt%(MAX_COUNT/4)+1);
        printf("\n=======\n");
        printf("src : ");  bi_sage_show(src,16); printf("\n");
        printf("dst : ");  bi_sage_show(dst,16); printf("\n");
        printf("\n--------\n");
        printf("src : ");  bi_sage_show(src,16); printf("\n");
        printf("dst : ");  bi_sage_show(dst,16); printf("\n");

        fmpz_set_ui_array(x, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src))  fmpz_sub(x,zero,x); 

        fmpz_mul(z, x, x);
        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(dst))  fmpz_sub(cal,zero,cal); 

        if ((fmpz_equal(z, cal) != 1)){ break;}
        cnt++;
    }
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
    fmpz_clear(z);
    fmpz_clear(cal);
}

void KaratsubaSQU_test()
{
    printf("\n < bigint karatsuba Squaring > \n");
    bigint* src = NULL;
    bigint* dst = NULL;

    fmpz_t x, z, cal, zero;
    fmpz_init(x);           fmpz_init(z);           fmpz_init(cal);
    fmpz_init(zero);        fmpz_zero(zero); //zero¸¦ 0À¸·Î ¼³Á¤.    
    //FLINT °ö¼ÀÀÇ ÀÔ·Â¿¡ °°Àº°ªÀ» ³Ö´Â°ÍÀ¸·Î Á¦°öÀ» °ËÁõ
    
    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand()%2, Wordlen);
        KaratsubaSQU(&dst, src);
        fmpz_set_ui_array(x, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src))  fmpz_sub(x,zero,x); 

        fmpz_mul(z, x, x);
        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(dst))  fmpz_sub(cal,zero,cal); 

        if ((fmpz_equal(z, cal) != 1)){ break;}
        cnt++;
    }
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
    fmpz_clear(z);
    fmpz_clear(cal);
}

void NAIVE_div_test()
{
    printf("\n< bigint NaiveDiv > \n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dstQ[2];         dstQ[0] = dstQ[1] = NULL;
    bigint* dstR[2];         dstR[0] = dstR[1] = NULL;
    int flag_valid = 0, flag;

    fmpz_t q[2], r[2], x, y, calq[2], calr[2];
    fmpz_init(q[0]);        fmpz_init(q[1]);
    fmpz_init(r[0]);        fmpz_init(r[1]);
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(calq[0]);     fmpz_init(calq[1]);
    fmpz_init(calr[0]);     fmpz_init(calr[1]);

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        if(cnt < MAX_COUNT/5) // src2 = 0
        {
            bi_gen_rand(&src[0], rand()%2, 2 * Wordlen);
            bi_set_zero(&src[1]);
            if(INVALID != NaiveDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }
            else{   cnt++; continue;}
        }
        else if(cnt < (MAX_COUNT/5)*2) // src2 < 0
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
            if(INVALID != BinaryLongDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }
            else{   cnt++; continue;}
        }
        else if(cnt < (MAX_COUNT/5)*3) // src2 = 1ÀÎ °æ¿ì 
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
            bi_set_one(&src[1]);
            NaiveDiv(&dstQ[0], &dstR[0], src[0], src[1]);
            NaiveDiv(&dstQ[1], &dstR[1], src[1], src[0]);
        }
        else
        {
            while (1)
            {
                bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
                bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
                if(VALID == NaiveDiv(&dstQ[0], &dstR[0], src[0], src[1]) && VALID == NaiveDiv(&dstQ[1], &dstR[1], src[1], src[0]))
                    break;
            }
        }
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        fmpz_fdiv_qr(q[0], r[0], x, y);
        fmpz_fdiv_qr(q[1], r[1], y, x);
        fmpz_set_ui_array(calq[0], (const mp_limb_t*)dstQ[0]->a, (dstQ[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calq[1], (const mp_limb_t*)dstQ[1]->a, (dstQ[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[0], (const mp_limb_t*)dstR[0]->a, (dstR[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[1], (const mp_limb_t*)dstR[1]->a, (dstR[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        if ((fmpz_equal(q[0], calq[0]) != 1) || (fmpz_equal(r[0], calr[0]) != 1)){flag = 0;  break;}
        if ((fmpz_equal(q[1], calq[1]) != 1) || (fmpz_equal(r[1], calr[1]) != 1)){flag = 1;  break;}
        cnt++;
    }

    if(flag_valid == 1)
    {
        printf("INVALID error\n");
        printf("A = ");  bi_show(src[flag], 16);     printf("B = ");  bi_show(src[flag^1], 16);
        return;
    }
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("calQ = ");      bi_show(dstQ[flag], 16);
        printf("calR = ");      bi_show(dstR[flag], 16);
        printf("realQ = ");     fmpz_print(q[flag]); printf("\n");
        printf("realR = ");     fmpz_print(r[flag]); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    bi_delete(&src[0]);         bi_delete(&src[1]);
    bi_delete(&dstQ[0]);         bi_delete(&dstQ[1]);
    bi_delete(&dstR[0]);         bi_delete(&dstR[1]);
    fmpz_clear(x);              fmpz_clear(y);
    fmpz_clear(q[0]);           fmpz_clear(q[1]);
    fmpz_clear(r[0]);           fmpz_clear(r[1]);
    fmpz_clear(calq[0]);        fmpz_clear(calq[1]);
    fmpz_clear(calr[0]);        fmpz_clear(calr[1]);
}

void BinaryLongDiv_test()
{
    printf("\n< bigint BinaryLongDiv > \n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dstQ[2];         dstQ[0] = dstQ[1] = NULL;
    bigint* dstR[2];         dstR[0] = dstR[1] = NULL;
    int flag_valid = 0, flag;

    fmpz_t q[2], r[2], x, y, calq[2], calr[2];
    fmpz_init(q[0]);        fmpz_init(q[1]);
    fmpz_init(r[0]);        fmpz_init(r[1]);
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(calq[0]);     fmpz_init(calq[1]);
    fmpz_init(calr[0]);     fmpz_init(calr[1]);

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        if(cnt < MAX_COUNT/5) // src2 = 0
        {
            bi_gen_rand(&src[0], rand()%2, 2 * Wordlen);
            bi_set_zero(&src[1]);
            if(INVALID != BinaryLongDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }
            else{   cnt++; continue;}
        }
        else if(cnt < (MAX_COUNT/5)*2) // src2 < 0
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
            if(INVALID != BinaryLongDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }
            else{   cnt++; continue;}
        }
        else
        {
            while (1)
            {
                bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
                bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
                if(VALID == BinaryLongDiv(&dstQ[0], &dstR[0], src[0], src[1]) && VALID == BinaryLongDiv(&dstQ[1], &dstR[1], src[1], src[0]))
                    break;
            }
        }
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        fmpz_fdiv_qr(q[0], r[0], x, y);
        fmpz_fdiv_qr(q[1], r[1], y, x);
        fmpz_set_ui_array(calq[0], (const mp_limb_t*)dstQ[0]->a, (dstQ[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calq[1], (const mp_limb_t*)dstQ[1]->a, (dstQ[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[0], (const mp_limb_t*)dstR[0]->a, (dstR[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[1], (const mp_limb_t*)dstR[1]->a, (dstR[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        if ((fmpz_equal(q[0], calq[0]) != 1) || (fmpz_equal(r[0], calr[0]) != 1)){flag = 0;  break;}
        if ((fmpz_equal(q[1], calq[1]) != 1) || (fmpz_equal(r[1], calr[1]) != 1)){flag = 1;  break;}
        cnt++;
    }
    if(flag_valid == 1)
    {
        printf("INVALID error\n");
        printf("A = ");  bi_show(src[flag], 16);     printf("B = ");  bi_show(src[flag^1], 16);
        return;
    }
    if (cnt != MAX_COUNT)
    {
        
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("calQ = ");      bi_show(dstQ[flag], 16);
        printf("calR = ");      bi_show(dstR[flag], 16);
        printf("realQ = ");     fmpz_print(q[flag]); printf("\n");
        printf("realR = ");     fmpz_print(r[flag]); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    bi_delete(&src[0]);         bi_delete(&src[1]);
    bi_delete(&dstQ[0]);         bi_delete(&dstQ[1]);
    bi_delete(&dstR[0]);         bi_delete(&dstR[1]);
    fmpz_clear(x);              fmpz_clear(y);
    fmpz_clear(q[0]);           fmpz_clear(q[1]);
    fmpz_clear(r[0]);           fmpz_clear(r[1]);
    fmpz_clear(calq[0]);        fmpz_clear(calq[1]);
    fmpz_clear(calr[0]);        fmpz_clear(calr[1]);
}

void DIV_test()
{
    printf("\n< bigint Multi-precision_DIV > \n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dstQ[2];         dstQ[0] = dstQ[1] = NULL;
    bigint* dstR[2];         dstR[0] = dstR[1] = NULL;
    int flag_valid = 0, flag;

    fmpz_t q[2], r[2], x, y, calq[2], calr[2];
    fmpz_init(q[0]);        fmpz_init(q[1]);
    fmpz_init(r[0]);        fmpz_init(r[1]);
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(calq[0]);     fmpz_init(calq[1]);
    fmpz_init(calr[0]);     fmpz_init(calr[1]);

    int cnt = 0;
    while (cnt < MAX_COUNT)
    { 
        if(cnt < MAX_COUNT/3) // src2 = 0
        {
            bi_gen_rand(&src[0], rand()%2, 2 * Wordlen);
            bi_set_zero(&src[1]);
            if(INVALID != BinaryLongDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }
            else{   cnt++; continue;}
        }
        else if(cnt < (MAX_COUNT/3)*2) // src2 < 0
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
            if(INVALID != BinaryLongDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }
            else{   cnt++; continue;}
        }
        else
        {
            while (1)
            {
                bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
                bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
                if(VALID == DIV(&dstQ[0], &dstR[0], src[0], src[1]) && VALID == DIV(&dstQ[1], &dstR[1], src[1], src[0]))
                    break;
            }
        }
        if(0==cnt%(MAX_COUNT/3))
            printf("case : %d\n",cnt%(MAX_COUNT/3)+1);
        printf("\n=======\n");
        printf("src1 : ");  bi_sage_show(src[0],16); printf("\n");
        printf("src2 : ");  bi_sage_show(src[1],16); printf("\n");
        printf("Q    : ");  bi_sage_show(dstQ[0],16); printf("\n");
        printf("R    : ");  bi_sage_show(dstR[0],16); printf("\n");

        printf("\n--------\n");
        printf("src1 : ");  bi_sage_show(src[1],16); printf("\n");
        printf("src2 : ");  bi_sage_show(src[0],16); printf("\n");
        printf("Q    : ");  bi_sage_show(dstQ[1],16); printf("\n");
        printf("R    : ");  bi_sage_show(dstR[1],16); printf("\n");

        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        fmpz_fdiv_qr(q[0], r[0], x, y);
        fmpz_fdiv_qr(q[1], r[1], y, x);
        fmpz_set_ui_array(calq[0], (const mp_limb_t*)dstQ[0]->a, (dstQ[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calq[1], (const mp_limb_t*)dstQ[1]->a, (dstQ[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[0], (const mp_limb_t*)dstR[0]->a, (dstR[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[1], (const mp_limb_t*)dstR[1]->a, (dstR[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        if ((fmpz_equal(q[0], calq[0]) != 1) || (fmpz_equal(r[0], calr[0]) != 1)){flag = 0;  break;}
        if ((fmpz_equal(q[1], calq[1]) != 1) || (fmpz_equal(r[1], calr[1]) != 1)){flag = 1;  break;}
        cnt++;  
    }
    if(flag_valid == 1)
    {
        printf("INVALID error\n");
        printf("A = ");  bi_show(src[flag], 16);     printf("B = ");  bi_show(src[flag^1], 16);
        return;
    }
    if (cnt != MAX_COUNT)
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("calQ = ");      bi_show(dstQ[flag], 16);
        printf("calR = ");      bi_show(dstR[flag], 16);
        printf("realQ = ");     fmpz_print(q[flag]); printf("\n");
        printf("realR = ");     fmpz_print(r[flag]); printf("\n");
    }
    else
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    bi_delete(&src[0]);         bi_delete(&src[1]);
    bi_delete(&dstQ[0]);         bi_delete(&dstQ[1]);
    bi_delete(&dstR[0]);         bi_delete(&dstR[1]);
    fmpz_clear(x);              fmpz_clear(y);
    fmpz_clear(q[0]);           fmpz_clear(q[1]);
    fmpz_clear(r[0]);           fmpz_clear(r[1]);
    fmpz_clear(calq[0]);        fmpz_clear(calq[1]);
    fmpz_clear(calr[0]);        fmpz_clear(calr[1]);

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
        while (!bi_is_zero(M)) // M != 0ÀÌ¿©¾ß ÇÔ 
            bi_gen_rand(&M, NON_NEGATIVE, Wordlen);

        MODExp_L2R(&dst, base, power, M);
        if(0==cnt%(MAX_COUNT/5))
            printf("case : %d\n",cnt%(MAX_COUNT/4)+1);
        printf("\n=======\n");
        printf("base  : ");  bi_sage_show(base,16); printf("\n");
        printf("power : ");  bi_sage_show(power,16); printf("\n");
        printf("M     : ");  bi_sage_show(M,16); printf("\n");
        printf("dst   : ");  bi_sage_show(dst,16); printf("\n");
        fmpz_set_ui_array(g, (const mp_limb_t*)base->a, (base->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // x = src1
        fmpz_set_ui_array(e, (const mp_limb_t*)power->a, (power->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // y = src2
        fmpz_set_ui_array(m, (const mp_limb_t*)M->a, (M->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // y = src2

        fmpz_powm(f, g, e, m);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

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

        fmpz_set_ui_array(g, (const mp_limb_t*)base->a, (base->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // x = src1
        fmpz_set_ui_array(e, (const mp_limb_t*)power->a, (power->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // y = src2
        fmpz_set_ui_array(m, (const mp_limb_t*)M->a, (M->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // y = src2

        fmpz_powm(f, g, e, m);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

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
        

        fmpz_set_ui_array(g, (const mp_limb_t*)base->a, (base->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // x = src1
        fmpz_set_ui_array(e, (const mp_limb_t*)power->a, (power->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // y = src2
        fmpz_set_ui_array(m, (const mp_limb_t*)M->a, (M->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // y = src2

        fmpz_powm(f, g, e, m);

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

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
