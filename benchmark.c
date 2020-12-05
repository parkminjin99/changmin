#include "benchmark.h"
/******************************
 benchmark.c
 ������ �Լ��� FLINT���̺귯���� �ӵ� ���̸� ���Ѵ�.
 �ӵ����̴� ������ �Լ��� ���ߴ�.
 �Լ���                cm              FLINT           
 ----------------------------------------------
 ADD_FLINTvsCM    |  ADD_zxy         fmpz_add
 SUB_FLINTvsCM    |  SUB_zxy         fmpz_sub
 MUL_FLINTvsCM    |  KaratsubaMUL    fmpz_mul
 DIV_FLINTvsCM    |  DIV             fmpz_fdiv_qr
 EXPMOD_FLINTvsCM |  MODExp_L2R      fmpz_powm

 ���Ҿ� ������ �Լ����� �ӵ� ���̵� �Բ� ���ߴ�.
 �Լ���                          ���Լ�
 -------------------------------------------------------------
 MULvsKara                   | MUL_zxy    KaratsubaMUL
 MULvsSQU                    | MUL_zxy    SQU_zxx
 SQUvsKara                   | SQU_zxx    KaratsubaSQU
 NAIVEvsBINARYLONGvsMULTIDIV | NaiveDiv   BinaryLongDiv   DIV

 ���������� flag�� ���� Karatsuba������ �ӵ��� ���ߴ�.
 �Լ���
 -------------
 Kara_flag()
 *****************************/

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

//int wordlen = 10; // 512-> 8, 1024 -> 16, 2048 -> 32, 3072 -> 48, 4096 -> 64
// RSA PARAMETER?��?��?�� ?��?��?��?�� ?��?��뤄옙?��?��?��? ?��?��깍옙
// PARAMETER ?��?��?��별占?��?�� ?��?��?��? -> ?��?��뤄옙?��?��?��?��?��?�� ?��?��곤옙 ?��????��?��?��?��?�� ?��?��?��?��?��?��?��?��곤옙?��?��?��?��?��?��... // 
// wordlen -> karatsuba?��?��?��?��?��?��(8-100) ->  4?��?��?��?��?��?��?��?��?��!

// iso?��?��?��?��?��?��? bin ?��?��?��?�� ?��?��?�� ? 


void ADD_FLINTvsCM(int wordlen)
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ���Ƿ� ����
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen); // x�� src1 ����
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen); // y�� src2 ����

    clock_t start, end; 
    double result_ac, result_af;

    int cnt = 0;
    start = clock();                    //������ �����Լ� �ð����� 
    while(cnt < MAX_COUNT)
    {
        ADD_zxy(&dst, src1, src2);
        ADD_zxy(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_ac = (double)(end - start)/(double)CLOCKS_PER_SEC;
    
    cnt = 0;
    start = clock();                    //FLINT�� �����Լ� �ð�����
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

void SUB_FLINTvsCM(int wordlen)
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen);  // src1, src2 ���Ƿ� ����
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen); // x�� src1 �Է�
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen); // y�� src2 �Է�

    clock_t start, end; 
    double result_sc, result_sf;

    int cnt = 0;
    start = clock();                        //������ ���� �ð�����
    while(cnt < MAX_COUNT)
    {
        SUB_zxy(&dst, src1, src2);
        SUB_zxy(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_sc = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0;
    start = clock();                        //FLINT ���� �ð�����
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

void MUL_FLINTvsCM(int wordlen)
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ���Ƿ� ����
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen); // x�� src1 �Է�
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen); // y�� src2 �Է�

    clock_t start, end; 
    double result_mc, result_mf;

    int cnt = 0;
    start = clock();                        //������ �����Լ� �ð�����
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
    start = clock();                        //FLINT �Լ� �ð�����.
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


