#include "benchmark.h"
// fmpz_powm(z,x,y,a);
// fmpz_print(z);
// flint_printf("\n");

//fmpz_add(z,x,y); add 
//fmpz_sub(z,x,y); sub 
//fmpz_mul(z,x,y); mul
    
//fmpz_print(z);
//flint_printf("\n");
    
// fmpz_fdiv_qr(q,r,x,y); div

// fmpz_print(q);
// flint_printf("\n");
// fmpz_print(r);
// flint_printf("\n");
// gcc -Wall -O2 *.c -I /usr/local/include/flint/ -lflint -lmpfr -lgmp -lpthread

int wordlen = 10; // 512-> 8, 1024 -> 16, 2048 -> 32, 3072 -> 48, 4096 -> 64
// RSA PARAMETER? ?™?˜™ ?‘œ? ?™?˜™ ? ?Œ“ë¤„ì˜™? ?™?˜™? ? ?Œê¹ì˜™
// PARAMETER ?¬? ?©ë³„å ?™?˜™ ? ?™?˜™? -> ? ?Œ“ë¤„ì˜™? ?™?˜™? ?™?˜™ ? ?Œê³¤ì˜™ ? ????‡½?˜™? ?™?˜™ ? ?™?˜™? ?™?˜™? ?‹¶ê³¤ì˜™? ?™?˜™? ?™?˜™... // 
// wordlen -> karatsuba? ?™?˜™? ?™?˜™(8-100) ->  4? ?™?˜™? ?™?˜™? ?™?˜™!

// iso? ?™?˜™? ?™?˜™? bin ?¬? ?™?˜™ ? ?™?˜™ ? 


void ADD_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ?œ?¤?•˜ê²? ?ƒ?„± 
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen); // x = src1
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen); // y = src2

    clock_t start, end; 
    double result_ac, result_af;

    int cnt = 0;
    start = clock();
    while(cnt < MAX_COUNT)
    {
        ADD_zxy(&dst, src1, src2);
        ADD_zxy(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_ac = (double)(end - start)/(double)CLOCKS_PER_SEC;
    
    cnt = 0;
    start = clock();
    while(cnt < MAX_COUNT)
    {
        fmpz_add(z,x,y);
        fmpz_add(y,z,x);
        cnt++;
    }
    end = clock(); 
    result_af = (double)(end - start)/(double)CLOCKS_PER_SEC;
    printf("[ADD | CM vs FLINT] %f %f\n", result_ac, result_af);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
}

void SUB_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ?œ?¤?•˜ê²? ?ƒ?„± 
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen); // x = src1
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen); // y = src2

    clock_t start, end; 
    double result_sc, result_sf;

    int cnt = 0;
    start = clock();
    while(cnt < MAX_COUNT)
    {
        SUB_zxy(&dst, src1, src2);
        SUB_zxy(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_sc = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0;
    start = clock();
    while(cnt < MAX_COUNT)
    {
        fmpz_sub(z,x,y);
        fmpz_sub(y,z,x);
        cnt++;
    }
    end = clock(); 
    result_sf = (double)(end - start)/(double)CLOCKS_PER_SEC;
    printf("[SUB | CM vs FLINT] %f %f\n", result_sc, result_sf);
    
    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
}

void MUL_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ?œ?¤?•˜ê²? ?ƒ?„± 
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen); // x = src1
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen); // y = src2

    clock_t start, end; 
    double result_mc, result_mf;

    int cnt = 0;
    start = clock();
    while(cnt < MAX_COUNT)
    {
        //MUL_zxy(&dst, src1, src2);
        //MUL_zxy(&src2, dst, src1);
        KaratsubaMUL(&dst, src1, src2);
        KaratsubaMUL(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_mc = (double)(end - start)/(double)CLOCKS_PER_SEC;   

    cnt = 0;
    start = clock();
    while(cnt < MAX_COUNT)
    {
        fmpz_mul(z,x,y);
        fmpz_mul(y,z,x);
        cnt++;
    }
    end = clock(); 
    result_mf = (double)(end - start)/(double)CLOCKS_PER_SEC;
    printf("[MUL | CM vs FLINT] %f %f\n", result_mc, result_mf);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
}


void Kara_flag() 
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    int cnt = 0, flag = 2; 
    clock_t start, end; 
    double result;

    bi_gen_rand(&src1, NON_NEGATIVE, 2*wordlen);
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    while(flag < wordlen)
    {
        cnt = 0;
        start = clock();
        while(cnt < MAX_COUNT)
        {
            KaratsubaMUL_Flag(&dst, src1, src2, flag);
            cnt=cnt+4;
        }
        end = clock(); 
        result = (double)(end - start) / (double)CLOCKS_PER_SEC;
        printf("[Karatsuba | CM] %f (flag = %d)\n", result, flag);
        flag++;
    }
    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
}

