//
//  bigint.c
//  Changmin's library
//
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
// 

#include "bigint.h"
#include "array.h"
#include <stdlib.h>
#include <memory.h>

void bi_sage_show(const bigint* x, const int base)
{
    int i, j;
    if (get_sign(x) == NEGATIVE)
        printf("-");
    if (base == 16)
    {
        printf("0x");
        if(bi_is_zero(x) == TRUE)
            printf("0");
        else
        {
            for (i = get_wordlen(x) - 1; i >= 0; i--)
                for (j = WORD_BITLEN - 4; j >= 0; j = j - 4)
                    printf("%x", (int)(((x->a[i]) >> j) & 0xf));
        }
    }
    else if (base == 2)
    {
        printf("0b");
        if(bi_is_zero(x) == TRUE)
            printf("0");
        else
        {
            for (int i = get_wordlen(x) - 1; i >= 0; i--)
                for (int j = WORD_BITLEN - 1; j >= 0; j--)
                    printf("%x", (int)(((x->a[i]) >> j) & 0x1));
        }
    }
    else // base = 10
    {
        if (bi_is_zero(x) == TRUE)
            printf("0");
        else
        {
            int str[5000];
            bigint* ten = NULL;
            bigint* q = NULL;
            bigint* r = NULL;
            bigint* xtemp = NULL;

            bi_assign(&xtemp, x);

            bi_new(&ten, 1, NON_NEGATIVE);
            ten->a[0] = 10;
            int i = 0;
            while (TRUE)
            {
                DIV(&q, &r, xtemp, ten);
                str[i] = (int)(r->a[0]);
                bi_assign(&xtemp, q);
                i++;
                if (-1 == bi_compare(xtemp, ten))
                {
                    str[i] = (int)(xtemp->a[0]);
                    break;
                }

            }
            bi_delete(&q);
            bi_delete(&r);
            bi_delete(&ten);
            bi_delete(&xtemp);
            for (int j = i; j >= 0; j--)
                printf("%d", str[j]);
        }
    }
    //printf(")\n");
}

/********************************
bi_show
����ü�� ����Ǿ��ִ� bignum�� ���ϴ� ����(2,10,16)�� ����ϴ� �Լ�
*********************************/

void bi_show(const bigint* x, const int base)
{
    int i, j;
    if(bi_is_zero(x) == TRUE)
    {
        printf("0\n");
        return;
    }
    if (get_sign(x) == NEGATIVE)
        printf("-");
    if (base == 16)
    {
        for (i = get_wordlen(x) - 1; i >= 0; i--)
            for (j = WORD_BITLEN - 4; j >= 0; j = j - 4)
                printf("%x", (int)(((x->a[i]) >> j) & 0xf));
    }
    else if (base == 2)
    {
        for (int i = get_wordlen(x) - 1; i >= 0; i--)
            for (int j = WORD_BITLEN - 1; j >= 0; j--)
                printf("%x", (int)(((x->a[i]) >> j) & 0x1));
    }
    else // base = 10
    {
        int str[5000];
        bigint* ten = NULL;
        bigint* q = NULL;
        bigint* r = NULL;
        bigint* xtemp = NULL;

        bi_assign(&xtemp, x);
        xtemp->sign = NON_NEGATIVE;
        bi_new(&ten, 1, NON_NEGATIVE);
        ten->a[0] = 10;
        int i = 0;
        while (TRUE)
        {
            DIV(&q, &r, xtemp, ten);
            str[i] = (int)(r->a[0]);
            bi_assign(&xtemp, q);
            i++;
            if (-1 == bi_compare(xtemp, ten))
            {
                str[i] = (int)(xtemp->a[0]);
                break;
            }

        }
        bi_delete(&q);
        bi_delete(&r);
        bi_delete(&ten);
        bi_delete(&xtemp);
        for (int j = i; j >= 0; j--)
            printf("%d", str[j]);
    }
    printf("\n");
}
void bi_delete(bigint** x) // bigint ����ü�� �޸𸮸� �����ϴ� �Լ�
{
    if (*x == NULL) // �޸𸮰� ������ �ʿ䰡 ���� ���
        return;
#ifdef ZEROIZE // �ʿ��� ��� #define ZEROIZE�� ���־� ����ü �� �迭 �޸𸮸� �ʱ�ȭ �� �� �޸� ����
    array_init((*x)->a, (*x)->wordlen);
#endif
    free((*x)->a);  // ����ü �� �迭 �޸� ����
    free(*x);       // ����ü �޸� ����
    *x = NULL;
}


