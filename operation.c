//
//  operation.c
//  Changmin's library
//
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//

#include "operation.h"

void left_shift(bigint* x, int r) // bigint x를 r비트만큼 왼쪽으로 shift하는 함수
{
    int i;
    if (r % WORD_BITLEN == 0) // r가 WORD_BITLEN의 배수인 경우
    {
        x->wordlen += r/WORD_BITLEN;
        array_copy(x->a + (r / WORD_BITLEN), x->a, x->wordlen - (r / WORD_BITLEN));
        array_init(x->a, r / WORD_BITLEN);
    }
    else // r이 WORD_BITLEN의 배수가 아닌 경우
    {
        x->wordlen += r / WORD_BITLEN + 1;
        x->a = (word*)realloc(x->a, sizeof(word) * get_wordlen(x));
     
        int n = get_wordlen(x) - r / WORD_BITLEN; // n은 shift했을 때 0이 아닌 부분의 길이
        x->a[get_wordlen(x)-1] = (x->a[get_wordlen(x) - 1 - r / WORD_BITLEN - 1] >> (WORD_BITLEN - r % WORD_BITLEN));
        for (i = get_wordlen(x) - 2; i > get_wordlen(x) - n; i--)
            x->a[i] = (x->a[i - r/WORD_BITLEN - 1] >> (WORD_BITLEN - r % WORD_BITLEN)) | (x->a[i - r / WORD_BITLEN] << (r % WORD_BITLEN)); // x->a[i]는 x->a[i-1]의 상위 r%WORD_BITLEN비트와 x->a[i]의 하위 WORD_BITLEN-r%WORD_BITLEN비트로 구성
        x->a[get_wordlen(x) - n] = x->a[get_wordlen(x)- n - r / WORD_BITLEN] << (r%WORD_BITLEN);
        array_init(x->a, r / WORD_BITLEN);
    }
}

void right_shift(bigint* x, int r) // bigint x를 r비트만큼 오른쪽으로 shift하는 함수
{
    if (r >= get_wordlen(x) * WORD_BITLEN) // r이 x->wordlen*WORD_BITLEN보다 크거나 같은 경우
        bi_zeroize(x);
    else if (r % WORD_BITLEN == 0) // r이 WORD_BITLEN의 배수인 경우
    {
        array_copy(x->a, x->a + (r / WORD_BITLEN), get_wordlen(x) - (r / WORD_BITLEN));
        array_init(x->a + (get_wordlen(x) - (r / WORD_BITLEN)), r / WORD_BITLEN);
        bi_refine(x);
    }
    else // r이 WORD_BITLEN의 배수가 아닌 경우
    {
        int i;
        int n = get_wordlen(x) - r / WORD_BITLEN; // n은 shift했을 때 0이 아닌 부분의 길이
        for (i = 0; i < n - 1; i++)
            x->a[i] = (x->a[i + 1 + r/WORD_BITLEN] << (WORD_BITLEN - r % WORD_BITLEN)) | (x->a[i + r / WORD_BITLEN] >> (r % WORD_BITLEN)); // x->a[i]는 x->a[i+1]의 하위 r%WORD_BITLEN비트와 x->a[i]의 상위 WORD_BITLEN-r%WORD_BITLEN비트로 구성
        x->a[n - 1] = x->a[n - 1 + r / WORD_BITLEN] >> (r % WORD_BITLEN);
        array_init(x->a + (get_wordlen(x) - r / WORD_BITLEN), r / WORD_BITLEN);
        bi_refine(x);
    }
}

void reduction_2_r(bigint* x, int r) // bigint x의 x mod 2^r를 출력하는 함수
{
    if (r >= (get_wordlen(x) * WORD_BITLEN)) // r가 x->wordlen*WORD_BITLEN보다 크거나 같은 경우
        return;
    else if (r % WORD_BITLEN == 0) // r가 WORD_BITLEN의 배수인 경우
    {
        array_init(x->a + r / WORD_BITLEN, x->wordlen - r / WORD_BITLEN);
        bi_refine(x);
    }
    else    // r가 WORD_BITLEN의 배수가 아닌 경우
    {
        word k = -1; // k = 2^(WORD_BITLEN)-1
        x->a[r / WORD_BITLEN] &= (k >> (WORD_BITLEN - r % WORD_BITLEN)); // x->a[r/WORD_BITLEN]의 하위 r%WORD_BITLEN비트만 남김
        array_init(x->a + r / WORD_BITLEN + 1, x->wordlen - r / WORD_BITLEN - 1);
        bi_refine(x);
    }
}
void ADD_ABc(word* dst, word* carry, const word* src1, const word* src2)
{
    word new_carry = 0;
    *dst = (*src1) + (*src2);
    if (*dst < *src1) // carry 발생
        new_carry = 1;
    *dst += *carry;
    if (*dst < *carry) // carry 발생
        new_carry += 1;
    *carry = new_carry;
}