void MULvsKara() // ? ?™?˜™? ?™?˜™: schoolbook vs. Karatsuba
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ?œ?¤?•˜ê²? ?ƒ?„± 
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    bigint* src1_t = NULL;
    bigint* src2_t = NULL;
    bigint* dst_t = NULL;
    bi_assign(&src1_t, src1); // src1_t = src1
    bi_assign(&src2_t, src2); // src2_t = src2

    clock_t start, end; 
    double result_mul, result_kara;

    int cnt = 0; 
    start = clock();
    while(cnt < MAX_COUNT)
    {
        MUL_zxy(&dst, src1, src2);
        MUL_zxy(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_mul = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0; 
    start = clock();
    while(cnt < MAX_COUNT)
    {
        KaratsubaMUL(&dst_t, src1_t, src2_t);
        KaratsubaMUL(&src2_t, dst_t, src1_t);
        cnt++;
    }
    end = clock(); 
    result_kara = (double)(end - start)/(double)CLOCKS_PER_SEC;
    printf("[MUL vs Karatsuba | CM] %f %f\n", result_mul, result_kara);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
    bi_delete(&src1_t);
    bi_delete(&src2_t);
    bi_delete(&dst_t);
}

void MULvsSQU() 
{
    bigint* src = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src, NON_NEGATIVE, wordlen); // src ?œ?¤?•˜ê²? ?ƒ?„± 

    bigint* src_t = NULL;
    bigint* dst_t = NULL;
    bi_assign(&src_t, src); // src1_t = src1

    clock_t start, end; 
    double result_mul, result_squ;

    int cnt = 0; 
    start = clock();
    while(cnt < MAX_COUNT)
    {
        MUL_zxy(&dst, src, src);
        //MUL_zxy(&src, dst, dst);
        cnt++;
    }
    end = clock(); 
    result_mul = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0; 
    start = clock();
    while(cnt < MAX_COUNT)
    {
        SQU_zxx(&dst_t, src_t);
        //SQU_zxx(&src_t, dst_t);
        cnt++;
    }
    end = clock(); 
    result_squ = (double)(end - start)/(double)CLOCKS_PER_SEC;
    printf("[MUL vs SQU | CM] %f %f\n", result_mul, result_squ);

    bi_delete(&src);
    bi_delete(&dst);
    bi_delete(&src_t);
    bi_delete(&dst_t);
}
//////////////////////////////////////////////////////////////////////////////////////////
void SQUvsKara() // ? ?™?˜™? ?™?˜™: schoolbook vs. Karatsuba
{
    bigint* src = NULL;
    bigint* dst = NULL;

    bi_gen_rand(&src, NON_NEGATIVE, wordlen);

    int cnt = 0;
    clock_t start, end;
    double result_squ, result_ka;

    start = clock();
    while (cnt < MAX_COUNT)
    {
        SQU_zxx(&dst, src);
        cnt++;
    }
    end = clock();
    result_squ = (double)(end - start)/(double)CLOCKS_PER_SEC;


    cnt = 0;
    start = clock();
    while (cnt < MAX_COUNT)
    {
        KaratsubaSQU(&dst, src);
        cnt++;
    }
    end = clock();
    result_ka = (double)(end - start)/(double)CLOCKS_PER_SEC;

    printf("[SQU vs Karatsuba | CM] %f %f\n", result_squ, result_ka);
    bi_delete(&src);
    bi_delete(&dst);

}