int bi_new(bigint** x, int wordlen, int sign) // bigint ����ü �޸� �����Ҵ� �Լ�
{
    if (*x != NULL) // �޸𸮰� NULL�� �ƴϸ� �޸� ����
        bi_delete(x);
    *x = (bigint*)malloc(sizeof(bigint)); // bigint ����ü �޸� �����Ҵ�
    if (*x == NULL) // �޸𸮰� �Ҵ���� ������ FAIL ����
        return FAIL;
    (*x)->sign = sign;
    (*x)->wordlen = wordlen;
    (*x)->a = (word*)calloc(wordlen, sizeof(word)); // bigint ����ü �� �迭 �޸� �����Ҵ�
    return SUCCESS;
}


int bi_refine(bigint* x) // bigint ����ü ���� �迭���� 0�� ������ �迭�� �����ϴ� �Լ�
{
    if (x == NULL)
        return SUCCESS;
    int new_wordlen = get_wordlen(x);
    while (new_wordlen > 1)
    {
        if (x->a[new_wordlen - 1] != 0) // 0�� �ƴ� �迭�� ������ break
            break;
        new_wordlen--;
    }
    if (get_wordlen(x) != new_wordlen) // �޸� ���Ҵ�
    {
        x->wordlen = new_wordlen;
        x->a = (word*)realloc(x->a, sizeof(word) * new_wordlen);
        if (x->a == NULL)
            return FAIL;
    }
    if ((get_wordlen(x) == 0) && (x->a[0] == 0x0)) // bigint�� 0�� ��쿡 sign���� NON_NEGATIVE�� ����
        x->sign = NON_NEGATIVE;
    return SUCCESS;
}

void bi_zeroize(bigint* x) // bigint ���� �迭�� 0���� �ʱ�ȭ�ϴ� �Լ�
{
    array_init(x->a, get_wordlen(x));
    bi_refine(x);
}

void bi_assign(bigint** dst, const bigint* src) // bigint ����ü�� �����ϴ� �Լ�
{
    int srcLen = get_wordlen(src);
    if (FAIL == bi_new(dst, srcLen, get_sign(src)))
        return;
    array_copy((*dst)->a, src->a, srcLen);
}

void bi_set_by_array(bigint** x, int sign, word* a, int wordlen)  // a�� sign ������ struct�� �����ϱ�.
{
    if (FAIL == bi_new(x, wordlen, sign))
        return;
    array_copy((*x)->a, a, wordlen);
}