void ADD_ABc2(word* dst, word* carry, const word* src)
{
    word new_carry = 0;
    *dst += *src;
    if (*dst < *src) // carry 발생
        new_carry = 1;
    *dst += *carry;
    if (*dst < *carry) // carry 발생
        new_carry += 1;
    *carry = new_carry;
}

void ADDC(bigint** dst, const bigint* src1, const bigint* src2)
{
    bi_new(dst, get_wordlen(src1) + 1, get_sign(src1));
    int i;
    word carry = 0; // carry
    for (i = 0; i < get_wordlen(src2); i++){
        ADD_ABc(&(*dst)->a[i], &carry, &src1->a[i], &src2->a[i]); // 1워드 덧셈
    }
    for (i = get_wordlen(src2); i < get_wordlen(src1); i++)    // *수정*
    {
        (*dst)->a[i] = src1->a[i] + carry;
        if ((*dst)->a[i] < carry && carry == 1) // carry 발생
            carry = 1;
        else
            carry = 0;
    }
    (*dst)->a[i] = carry;  // *수정*

    bi_refine(*dst);

}

// void ADDC2(bigint* dst, const bigint* src)
// {
//     int i;
//     word carry = 0; // carry
//     for (i = 0; i < get_wordlen(src); i++)
//         ADD_ABc2(&dst->a[i], &carry, &src->a[i]); // 1워드 덧셈
//     dst->a[i] = carry;
// }

void ADD(bigint** dst, const bigint* src1, const bigint* src2)
{
    bigint* temp = NULL;
    if (bi_is_zero(src1) == TRUE) // src1 = 0
    {
        bi_assign(dst, src2);
        //printf("#src1=0\n");

    }
    else if (bi_is_zero(src2) == TRUE) // src2 = 0
    {
        bi_assign(dst, src1);
        //printf("#src2=0\n");

    }
    else if ((get_sign(src1) == NON_NEGATIVE) && (get_sign(src2) == NEGATIVE)) // src1 >= 0, src2 < 0
    {
        //printf("#src1>0>src2\n");
        bi_assign(&temp,src2);
        flip_sign(temp);
        SUB(dst, src1, temp);
        
        //flip_sign(src2);       // *수정*
        //SUB(dst, src1, src2); // *수정*
        //flip_sign(src2);       // *수정*

    }
    else if ((get_sign(src1) == NEGATIVE) && (get_sign(src2) == NON_NEGATIVE)) // src1 < 0, src2 >= 0
    {
        //printf("#src2>0>src1\n");
        bi_assign(&temp,src1);
        flip_sign(temp);
        SUB(dst, src2, temp);
        
        //flip_sign(src1);       // *수정*
        //SUB(dst, src2, src1); // *수정*
        //flip_sign(src1);       // *수정*

    }
    else if (get_wordlen(src1) >= get_wordlen(src2))
    {
        //printf("#src1>src2\n");
        ADDC(dst, src1, src2);
    }
    else {
        //printf("#src2>src1\n");

        ADDC(dst, src2, src1);
    }
    bi_delete(&temp);
}

void ADD2(bigint** dst, const bigint* src)
{
    bigint* temp = NULL;
    bi_assign(&temp,*dst);
    ADD(dst,temp,src);
    bi_delete(&temp);
}

void subABS(word* dst, int* carry, const word* src1, const word* src2)    // src1과 src2, carry를 입력받아 1word에 대한 뺄셈의 절댓값을 출력
{
    *dst = (*src1) - (*carry);

    if (*src1 < *carry)
        *carry = 1;
    else
        *carry = 0;

    if (*dst < *src2)
        *carry = *carry + 1;

    *dst = *dst - *src2;

}

