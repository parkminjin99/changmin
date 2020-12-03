#include "benchmark.h"
/******************************
 benchmark.c
 구현한 함수와 FLINT라이브러리의 속도 차이를 비교한다.
 속도차이는 다음의 함수를 비교했다.
 함수명                cm              FLINT           
 ----------------------------------------------
 ADD_FLINTvsCM    |  ADD_zxy         fmpz_add
 SUB_FLINTvsCM    |  SUB_zxy         fmpz_sub
 MUL_FLINTvsCM    |  KaratsubaMUL    fmpz_mul
 DIV_FLINTvsCM    |  DIV             fmpz_fdiv_qr
 EXPMOD_FLINTvsCM |  MODExp_L2R      fmpz_powm

 더불어 구현한 함수간에 속도 차이도 함께 비교했다.
 함수명                          비교함수
 -------------------------------------------------------------
 MULvsKara                   | MUL_zxy    KaratsubaMUL
 MULvsSQU                    | MUL_zxy    SQU_zxx
 SQUvsKara                   | SQU_zxx    KaratsubaSQU
 NAIVEvsBINARYLONGvsMULTIDIV | NaiveDiv   BinaryLongDiv   DIV

 마지막으로 flag에 따른 Karatsuba연산의 속도를 비교했다.
 함수명
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
// RSA PARAMETER?뜝?룞?삕 ?몴?뜝?룞?삕 ?뜝?뙎琉꾩삕?뜝?룞?삕? ?뜝?뙇源띿삕
// PARAMETER ?겕?뜝?뜦蹂꾢뜝?룞?삕 ?뜝?룞?삕? -> ?뜝?뙎琉꾩삕?뜝?룞?삕?뜝?룞?삕 ?뜝?뙇怨ㅼ삕 ?뜝????눦?삕?뜝?룞?삕 ?뜝?룞?삕?뜝?룞?삕?뜝?떢怨ㅼ삕?뜝?룞?삕?뜝?룞?삕... // 
// wordlen -> karatsuba?뜝?룞?삕?뜝?룞?삕(8-100) ->  4?뜝?룞?삕?뜝?룞?삕?뜝?룞?삕!

// iso?뜝?룞?삕?뜝?룞?삕? bin ?겕?뜝?룞?삕 ?뜝?룞?삕 ? 


void ADD_FLINTvsCM(int wordlen)
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 임의로 생성
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen); // x에 src1 저장
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen); // y에 src2 저장

    clock_t start, end; 
    double result_ac, result_af;

    int cnt = 0;
    start = clock();                    //구현한 덧셈함수 시간측정 
    while(cnt < MAX_COUNT)
    {
        ADD_zxy(&dst, src1, src2);
        ADD_zxy(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_ac = (double)(end - start)/(double)CLOCKS_PER_SEC;
    
    cnt = 0;
    start = clock();                    //FLINT의 덧셈함수 시간측정
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
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen);  // src1, src2 임의로 생성
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen); // x에 src1 입력
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen); // y에 src2 입력

    clock_t start, end; 
    double result_sc, result_sf;

    int cnt = 0;
    start = clock();                        //구현한 뺄셈 시간측정
    while(cnt < MAX_COUNT)
    {
        SUB_zxy(&dst, src1, src2);
        SUB_zxy(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_sc = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0;
    start = clock();                        //FLINT 뺄셈 시간측정
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
    bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 임의로 생성
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    fmpz_t x,y,z;
    fmpz_init(x);
    fmpz_init(y);
    fmpz_init(z);
    fmpz_set_ui_array(x, (const mp_limb_t*)src1->a, src1->wordlen); // x에 src1 입력
    fmpz_set_ui_array(y, (const mp_limb_t*)src2->a, src2->wordlen); // y에 src2 입력

    clock_t start, end; 
    double result_mc, result_mf;

    int cnt = 0;
    start = clock();                        //구현한 곱셈함수 시간측정
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
    start = clock();                        //FLINT 함수 시간측정.
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

    //bi_gen_rand(&src1, NON_NEGATIVE, 2*wordlen);        // src1, src2 임의로 생성    
   // bi_gen_rand(&src2, NON_NEGATIVE, wordlen);
/***
    while(flag < wordlen/2)                           //flag를 변경하면서 KaratsubaMUL 시간측정
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
    }***/
    bi_delete(&src1);
    bi_delete(&src2);
    bi_delete(&dst);
}
#if 0
void MULvsKara() 
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dst = NULL;
   // bi_gen_rand(&src1, NON_NEGATIVE, wordlen); // src1, src2 임의로 생성 
   // bi_gen_rand(&src2, NON_NEGATIVE, wordlen);

    bigint* src1_t = NULL;
    bigint* src2_t = NULL;
    bigint* dst_t = NULL;
    bi_assign(&src1_t, src1); // src1_t에 src1 입력
    bi_assign(&src2_t, src2); // src2_t에 src2 입력

    clock_t start, end; 
    double result_mul, result_kara;

    int cnt = 0; 
    start = clock();                //schoolbookMUL 시간측정
    while(cnt < MAX_COUNT)
    {
        MUL_zxy(&dst, src1, src2);
        MUL_zxy(&src2, dst, src1);
        cnt++;
    }
    end = clock(); 
    result_mul = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0; 
    start = clock();                //KaratsubaMUL 시간측정
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
    bi_gen_rand(&src, NON_NEGATIVE, wordlen); // src 임의로 생성

    bigint* src_t = NULL;
    bigint* dst_t = NULL;
    bi_assign(&src_t, src); // src1_t에 src1 입력

    clock_t start, end; 
    double result_mul, result_squ;

    int cnt = 0; 
    start = clock();            //곱셈함수를 이용한 제곱연산 시간측정
    while(cnt < MAX_COUNT)
    {
        MUL_zxy(&dst, src, src);
        //MUL_zxy(&src, dst, dst);
        cnt++;
    }
    end = clock(); 
    result_mul = (double)(end - start)/(double)CLOCKS_PER_SEC;

    cnt = 0; 
    start = clock();            //제곱함수를 이용한 제곱연산 시간측정
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
void SQUvsKara() 
{
    bigint* src = NULL;
    bigint* dst = NULL;

    bi_gen_rand(&src, NON_NEGATIVE, wordlen);   //src 임의로 생성

    int cnt = 0;
    clock_t start, end;
    double result_squ, result_ka;

    start = clock();            //schoolbook SQU 시간측정
    while (cnt < MAX_COUNT)
    {
        SQU_zxx(&dst, src);             
        cnt++;
    }
    end = clock();
    result_squ = (double)(end - start)/(double)CLOCKS_PER_SEC;


    cnt = 0;
    start = clock();            //Karatsuba SQU 시간측정
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

    bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen);      //src1, src2 임의로 생성
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);          // 나눗셈이므로 src1는 src2의 두배 길이.

    while (VALID != DIV(&dstQ, &dstR, src1, src2))      
    {
        bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen);
        bi_gen_rand(&src2, NON_NEGATIVE, wordlen);
    }

    int cnt = 0;

    clock_t start, end;
    double result_nai, result_bin, result_mul;
    start = clock();                                    //NaiveDiv 시간측정
    while (cnt < MAX_COUNT)
    {
        NaiveDiv(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_nai = (double)(end - start) / CLOCKS_PER_SEC;

    cnt = 0;
    start = clock();                                     //binarylongDiv 시간측정
    while (cnt < MAX_COUNT)
    {
        BinaryLongDiv(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_bin = (double)(end - start) / CLOCKS_PER_SEC;

    cnt = 0;            
    start = clock();                                    //multi-precision Div 시간측정
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
#endif
void DIV_FLINTvsCM(int wordlen)
{
    bigint* src1 = NULL;
    bigint* src2 = NULL;
    bigint* dstQ = NULL;
    bigint* dstR = NULL;

    bi_gen_rand(&src1, NON_NEGATIVE, 2 * wordlen);  //src1, src2 임의로 생성
    bi_gen_rand(&src2, NON_NEGATIVE, wordlen);      // 나눗셈이므로 src1는 src2의 두배 길이.

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

    fmpz_set_ui_array(g, (const mp_limb_t*)src1->a, src1->wordlen); //g에 src1 입력
    fmpz_set_ui_array(h, (const mp_limb_t*)src2->a, src2->wordlen); //h에 src2 입력

    clock_t start, end;
    double result_dc, result_df;

    int cnt = 0;

    start = clock();
    while (cnt < MAX_COUNT)                             //구현한 나눗셈 시간측정
    {
        DIV(&dstQ, &dstR, src1, src2);
        cnt++;
    }
    end = clock();
    result_dc = (double)(end - start) / CLOCKS_PER_SEC;


    cnt = 0;
    start = clock();                                    //FLINT 나눗셈 시간측정
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

    bi_gen_rand(&base, NON_NEGATIVE, wordlen);      //base, power, M 임의로 생성
    bi_gen_rand(&power,  NON_NEGATIVE, wordlen);
    bi_gen_rand(&M, NON_NEGATIVE, wordlen);
    while (!bi_is_zero(M))
        bi_gen_rand(&M, NON_NEGATIVE, wordlen);

    fmpz_t f, g, e, m;
    fmpz_init(f);
    fmpz_init(g);
    fmpz_init(e);
    fmpz_init(m);
    fmpz_set_ui_array(g, (const mp_limb_t*)base->a, base->wordlen);     // g에 base입력
    fmpz_set_ui_array(e, (const mp_limb_t*)power->a, power->wordlen);   // e에 power입력
    fmpz_set_ui_array(m, (const mp_limb_t*)M->a, M->wordlen);           // m에 M입력

    clock_t start, end;
    double result_ec, result_ef;

    int cnt = 0;

    start = clock();                           //구현한 modexp 시간측정
    while (cnt < MAX_COUNT)
    {
        MODExp_L2R(&dst, base, power, M);
        //MODExp_L2R(&power, dst, base, M);
        cnt++;
    }
    end = clock();
    result_ec = (double)(end - start) / CLOCKS_PER_SEC;


    cnt = 0;
    start = clock();                            //FLINT MODExp시간측정
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


// time.c // ?뜝?룞?삕?샇?뜝?떙怨ㅼ삕?뜝?룞?삕?뜝?룞?삕?뜝?떇?씛?삕?뜝?룞?삕?븙?뜝? ?뜝?뙂?벝?삕?뜝?룞?삕 -> 1024, 2048?뜝?룞?삕?듃
// void mod_test() // ?뜝?룞?삕?뜝?룞?삕?뜝?룞?삕?뜝????
// ?뜝?뙎琉꾩삕?뜝?룞?삕???? -> ?몴??? -> overleaf 

// 1 : time.c ??? ?뜝?룞?삕?뜝?룞?삕 & ?뜝?뙇?눦?삕  -> ?뜝?떛怨ㅼ삕 ?뜝?룞?삕?뜝?룞?삕?뜝?떦源띿삕 
// 2 : sage while?뜝?룞?삕 ?뜝?룞?삕?뜝?룞?삕 & ?뜝?뙇?눦?삕 -> ?뜝?룞?삕?뜝?룞?삕燁듿뜝? while()

// ?뜝?룞?삕?뜝?룞?삕 : ?뜝?뙠諭꾩삕 ?뜝?룞?삕?뜝?룞?삕?뜝?룞?삕 ?뜝?뙓?벝?삕 ?뜝?룞?삕?뜝?룞?삕 

///////////////// ?뜝?뙠諭꾩삕 ?뜝?떖?벝?삕? ?뜝?떦?슱?삕?뜝?룞?삕 2?뜝?룞?삕 ////////////////////////

// 1: overleaf?뜝?룞?삕?뜝?뙐怨ㅼ삕 ?뜝?룞?삕?뜝? ?뜝?뙗?눦?삕(?뜝?룞?삕?샇?뜝?떙怨ㅼ삕?뜝?룞?삕?뜝?룞?삕?뜝?떇?씛?삕?뜝?룞?삕?븙?뜝? ?뜝?뙂?벝?삕?뜝?룞?삕 -> 1024, 2048?뜝?룞?삕?듃)
// 2: overleaf ?뜝?떊?뙋?삕?뜝?룞?삕 ?뜝?뙗?눦?삕 & readme?뜝?뙗?눦?삕 

/////////////////////// ?솕,?뜝?룞?삕?뜝?룞?삕 ?뜝?룞?삕?뜝?룞?삕?뜝?룞?삕 ?뜝?룞?삕 ////////////////////////

// test code ?뜝?룞?삕?뜝?룞?삕?뜝? ?뜝?룞?삕?뜝?룞?삕?뜝?떦怨ㅼ삕 ?뜝?뙇?뒗怨ㅼ삕 -> ?뜝?룞?삕?뜝?룞?삕?뜝?룞?삕 appendix?뜝?룞?삕 ?뜝?룞?삕?뜝?떛源띿삕 

// ?뜝?떦?슱?삕?뜝?떦?슱?삕?뜝?룞?삕 ?뜝?룞?삕?뜝?룜?룄 ?뜝?룞?삕?뜝?룞?삕 ?뜝?룞?삕?뜝?룞?삕... -> 15?뜝?룞?삕...?뜝?룞?삕 