void bi_set_by_string(bigint** x, int sign, char* str, word base) // str = "1234567896321356"
{
    int stln = (int)strlen(str);
    if (base == 2)
    {
        if (FAIL == bi_new(x, (stln / (WORD_BITLEN + 1)) + 1, sign))
            return;
        for (int i = stln - 1; i >= 0; i--)   //  11110001       10001111 0001 1111
            (*x)->a[(stln - 1 - i) / WORD_BITLEN] ^= ((str[i] - '0') << ((stln - 1 - i) % WORD_BITLEN));
    }
    else if (base == 16)
    {
        int len = (stln*4) / WORD_BITLEN;
        if((stln*4)%WORD_BITLEN != 0)
            len++;
        if (FAIL == bi_new(x, len, sign))
            return;
        printf("x->wordlen = %d\n", (*x)->wordlen);
        int tmp[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
        for (int i = stln - 1; i >= 0; i--)   //  11110001       10001111 0001 1111
        {
            int j = 0;
            for (j = 0; j < 16; j++)
            {
                if (str[i] == tmp[j])
                    break;
            }
            (*x)->a[4 * (stln - 1 - i) / WORD_BITLEN] ^= ((word)(j) << (4 * (stln - 1 - i) % WORD_BITLEN));
        }
    }
    else // base = 10
    {
        bigint* ten = NULL;
        bigint* b = NULL;
        bigint* st = NULL;
        bi_new(&ten, 1, NON_NEGATIVE);
        char temp;
        ten->a[0] = base;
        bi_new(&st, 1, NON_NEGATIVE);

        char tm[10] = { '0','1','2','3','4','5','6','7','8','9' };
        temp = str[stln - 1];
        int j;
        for (j = 0; j < base; j++)
            if (tm[j] == temp)
                break;

        st->a[0] = j;
        bi_assign(x, st);
        bi_assign(&b, ten);
        for (int i = stln - 2; i >= 0; i--)
        {
            temp = str[i];
            for (j = 0; j < 10; j++)
                if (tm[j] == temp)
                    break;
            st->a[0] = j;
            MUL_zzy(&st, ten);
            ADD_zzy(x, st);
            MUL_zzy(&ten, b);
            bi_set_one(&st);
        }

        (*x)->sign = sign;

        bi_delete(&ten);
        bi_delete(&b);
        bi_delete(&st);
    }

}
void bi_gen_rand(bigint** x, int sign, int wordlen)
{
    if (FAIL == bi_new(x, wordlen, sign))
    {
        printf("MEMORY FAIL\n");
        return;
    }
    array_rand((*x)->a, wordlen);
    bi_refine(*x);
}
/**********************
get_wordlen
����Ǿ��ִ� bignum�� word���̸� ������ִ� �Լ�.
����� int������ ����.
**********************/

int get_wordlen(const bigint* x) 
{
    return x->wordlen;             //����ü�� wordlen�� ����� ���� ����.
}

/**********************
get_bitlen
����Ǿ��ִ� bignum�� bit���̸� ������ִ� �Լ�.
�������� ���� �Լ��� ����� int������ ����.
**********************/

int get_bitlen(const bigint* x)            // ������ ������ ��Ʈ�� ��..?
{
    word last = x->a[get_wordlen(x) - 1];
    for (int i = WORD_BITLEN - 1; i > 0; i--)
    {
        if (((last >> i) | 0x0) == 1)
            return i;
    }
    return FAIL;
}

/**********************
get_jth_bit
����Ǿ��ִ� bignum�� j��° bit�� ������ִ� �Լ�.
���⼭ j��°�� ������Ʈ�� 1��°�� ���� ���.
����� int������ ����.
**********************/

int get_jth_bit(const bigint* x, const int j)  
{
    int jword, jbit;
    jword = j / WORD_BITLEN;
    jbit = j % WORD_BITLEN;
    return ((x->a[jword]) >> jbit) & 0x1;
}

/**********************
get_sign
����Ǿ��ִ� bignum�� ��ȣ�� ������ִ� �Լ�.
�������� ���� �Լ��� ����� int������ ����.
NEGATIVE�ΰ�� 1, NON_NEGATIVE�� ��� 0 ����.
**********************/

int get_sign(const bigint* x)     
{
    return x->sign;
}

/**********************
flip_sign
����Ǿ��ִ� bignum�� ��ȣ�� �ٲپ��ִ� �Լ�.
NEGATIVE�ΰ�� 1, NON_NEGATIVE�� ��� 0 ���� ����Ǳ� ������
XOR 1�� ���� ��ȣ�� �����ϴ� ���� �����ϴ�.
**********************/

void flip_sign(bigint* x)    
{
    x->sign = 0x1 ^ (x->sign);
}

/**********************
bi_set_one
�Է¹��� �ּҿ� �ش��ϴ� bignum�� ��� 1�� �����ϴ� �Լ�.
������ ������ 1�� ����ϱ⿡ ���Ǹ� ����.
�Է��� bignum�� �ּҷ� ����.
word���̸� 1, ��ȣ�� NON_NEGATIVE, ����� ���� 1�� ����
**********************/

void bi_set_one(bigint** x)     
{
    if (FAIL == bi_new(x, 1, NON_NEGATIVE))
        return;
    (*x)->a[0] = 0x1;
}

/**********************
bi_set_zero
�Է¹��� �ּҿ� �ش��ϴ� bignum�� ��� 0���� �����ϴ� �Լ�. (0�� ���ǻ� ����� ����.)
FOR�� ��� 0�� �ʿ��� ��찡 �ֱ⿡ ���Ǹ� ����.
�Է��� bignum�� �ּҷ� ����.
word���̸� 1, ��ȣ�� NON_NEGATIVE, ����� ���� 0�� ����
**********************/

void bi_set_zero(bigint** x)   
{
    if (FAIL == bi_new(x, 1, NON_NEGATIVE))
        return;
    (*x)->a[0] = 0x0;
}

/**********************
bi_is_minus_one
�Է¹��� bignum�� -1���� Ȯ���ϴ� �Լ�
        �ʿ��� ��찡 �ֱ⿡ ���Ǹ� ����.
�Է��� bignum�� �޾Ƽ� ���ڸ� �����ϴ� x->a�� 1�̰� ��ȣ�� NEGATIVE���� Ȯ���Ѵ�.
������ TRUE, Ʋ���� FALSE�� ����
**********************/

int bi_is_minus_one(const bigint* x)
{
    if ((get_sign(x) != NEGATIVE) || (x->a[0] != 0x1))
        return FALSE;
    for (int j = get_wordlen(x) - 1; j > 0; j--)
        if (x->a[j] != 0)
            return FALSE;
    return TRUE;
}

/**********************
bi_is_one
�Է¹��� bignum�� 1���� Ȯ���ϴ� �Լ�
        �ʿ��� ��찡 �ֱ⿡ ���Ǹ� ����.
�Է��� bignum�� �޾Ƽ� ���ڸ� �����ϴ� x->a�� 1�̰� ��ȣ�� NON_NEGATIVE���� Ȯ���Ѵ�.
������ TRUE, Ʋ���� FALSE�� ����
**********************/

int bi_is_one(const bigint* x)     
{
    if ((get_sign(x) == NEGATIVE) || (x->a[0] != 0x1))
    {
        return FALSE;
    }
    for (int j = get_wordlen(x) - 1; j > 0; j--)
    {
        if (x->a[j] != 0)
            return FALSE;
    }
    return TRUE;
}

/**********************
bi_is_zero
�Է¹��� bignum�� 0���� Ȯ���ϴ� �Լ�
        �ʿ��� ��찡 �ֱ⿡ ���Ǹ� ����.
�Է��� bignum�� �޾Ƽ� ���ڸ� �����ϴ� x->a�� 0�̰� ��ȣ�� NON_NEGATIVE���� Ȯ���Ѵ�.
������ TRUE, Ʋ���� FALSE�� ����
**********************/

int bi_is_zero(const bigint* x)       
{
    if (get_wordlen(x) == 0)
        return TRUE;
    if ((get_sign(x) == 1) || (x->a[0] != 0x0))
        return FALSE;
    for (int j = get_wordlen(x) - 1; j > 0; j--)
    {
        if (x->a[j] != 0)
            return FALSE;
    }
    return TRUE;
}

int bi_compareABS(const bigint* src1, const bigint* src2) // �� bigint�� ������ ���ϴ� �Լ�
{
    if (get_wordlen(src1) > get_wordlen(src2))   // src1 > src2
        return 1;                                                              // *����*
    else if (get_wordlen(src1) < get_wordlen(src2)) // src1 < src2
        return -1;                                                                // *����*
    else // get_wordlen(src1) = get_wordlen(src2)
    {
        int j;
        for (j = get_wordlen(src1) - 1; j >= 0; j--)
        {
            if (src1->a[j] > src2->a[j]) // src1 > src2
                return 1;
            else if (src1->a[j] < src2->a[j]) // src1 < src2
                return -1;
        }
    }
    return 0; // src1 = src2
}

int bi_compare(const bigint* src1, const bigint* src2) // �� bigint�� ���ϴ� �Լ�
{
    /*
        A > B : 1
        A < B : -1
        A = B : 0
    */
    if (src1->sign == NEGATIVE && src2->sign == NON_NEGATIVE) // src1�� ����, src2�� ��� �Ǵ� 0
        return -1;
    else if (src1->sign == NON_NEGATIVE && src2->sign == NEGATIVE) // src1�� ��� �Ǵ� 0, src2�� ����
        return 1;
    else
    {
        int ret = bi_compareABS(src1, src2); // src1, src2�� ������ ũ�⸦ ��
        if (src1->sign == NON_NEGATIVE) // src1, src2 �� �� ���
            return ret;
        else                // src1, src2 �� �� ����
            return ret * (-1);
    }
}