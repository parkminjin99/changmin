//  
//  op_bit.c
//  Changmin's library
//  
//  Created by �ְ�â�� on 2020/12/06.
//  Copyright 2020 �ְ�â��. All rights reserved.
//  

#include "operation.h"


void left_shift(bigint* x, int r)   // bigint x�� r��Ʈ��ŭ �������� shift�ϴ� �Լ�
{
    int i;
    if (r % WORD_BITLEN == 0)       // r�� WORD_BITLEN�� ����� ���
    {
        x->wordlen += r/WORD_BITLEN;
        x->a = (word*)realloc(x->a, sizeof(word) * get_wordlen(x));
        array_copy(x->a + (r / WORD_BITLEN), x->a, x->wordlen - (r / WORD_BITLEN));
        array_init(x->a, r / WORD_BITLEN);
    }
    else                            // r�� WORD_BITLEN�� ����� �ƴ� ���
    {
        x->wordlen += r / WORD_BITLEN + 1;
        x->a = (word*)realloc(x->a, sizeof(word) * get_wordlen(x));

        int n = get_wordlen(x) - r / WORD_BITLEN;   // n�� shift���� �� 0�� �ƴ� �κ��� ����
        x->a[get_wordlen(x)-1] = (x->a[get_wordlen(x) - 1 - r / WORD_BITLEN - 1] >> (WORD_BITLEN - r % WORD_BITLEN));
        for (i = get_wordlen(x) - 2; i > get_wordlen(x) - n; i--)
            x->a[i] = (x->a[i - r/WORD_BITLEN - 1] >> (WORD_BITLEN - r % WORD_BITLEN)) | (x->a[i - r / WORD_BITLEN] << (r % WORD_BITLEN)); // x->a[i]�� x->a[i-1]�� ���� r%WORD_BITLEN��Ʈ�� x->a[i]�� ���� WORD_BITLEN-r%WORD_BITLEN��Ʈ�� ����
        x->a[get_wordlen(x) - n] = x->a[get_wordlen(x)- n - r / WORD_BITLEN] << (r%WORD_BITLEN);
        array_init(x->a, r / WORD_BITLEN);
    }
    bi_refine(x);
}

void right_shift(bigint* x, int r)          // bigint x�� r��Ʈ��ŭ ���������� shift�ϴ� �Լ�
{
    if (r >= get_wordlen(x) * WORD_BITLEN)  // r�� x->wordlen*WORD_BITLEN���� ũ�ų� ���� ���
        bi_zeroize(x);
    else if (r % WORD_BITLEN == 0)          // r�� WORD_BITLEN�� ����� ���
    {
        array_copy(x->a, x->a + (r / WORD_BITLEN), get_wordlen(x) - (r / WORD_BITLEN));
        array_init(x->a + (get_wordlen(x) - (r / WORD_BITLEN)), r / WORD_BITLEN);
        bi_refine(x);
    }
    else                                    // r�� WORD_BITLEN�� ����� �ƴ� ���
    {
        int i;
        int n = get_wordlen(x) - r / WORD_BITLEN; // n�� shift���� �� 0�� �ƴ� �κ��� ����
        for (i = 0; i < n - 1; i++)
            x->a[i] = (x->a[i + 1 + r/WORD_BITLEN] << (WORD_BITLEN - r % WORD_BITLEN)) | (x->a[i + r / WORD_BITLEN] >> (r % WORD_BITLEN)); // x->a[i]�� x->a[i+1]�� ���� r%WORD_BITLEN��Ʈ�� x->a[i]�� ���� WORD_BITLEN-r%WORD_BITLEN��Ʈ�� ����
        x->a[n - 1] = x->a[n - 1 + r / WORD_BITLEN] >> (r % WORD_BITLEN);
        array_init(x->a + (get_wordlen(x) - r / WORD_BITLEN), r / WORD_BITLEN);
        bi_refine(x);
    }
}

void reduction_2_r(bigint* x, int r)            // bigint x�� x mod 2^r�� ����ϴ� �Լ�
{
    if (r >= (get_wordlen(x) * WORD_BITLEN))    // r�� x->wordlen*WORD_BITLEN���� ũ�ų� ���� ���
        return;
    else if (r % WORD_BITLEN == 0)              // r�� WORD_BITLEN�� ����� ���
    {
        array_init(x->a + r / WORD_BITLEN, x->wordlen - r / WORD_BITLEN);
        bi_refine(x);
    }
    else                                        // r�� WORD_BITLEN�� ����� �ƴ� ���
    {
        word k = BITMASK;
        x->a[r / WORD_BITLEN] &= (k >> (WORD_BITLEN - r % WORD_BITLEN)); // x->a[r/WORD_BITLEN]�� ���� r%WORD_BITLEN��Ʈ�� ����
        array_init(x->a + r / WORD_BITLEN + 1, x->wordlen - r / WORD_BITLEN - 1);
        bi_refine(x);
    }
}