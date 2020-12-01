#include "benchmark.h"
// fmpz_powm(z,x,y,a);
// fmpz_print(z);
// flint_printf("\n");

//fmpz_add(z,x,y); add 
//fmpz_SUB_zxy(z,x,y); sub 
//fmpz_MUL_zxy(z,x,y); mul
    
//fmpz_print(z);
//flint_printf("\n");
    
// fmpz_fdiv_qr(q,r,x,y); div

// fmpz_print(q);
// flint_printf("\n");
// fmpz_print(r);
// flint_printf("\n");
// gcc -Wall -O2 *.c -I /usr/local/include/flint/ -lflint -lmpfr -lgmp -lpthread

int wordlen = 10; // 512-> 8, 1024 -> 16, 2048 -> 32, 3072 -> 48, 4096 -> 64
// RSA PARAMETERï¿½ï¿½ Ç¥ï¿½ï¿½ ï¿½×·ï¿½ï¿½ï¿½? ï¿½Ö±ï¿½
// PARAMETER Å©ï¿½âº°ï¿½ï¿½ ï¿½ï¿½? -> ï¿½×·ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö°ï¿½ ï¿½Ò¼ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Í°ï¿½ï¿½ï¿½ï¿½ï¿½... // 
// wordlen -> karatsubaï¿½ï¿½ï¿½ï¿½(8-100) ->  4ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½!

// isoï¿½ï¿½ï¿½ï¿½? bin Å©ï¿½ï¿½ ï¿½ï¿½ ? 


void ADD_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ·£´ýÇÏ°Ô »ý¼º 
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, wordlen); // x = src1
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, wordlen); // y = src2

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
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ·£´ýÇÏ°Ô »ý¼º 
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, wordlen); // x = src1
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, wordlen); // y = src2

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
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ·£´ýÇÏ°Ô »ý¼º 
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, wordlen); // x = src1
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, wordlen); // y = src2

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

    while(flag < (wordlen/2))
    {
        cnt = 0;
        start = clock();
        while(cnt < MAX_COUNT)
        {
            bi_gen_rand(&src1, rand()%2, wordlen);
            bi_gen_rand(&src2, rand()%2, wordlen);
            KaratsubaMUL_Flag(&dst, src1, src2, flag);
            bi_delete(&src1);
            bi_delete(&src2);
            bi_delete(&dst);
            cnt++;
        }
        end = clock(); 
        result = (double)(end - start) / (double)CLOCKS_PER_SEC;
        printf("[Karatsuba | CM] %f (flag = %d)\n", result, flag);
        flag++;
    }

}

void MULvsKara() // ï¿½ï¿½ï¿½ï¿½: schoolbook vs. Karatsuba
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ·£´ýÇÏ°Ô »ý¼º 
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
    bi_gen_rand(&src, NON_NEGATIVE, wordlen); // src ·£´ýÇÏ°Ô »ý¼º 

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
        MUL_zxy(&src, dst, dst);
        cnt++;
    }
    end = clock(); 
    result_mul = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0; 
    start = clock();
    while(cnt < MAX_COUNT)
    {
        SQU_zxx(&dst_t, src_t);
        SQU_zxx(&src_t, dst_t);
        cnt++;
    }
    end = clock(); 
    result_squ = (double)(end - start)/(double)CLOCKS_PER_SEC;
    printf("[MUL vs SQU | CM] %f %f\n", result_mul, result_squ);

    bi_delete(src);
    bi_delete(dst);
    bi_delete(src_t);
    bi_delete(dst_t);
}
//////////////////////////////////////////////////////////////////////////////////////////
void SQUvsKara() // ï¿½ï¿½ï¿½ï¿½: schoolbook vs. Karatsuba
{
    bigint* src = NULL;
    bigint* dst = NULL;
    int cnt , wordlen = 100;
        
    cnt = 0;
    clock_t startsqu, endsqu;
    double resultsqu;
    startsqu = clock();
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand() % 2, wordlen);
        SQU_zxx(&dst, src);
        bi_delete(&src);
        bi_delete(&dst);
        cnt++;
    }
    endsqu = clock();
    resultsqu = (double)(endsqu - startsqu)/CLOCKS_PER_SEC;
    //printf("squaring = %f\n", (resultsqu - result_single_c) / CLOCKS_PER_SEC);


    cnt = 0;
    clock_t startka, endka;
    int flag = 2;  // ï¿½Ì°Å´ï¿½ ï¿½Ä¿ï¿½ ï¿½Ù½Ã¼ï¿½ï¿½ï¿½
    double resultka;
    startka = clock();
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand() % 2, wordlen);
        SQUCKaratsuba(&dst, src, flag);
        bi_delete(&src);
        bi_delete(&dst);
        cnt++;
    }
    endka = clock();
    resultka = (double)(endka - startka)/CLOCKS_PER_SEC;
    //printf("karatsuba squaring = %f\n", (resultka - result_single_c) / CLOCKS_PER_SEC);
    printf("[SQU vs Karatsuba | CM] %f %f\n",resultsqu,resultka);

}

