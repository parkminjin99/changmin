//
//  test.c
//  Changmin's library
//
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
//
#include "test.h"
/**********************************
 test.c
 ������ �Լ��� ��Ȯ�� ���� ����ϴ��� Ȯ���ϴ� ������ �����ϱ� ���� 
 FLINT�� ������ ������ �����ϴ� �Լ��� ���Ͽ���.
 ���� �Լ��� ������ ����. 

�Լ���                           cm                 FLINT          
-------------------------------------------------------------------- 
COMPARE_test();           | bi_compare()           fmpz_cmp
SHIFT_test();             | left_shift()           fmpz_mul_2exp
                          | rightshift()           fmpz_fdiv_q_2exp
REDUCTION_test();         | reduction_2_r()        fmpz_fdiv_r_2exp
ADD_test();               | ADD_zxy()              fmpz_add
SUB_test();               | SUB_zxy()              fmpz_sub
MUL_test();               | MUL_zxy()              fmpz_mul
Karatsuba_test();         | KaratsubaMUL()         fmpz_mul
SQU_test();               | SQU_zxx()              fmpz_mul 
KaratsubaSQU_test();      | KaratsubaSQU()         fmpz_mul
NAIVE_div_test();         | NaiveDiv()             fmpz_fdiv_qr
BinaryLongDiv_test();     | BinaryLongDiv()        fmpz_fdiv_qr
DIV_test();               | DIV()                  fmpz_fdiv_qr
MODExp_L2R_test();        | MODExp_L2R()           fmpz_powm
MODExp_R2L_test();        | MODExp_R2L()           fmpz_powm
MODExp_Montgomery_test(); | MODExp_Montgomery      fmpz_powm

�ش� �Լ��� MAX_COUNT���� ���ϰ�, �� ���꿡�� ����Ǵ� ��� case�� ���� 
�����ϱ� ���� ������ case�� ���� ���ڸ� �Է°����� �־��ش�.
�ݺ��� �����ϸ鼭 ����� �ٸ���� ��� �ݺ��� ���߰�, �ش� ������ �Է°�
FLINT, �ְ�â�� ������ ����� ��Ÿ����. 
�������� FLINT�� 10������ ��µȴ�. 
****************************************/

void BASIC_test()                   // �⺻���� bigint ����� Ȯ��
{
    bigint* x = NULL;
    bigint* y = NULL;
#if WORD_BITLEN == 64
    word arr[5] = { 0x1234567890abcdef, 0x1234567890abcdef, 0x1234567890abcdef, 0x1234567890abcdef, 0x1234567890abcdef };
    bi_set_by_array(&x, NON_NEGATIVE, arr, 5);              //�迭 ����ü�� �Է�
    printf("bigint x = ");       bi_show(x, 16);
    bi_gen_rand(&y, NON_NEGATIVE, 5);                       //����ü ���� ����
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
    bi_set_by_string(&a, NON_NEGATIVE, chr2, 2);            // ���ڿ� ����ü�� �Է�
    printf("A -> bigint a = ");      bi_show(a, 2);

    printf("\nstring B = \"%s\"\n", chr16);
    bi_set_by_string(&b, NON_NEGATIVE, chr16, 16);
    printf("B -> bigint b = ");     bi_show(b, 16);

    bi_assign(&b_copy, b);                                  //����ü ����
    printf("bigint b's copy = ");   bi_show(b_copy, 16);

    bi_delete(&x);
    bi_delete(&y);
    bi_delete(&a);
    bi_delete(&b);
    bi_delete(&b_copy);
}