void subc(bigint** dst, const bigint* src1, const bigint* src2)    // src1>src2로 입력받아 둘의 차를 dst에 저장
{
    int new_wordlen = get_wordlen(src1);
    int y_wordlen = get_wordlen(src2);

    bi_new(dst, new_wordlen, NON_NEGATIVE);  //z는 src1, src2중 긴길이로 우선 할당

    bigint* temp = NULL;
    bi_assign(&temp, src2); //src2를 변형해야 하는 경우 

    int carry = 0;
    //bi_show(temp, 16);
    if (get_wordlen(src1) != get_wordlen(temp))     // src1, src2 길이 다르면
    {
        temp->wordlen = new_wordlen;
        temp->a = (word*)realloc(temp->a, sizeof(word) * new_wordlen);       // scr2 재할당
        //bi_show(temp, 16);
        //printf("=\n");
        for (int i = new_wordlen; i > y_wordlen; i--)
            temp->a[i - 1] = 0;

        //bi_show(temp, 16);
        //printf("=\n");
    }
    for (int i = 0; i < new_wordlen; i++)
    {
        subABS(&(*dst)->a[i], &carry, &src1->a[i], &temp->a[i]);
    }
    bi_delete(&temp);
}

void SUB(bigint** dst, const bigint* src1, const bigint* src2)   //src1 과 src2를 비교하여 subc로 이동시키는 함수
{
    bigint* temp = NULL;
    if(bi_is_zero(src1) == TRUE && bi_is_zero(src2) == TRUE)
    {
        bi_set_zero(dst);
    }
    else if (TRUE == bi_is_zero(src1))  //  src1=0
    {
        bi_assign(dst, src2); // bigint 구조체를 복사하는 함수
        flip_sign(*dst);
        //printf("#src1=0\n");
    }
    else if (TRUE == bi_is_zero(src2)) //  src2=0
    {
        bi_assign(dst, src1);
        //printf("#src2=0\n");
    }
    else if (0 == bi_compare(src1, src2)) //  src1=src2
    {
        bi_set_zero(dst);
        //printf("#src2=src1\n");

    }
    else if ((1 == bi_compare(src1, src2)) && (src2->sign == NON_NEGATIVE))  //  src1>src2>0
    {
        //printf("#src1>src2>0\n");
        subc(dst, src1, src2);
    }
    else if ((-1 == bi_compare(src1, src2)) && (src1->sign == NON_NEGATIVE))  // src2>src1>0
    {
        //printf("#src2>src1>0\n");
        subc(dst, src2, src1);
        flip_sign(*dst);
    }
    else if ((1 == bi_compare(src1, src2)) && (src1->sign == NEGATIVE))      // 0>src1>src2
    {
        //printf("#0>src1>src2\n");
        subc(dst, src2, src1);
    }
    else if ((-1 == bi_compare(src1, src2)) && (src2->sign == NEGATIVE))   //   0>src2>src1
    {
        //printf("# 0>src2>src1\n");
        subc(dst, src1, src2);
        flip_sign(*dst);
    }
    else if ((src1->sign == NON_NEGATIVE) && (src2->sign == NEGATIVE))    //  src1>0>src2
    {
        //printf("# src1>0>src2\n");
        bi_assign(&temp, src2);
        flip_sign(temp);
        ADD(dst, src1, temp);
        //flip_sign(src2);
        //ADD(dst, src1, src2); // *수정*
        //flip_sign(src2);
    }
    else                           // src2>0>src1
    {
        //printf("#else\n");
        bi_assign(&temp,src1);
        flip_sign(temp);
        ADD(dst, temp, src2);
        //flip_sign(src1);
        //ADD(dst, src1, src2); // *수정*
        //flip_sign(src1);
        flip_sign(*dst);
    }
    bi_delete(&temp);
}


void MUL_1Word(word* dst, const word* src1, const word* src2)
{
    word A[2], B[2], temp[2], t;
    A[1] = (*src1)>>(WORD_BITLEN/2);
    A[0] = (*src1)&HALF_WORDBIT;
    B[1] = (*src2)>>(WORD_BITLEN/2);
    B[0] = (*src2)&HALF_WORDBIT;

    temp[1] = A[1]*B[0];
    temp[0] = (A[0]*B[1])+(temp[1]);
    if(temp[0] < temp[1])   temp[1] = 1;
    else temp[1] = 0;

    dst[1] = A[1]*B[1];
    dst[0] = A[0]*B[0];
    t = dst[0];

    dst[0] += temp[0]<<(WORD_BITLEN/2);
    dst[1] += (temp[1]<<(WORD_BITLEN/2)) + (temp[0]>>(WORD_BITLEN/2));
    if(dst[0] < t)  dst[1]++;
} 