void NAIVEvsBINARYLONGvsMULTIDIV() // Naive vs. binary long vs. multi-precision long
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;
    int cnt , wordlen = 100;

    cnt = 0;
    clock_t startnai, endnai;
    double resultnai;
    startnai = clock();
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand() % 2, wordlen);
        bi_gen_rand(&src2, rand() % 2, wordlen);

        if(VALID==NaiveDiv(&dstQ, &dstR, src1, src2))
            cnt++;
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
    }
    endnai = clock();
    resultnai = (double)(endnai - startnai) / CLOCKS_PER_SEC;
    //printf("NAIVE_DIV = %f\n", (resultnai - result_c) / CLOCKS_PER_SEC);


    cnt = 0;
    clock_t startbin, endbin;
    double resultbin;
    startbin = clock();
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand() % 2, wordlen);
        bi_gen_rand(&src2, rand() % 2, wordlen);

        if (VALID == BinaryLongDiv(&dstQ, &dstR, src1, src2))
            cnt++;
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
    }
    endbin = clock();
    resultbin = (double)(endbin - startbin) / CLOCKS_PER_SEC;
    //printf("BinaryLongDiv = %f\n", (resultbin - result_c) / CLOCKS_PER_SEC);


    cnt = 0;
    clock_t startmul, endmul;
    double resultmul;
    startmul = clock();
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand() % 2, wordlen);
        bi_gen_rand(&src2, rand() % 2, wordlen);

        if (VALID == DIV(&dstQ, &dstR, src1, src2))
            cnt++;
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
    }
    endmul = clock();
    resultmul = (double)(endmul - startmul) / CLOCKS_PER_SEC;
    //printf("multi_precision_DIV = %f\n", (resultmul - result_c) / CLOCKS_PER_SEC);
    printf("[NAIVE vs Binary vs Multi | CM] %f %f %f\n",resultnai, resultbin, resultmul);
}

void DIV_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;

    int cnt = 0;

    clock_t startc, endc;
    double resultc;
    startc = clock();

    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, wordlen);
        if (VALID == DIV(&dstQ, &dstR, src1, src2))
            cnt++;
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
    }
    endc = clock();
    resultc = (double)(endc - startc) / CLOCKS_PER_SEC;
    //printf("CM DIV = %f\n", (resultc - result_c) / CLOCKS_PER_SEC);


    fmpz_t f, s, g, h;
    fmpz_init(f);
    fmpz_init(s);
    fmpz_init(g);
    fmpz_init(h);
    FLINT_TEST_INIT(state);
    cnt = 0;

    clock_t startf, endf;
    double resultf;
    startf = clock();
    while (cnt < MAX_COUNT)
    {
        fmpz_randtest(g, state, wordlen * WORD_BITLEN);
        do {
            fmpz_randtest(h, state, wordlen * WORD_BITLEN);
        } while (fmpz_is_zero(h));

        fmpz_fdiv_qr(f, s, g, h);
        cnt++;
    }
    endf = clock();
    resultf = (double)(endf - startf) / CLOCKS_PER_SEC;
    printf("[DIV | CM vs FLINT] %f %f\n",resultc, resultf);
    //printf("FLINT DIV = %f\n", (resultf - result_f) / CLOCKS_PER_SEC);
    fmpz_clear(f);
    fmpz_clear(s);
    fmpz_clear(g);
    fmpz_clear(h);

    FLINT_TEST_CLEANUP(state);
}

