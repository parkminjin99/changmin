//
//  bigint.c
//  Changmin's library
//
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
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
        if(bi_is_one(x) == TRUE)
            printf("0");
        else
        {
            for (i = get_wordlen(x) - 1; i >= 0; i--)
                for (j = WORD_BITLEN - 4; j >= 0; j = j - 4)
                    printf("%x", ((x->a[i]) >> j) & 0xf);
        }
    }
    else if (base == 2)
    {
        printf("0b");
        if(bi_is_one(x) == TRUE)
            printf("0");
        else
        {
            for (int i = get_wordlen(x) - 1; i >= 0; i--)
                for (int j = WORD_BITLEN - 1; j >= 0; j--)
                    printf("%x", ((x->a[i]) >> j) & 0x1);
        }
    }
    else // base = 10
    {

    }
    printf(")\n");
}

void bi_show(const bigint* x, const int base)
{
    int i, j;
    if(bi_is_one(x) == TRUE)
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
                printf("%x", ((x->a[i]) >> j) & 0xf);
    }
    else if (base == 2)
    {
        for (int i = get_wordlen(x) - 1; i >= 0; i--)
            for (int j = WORD_BITLEN - 1; j >= 0; j--)
                printf("%x", ((x->a[i]) >> j) & 0x1);
    }
    else // base = 10
    {

    }
    printf("\n");
}

void bi_delete(bigint** x) // bigint 구조체의 메모리를 해제하는 함수
{
    if (*x == NULL) // 메모리가 해제될 필요가 없는 경우
        return;
#ifdef ZEROIZE // 필요한 경우 #define ZEROIZE를 해주어 구조체 안 배열 메모리를 초기화 한 후 메모리 해제
    array_init((*x)->a, (*x)->wordlen);
#endif
    free((*x)->a);  // 구조체 안 배열 메모리 해제
    free(*x);       // 구조체 메모리 해제
    *x = NULL;
}

int bi_new(bigint** x, int wordlen, int sign) // bigint 구조체 메모리 동적할당 함수
{
    if (*x != NULL) // 메모리가 NULL이 아니면 메모리 해제
        bi_delete(x);
    *x = (bigint*)malloc(sizeof(bigint)); // bigint 구조체 메모리 동적할당
    if (*x == NULL) // 메모리가 할당되지 않으면 FAIL 리턴
        return FAIL;
    (*x)->sign = sign;
    (*x)->wordlen = wordlen;
    (*x)->a = (word*)calloc(wordlen, sizeof(word)); // bigint 구조체 안 배열 메모리 동적할당
    return SUCCESS;
}


int bi_refine(bigint* x) // bigint 구조체 안의 배열에서 0인 하위의 배열을 삭제하는 함수
{
    if (x == NULL)
        return SUCCESS;
    int new_wordlen = get_wordlen(x);
    while (new_wordlen > 1)
    {
        if (x->a[new_wordlen - 1] != 0) // 0이 아닌 배열을 만나면 break
            break;
        new_wordlen--;
    }
    if (get_wordlen(x) != new_wordlen) // 메모리 재할당
    {
        x->wordlen = new_wordlen;
        x->a = (word*)realloc(x->a, sizeof(word) * new_wordlen);
        if (x->a == NULL)
            return FAIL;
    }
    if ((get_wordlen(x) == 1) && (x->a[0] == 0x0)) // bigint가 0인 경우에 sign값을 NON_NEGATIVE로 설정
        x->sign = NON_NEGATIVE;
    return SUCCESS;
}

void bi_zeroize(bigint* x) // bigint 안의 배열을 0으로 초기화하는 함수
{
    array_init(x->a, get_wordlen(x));
    bi_refine(x);
}

void bi_assign(bigint** dst, const bigint* src) // bigint 구조체를 복사하는 함수
{
    if (FAIL == bi_new(dst, get_wordlen(src), get_sign(src)))
        return;
    array_copy((*dst)->a, src->a, get_wordlen(src));
}