void MULC(bigint** dst, const bigint* src1, const bigint* src2)// schoolbook multiplication 
{
    word temp[2];
    int n = get_wordlen(src1), m = get_wordlen(src2), i, j;
    bi_new(dst, n+m, NON_NEGATIVE);
    bigint* temp_bigint = NULL;
    bi_new(&temp_bigint, n+m, NON_NEGATIVE);
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < m; j++)
        {
            MUL_1Word(temp, &src1->a[i], &src2->a[j]);
            temp_bigint->a[i+j] = temp[0];  
            temp_bigint->a[i+j+1] = temp[1];
            ADD2(dst,temp_bigint);
            array_init(temp_bigint->a + i+j, 2);
        }
    }
    bi_delete(&temp_bigint);
}

void MUL(bigint** dst, const bigint* src1, const bigint* src2) // schoolbook multiplication 
{

    if(bi_is_zero(src1) == TRUE || bi_is_zero(src2) == TRUE)
        bi_set_zero(dst);
    else if (bi_is_one(src1) == TRUE)
    {
        bi_assign(dst, src2);       

    }
    else if(bi_is_minus_one(src1) == TRUE)
    {
        bi_assign(dst, src2);
        flip_sign(*dst);
    }
    else if(bi_is_one(src2) == TRUE)
        bi_assign(dst,src1);
    else if(bi_is_minus_one(src2) == TRUE)
    {
        bi_assign(dst, src1);
        flip_sign(*dst);
    }
    else
    {
        MULC(dst,src1,src2);

        (*dst)->sign = get_sign(src1)^get_sign(src2);
        // src1의 부호 1 0 1 0 
        // src2의 부호 1 0 0 1
        // dst의 부호  0 0 1 1 -> 양 양 음 음 
    }

}

void abattach(bigint** dst, const bigint* src1, const bigint* src2)
{
    bi_new(dst, get_wordlen(src1) , get_sign(src1));
    int i;
    for (i = 0; i < get_wordlen(src2); i++)
        (*dst)->a[i] = src2->a[i];
    for (i = get_wordlen(src2); i < get_wordlen(src1) ; i++)
    {
        (*dst)->a[i] = src1->a[i] ;
    }
    bi_refine(*dst);

}

void Karatsuba(bigint** dst, const bigint* src1, const bigint* src2, const int flag)
{
    int temp = min(get_wordlen(src1), get_wordlen(src2));
    if (flag >= temp)
    {
        MUL(dst, src1, src2);
        return;
    }
    int l;
    bigint* aco0 = NULL;    //a 하위 절반
    bigint* aco1 = NULL;    //a 상위 절반
    bigint* bco0 = NULL;    //b 하위 절반
    bigint* bco1 = NULL;    //b 상위 절반
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint* tco1 = NULL;
    bigint* R = NULL;
    bigint* S0 = NULL;
    bigint* S1 = NULL;
    bigint* S = NULL;
   

    l = (max(get_wordlen(src1), get_wordlen(src2)) + 1) >> 1;    // 전체 word 길이 절반으로 
    bi_assign(&aco0, src1);         bi_assign(&aco1, src1);    // a 두개 써야되서 2개 할당
    bi_assign(&bco0, src2);         bi_assign(&bco1, bco0);     // b 도 두개 써야되서


    right_shift(aco1, l * WORD_BITLEN);     reduction_2_r(aco0, l * WORD_BITLEN);     // 복사한 a 2개 각각 shift랑 reduct

    right_shift(bco1, l * WORD_BITLEN);     reduction_2_r(bco0, l * WORD_BITLEN);    
    //bi_show(aco0, 16);     bi_show(aco1, 16);      bi_show(bco0, 16);     bi_show(bco1, 16);   // 일단 잘들어갔나 보기 여기까지는 잘됨


    //printf("*******\n");
    Karatsuba(&t1, aco1, bco1, flag);
    // printf("# t1:");
    // bi_show(t1, 16);
    Karatsuba(&t0, aco0, bco0, flag);
    // printf("# t0:");
    // bi_show(t0, 16);
    bi_assign(&tco1, t1);
    left_shift(tco1, 2 * l * WORD_BITLEN);
   
    abattach(&R, tco1, t0);
    right_shift(tco1, 2 * l * WORD_BITLEN);
    // printf("#R:");
    // bi_show(R, 16);

    SUB(&S1, aco0, aco1);
    // printf("# aco0:");
    // bi_show(aco0, 16);
    // printf("# aco1:");

    // bi_show(aco1, 16);
    // printf("# s1:");
    // bi_show(S1, 16);

    SUB(&S0, bco1, bco0);
    // printf("# bco0:");

    // bi_show(bco1, 16);
    // printf("# bco0:");

    // bi_show(bco0, 16);
    // printf("# s1:");

    // bi_show(S0, 16);

    int temp1 = 1, temp2 = 1;

    if (S0->sign == NEGATIVE)
    {
        temp1 = 2;
        S0->sign = NON_NEGATIVE;
    }
    if (S1->sign == NEGATIVE)
    {
        temp2 = 2;
        S1->sign = NON_NEGATIVE;
    }
    Karatsuba(&S, S1, S0, flag);
    
    // printf("# s:");
    // bi_show(S, 16);

    if (temp1 == 2)
    {
        S0->sign = NEGATIVE;
    }
    if (temp2 == 2)
    {
        S1->sign = NEGATIVE;
    }

    if ((temp1 * temp2) == 2)     //둘의 부호가 다르면 곱이 2나옴
        S->sign = NEGATIVE;
    else
        S->sign = NON_NEGATIVE;

    
    //printf("**s**\n");
    // printf("# s:");
    // bi_show(S, 16);
    // printf("# t1:");
    // bi_show(t1, 16);

    bigint* tmp1 = NULL;
    bigint* tmp2 = NULL;

    //ADDC2(S, t1);
    ADD(&tmp1, S, t1);
    //printf("**tmp1**\n");
    // printf("# tmp1:");
    // bi_show(tmp1, 16);
    // printf("# t0:");
    // bi_show(t0, 16);

    //ADDC2(S, t0);
    ADD(&tmp2, tmp1, t0);
    // printf("# tmp2:");
    // bi_show(tmp2, 16);

    left_shift(tmp2, l * WORD_BITLEN);
    // printf("# tmp2:");
    // bi_show(tmp2, 16);

    //ADDC2(R, S);
    // printf("#R:");
    // bi_show(R, 16);

    ADD(dst, R, tmp2);
    // printf("# dst:");
    // bi_show(*dst, 16);

    right_shift(tmp2, l * WORD_BITLEN);
    //bi_assign(dst, R);           //RETURN R


    bi_delete(&aco0);
    bi_delete(&aco1);
    bi_delete(&bco0);
    bi_delete(&bco1);
    bi_delete(&t0);
    bi_delete(&t1); 
    bi_delete(&R);
    bi_delete(&S0);
    bi_delete(&S1);
    bi_delete(&S); 
    bi_delete(&tco1);//문제
    bi_delete(&tmp1);
    bi_delete(&tmp2);//문제

}