void COMPARE_test()         //bi_compare()
{
    printf("\n< bigint compare > \n");
    bigint* src[2];         src[0] = src[1] = NULL;
    fmpz_t x, y, zero;
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(zero);        fmpz_zero(zero);  //zero�� 0���� ����. 

    int cnt = 0, ans_cm, ans_flint;
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src[0], rand()%2, Wordlen);    //src 2�� ���Ƿ� ����
        bi_gen_rand(&src[1], rand()%2, Wordlen);
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));  // FLINT ��� ���� src�� �Է�
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src[0]))  fmpz_sub(x,zero,x); 
        if(NEGATIVE == get_sign(src[1]))  fmpz_sub(y,zero,y); 

        ans_cm = bi_compare(src[0], src[1]);        // �ְ�â�� compare
        ans_flint = fmpz_cmp(x,y);                  // flint compare
        if(ans_cm != ans_flint)                     //��� Ȯ��
            break;
        cnt++;
    }
    if (cnt != MAX_COUNT)                                   //�ٸ� ����� ������
    { 
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[0], 16);
        printf("B = ");         bi_show(src[1], 16);
        printf("cal = ");
        if(ans_cm == 1)             printf("A > B\n");
        else if(ans_cm == 0)        printf("A = B\n");
        else                        printf("A < B\n");
        printf("real = ");      
        if(ans_flint == 1)          printf("A > B\n");
        else if(ans_flint == 0)     printf("A = B\n");
        else                        printf("A < B\n");
    }
    else                                                    //���� ����
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    bi_delete(&src[0]);         bi_delete(&src[1]);
    fmpz_clear(x);              fmpz_clear(y);              fmpz_clear(zero);
}

void SHIFT_test()           //left_shift(), right_shift()
{
    bigint* src = NULL;
    bigint* srctemp = NULL;

    fmpz_t x, cal;
    fmpz_init(x);           fmpz_init(cal);
    int cnt = 0;
    printf("\n< bigint left shift >\n");
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, NON_NEGATIVE, Wordlen);       bi_assign(&srctemp, src);   // ������ bigint����
        int lshift = rand()%(Wordlen*WORD_BITLEN/2);
        fmpz_set_ui_array(x, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));        // shift���� bigint �Է�

        left_shift(src, lshift);            // �ְ�â�� leftshift
        fmpz_mul_2exp(x,x,lshift);          // FLINT   letfshift
        fmpz_set_ui_array(cal, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if ((fmpz_equal(x, cal) != 1))      break;          // ��� Ȯ��
        cnt++;
    }
    if (cnt != MAX_COUNT)                                   //�ٸ� ��� �ִ°��
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(srctemp, 16);
        printf("cal = ");       bi_show(src, 16);
        printf("real = ");      fmpz_print(x);        printf("\n");
    }
    else                                                    //���� ���� ���
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }

    cnt = 0;
    printf("\n< bigint right shift >\n");
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, NON_NEGATIVE, Wordlen);       bi_assign(&srctemp, src);   // ������ bigint����
        int rshift = rand()%(Wordlen*WORD_BITLEN/2);
        fmpz_set_ui_array(x, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // shift���� bigint �Է�

        right_shift(src, rshift);           // �ְ�â�� leftshift
        fmpz_fdiv_q_2exp(x,x,rshift);       // FLINT   letfshift
        fmpz_set_ui_array(cal, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if ((fmpz_equal(x, cal) != 1))       break; // ��� Ȯ��
        cnt++;
    }
    if (cnt != MAX_COUNT)       //�ٸ� ��� �ִ°��
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(srctemp, 16);
        printf("cal = ");       bi_show(src, 16);
        printf("real = ");      fmpz_print(x);        printf("\n");
    }
    else                          //���� ���� ���    
    {
        printf("%dth test done.\n", MAX_COUNT);     
        printf("All true!\n");
    }
    
    bi_delete(&src);            bi_delete(&srctemp);
    fmpz_clear(x);              fmpz_clear(cal);              
}   

void REDUCTION_test()           // fmpz_cdiv_r_2exp
{
    printf("\n< bigint reduction 2^r(a mod 2^r) >\n");
    bigint* src = NULL;
    bigint* srctemp = NULL;

    fmpz_t x, cal;
    fmpz_init(x);           fmpz_init(cal);
    int cnt = 0;
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, NON_NEGATIVE, Wordlen);       bi_assign(&srctemp, src);       // ���Ƿ� bigint ����
        int r = rand() % (Wordlen*WORD_BITLEN);
        fmpz_set_ui_array(x, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));    //reduction���� bigint FLINT����ü�� 
        
        reduction_2_r(src, r);          //�ְ�â�� reduction
        fmpz_fdiv_r_2exp(x,x,r);        //FLINT reduction
        fmpz_set_ui_array(cal, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if ((fmpz_equal(x, cal) != 1))       break;         // ��� ��
        cnt++;
    }
    if (cnt != MAX_COUNT)               //�ٸ���� �߻�
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(srctemp, 16);
        printf("cal = ");       bi_show(src, 16);
        printf("real = ");      fmpz_print(x);        printf("\n");
    }
    else                                //���� ����
    {
        printf("%dth test done.\n", MAX_COUNT);
        printf("All true!\n");
    }
    
    bi_delete(&src);            bi_delete(&srctemp);
    fmpz_clear(x);              fmpz_clear(cal);
}

