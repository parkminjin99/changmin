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
        array_init(x->a + (get_wordlen(x) - (r / WORD_BITLEN)), r * WORD_BITLEN);
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
    for (i = 0; i < get_wordlen(src2); i++)
        ADD_ABc(&(*dst)->a[i], &carry, &src1->a[i], &src2->a[i]); // 1워드 덧셈
    for (i = get_wordlen(src2); i < get_wordlen(src1); i++)
    {
        (*dst)->a[i] = src1->a[i] + carry;
        if ((*dst)->a[i] < carry) // carry 발생
            carry = 1;
        else
            carry = 0;
    }
    if (carry == 0) // carry가 0일 경우 refine
        bi_refine(*dst);
}

void ADDC2(bigint* dst, const bigint* src)
{
    int i;
    word carry = 0; // carry
    for (i = 0; i < get_wordlen(src); i++)
        ADD_ABc2(&dst->a[i], &carry, &src->a[i]); // 1워드 덧셈
    for (i = get_wordlen(src); i < get_wordlen(src); i++)
    {
        dst->a[i] = src->a[i] + carry;
        if (dst->a[i] < carry) // carry 발생
            carry = 1;
        else
            carry = 0;
    }
}

void ADD(bigint** dst, const bigint* src1, const bigint* src2)
{
    if (bi_is_zero(src1) == TRUE) // src1 = 0
        bi_assign(dst, src1);
    else if (bi_is_zero(src2) == TRUE) // src2 = 0
        bi_assign(dst, src2);
    else if ((get_sign(src1) == NON_NEGATIVE) && (get_sign(src2) == NEGATIVE)) // src1 >= 0, src2 < 0
        SUB(dst, src1, src2);
    else if ((get_sign(src1) == NEGATIVE) && (get_sign(src2) == NON_NEGATIVE)) // src1 < 0, src2 >= 0
        SUB(dst, src2, src1);
    else if (get_wordlen(src1) >= get_wordlen(src2))
        ADDC(dst, src1, src2);
    else
        ADDC(dst, src2, src1);
}

void subABS(word* dst, int* carry, const word src1, const word src2)    // src1과 src2, carry를 입력받아 1word에 대한 뺄셈의 절댓값을 출력
{
	if (src1 > *carry)                  
		*dst = src1 - *carry;
	else
		*dst = -(src1 - *carry);

	if (src1 < *carry)
		*carry = 1;
	else
		*carry = 0;

	if (*dst < src2)
		*carry = *carry + 1;

	if (*dst > src2)
		*dst = *dst - src2;
	else
		*dst = -(src2 -*dst);
}

void subc(bigint** dst, bigint* src1, bigint* src2)    // src1>src2로 입력받아 둘의 차를 dst에 저장
{
    bi_new(dst, get_wordlen(max(src1, src2)), NON_NEGATIVE);  //z는 src1, src2중 긴길이로 우선 할당
    int new_wordlen = get_wordlen(src1);
    int y_wordlen = get_wordlen(src2);
    int carry = 0;
    if (new_wordlen != y_wordlen)     // src1, src2 길이 다르면
    {
        src2->wordlen = new_wordlen;
        (*dst)->wordlen = new_wordlen;
        src2->a = (word*)realloc(src2->a, sizeof(word) * new_wordlen);       // scr2 재할당
        (*dst)->a = (word*)realloc((*dst)->a, sizeof(word) * new_wordlen);   // dst 재할당
        for (int i = new_wordlen; i > new_wordlen - y_wordlen; i--)
            src2->a[i - 1] = 0;
    }
    for (int i = 0; i < new_wordlen; i++)
    {
        subABS(&(*dst)->a[i], &carry, src1->a[i], src2->a[i]);
    }
}

void SUB(bigint** dst, bigint* src1, bigint* src2)   //src1 과 src2를 비교하여 subc로 이동시키는 함수
{
    if (TRUE == bi_is_zero(src1))  //  src1=0
    {
        bi_assign(dst, src2); // bigint 구조체를 복사하는 함수
        flip_sign(*dst);
    }
    else if (TRUE == bi_is_zero(src2)) //  src2=0
        bi_assign(dst, src1);
    else if (0 == bi_compare(src1, src2)) //  src1=src2
        bi_set_zero(dst);
    else if ((1 == bi_compare(src1, src2)) && (src2->sign == NON_NEGATIVE))  //  src1>src2>0
    {
        subc(dst, src1, src2);
    }
    else if ((-1 == bi_compare(src1, src2)) && (src1->sign == NON_NEGATIVE))  // src2>src1>0
    {
        subc(dst, src2, src1);
        flip_sign(*dst);
    }
    else if ((1 == bi_compare(src1, src2)) && (src1->sign == NEGATIVE))      // 0>src1>src2
    {
        flip_sign(src1);
        flip_sign(src2);
        subc(dst, src2, src1);
    }
    else if ((-1 == bi_compare(src1, src2)) && (src2->sign == NEGATIVE))   //   0>src2>src1
    {
        flip_sign(src1);
        flip_sign(src2);
        subc(dst, src1, src2);
        flip_sign(*dst);
    }
    else if ((src1->sign == NON_NEGATIVE) && (src2->sign == NEGATIVE))    //  src1>0>src2
    {
        flip_sign(src2);
        ADD(dst, src1, src2);
    }
    else                           // src2>0>src1
    {
        flip_sign(src1);
        ADD(dst, src1, src2);
        flip_sign(*dst);
    }

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
            ADDC2(*dst,temp_bigint);
            array_init(temp_bigint->a, get_wordlen(temp_bigint));
        }
    }
    bi_delete(&temp_bigint);
}

void MUL(bigint** dst, const bigint* src1, const bigint* src2) // schoolbook multiplication 
{
    if(bi_is_zero(src1) == TRUE || bi_is_zero(src2) == TRUE)
        bi_set_zero(dst);
    else if(bi_is_one(src1) == TRUE)
        bi_assign(dst,src2);
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

void SQUC_1Word(word* dst, const word* src)
{
    
}

void SQUC(bigint** dst, const bigint* src)
{
    word temp[2];
    int i,j, t = get_wordlen(src);
    bigint* temp_bigint = NULL;
    bi_new(&temp_bigint, 2*t, NON_NEGATIVE);
    for ( i = 0; i < t; i++)
    {
        MUL_1Word(temp, &src->a[i], &src->a[i]);
        temp_bigint->a[2*i] = temp[0];  
        temp_bigint->a[2*i+1] = temp[1];
        ADDC2(*dst,temp_bigint);
        array_init(temp_bigint->a, get_wordlen(temp_bigint));
        for ( j = i+1; j < t; j++)
        {
            MUL_1Word(temp, &src->a[i], &src->a[j]);
            temp_bigint->a[i+j] = temp[0];  
            temp_bigint->a[i+j+1] = temp[1];
            ADDC2(*dst,temp_bigint);
            array_init(temp_bigint->a, get_wordlen(temp_bigint));
        } 
        
    }
    
}