void Kara_flag(int wordlen) 
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;

    while(1)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ���Ƿ� ���� 
        bi_gen_rand(&src2, NON_NEGATIVE, wordlen);
        if(src1->wordlen == wordlen && src2->wordlen == wordlen)
            break;
    }

    int cnt = 0, flag = 2; 
    clock_t start, end; 
    double result;

    while(flag <= wordlen/2)                           //flag�� �����ϸ鼭 KaratsubaMUL �ð�����
    {
        cnt = 0;
        start = clock();
        while(cnt < MAX_COUNT)
        {
            KaratsubaMUL_Flag(&dst, src1, src2, flag);
            cnt++;
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

void MULvsKara(int wordlen) 
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    while(1)
    {
        bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 ���Ƿ� ���� 
        bi_gen_rand(&src2, NON_NEGATIVE, wordlen);
        if(src1->wordlen == wordlen && src2->wordlen == wordlen)
            break;
    }

    clock_t start, end; 
    double result_mul, result_kara;

    int cnt = 0; 
    start = clock();                //schoolbookMUL �ð�����
    while(cnt < MAX_COUNT)
    {
        MUL_zxy(&dst, src1, src2);
        //MUL_zxy(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_mul = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0; 
    start = clock();                //KaratsubaMUL �ð�����
    while(cnt < MAX_COUNT)
    {
        KaratsubaMUL(&dst, src1, src2);
        //KaratsubaMUL(&src2_t, dst_t, src1_t);
        cnt++;
    }
    end = clock(); 
    result_kara = (double)(end - start)/(double)CLOCKS_PER_SEC;
    printf("[MUL vs Karatsuba | CM] %f %f\n", result_mul, result_kara);

    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
}

void MULvsSQU(int wordlen) 
{
    bigint* src = NULL;
    bigint* dst = NULL;
    while(1)
    {
        bi_gen_rand(&src, NON_NEGATIVE, wordlen);   //src ���Ƿ� ����
        if(src->wordlen == wordlen)
            break;
    }

    clock_t start, end; 
    double result_mul, result_squ;

    int cnt = 0; 
    start = clock();            //�����Լ��� �̿��� �������� �ð�����
    while(cnt < MAX_COUNT)
    {
        MUL_zxy(&dst, src, src);
        //MUL_zxy(&src, dst, dst);
        cnt++;
    }
    end = clock(); 
    result_mul = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0; 
    start = clock();            //�����Լ��� �̿��� �������� �ð�����
    while(cnt < MAX_COUNT)
    {
        SQU_zxx(&dst, src);
        //SQU_zxx(&src_t, dst_t);
        cnt++;
    }
    end = clock(); 
    result_squ = (double)(end - start)/(double)CLOCKS_PER_SEC;
    printf("[MUL vs SQU | CM] %f %f\n", result_mul, result_squ);

    bi_delete(&src);
    bi_delete(&dst);
}
//////////////////////////////////////////////////////////////////////////////////////////
void SQUvsKara(int wordlen) 
{
    bigint* src = NULL;
    bigint* dst = NULL;
    while(1)
    {
        bi_gen_rand(&src, NON_NEGATIVE, wordlen);   //src ���Ƿ� ����
        if(src->wordlen == wordlen)
            break;
    }

    int cnt = 0;
    clock_t start, end;
    double result_squ, result_ka;

    start = clock();            //schoolbook SQU �ð�����
    while (cnt < MAX_COUNT)
    {
        SQU_zxx(&dst, src);             
        cnt++;
    }
    end = clock();
    result_squ = (double)(end - start)/(double)CLOCKS_PER_SEC;


    cnt = 0;
    start = clock();            //Karatsuba SQU �ð�����
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

void NAIVEvsBINARYLONGvsMULTIDIV(int wordlen) // Naive vs. binary long vs. multi-precision long
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;

    while (1)      
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen); // src1, src2 ���Ƿ� ����
        bi_gen_rand(&src2, NON_NEGATIVE, wordlen); // �������̹Ƿ� src1�� src2�� �ι� ����.
        if(VALID == DIV(&dstQ, &dstR, src1, src2) && src1->wordlen == 2*wordlen && src2->wordlen == wordlen)
            break;
    }

    int cnt = 0;

    clock_t start, end;
    double result_nai, result_bin, result_mul;
    start = clock();                                    //NaiveDiv �ð�����
    while (cnt < MAX_COUNT)
    {
        NaiveDiv(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_nai = (double)(end - start) / CLOCKS_PER_SEC;

    cnt = 0;
    start = clock();                                     //binarylongDiv �ð�����
    while (cnt < MAX_COUNT)
    {
        BinaryLongDiv(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_bin = (double)(end - start) / CLOCKS_PER_SEC;

    cnt = 0;            
    start = clock();                                    //multi-precision Div �ð�����
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

void BINARYLONGvsMULTIDIV(int wordlen) // Naive vs. binary long vs. multi-precision long
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;
    clock_t start, end;
    double result_bin, result_mul;

    while (1)      
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen); // src1, src2 ���Ƿ� ����
        bi_gen_rand(&src2, NON_NEGATIVE, wordlen); // �������̹Ƿ� src1�� src2�� �ι� ����.
        if(VALID == DIV(&dstQ, &dstR, src1, src2) && src1->wordlen == 2*wordlen && src2->wordlen == wordlen)
            break;
    }

    int cnt = 0;
    start = clock();                                     //binarylongDiv �ð�����
    while (cnt < MAX_COUNT)
    {
        BinaryLongDiv(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_bin = (double)(end - start) / CLOCKS_PER_SEC;

    cnt = 0;            
    start = clock();                                    //multi-precision Div �ð�����
    while (cnt < MAX_COUNT)
    {
        DIV(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_mul = (double)(end - start) / CLOCKS_PER_SEC;

    printf("[Binary vs Multi | CM] %f %f\n", result_bin, result_mul);
    bi_delete(&dstQ);
    bi_delete(&dstR);
    bi_delete(&src1);
    bi_delete(&src2);
}

void DIV_FLINTvsCM(int wordlen)
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;

    bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen);  //src1, src2 ���Ƿ� ����
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);      // �������̹Ƿ� src1�� src2�� �ι� ����.

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

    fmpz_set_ui_array(g, (const mp_limb_t*)src1->a, src1->wordlen); //g�� src1 �Է�
    fmpz_set_ui_array(h, (const mp_limb_t*)src2->a, src2->wordlen); //h�� src2 �Է�

    clock_t start, end;
    double result_dc, result_df;

    int cnt = 0;

    start = clock();
    while (cnt < MAX_COUNT)                             //������ ������ �ð�����
    {
        DIV(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_dc = (double)(end - start) / CLOCKS_PER_SEC;


    cnt = 0;
    start = clock();                                    //FLINT ������ �ð�����
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

void EXPMOD_FLINTvsCM(int wordlen)
{
    bigint* base = NULL;
    bigint* power = NULL;
    bigint* dst = NULL;
    bigint* M = NULL;

    bi_gen_rand(&base, NON_NEGATIVE, wordlen);      //base, power, M ���Ƿ� ����
    bi_gen_rand(&power,  NON_NEGATIVE, wordlen);
    bi_gen_rand(&M, NON_NEGATIVE, wordlen);
    while (!bi_is_zero(M))
        bi_gen_rand(&M, NON_NEGATIVE, wordlen);

    fmpz_t f, g, e, m;
    fmpz_init(f);
    fmpz_init(g);
    fmpz_init(e);
    fmpz_init(m);
    fmpz_set_ui_array(g, (const mp_limb_t*)base->a, base->wordlen);     // g�� base�Է�
    fmpz_set_ui_array(e, (const mp_limb_t*)power->a, power->wordlen);   // e�� power�Է�
    fmpz_set_ui_array(m, (const mp_limb_t*)M->a, M->wordlen);           // m�� M�Է�

    clock_t start, end;
    double result_ec, result_ef;

    int cnt = 0;

    start = clock();                           //������ modexp �ð�����
    while (cnt < MAX_COUNT)
    {
        MODExp_L2R(&dst, base, power, M);
        //MODExp_L2R(&power, dst, base, M);
        cnt++;
    }
    end = clock();
    result_ec = (double)(end - start) / CLOCKS_PER_SEC;


    cnt = 0;
    start = clock();                            //FLINT MODExp�ð�����
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