void EXPMOD_FLINTvsCM()
{
    bigint* base = NULL;
    bigint* power = NULL;
    bigint* dst = NULL;
    int cnt = 0, wordlen = 100;
    int modn = 50;

    cnt = 0;
    clock_t startc, endc;
    double resultc;
    startc = clock();
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&base, rand() % 2, wordlen);
        bi_gen_rand(&power, rand() % 2, wordlen);
        L2R(&dst, base, power, modn);
        bi_delete(&base);
        bi_delete(&power);
        bi_delete(&dst);
        cnt++;
    }
    endc = clock();
    resultc = (double)(endc - startc) / CLOCKS_PER_SEC;
    //printf("CM expmod = %f\n", (resultc - result_c) / CLOCKS_PER_SEC);


    fmpz_t f, g, e, m;
    fmpz_init(f);
    fmpz_init(g);
    fmpz_init(e);
    fmpz_init(m);

    FLINT_TEST_INIT(state);
    cnt = 0;

    clock_t startf, endf;
    double resultf;
    startf = clock();
    while (cnt < MAX_COUNT)
    {
        fmpz_randtest(g, state, wordlen * WORD_BITLEN);
        fmpz_randtest_unsigned(e, state, wordlen * WORD_BITLEN);
        fmpz_randtest_not_zero(m, state, wordlen * WORD_BITLEN);
        fmpz_abs(m, m);
        fmpz_powm(f, g, e, m);  
        cnt++;
    }
    endf = clock();
    resultf = (double)(endf - startf) / CLOCKS_PER_SEC;
    //printf("FLINT expmod = %f\n", (resultf-result_c) / CLOCKS_PER_SEC);
    printf("[EXPMOD | CM vs FLINT] %f %f\n",resultc, resultf);
    fmpz_clear(f);
    fmpz_clear(g);
    fmpz_clear(e);
    fmpz_clear(m);
    FLINT_TEST_CLEANUP(state);
}

void EXPMOD_test() // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿????
{

}
// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½..

// time.c // ï¿½ï¿½È£ï¿½Ë°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä¶ï¿½ï¿½ï¿½Íºï¿? ï¿½Óµï¿½ï¿½ï¿½ -> 1024, 2048ï¿½ï¿½Æ®
// void mod_test() // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿????
// ï¿½×·ï¿½ï¿½ï¿½???? -> Ç¥??? -> overleaf 

// 1 : time.c Æ² ï¿½ï¿½ï¿½ï¿½ & ï¿½Ö¼ï¿½  -> ï¿½Ì°ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï±ï¿½ 
// 2 : sage whileï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ & ï¿½Ö¼ï¿½ -> ï¿½ï¿½ï¿½ï¿½Ò¶ï¿? while()

// ï¿½ï¿½ï¿½ï¿½ : ï¿½Ý¹ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Úµï¿½ ï¿½ï¿½ï¿½ï¿½ 

///////////////// ï¿½Ý¹ï¿½ ï¿½Éµï¿½? ï¿½Ï¿ï¿½ï¿½ï¿½ 2ï¿½ï¿½ ////////////////////////

// 1: overleafï¿½ï¿½ï¿½Ù°ï¿½ ï¿½ï¿½ï¿? ï¿½Û¼ï¿½(ï¿½ï¿½È£ï¿½Ë°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä¶ï¿½ï¿½ï¿½Íºï¿? ï¿½Óµï¿½ï¿½ï¿½ -> 1024, 2048ï¿½ï¿½Æ®)
// 2: overleaf ï¿½Å´ï¿½ï¿½ï¿½ ï¿½Û¼ï¿½ & readmeï¿½Û¼ï¿½ 

/////////////////////// È­,ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ////////////////////////

// test code ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½ï¿½Ï°ï¿½ ï¿½Ö´Â°ï¿½ -> ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ appendixï¿½ï¿½ ï¿½ï¿½ï¿½Ì±ï¿½ 

// ï¿½Ï¿ï¿½ï¿½Ï¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½îµµ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½... -> 15ï¿½ï¿½...ï¿½ï¿½ 