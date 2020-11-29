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

void Kara_flag() // flag�� ���� ���� 
{

}

void MULvsKara() // ����: schoolbook vs. Karatsuba
{

}

void MULvsSQU() 
{

}
//////////////////////////////////////////////////////////////////////////////////////////
void SQUvsKara() // ����: schoolbook vs. Karatsuba
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

void EXPMOD_test() // �������???
{

}
// ������ ����..

// time.c // ��ȣ�˰����Ķ���ͺ� �ӵ��� -> 1024, 2048��Ʈ
// void mod_test() // �������???
// �׷���???? -> ǥ??? -> overleaf 

// 1 : time.c Ʋ ���� & �ּ�  -> �̰� �����ϱ� 
// 2 : sage while�� ���� & �ּ� -> ����Ҷ� while()

// ���� : �ݹ� ������ �ڵ� ���� 

///////////////// �ݹ� �ɵ�? �Ͽ��� 2�� ////////////////////////

// 1: overleaf���ٰ� ��� �ۼ�(��ȣ�˰����Ķ���ͺ� �ӵ��� -> 1024, 2048��Ʈ)
// 2: overleaf �Ŵ��� �ۼ� & readme�ۼ� 

/////////////////////// ȭ,���� ������ �� ////////////////////////

// test code ����� �����ϰ� �ִ°� -> ���� appendix�� ���̱� 

// �Ͽ��Ͽ��� ��� ���� ����... -> 15��...�� 