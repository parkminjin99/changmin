#include "clock.h"
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

int wordlen = 16; // 512-> 8, 1024 -> 16, 2048 -> 32, 3072 -> 48, 4096 -> 64
// RSA PARAMETER는 표나 그래프? 넣구
// PARAMETER 크기별로 비교? -> 그래프만 넣고 할수는 있을것같은데... // 
// wordlen -> karatsuba범위(8-100) ->  4씩증가!

// iso파일? bin 크기 비교 ? 

double result_c, result_f;

void CM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    int cnt = 0;

    clock_t start1, end1;
    start1 = clock();
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, wordlen);
        bi_gen_rand(&src2, rand()%2, wordlen);
        bi_delete(&src1);
        bi_delete(&src2);
        cnt++;
    }
    end1 = clock(); 
    result_c = (double)(end1 - start1);
}

void FLINT()
{
    fmpz_t x,y;
    fmpz_init(x);
    fmpz_init(y);
    FLINT_TEST_INIT(state);

    int cnt = 0;
    clock_t start2, end2;
    start2 = clock();
    while(cnt < MAX_COUNT)
    {
        fmpz_randtest(x, state, wordlen*WORD_BITLEN);
        fmpz_randtest(y, state, wordlen*WORD_BITLEN);
        cnt++;
    }
    end2 = clock(); 
    result_f = (double)(end2 - start2);

    fmpz_clear(x);
    fmpz_clear(y);
    FLINT_TEST_CLEANUP(state);
}

void ADD_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    int cnt = 0; 
    clock_t start, end; 
    double result_ac, result_af;

    start = clock();
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, wordlen);
        bi_gen_rand(&src2, rand()%2, wordlen);
        ADD(&dst, src1, src2);
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    end = clock(); 
    result_ac = (double)(end - start - result_c)/(double)CLOCKS_PER_SEC;

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    FLINT_TEST_INIT(state);
    
    cnt = 0;
    start = clock();
    while(cnt < MAX_COUNT)
    {
        fmpz_randtest(x, state, wordlen*WORD_BITLEN);
        fmpz_randtest(y, state, wordlen*WORD_BITLEN);
        fmpz_add(z,x,y);
        cnt++;
    }
    end = clock(); 
    result_af = (double)(end - start - result_f)/(double)CLOCKS_PER_SEC;
    printf("[ADD | CM vs FLINT] %f %f\n", result_ac, result_af);

    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    FLINT_TEST_CLEANUP(state);
}

void SUB_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    int cnt = 0; 
    clock_t start, end; 
    double result_sc, result_sf;

    start = clock();
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, wordlen);
        bi_gen_rand(&src2, rand()%2, wordlen);
        SUB(&dst, src1, src2);
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    end = clock(); 
    result_sc = (double)(end - start - result_c) / (double)CLOCKS_PER_SEC;

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    FLINT_TEST_INIT(state);

    cnt = 0;
    start = clock();
    while(cnt < MAX_COUNT)
    {
        fmpz_randtest(x, state, wordlen*WORD_BITLEN);
        fmpz_randtest(y, state, wordlen*WORD_BITLEN);
        fmpz_sub(z,x,y);
        cnt++;
    }
    end = clock(); 
    result_sf = (double)(end - start - result_f) / (double)CLOCKS_PER_SEC;
    printf("[SUB | CM vs FLINT] %f %f\n", result_sc, result_sf);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    FLINT_TEST_CLEANUP(state);
}

void MUL_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    int cnt = 0; 
    clock_t start, end; 
    double result_mc, result_mf;

    start = clock();
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, wordlen);
        bi_gen_rand(&src2, rand()%2, wordlen);
        //MUL(&dst, src1, src2);
        Karatsuba(&dst, src1, src2, 6);
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    end = clock(); 
    result_mc = (double)(end - start - result_c)/(double)CLOCKS_PER_SEC;

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    FLINT_TEST_INIT(state);

    cnt = 0;
    start = clock();
    while(cnt < MAX_COUNT)
    {
        fmpz_randtest(x, state, wordlen*WORD_BITLEN);
        fmpz_randtest(y, state, wordlen*WORD_BITLEN);
        fmpz_mul(z,x,y);
        cnt++;
    }
    end = clock(); 
    result_mf = (double)(end - start - result_f)/(double)CLOCKS_PER_SEC;
    printf("[MUL | CM vs FLINT] %f %f\n", result_mc, result_mf);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    FLINT_TEST_CLEANUP(state);
}