void bi_set_by_array(bigint** x, int sign, word* a, int wordlen)  // a와 sign 정보를 struct에 저장하기.
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
        {
            (*x)->a[(stln - 1 - i) / WORD_BITLEN] ^= ((str[i] - '0') << ((stln - 1 - i) % WORD_BITLEN));
        }
    }
    else if (base == 16)
    {
        if (FAIL == bi_new(x, ((stln * 4) / (WORD_BITLEN + 1)) + 1, sign))
            return;
        int tmp[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
        for (int i = stln - 1; i >= 0; i--)   //  11110001       10001111 0001 1111
        {
            int j = 0;
            for (j = 0; j < 16; j++)
            {
                if (str[i] == tmp[j])
                    break;
            }
            (*x)->a[4 * (stln - 1 - i) / WORD_BITLEN] ^= ((j) << (4 * (stln - 1 - i) % WORD_BITLEN));
        }
    }
    else // base = 10
    {
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

int get_wordlen(const bigint* x)  // refine 해주고 해준 길이를 리턴
{
    return x->wordlen;
}

int get_bitlen(const bigint* x)            // 마지막 워드의 비트만 비교..
{
    word last = x->a[get_wordlen(x) - 1];
    for (int i = WORD_BITLEN - 1; i > 0; i--)
    {
        if (((last >> i) | 0x0) == 1)
            return i;
    }
    return FAIL;
}

int get_jth_bit(const bigint* x, const int j)  //아래에서 j번째
{
    int jword, jbit;
    jword = j / WORD_BITLEN;
    jbit = j % WORD_BITLEN;
    return ((x->a[jword]) >> jbit) ^ 0x1;
}

int get_sign(const bigint* x)     // 가독성
{
    return x->sign;
}

void flip_sign(bigint* x)    // 1^1 =0, 0^1 =1   근데 포인터인지 이중포인터인지?
{
    x->sign = 0x1 ^ (x->sign);
}

void bi_set_one(bigint** x)     //있던거
{
    if (FAIL == bi_new(x, 1, NON_NEGATIVE))
        return;
    (*x)->a[0] = 0x1;
}

void bi_set_zero(bigint** x)   //있던거
{
    if (FAIL == bi_new(x, 1, NON_NEGATIVE))
        return;
    (*x)->a[0] = 0x0;
}

int bi_is_minus_one(const bigint* x)
{
    if ((get_sign(x) != NEGATIVE) || (x->a[0] != 0x0))
        return FALSE;
    for (int j = get_wordlen(x) - 1; j > 0; j--)
        if (x->a[j] != 0)
            return FALSE;
    return TRUE;
}

int bi_is_one(const bigint* x)     //1인지 확인
{
    if ((get_sign(x) == 1) || (x->a[0] != 0x0))
        return FALSE;
    for (int j = get_wordlen(x) - 1; j > 0; j--)
        if (x->a[j] != 0)
            return FALSE;
    return TRUE;
}


int bi_is_zero(const bigint* x)       //0인지 확인
{
    if ((get_sign(x) == 1) || (x->a[0] != 0x1))
        return FALSE;
    for (int j = get_wordlen(x) - 1; j > 0; j--)
    {
        if (x->a[j] != 0)
            return FALSE;
    }
    return TRUE;
}

int bi_compareABS(const bigint* src1, const bigint* src2) // 두 bigint의 절댓값을 비교하는 함수
{
    if (get_wordlen(src1) > get_wordlen(src2))   // src1 > src2
        return 1;
    else if (get_wordlen(src1) < get_wordlen(src2)) // src1 < src2
        return -1;
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

int bi_compare(const bigint* src1, const bigint* src2) // 두 bigint를 비교하는 함수
{
    /*
        A > B : 1
        A < B : -1
        A = B : 0
    */
    if (src1->sign == NEGATIVE && src2->sign == NON_NEGATIVE) // src1은 음수, src2은 양수 또는 0
        return 1;
    else if (src1->sign == NON_NEGATIVE && src2->sign == NEGATIVE) // src1은 양수 또는 0, src2은 음수
        return 0;
    else
    {
        int ret = bi_compareABS(src1, src2); // src1, src2의 절댓값의 크기를 비교
        if (src1->sign == NON_NEGATIVE) // src1, src2 둘 다 양수
            return ret;
        else                // src1, src2 둘 다 음수
            return ret ^ 1;
    }
}