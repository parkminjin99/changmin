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

void ADD_FLINTvsCM()
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    int cnt = 0, wordlen = 100;

    clock_t start1, end1; 
    long double result1;
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
    result1 = (long double)(end1 - start1);

    
    cnt = 0; 
    clock_t start, end; 
    long double result;
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
    result = (long double)(end - start);
    printf("CM add = %Lf\n", (result-result1) / CLOCKS_PER_SEC);
    


    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    FLINT_TEST_INIT(state);
    cnt = 0;
    fmpz_randbits(x,state,wordlen*WORD_BITLEN); // �̺κ��� �����ؾ���
    fmpz_randbits(y,state,wordlen*WORD_BITLEN); // �̺κ��� �����ؾ���

    clock_t start2, end2; 
    double result2;
    start2 = clock();
    while(cnt < MAX_COUNT)
    {
        //fmpz_randbits(x,state,wordlen*WORD_BITLEN); // �̺κ��� �����ؾ���
        //fmpz_randbits(y,state,wordlen*WORD_BITLEN); // �̺κ��� �����ؾ���
        fmpz_add(z,x,y);
        cnt++;
    }
    end2 = clock(); 
    result2 = (double)(end2 - start2);
    printf("FLINT add = %f\n", result2 / CLOCKS_PER_SEC);
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