void NAIVEvsBINARYLONGvsMULTIDIV() // Naive vs. binary long vs. multi-precision long
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;

    bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen);
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    while (VALID != DIV(&dstQ, &dstR, src1, src2))
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, wordlen);
    }

    int cnt = 0;

    clock_t start, end;
    double result_nai, result_bin, result_mul;
    start = clock();
    while (cnt < MAX_COUNT)
    {
        NaiveDiv(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_nai = (double)(end - start) / CLOCKS_PER_SEC;

    cnt = 0;
    start = clock();
    while (cnt < MAX_COUNT)
    {
        BinaryLongDiv(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_bin = (double)(end - start) / CLOCKS_PER_SEC;

    cnt = 0;
    start = clock();
    while (cnt < MAX_COUNT)
    {
        DIV(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_mul = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[NAIVE vs Binary vs Multi | CM] %f %f %f\n", result_nai, result_bin, result_mul);
    bi_delete(&dstQ);
    bi_delete(&dstR);
    bi_delete(&src1);
    bi_delete(&src2);
}

void DIV_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;

    bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen);
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    while (VALID != DIV(&dstQ, &dstR, src1, src2))
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, wordlen);
    }

    fmpz_t f, s, g, h;
    fmpz_init(f);
    fmpz_init(s);
    fmpz_init(g);
    fmpz_init(h);

    fmpz_set_ui_array(g, (const mp_limb_t*)src1->a, src1->wordlen);
    fmpz_set_ui_array(h, (const mp_limb_t*)src2->a, src2->wordlen);

    clock_t start, end;
    double result_dc, result_df;

    int cnt = 0;

    start = clock();
    while (cnt < MAX_COUNT)
    {
        DIV(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_dc = (double)(end - start) / CLOCKS_PER_SEC;


    cnt = 0;
    start = clock();
    while (cnt < MAX_COUNT)
    {
        fmpz_fdiv_qr(f, s, g, h);
        cnt++;
    }
    end = clock();
    result_df = (double)(end - start) / CLOCKS_PER_SEC;
    printf("[DIV | CM vs FLINT] %f %f\n", result_dc, result_df);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dstQ);
    bi_delete(&dstR);

    fmpz_clear(f);
    fmpz_clear(s);
    fmpz_clear(g);
    fmpz_clear(h);
}

void EXPMOD_FLINTvsCM()
{
    bigint* base = NULL;
    bigint* power = NULL;
    bigint* dst = NULL;
    bigint* M = NULL;

    bi_gen_rand(&base, NON_NEGATIVE, wordlen);
    bi_gen_rand(&power,  NON_NEGATIVE, wordlen);
    bi_gen_rand(&M, NON_NEGATIVE, wordlen);
    while (!bi_is_zero(M))
        bi_gen_rand(&M, NON_NEGATIVE, wordlen);

    fmpz_t f, g, e, m;
    fmpz_init(f);
    fmpz_init(g);
    fmpz_init(e);
    fmpz_init(m);
    //bi_show(base,10);
    fmpz_set_ui_array(g, (const mp_limb_t*)base->a, base->wordlen); // x = src1
    //fmpz_print(g);
    fmpz_set_ui_array(e, (const mp_limb_t*)power->a, power->wordlen); // y = src2
    fmpz_set_ui_array(m, (const mp_limb_t*)M->a, M->wordlen); // y = src2

    clock_t start, end;
    double result_ec, result_ef;

    int cnt = 0;

    start = clock();
    while (cnt < MAX_COUNT)
    {
        MODExp_L2R(&dst, base, power, M);
        //MODExp_L2R(&power, dst, base, M);
        cnt++;
    }
    end = clock();
    result_ec = (double)(end - start) / CLOCKS_PER_SEC;


    cnt = 0;
    start = clock();
    while (cnt < MAX_COUNT)
    {
        fmpz_powm(f, g, e, m);
        //fmpz_powm(e, f, g, m);
        cnt++;
    }
    end = clock();
    result_ef = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[EXPMOD | CM vs FLINT] %f %f\n", result_ec, result_ef);
    bi_delete(&base);
    bi_delete(&power);
    bi_delete(&M);
    bi_delete(&dst);
    fmpz_clear(f);
    fmpz_clear(g);
    fmpz_clear(e);
    fmpz_clear(m);
}

void EXPMOD_test() // ? ?™?˜™? ?™?˜™? ?™?˜™? ????
{

}
// ? ?™?˜™? ?™?˜™? ?™?˜™ ? ?™?˜™? ?™?˜™..

// time.c // ? ?™?˜™?˜¸? ?‹¯ê³¤ì˜™? ?™?˜™? ?™?˜™? ?‹?°?˜™? ?™?˜™?•…? ? ? ?Œˆ?“¸?˜™? ?™?˜™ -> 1024, 2048? ?™?˜™?Š¸
// void mod_test() // ? ?™?˜™? ?™?˜™? ?™?˜™? ????
// ? ?Œ“ë¤„ì˜™? ?™?˜™???? -> ?‘œ??? -> overleaf 

// 1 : time.c ??? ? ?™?˜™? ?™?˜™ & ? ?Œ?‡½?˜™  -> ? ?‹±ê³¤ì˜™ ? ?™?˜™? ?™?˜™? ?‹¹ê¹ì˜™ 
// 2 : sage while? ?™?˜™ ? ?™?˜™? ?™?˜™ & ? ?Œ?‡½?˜™ -> ? ?™?˜™? ?™?˜™ç§Šå ? while()

// ? ?™?˜™? ?™?˜™ : ? ?Œ¥ë±„ì˜™ ? ?™?˜™? ?™?˜™? ?™?˜™ ? ?Œ˜?“¸?˜™ ? ?™?˜™? ?™?˜™ 

///////////////// ? ?Œ¥ë±„ì˜™ ? ?‹¬?“¸?˜™? ? ?‹¹?š¸?˜™? ?™?˜™ 2? ?™?˜™ ////////////////////////

// 1: overleaf? ?™?˜™? ?Œ•ê³¤ì˜™ ? ?™?˜™? ? ? ?Œœ?‡½?˜™(? ?™?˜™?˜¸? ?‹¯ê³¤ì˜™? ?™?˜™? ?™?˜™? ?‹?°?˜™? ?™?˜™?•…? ? ? ?Œˆ?“¸?˜™? ?™?˜™ -> 1024, 2048? ?™?˜™?Š¸)
// 2: overleaf ? ?‹ ?Œ?˜™? ?™?˜™ ? ?Œœ?‡½?˜™ & readme? ?Œœ?‡½?˜™ 

/////////////////////// ?™”,? ?™?˜™? ?™?˜™ ? ?™?˜™? ?™?˜™? ?™?˜™ ? ?™?˜™ ////////////////////////

// test code ? ?™?˜™? ?™?˜™? ? ? ?™?˜™? ?™?˜™? ?‹¹ê³¤ì˜™ ? ?Œ?Š”ê³¤ì˜™ -> ? ?™?˜™? ?™?˜™? ?™?˜™ appendix? ?™?˜™ ? ?™?˜™? ?‹±ê¹ì˜™ 

// ? ?‹¹?š¸?˜™? ?‹¹?š¸?˜™? ?™?˜™ ? ?™?˜™? ?˜?„ ? ?™?˜™? ?™?˜™ ? ?™?˜™? ?™?˜™... -> 15? ?™?˜™...? ?™?˜™ 