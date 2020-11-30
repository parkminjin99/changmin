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

int wordlen = 16; // 512-> 8, 1024 -> 16, 2048 -> 32, 3072 -> 48, 4096 -> 64
// RSA PARAMETER�� ǥ�� �׷���? �ֱ�
// PARAMETER ũ�⺰�� ��? -> �׷����� �ְ� �Ҽ��� �����Ͱ�����... // 
// wordlen -> karatsuba����(8-100) ->  4������!

// iso����? bin ũ�� �� ? 

double result_c, result_f;
double result_single_c, result_tri_f;

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

// flag�� ���� karatsuba -> ���? wordlen�� ���� 
// �ش� wordlen�� ���� 1/4�̳� 1/8

void Kara_flag() // flag�� ���� ���� 
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    int cnt = 0, flag = 2; 
    clock_t start, end; 
    double result;
    while(flag < (wordlen/2)) 
    // flag <- wordlen ������?
    // RSA
    // 10, 12, 14, 50 -> 20�� 
    // wordlen(10~50, 1����? 2����??) -> flag�� ����  
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

void MULvsKara() // ����: schoolbook vs. Karatsuba
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
void CM_single()
{
    bigint* src = NULL;
    int cnt = 0;

    clock_t start1, end1;
    start1 = clock();
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src, rand() % 2, wordlen);
        bi_delete(&src);
        cnt++;
    }
    end1 = clock();
    result_single_c = (double)(end1 - start1);
}


void SQUvsKara() // ����: schoolbook vs. Karatsuba
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
        SQU(&dst, src);
        bi_delete(&src);
        bi_delete(&dst);
        cnt++;
        //printf("%d\n",cnt);
    }
    endsqu = clock();
    resultsqu = (double)(endsqu - startsqu - result_single_c)/CLOCKS_PER_SEC;
    //printf("squaring = %f\n", (resultsqu - result_single_c) / CLOCKS_PER_SEC);


    cnt = 0;
    clock_t startka, endka;
    int flag = 2;  // �̰Ŵ� �Ŀ� �ٽü���
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
    resultka = (double)(endka - startka - result_single_c)/CLOCKS_PER_SEC;
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

        if(VALID==NAIVE_div(&dstQ, &dstR, src1, src2))
            cnt++;
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
    }
    endnai = clock();
    resultnai = (double)(endnai - startnai - result_c) / CLOCKS_PER_SEC;
    //printf("NAIVE_DIV = %f\n", (resultnai - result_c) / CLOCKS_PER_SEC);


    cnt = 0;
    clock_t startbin, endbin;
    double resultbin;
    startbin = clock();
    while (cnt < MAX_COUNT)
    {
        bi_gen_rand(&src1, rand() % 2, wordlen);
        bi_gen_rand(&src2, rand() % 2, wordlen);

        if (VALID == Binary_Long_Div(&dstQ, &dstR, src1, src2))
            cnt++;
        bi_delete(&src1);
        bi_delete(&src2);
        bi_delete(&dstQ);
        bi_delete(&dstR);
    }
    endbin = clock();
    resultbin = (double)(endbin - startbin - result_c) / CLOCKS_PER_SEC;
    //printf("binary_long_DIV = %f\n", (resultbin - result_c) / CLOCKS_PER_SEC);


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
    resultmul = (double)(endmul - startmul - result_c) / CLOCKS_PER_SEC;
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
    resultc = (double)(endc - startc - result_c) / CLOCKS_PER_SEC;
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
    resultf = (double)(endf - startf - result_f) / CLOCKS_PER_SEC;
    printf("[DIV | CM vs FLINT] %f %f\n",resultc, resultf);
    //printf("FLINT DIV = %f\n", (resultf - result_f) / CLOCKS_PER_SEC);
    fmpz_clear(f);
    fmpz_clear(s);
    fmpz_clear(g);
    fmpz_clear(h);

    FLINT_TEST_CLEANUP(state);
}


void FLINT_tri()
{
    fmpz_t x, y, z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);

    FLINT_TEST_INIT(state);

    int cnt = 0;
    clock_t start2, end2;
    start2 = clock();
    while (cnt < MAX_COUNT)
    {
        fmpz_randtest(x, state, wordlen * WORD_BITLEN);
        fmpz_randtest(y, state, wordlen * WORD_BITLEN);
        fmpz_randtest(z, state, wordlen * WORD_BITLEN);

        cnt++;
    }
    end2 = clock();
    result_tri_f = (double)(end2 - start2);

    fmpz_clear(x);
    fmpz_clear(y);
    fmpz_clear(z);

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
    resultc = (double)(endc - startc -result_c) / CLOCKS_PER_SEC;
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
    resultf = (double)(endf - startf - result_c) / CLOCKS_PER_SEC;
    //printf("FLINT expmod = %f\n", (resultf-result_c) / CLOCKS_PER_SEC);
    printf("[EXPMOD | CM vs FLINT] %f %f\n",resultc, resultf);
    fmpz_clear(f);
    fmpz_clear(g);
    fmpz_clear(e);
    fmpz_clear(m);
    FLINT_TEST_CLEANUP(state);
}

void EXPMOD_test() // �������????
{

}
// ������ ����..

// time.c // ��ȣ�˰������Ķ���ͺ�? �ӵ��� -> 1024, 2048��Ʈ
// void mod_test() // �������????
// �׷���???? -> ǥ??? -> overleaf 

// 1 : time.c Ʋ ���� & �ּ�  -> �̰� �����ϱ� 
// 2 : sage while�� ���� & �ּ� -> ����Ҷ�? while()

// ���� : �ݹ� ������ �ڵ� ���� 

///////////////// �ݹ� �ɵ�? �Ͽ��� 2�� ////////////////////////

// 1: overleaf���ٰ� ���? �ۼ�(��ȣ�˰������Ķ���ͺ�? �ӵ��� -> 1024, 2048��Ʈ)
// 2: overleaf �Ŵ��� �ۼ� & readme�ۼ� 

/////////////////////// ȭ,���� ������ �� ////////////////////////

// test code �����? �����ϰ� �ִ°� -> ������ appendix�� ���̱� 

// �Ͽ��Ͽ��� ��� ���� ����... -> 15��...�� 