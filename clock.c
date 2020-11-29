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

int wordlen = 100;
double result_c, result_f;

void CM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    int cnt = 0;

    clock_t start1, end1;
    start1 = clock();
    while(cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand()%2, wordlen);
        bi_gen_rand(&src2, rand()%2, wordlen);
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dst);
        cnt++;
    }
    end1 = clock(); 
    result_c = (double)(end1 - start1)/(double)CLOCKS_PER_SEC;
}

void FLINT()
{
    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
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
    result_f = (double)(end2 - start2)/ (double)CLOCKS_PER_SEC;

    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    FLINT_TEST_CLEANUP(state);
}

void ADD_FLINTvsCM()
{

    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    int cnt = 0; 
    clock_t start, end; 
    double result;
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
    result = (double)(end - start);
    printf("CM add = %f\n", (result-result_c) / CLOCKS_PER_SEC);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    FLINT_TEST_INIT(state);

    cnt = 0;
    clock_t start3, end3;
    double result3;
    start3 = clock();
    while(cnt < MAX_COUNT)
    {
        fmpz_randtest(x, state, wordlen*WORD_BITLEN);
        fmpz_randtest(y, state, wordlen*WORD_BITLEN);
        fmpz_add(z,x,y);
        cnt++;
    }
    end3 = clock(); 
    result3 = (double)(end3 - start3);
    printf("FLINT add = %f\n", (result3-result_f)/CLOCKS_PER_SEC);
    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);
    FLINT_TEST_CLEANUP(state);
}

void SUB_FLINTvsCM()
{

}

void MUL_FLINTvsCM()
{

}

void Kara_flag() // flag에 따라 설정 
{

}

void MULvsKara() // 곱셈: schoolbook vs. Karatsuba
{

}

void MULvsSQU() 
{

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