// flag에 따른 karatsuba -> 모든 wordlen에 대해 
// 해당 wordlen에 대해 1/4이나 1/8

void Kara_flag() // flag에 따라 설정 
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    int cnt = 0, flag = 2; 
    clock_t start, end; 
    double result;
    while(flag < (wordlen/2)) 
    // flag <- wordlen 어디까지?
    // RSA
    // 10, 12, 14, 50 -> 20번 
    // wordlen(10~50, 1단위? 2단위??) -> flag에 대해  
    {
        cnt = 0;
        start = clock();
        while(cnt < MAX_COUNT)
        {
            bi_gen_rand(&src1, rand()%2, wordlen);
            bi_gen_rand(&src2, rand()%2, wordlen);
            Karatsuba(&dst, src1, src2, flag);
            bi_delete(&src1);
            bi_delete(&src2);
            bi_delete(&dst);
            cnt++;
        }
        end = clock(); 
        result = (double)(end - start - result_c) / (double)CLOCKS_PER_SEC;
        printf("[Karatsuba | CM] %f (flag = %d)\n", result, flag);
        flag++;
    }

}

void MULvsKara() // 곱셈: schoolbook vs. Karatsuba
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    int cnt = 0; 
    clock_t start, end; 
    double result_mul, result_kara;

    start = clock();
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, wordlen);
        bi_gen_rand(&src2, rand()%2, wordlen);
        MUL(&dst, src1, src2);
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    end = clock(); 
    result_mul = (double)(end - start - result_c)/(double)CLOCKS_PER_SEC;

    cnt = 0; 
    start = clock();
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, wordlen);
        bi_gen_rand(&src2, rand()%2, wordlen);
        Karatsuba(&dst, src1, src2, 6);
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    end = clock(); 
    result_kara = (double)(end - start - result_c)/(double)CLOCKS_PER_SEC;
    printf("[MUL vs Karatsuba | CM] %f %f\n", result_mul, result_kara);
}

void MULvsSQU() 
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    int cnt = 0; 
    clock_t start, end; 
    double result_mul, result_squ;

    start = clock();
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, wordlen);
        bi_gen_rand(&src2, rand()%2, wordlen);
        MUL(&dst, src1, src1);
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    end = clock(); 
    result_mul = (double)(end - start - result_c)/(double)CLOCKS_PER_SEC;

    cnt = 0; 
    start = clock();
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, wordlen);
        bi_gen_rand(&src2, rand()%2, wordlen);
        SQU(&dst, src1);
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    end = clock(); 
    result_squ = (double)(end - start - result_c)/(double)CLOCKS_PER_SEC;
    printf("[MUL vs SQU | CM] %f %f\n", result_mul, result_squ);
}
//////////////////////////////////////////////////////////////////////////////////////////
void SQUvsKara() // 제곱: schoolbook vs. Karatsuba
{

}

void NAIVEvsBINARYLONGvsMULTIDIV() // Naive vs. binary long vs. multi-precision long
{

}

void DIV_FLINTvsCM()
{

}

void EXPMOD_FLINTvsCM()
{

}

void EXPMOD_test() // 사전계산???
{

}
// 저장할 공간..

// time.c // 암호알고리듬파라미터별 속도비교 -> 1024, 2048비트
// void mod_test() // 사전계산???
// 그래프???? -> 표??? -> overleaf 

// 1 : time.c 틀 제작 & 주석  -> 이거 수정하기 
// 2 : sage while문 제작 & 주석 -> 출력할때 while()

// 공통 : 반반 나눈거 코드 제작 

///////////////// 금방 될듯? 일요일 2시 ////////////////////////

// 1: overleaf에다가 결과 작성(암호알고리듬파라미터별 속도비교 -> 1024, 2048비트)
// 2: overleaf 매뉴얼 작성 & readme작성 

/////////////////////// 화,수에 끝나야 함 ////////////////////////

// test code 충분히 제공하고 있는가 -> 보고서 appendix에 붙이기 

// 일요일에는 적어도 영상 찍어야... -> 15분...ㅠ 