void ADD_test()          //ADD_zxy()
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
    fmpz_zero(zero);  //zero�� 0���� ����. 

    int cnt = 0;
    while (cnt < MAX_COUNT)              // case���� src1, src2 ����
    {
        if(cnt < MAX_COUNT/4)       // src[0] = 0
        {
            bi_set_zero(&src[0]);                      
            bi_gen_rand(&src[1], rand()%2, Wordlen);
        }
        else if(cnt < ((MAX_COUNT/4) * 2))  // src[0] > 0 > src[1]
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }
        else if(cnt < ((MAX_COUNT/4)*3)) // 0 <src[0] ,src[1]
        {   
            bi_gen_rand(&src[0], NON_NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else                    // 0 >src[0] ,src[1]
        {
            bi_gen_rand(&src[0], NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }

        ADD_zxy(&dst[0], src[0], src[1]);           //�ְ�â�� ����.
        ADD_zxy(&dst[1], src[1], src[0]);
        
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));      //FLINT ����ü�� ����
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src[0]))  fmpz_sub(x,zero,x); 
        if(NEGATIVE == get_sign(src[1]))  fmpz_sub(y,zero,y); 

        fmpz_add(z[0], x, y);               //FLINT ����
        fmpz_add(z[1], y, x);
        fmpz_set_ui_array(cal0, (const mp_limb_t*)dst[0]->a, (dst[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(cal1, (const mp_limb_t*)dst[1]->a, (dst[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        
        if(NEGATIVE == get_sign(dst[0]))  fmpz_sub(cal0,zero,cal0); 
        if(NEGATIVE == get_sign(dst[1]))  fmpz_sub(cal1,zero,cal1); 

        if ((fmpz_equal(z[0], cal0) != 1)){flag = 0;  break;}       // FLINT�� �ְ�â�� ���� ��� ��
        if ((fmpz_equal(z[1], cal1) != 1)){flag = 1;  break;}
        
        cnt++;
        
    }
    printf("\n");
    if (cnt != MAX_COUNT)                           //�ٸ� ��� �ִ°��
    { 
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("cal = ");       bi_show(dst[flag], 16);
        printf("real = ");      fmpz_print(z[flag]);        printf("\n");
    }
    else                                            //���� ����
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

void SUB_test()             //SUB_zxy()
{
    printf(" < bigint Subtraction > \n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dst[2];         dst[0] = dst[1] = NULL;
    int flag;

    fmpz_t x, y, z[2], cal0, cal1, zero;
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(z[0]);        fmpz_init(z[1]);
    fmpz_init(cal0);        fmpz_init(cal1);
    fmpz_init(zero);        fmpz_zero(zero); //zero�� 0���� ����. 

    int cnt = 0;
    while (cnt < MAX_COUNT)     // case���� src1, src2 ����
    {
        if(cnt < MAX_COUNT/5)       //src1>0>src2
        {
            bi_gen_rand(&src[0], NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else if(cnt < (MAX_COUNT/5)*2)  //src1=0
        {
            bi_set_zero(&src[0]);
            bi_gen_rand(&src[1], rand()%2, Wordlen);
        }
        else if(cnt < (MAX_COUNT/5)*3) // src[0] = src[1]
        {
            bi_gen_rand(&src[0], rand()%2, Wordlen);
            bi_assign(&src[1], src[0]);
        }
        else if(cnt < (MAX_COUNT/5)*4)  //0<src1,src2
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else                             //0>src1,src2
        {
            bi_gen_rand(&src[0], NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }
        
        SUB_zxy(&dst[0], src[0], src[1]);  //�ְ�â�� ����
        SUB_zxy(&dst[1], src[1], src[0]); 
        
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src[0]))  fmpz_sub(x,zero,x); 
        if(NEGATIVE == get_sign(src[1]))  fmpz_sub(y,zero,y); 

        fmpz_sub(z[0], x, y);       // FLINT ����
        fmpz_sub(z[1], y, x);
        fmpz_set_ui_array(cal0, (const mp_limb_t*)dst[0]->a, (dst[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(cal1, (const mp_limb_t*)dst[1]->a, (dst[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        
        if(NEGATIVE == get_sign(dst[0]))  fmpz_sub(cal0,zero,cal0); 
        if(NEGATIVE == get_sign(dst[1]))  fmpz_sub(cal1,zero,cal1); 

        if ((fmpz_equal(z[0], cal0) != 1)){flag = 0;  break;}       //��� ��
        if ((fmpz_equal(z[1], cal1) != 1)){flag = 1;  break;}

        cnt++;
    }
    if (cnt != MAX_COUNT)   // �ٸ� ��� �߻�
    {   
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("cal = ");       bi_show(dst[flag], 16);
        printf("real = ");      fmpz_print(z[flag]);        printf("\n");
    }
    else    //��� ���� ����
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

void MUL_test()     //MUL_zxy() 
{
    printf(" < bigint Multiplication > \n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dst[2];         dst[0] = dst[1] = NULL;
    int flag;

    fmpz_t x, y, z[2], cal0, cal1, zero;
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(z[0]);        fmpz_init(z[1]);
    fmpz_init(cal0);        fmpz_init(cal1);
    fmpz_init(zero);        fmpz_zero(zero); //zero�� 0���� ����. 

    int cnt = 0;
    while (cnt < MAX_COUNT)     // case���� src1, src2 ����
    {
        if(cnt < MAX_COUNT/4)   //src1=0
        {
            bi_set_zero(&src[0]);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else if(cnt < ((MAX_COUNT/4) * 2))  //src1=1
        {
            bi_set_one(&src[0]);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }
        else if(cnt < ((MAX_COUNT/4)*3))    //src1=-1
        {   
            bi_set_minus_one(&src[0]);
            bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
        }
        else        //������ ���Է�
        {
            bi_gen_rand(&src[0], NEGATIVE, Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
        }
        
        MUL_zxy(&dst[0], src[0], src[1]); // �ְ�â�� ����
        MUL_zxy(&dst[1], src[1], src[0]);
               
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src[0]))  fmpz_sub(x,zero,x); 
        if(NEGATIVE == get_sign(src[1]))  fmpz_sub(y,zero,y); 

        fmpz_mul(z[0], x, y);   //FLINT ����
        fmpz_mul(z[1], y, x);

        fmpz_set_ui_array(cal0, (const mp_limb_t*)dst[0]->a, (dst[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(cal1, (const mp_limb_t*)dst[1]->a, (dst[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(dst[0]))  fmpz_sub(cal0,zero,cal0); 
        if(NEGATIVE == get_sign(dst[1]))  fmpz_sub(cal1,zero,cal1); 

        if ((fmpz_equal(z[0], cal0) != 1)){flag = 0;  break;}       //��� ��
        if ((fmpz_equal(z[1], cal1) != 1)){flag = 1;  break;}

        cnt++;
    }
    printf("\n");
    if (cnt != MAX_COUNT)   //�ٸ� ��� �߻�
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("cal = ");       bi_show(dst[flag], 16);
        printf("real = ");      fmpz_print(z[flag]);        printf("\n");
    }
    else  //��� ���� ����
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

void Karatsuba_test()   //KaratsubaMUL()
{
    printf("\n< bigint KARA Multiplication >\n");
    bigint* src[2];         src[0] = src[1] = NULL;
    bigint* dst[2];         dst[0] = dst[1] = NULL;
    int flag;

    fmpz_t x, y, z[2], cal0, cal1, zero;
    fmpz_init(x);           fmpz_init(y);
    fmpz_init(z[0]);        fmpz_init(z[1]);
    fmpz_init(cal0);        fmpz_init(cal1);
    fmpz_init(zero);        fmpz_zero(zero); //zero�� 0���� ����.       

    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src[0], rand()%2, Wordlen);    //������ src1, src2 ����
        bi_gen_rand(&src[1], rand()%2, Wordlen);

        KaratsubaMUL(&dst[0], src[0], src[1]); // �ְ�â�� karatsubaMul
        KaratsubaMUL(&dst[1], src[1], src[0]);
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src[0]))  fmpz_sub(x,zero,x); 
        if(NEGATIVE == get_sign(src[1]))  fmpz_sub(y,zero,y); 

        fmpz_mul(z[0], x, y);   //FLINT ����
        fmpz_mul(z[1], y, x);
        fmpz_set_ui_array(cal0, (const mp_limb_t*)dst[0]->a, (dst[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(cal1, (const mp_limb_t*)dst[1]->a, (dst[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(dst[0]))  fmpz_sub(cal0,zero,cal0); 
        if(NEGATIVE == get_sign(dst[1]))  fmpz_sub(cal1,zero,cal1); 

        if ((fmpz_equal(z[0], cal0) != 1)){flag = 0;  break;}       //�����
        if ((fmpz_equal(z[1], cal1) != 1)){flag = 1;  break;}
        cnt++;
    }
    if (cnt != MAX_COUNT)   //�ٸ� ��� �߻�
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("cal = ");       bi_show(dst[flag], 16);
        printf("real = ");      fmpz_print(z[flag]);        printf("\n");
    }
    else        //��� ���� ����
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

void SQU_test()  //SQU_zxx()
{
    printf("\n< bigint Squaring > \n");
    bigint* src = NULL;
    bigint* dst = NULL;

    fmpz_t x, z, cal, zero;
    fmpz_init(x);           fmpz_init(z);           fmpz_init(cal);
    fmpz_init(zero);        fmpz_zero(zero); //zero�� 0���� ����. 
    
    int cnt = 0;
    while (cnt < MAX_COUNT)   // case���� src1, src2 ����
    {
        if(cnt < MAX_COUNT/4)       //src=0
            bi_set_zero(&src);
        else if(cnt < (MAX_COUNT/4)*2)  //src=1
            bi_set_one(&src);
        else if(cnt < (MAX_COUNT/4)*3)  //src=-1
            bi_set_minus_one(&src);
        else                            //������ src
            bi_gen_rand(&src, rand()%2, Wordlen);

        SQU_zxx(&dst, src);         //�ְ�â�� schoolbook squ

        fmpz_set_ui_array(x, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src))  fmpz_sub(x,zero,x); 
        
        //FLINT ������ �Է¿� �������� �ִ°����� ������ ����
        fmpz_mul(z, x, x);          //FLINT ������ ������ �Է�.
        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(dst))  fmpz_sub(cal,zero,cal); 

        if ((fmpz_equal(z, cal) != 1)){ break;}     //�����
        cnt++;
    }
    if (cnt != MAX_COUNT)       //�ٸ���� �߻�.
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(z); printf("\n");
    }
    else        //��� ���� ����
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

void KaratsubaSQU_test()     //KaratsubaSQU()
{
    printf("\n < bigint karatsuba Squaring > \n");
    bigint* src = NULL;
    bigint* dst = NULL;

    fmpz_t x, z, cal, zero;
    fmpz_init(x);           fmpz_init(z);           fmpz_init(cal);
    fmpz_init(zero);        fmpz_zero(zero); //zero�� 0���� ����.    
    //FLINT ������ �Է¿� �������� �ִ°����� ������ ����
    
    int cnt = 0;
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand()%2, Wordlen);       // src ���Ƿ� ����
        KaratsubaSQU(&dst, src);                    //�ְ�â�� karatsubasqu
        fmpz_set_ui_array(x, (const mp_limb_t*)src->a, (src->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(src))  fmpz_sub(x,zero,x); 

        fmpz_mul(z, x, x);              //FLINT ������ ���� �Է� .
        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        if(NEGATIVE == get_sign(dst))  fmpz_sub(cal,zero,cal); 

        if ((fmpz_equal(z, cal) != 1)){ break;}     // �����
        cnt++;
    }
    if (cnt != MAX_COUNT)   // �ٸ���� �߻�
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");  bi_show(src, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(z); printf("\n");
    }
    else    // ��� ���ε���
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

void NAIVE_div_test()   //NaiveDiv()
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
    while (cnt < MAX_COUNT) // case���� src1, src2 ����
    {
        if(cnt < MAX_COUNT/5) // src2 = 0
        {
            bi_gen_rand(&src[0], rand()%2, 2 * Wordlen);
            bi_set_zero(&src[1]);
            if(INVALID != NaiveDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }    // �ְ�â�� NAIVE DIV
            else{   cnt++; continue;}
        }
        else if(cnt < (MAX_COUNT/5)*2) // src2 < 0
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
            if(INVALID != NaiveDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     } // �ְ�â�� NAIVE DIV
            else{   cnt++; continue;}
        }
        else if(cnt < (MAX_COUNT/5)*3) // src2 = 1�� ��� 
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
            bi_set_one(&src[1]);
            NaiveDiv(&dstQ[0], &dstR[0], src[0], src[1]);   // �ְ�â�� NAIVE DIV
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

        fmpz_fdiv_qr(q[0], r[0], x, y);     //FLINT ������
        fmpz_fdiv_qr(q[1], r[1], y, x);
        fmpz_set_ui_array(calq[0], (const mp_limb_t*)dstQ[0]->a, (dstQ[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calq[1], (const mp_limb_t*)dstQ[1]->a, (dstQ[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[0], (const mp_limb_t*)dstR[0]->a, (dstR[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[1], (const mp_limb_t*)dstR[1]->a, (dstR[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        if ((fmpz_equal(q[0], calq[0]) != 1) || (fmpz_equal(r[0], calr[0]) != 1)){flag = 0;  break;}        //��� ��
        if ((fmpz_equal(q[1], calq[1]) != 1) || (fmpz_equal(r[1], calr[1]) != 1)){flag = 1;  break;}
        cnt++;
    }

    if(flag_valid == 1) // �������� ���ǿ� ���� �ʴ� �Է�(����. �����¼� 0)
    {
        printf("INVALID error\n");
        printf("A = ");  bi_show(src[flag], 16);     printf("B = ");  bi_show(src[flag^1], 16);
        return;
    }
    if (cnt != MAX_COUNT)   //�ٸ� ��� �߻�
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("calQ = ");      bi_show(dstQ[flag], 16);
        printf("calR = ");      bi_show(dstR[flag], 16);
        printf("realQ = ");     fmpz_print(q[flag]); printf("\n");
        printf("realR = ");     fmpz_print(r[flag]); printf("\n");
    }
    else                    //��� ���ε���
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

void BinaryLongDiv_test()       //BinaryLongDiv()
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
    while (cnt < MAX_COUNT) // case���� src1, src2 ����
    {
        if(cnt < MAX_COUNT/5) // src2 = 0
        {
            bi_gen_rand(&src[0], rand()%2, 2 * Wordlen);
            bi_set_zero(&src[1]);
            if(INVALID != BinaryLongDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }  //�ְ�â�� Binarydiv
            else{   cnt++; continue;}
        }
        else if(cnt < (MAX_COUNT/5)*2) // src2 < 0
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
            if(INVALID != BinaryLongDiv(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }   //�ְ�â�� Binarydiv
            else{   cnt++; continue;}
        }
        else
        {
            while (1)
            {
                bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
                bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
                if(VALID == BinaryLongDiv(&dstQ[0], &dstR[0], src[0], src[1]) && VALID == BinaryLongDiv(&dstQ[1], &dstR[1], src[1], src[0]))    //�ְ�â�� Binarydiv
                    break;
            }
        }
        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        fmpz_fdiv_qr(q[0], r[0], x, y); // FLINT ������
        fmpz_fdiv_qr(q[1], r[1], y, x);
        fmpz_set_ui_array(calq[0], (const mp_limb_t*)dstQ[0]->a, (dstQ[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calq[1], (const mp_limb_t*)dstQ[1]->a, (dstQ[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[0], (const mp_limb_t*)dstR[0]->a, (dstR[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[1], (const mp_limb_t*)dstR[1]->a, (dstR[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        if ((fmpz_equal(q[0], calq[0]) != 1) || (fmpz_equal(r[0], calr[0]) != 1)){flag = 0;  break;}
        if ((fmpz_equal(q[1], calq[1]) != 1) || (fmpz_equal(r[1], calr[1]) != 1)){flag = 1;  break;}
        cnt++;
    }
    if(flag_valid == 1) // �������� ���ǿ� ���� �ʴ� �Է�(����. �����¼� 0)
    {
        printf("INVALID error\n");
        printf("A = ");  bi_show(src[flag], 16);     printf("B = ");  bi_show(src[flag^1], 16);
        return;
    }
    if (cnt != MAX_COUNT)   //�ٸ� ��� �߻�
    {
        
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("calQ = ");      bi_show(dstQ[flag], 16);
        printf("calR = ");      bi_show(dstR[flag], 16);
        printf("realQ = ");     fmpz_print(q[flag]); printf("\n");
        printf("realR = ");     fmpz_print(r[flag]); printf("\n");
    }
    else        // ���� ����
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

void DIV_test()  //DIV()
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
    while (cnt < MAX_COUNT) // case���� src1, src2 ����
    { 
        if(cnt < MAX_COUNT/3) 
        {
            bi_gen_rand(&src[0], rand()%2, 2 * Wordlen);
            bi_set_zero(&src[1]);
            if(INVALID != DIV(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }     //�ְ�â�� DIV
            else{   cnt++; continue;}
        }
        else if(cnt < (MAX_COUNT/3)*2) // src2 < 0
        {
            bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
            bi_gen_rand(&src[1], NEGATIVE, Wordlen);
            if(INVALID != DIV(&dstQ[0], &dstR[0], src[0], src[1])){   flag = 0;    flag_valid = 1;     break;     }       //�ְ�â�� DIV
            else{   cnt++; continue;}
        }
        else
        {
            while (1)
            {
                bi_gen_rand(&src[0], NON_NEGATIVE, 2 * Wordlen);
                bi_gen_rand(&src[1], NON_NEGATIVE, Wordlen);
                if(VALID == DIV(&dstQ[0], &dstR[0], src[0], src[1]) && VALID == DIV(&dstQ[1], &dstR[1], src[1], src[0]))    //�ְ�â�� DIV
                    break;
            }
        }
      

        fmpz_set_ui_array(x, (const mp_limb_t*)src[0]->a, (src[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(y, (const mp_limb_t*)src[1]->a, (src[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        fmpz_fdiv_qr(q[0], r[0], x, y);     //FLINT ������
        fmpz_fdiv_qr(q[1], r[1], y, x);
        fmpz_set_ui_array(calq[0], (const mp_limb_t*)dstQ[0]->a, (dstQ[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calq[1], (const mp_limb_t*)dstQ[1]->a, (dstQ[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[0], (const mp_limb_t*)dstR[0]->a, (dstR[0]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));
        fmpz_set_ui_array(calr[1], (const mp_limb_t*)dstR[1]->a, (dstR[1]->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        if ((fmpz_equal(q[0], calq[0]) != 1) || (fmpz_equal(r[0], calr[0]) != 1)){flag = 0;  break;}    // ��� ��
        if ((fmpz_equal(q[1], calq[1]) != 1) || (fmpz_equal(r[1], calr[1]) != 1)){flag = 1;  break;}
        cnt++;  
    }
    if(flag_valid == 1)     // �������� ���ǿ� ���� �ʴ� �Է�(����. �����¼� 0)
    {
        printf("INVALID error\n");
        printf("A = ");  bi_show(src[flag], 16);     printf("B = ");  bi_show(src[flag^1], 16);
        return;
    }
    if (cnt != MAX_COUNT)       // �ٸ� ��� �߻�
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("A = ");         bi_show(src[flag], 16);
        printf("B = ");         bi_show(src[flag^1], 16);
        printf("calQ = ");      bi_show(dstQ[flag], 16);
        printf("calR = ");      bi_show(dstR[flag], 16);
        printf("realQ = ");     fmpz_print(q[flag]); printf("\n");
        printf("realR = ");     fmpz_print(r[flag]); printf("\n");
    }
    else            //���� ����
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


void MODExp_L2R_test()      //MODExp_L2R()
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
        bi_gen_rand(&base, NON_NEGATIVE, Wordlen);      // ���Ƿ� base,power,M ����
        bi_gen_rand(&power, NON_NEGATIVE, Wordlen); 
        bi_gen_rand(&M, NON_NEGATIVE, Wordlen);
        while (!bi_is_zero(M)) // M != 0�̿��� �� 
            bi_gen_rand(&M, NON_NEGATIVE, Wordlen);

        MODExp_L2R(&dst, base, power, M);   //�ְ�â�� ��ⷯ������
       
        fmpz_set_ui_array(g, (const mp_limb_t*)base->a, (base->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // g = base
        fmpz_set_ui_array(e, (const mp_limb_t*)power->a, (power->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // e = power
        fmpz_set_ui_array(m, (const mp_limb_t*)M->a, (M->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); //m = M

        fmpz_powm(f, g, e, m);      //FLINT ��ⷯ ������

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        if ((fmpz_equal(f, cal) != 1))  // ��� Ȯ��
            break; 
        cnt++;

    }
    printf("\n");
    if (cnt != MAX_COUNT)       //�ٸ� ���� �ִ� ���
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("base = ");  bi_show(base, 10);
        printf("power = ");  bi_show(power, 10);
        printf("M = ");  bi_show(M, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(f); printf("\n");
    }
    else        // ���� ����
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


void MODExp_R2L_test()           //MODExp_R2L()
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
        bi_gen_rand(&base, NON_NEGATIVE, Wordlen); // ���Ƿ� base,power,M ����
        bi_gen_rand(&power, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&M, NON_NEGATIVE, Wordlen);
        while (!bi_is_zero(M))
            bi_gen_rand(&M, NON_NEGATIVE, Wordlen);

        MODExp_R2L(&dst, base, power, M);   // �ְ�â�� ��ⷯ������

        fmpz_set_ui_array(g, (const mp_limb_t*)base->a, (base->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // g = base
        fmpz_set_ui_array(e, (const mp_limb_t*)power->a, (power->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // e = power
        fmpz_set_ui_array(m, (const mp_limb_t*)M->a, (M->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // m = M

        fmpz_powm(f, g, e, m);              //FLINT ��ⷯ������

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        if ((fmpz_equal(f, cal) != 1)) // ��� Ȯ��
            break; 
        cnt++;

    }
    printf("\n");
    if (cnt != MAX_COUNT)       // �ٸ� ���� �ִ� ���
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("base = ");  bi_show(base, 10);
        printf("power = ");  bi_show(power, 10);
        printf("M = ");  bi_show(M, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(f); printf("\n");
    }
    else        // ���� ����
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

void MODExp_Montgomery_test()   //MODExp_Montgomery
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
        bi_gen_rand(&base, NON_NEGATIVE, Wordlen);      // ���Ƿ� base,power,M ����
        bi_gen_rand(&power, NON_NEGATIVE, Wordlen);
        bi_gen_rand(&M, NON_NEGATIVE, Wordlen);
        while (!bi_is_zero(M))
            bi_gen_rand(&M, NON_NEGATIVE, Wordlen);

        MODExp_Montgomery(&dst, base, power, M); // �ְ�â�� ��ⷯ������
        

        fmpz_set_ui_array(g, (const mp_limb_t*)base->a, (base->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // g = base
        fmpz_set_ui_array(e, (const mp_limb_t*)power->a, (power->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // e = power
        fmpz_set_ui_array(m, (const mp_limb_t*)M->a, (M->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN)); // m = M

        fmpz_powm(f, g, e, m);      //FLINT ��ⷯ������

        fmpz_set_ui_array(cal, (const mp_limb_t*)dst->a, (dst->wordlen+(64/WORD_BITLEN -1))/(64/WORD_BITLEN));

        if ((fmpz_equal(f, cal) != 1))  // �ο��� ��� ��
            break; 
        cnt++;

    }
    printf("\n");
    if (cnt != MAX_COUNT)               // �ٸ� ��� �ִ� ���
    {
        printf("False %dth calculation\n", cnt + 1);
        printf("base = ");  bi_show(base, 10);
        printf("power = ");  bi_show(power, 10);
        printf("M = ");  bi_show(M, 10);
        printf("cal = ");  bi_show(dst, 10);
        printf("real = ");   fmpz_print(f); printf("\n");
    }
    else                                //���� ����
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