void SQUC_1Word(word* dst, const word* src)
{
    word A[2], temp, t, carry = 0;
    A[1] = (*src)>>(WORD_BITLEN/2);
    A[0] = (*src)&HALF_WORDBIT;

    temp = A[0]*A[1];
    dst[1] = A[1]*A[1];
    dst[0] = A[0]*A[0];

    word temp1 = temp << (WORD_BITLEN/2+1);
    word temp2 = temp >> (WORD_BITLEN/2-1);
    ADD_ABc2(&dst[0], &carry, &temp1);
    ADD_ABc2(&dst[1], &carry, &temp2);
}

void SQUC(bigint** dst, const bigint* src)
{
    word temp[2];
    int i, j, t = get_wordlen(src);
    bigint* temp_bigint = NULL;
    bi_new(&temp_bigint, 2*t, NON_NEGATIVE);
    bigint* C0 = NULL;
    bigint* C1 = NULL;
    bi_new(&C0, 2*t, NON_NEGATIVE);
    bi_new(&C1, 2*t, NON_NEGATIVE);
    for ( i = 0; i < t; i++)
    {
        SQUC_1Word(temp, &src->a[i]);
        temp_bigint->a[2*i] = temp[0];  
        temp_bigint->a[2*i+1] = temp[1];
        ADD2(&C0, temp_bigint);
        array_init(temp_bigint->a + 2*i, 2);
        for ( j = i+1; j < t; j++)
        {
            MUL_1Word(temp, &src->a[i], &src->a[j]);
            temp_bigint->a[i+j] = temp[0];  
            temp_bigint->a[i+j+1] = temp[1];
            ADD2(&C1, temp_bigint);
            array_init(temp_bigint->a + i+j, 2);
        } 
    }
    left_shift(C1,1);
    ADD(dst, C0, C1);
    
    bi_delete(&temp_bigint);
    bi_delete(&C0);
    bi_delete(&C1);
}

void SQU(bigint** dst, const bigint* src)
{
    if(bi_is_zero(src) == TRUE || bi_is_minus_one(src) == TRUE || bi_is_one(src) == TRUE)
    {
        bi_assign(dst,src);
        (*dst)->sign = NON_NEGATIVE;
    } 
    else
        SQUC(dst,src);
}