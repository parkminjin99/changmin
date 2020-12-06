//  
//  op_bit.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/12/06.
//  Copyright 2020 최강창민. All rights reserved.
//  

#include "operation.h"


void left_shift(bigint* x, int r)   // bigint x를 r비트만큼 왼쪽으로 shift하는 함수
{
    int i;
    if (r % WORD_BITLEN == 0)       // r가 WORD_BITLEN의 배수인 경우
    {
        x->wordlen += r/WORD_BITLEN;
        x->a = (word*)realloc(x->a, sizeof(word) * get_wordlen(x));
        array_copy(x->a + (r / WORD_BITLEN), x->a, x->wordlen - (r / WORD_BITLEN));
        array_init(x->a, r / WORD_BITLEN);
    }
    else                            // r이 WORD_BITLEN의 배수가 아닌 경우
    {
        x->wordlen += r / WORD_BITLEN + 1;
        x->a = (word*)realloc(x->a, sizeof(word) * get_wordlen(x));

        int n = get_wordlen(x) - r / WORD_BITLEN;   // n은 shift했을 때 0이 아닌 부분의 길이
        x->a[get_wordlen(x)-1] = (x->a[get_wordlen(x) - 1 - r / WORD_BITLEN - 1] >> (WORD_BITLEN - r % WORD_BITLEN));
        for (i = get_wordlen(x) - 2; i > get_wordlen(x) - n; i--)
            x->a[i] = (x->a[i - r/WORD_BITLEN - 1] >> (WORD_BITLEN - r % WORD_BITLEN)) | (x->a[i - r / WORD_BITLEN] << (r % WORD_BITLEN)); // x->a[i]는 x->a[i-1]의 상위 r%WORD_BITLEN비트와 x->a[i]의 하위 WORD_BITLEN-r%WORD_BITLEN비트로 구성
        x->a[get_wordlen(x) - n] = x->a[get_wordlen(x)- n - r / WORD_BITLEN] << (r%WORD_BITLEN);
        array_init(x->a, r / WORD_BITLEN);
    }
    bi_refine(x);
}

void right_shift(bigint* x, int r)          // bigint x를 r비트만큼 오른쪽으로 shift하는 함수
{
    if (r >= get_wordlen(x) * WORD_BITLEN)  // r이 x->wordlen*WORD_BITLEN보다 크거나 같은 경우
        bi_zeroize(x);
    else if (r % WORD_BITLEN == 0)          // r이 WORD_BITLEN의 배수인 경우
    {
        array_copy(x->a, x->a + (r / WORD_BITLEN), get_wordlen(x) - (r / WORD_BITLEN));
        array_init(x->a + (get_wordlen(x) - (r / WORD_BITLEN)), r / WORD_BITLEN);
        bi_refine(x);
    }
    else                                    // r이 WORD_BITLEN의 배수가 아닌 경우
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

void reduction_2_r(bigint* x, int r)            // bigint x의 x mod 2^r를 출력하는 함수
{
    if (r >= (get_wordlen(x) * WORD_BITLEN))    // r가 x->wordlen*WORD_BITLEN보다 크거나 같은 경우
        return;
    else if (r % WORD_BITLEN == 0)              // r가 WORD_BITLEN의 배수인 경우
    {
        array_init(x->a + r / WORD_BITLEN, x->wordlen - r / WORD_BITLEN);
        bi_refine(x);
    }
    else                                        // r가 WORD_BITLEN의 배수가 아닌 경우
    {
        word k = BITMASK;
        x->a[r / WORD_BITLEN] &= (k >> (WORD_BITLEN - r % WORD_BITLEN)); // x->a[r/WORD_BITLEN]의 하위 r%WORD_BITLEN비트만 남김
        array_init(x->a + r / WORD_BITLEN + 1, x->wordlen - r / WORD_BITLEN - 1);
        bi_refine(x);
    }
}