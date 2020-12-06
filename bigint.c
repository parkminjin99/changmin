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

/********************************
bi_sage_show
구조체에 저장되어있는 bigint를 원하는 진수(2,10,16)로 출력하는 함수.
구조체와, 출력을 원하는 진수를 입력받는다. 
단 구조체의 값이 올바르게 나오는지 sage프로그램을 이용했기 때문에,
sage의 형식에 맞도록 출력되는 형식을 설정한다.
*********************************/
void bi_sage_show(const bigint* x, const int base)
{
    int i, j;
    if (get_sign(x) == NEGATIVE)
        printf("-");               // 음수인경우 앞에 - 붙이기
    if (base == 16)                //16진수인 경우
    {
        int enter=0;
        printf("0x");              //숫자가 출력되기전 0x를 출력하게 해서 sage가 16진수임을 알도록설정
        if(bi_is_zero(x) == TRUE)
            printf("0");           // 0이면 0출력
        else                       // 0이아니면 해당 구조체에 저장된 값 출력
        { 
            for (i = get_wordlen(x) - 1; i >= 0; i--)
            {
                for (j = WORD_BITLEN - 4; j >= 0; j = j - 4)
                {
                    printf("%x", (int)(((x->a[i]) >> j) & 0xf));
                    enter=enter+1;
                    if(enter%119==117)
                        printf("\n       ");
                        
                }
            }
        }
    }
    else if (base == 2)             //2진수인경우
    {
        printf("0b");               //숫자가 출력되기전 0b를 출력하게 해서 sage가 16진수임을 알도록설정
        if(bi_is_zero(x) == TRUE)   
            printf("0");            // 0이면 0출력
        else                        // 0아니면 해당 구조체에 저장된 값 출력
        {
            for (int i = get_wordlen(x) - 1; i >= 0; i--)
                for (int j = WORD_BITLEN - 1; j >= 0; j--)
                    printf("%x", (int)(((x->a[i]) >> j) & 0x1));
        }
    }
    else                            // 10진수인 경우
    {
        if (bi_is_zero(x) == TRUE)
            printf("0");            // 0이면 0출력
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
            while (1)
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
구조체에 저장되어있는 bigint를 원하는 진수(2,10,16)로 출력하는 함수.
구조체와, 출력을 원하는 진수를 입력받는다. 
*********************************/

void bi_show(const bigint* x, const int base)
{
    int i, j;
    if(bi_is_zero(x) == TRUE)         //입력된 값이 0이라면 0을 출력하고 종료
    {
        printf("0\n");
        return;
    }
    if (get_sign(x) == NEGATIVE)       //입력된 값이 음수이면 - 표시
        printf("-");
    if (base == 16)                    //16진수인 경우
    {
        for (i = get_wordlen(x) - 1; i >= 0; i--)
            for (j = WORD_BITLEN - 4; j >= 0; j = j - 4)
                printf("%x", (int)(((x->a[i]) >> j) & 0xf));
    }
    else if (base == 2)                 // 2진수인 경우
    {
        for (int i = get_wordlen(x) - 1; i >= 0; i--)
            for (int j = WORD_BITLEN - 1; j >= 0; j--)
                printf("%x", (int)(((x->a[i]) >> j) & 0x1));
    }
    else                                // 10진수인 경우
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
        while (1)
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

/***********************
 bi_delete
 bigint 구조체의 주소를 입력받아 구조체의 메모리를 해제하는 함수이다. 
 changmin_library.h에서 ZEROIZE를 define하면 
 구조체의 a를 지우는 과정에서 해당 배열을 0으로 초기화한 후에 메모리를 해제한다. 
***********************/
void bi_delete(bigint** x) // bigint 구조체의 메모리를 해제하는 함수
{
    if (*x == NULL)     // 메모리가 해제될 필요가 없는 경우
        return;
#ifdef ZEROIZE          // 필요하다면 #define ZEROIZE를 해주어 구조체 안 배열 메모리를 초기화한후 메모리 해제
    array_init((*x)->a, (*x)->wordlen);
#endif
    free((*x)->a);  // 구조체 안 배열 메모리 해제
    free(*x);       // 구조체 메모리 해제
    *x = NULL;
}

/***********************
 bi_new
 bigint 구조체의 주소, 구조체의 부호, 구조체의 워드길이를 입력받아 
 원하는 크기와 부호를 가진 구조체의 메모리를 동적할당하는 함수이다. 
 함수에 입력된 구조체의 주소가 NULL이 아니고 어떠한 값이 입력되어있는 경우에는
 bi_delete함수를 이용해서 메모리를 해제한후에 다시 생성해준다. 
***********************/
int bi_new(bigint** x, int wordlen, int sign) // bigint 구조체 메모리 동적할당 함수
{
    if (*x != NULL) // 메모리가 NULL이 아니면 메모리 해제
        bi_delete(x);
    *x = (bigint*)malloc(sizeof(bigint)); // bigint 구조체 메모리 동적할당
    if (*x == NULL) // 메모리 할당되지 않으면 FAIL 리턴
        return FAIL;
    (*x)->sign = sign;
    (*x)->wordlen = wordlen;
    (*x)->a = (word*)calloc(wordlen, sizeof(word)); // bigint 구조체 안 배열 메모리 동적할당
    return SUCCESS;
}

/*********************
 bi_refine
 구조체를 입력받아 해당 구조체에서 원래의 필요한 수 앞에 붙어있는 0으로 된 배열을 삭제하는 함수이다.
 연산을 진행하는 과정에서 자리수가 낮아지며 불필요하게 0으로 남게되는 앞쪽 배열이 존재하게 된다. 
 이러한 부분의 배열을 제거하므로 메모리를 관리하는 함수이다.
 ***********************/
int bi_refine(bigint* x) // bigint 구조체 안의 배열에서 0인 하위 배열을 삭제하는 함수
{
    if (x == NULL)
        return SUCCESS;
    int new_wordlen = get_wordlen(x);
    while (new_wordlen > 1)
    {
        if (x->a[new_wordlen - 1] != 0) // 0이 아닌 배열인 경우 break
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
    if ((get_wordlen(x) == 0) && (x->a[0] == 0x0)) // bigint가 0인 경우 sign값을 NON_NEGATIVE로 설정
        x->sign = NON_NEGATIVE;
    return SUCCESS;
}

/************************
 bi_zeroize
 입력받은 배열을 0으로 초기화하는 함수이다. 
 과정에서 우선 모든 배열을 0으로 초기화한 후에 
 bi_refine을 통해 불필요한 배열을 제거하면서, 길이가 1이면서 0을 담은 구조체를 만든다.
 ************************/
void bi_zeroize(bigint* x) // bigint 안의 배열을 0으로 초기화 하는 함수
{
    array_init(x->a, get_wordlen(x));  //배열을 0으로 초기화
    bi_refine(x);                       // 불필요한 배열 삭제
}

/************************
 bi_assign
 입력받은 구조체src를 구조체dst에 복사하는 함수이다.
 과정에서 dst는 주소로 입력받게 된다.
 ************************/
void bi_assign(bigint** dst, const bigint* src) // bigint 구조체를 복사하는 함수
{
    int srcLen = get_wordlen(src);
    if (FAIL == bi_new(dst, srcLen, get_sign(src)))
        return;
    array_copy((*dst)->a, src->a, srcLen);
}

/************************
 bi_set_by_array
 원하는 구조체의 정보(부호, 길이, 배열)를 설정하여 해당함수에 입력하면
 입력한 정보를 이용해서 구조체 x를 만들어 주는 함수이다.
 과정에서 구조체x는 주소로 입력받는다. 
 **************************/
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen)  // a와 sign 정보를 struct에 저장.
{
    if (FAIL == bi_new(x, wordlen, sign))
        return;
    array_copy((*x)->a, a, wordlen);
}

/************************
 bi_set_by_string
 문자열을 입력하면 해당 문자열을 이용해서 구조체를 만들어주는 함수이다.
 문자열, 해당 문자열이 어떠한 진수로 작성되었는지, 해당문자열의 부호를 입력한다.
 이를 이용해서 입력받은 구조체의 주소에 새로운 구조체를 만들어준다.
 ***********************/
void bi_set_by_string(bigint** x, int sign, char* str, word base) // 입력된 문자열을 구조체에 올바른 진수로 저장
{
    int stln = (int)strlen(str);
    if (base == 2)                  // 입력 문자가 2진수인 경우
    {
        if (FAIL == bi_new(x, (stln / (WORD_BITLEN + 1)) + 1, sign))
            return;
        for (int i = stln - 1; i >= 0; i--)   
            (*x)->a[(stln - 1 - i) / WORD_BITLEN] ^= ((str[i] - '0') << ((stln - 1 - i) % WORD_BITLEN));
    }
    else if (base == 16)            // 입력 문자가 16진수인 경우
    {
        int len = (stln*4) / WORD_BITLEN;
        if((stln*4)%WORD_BITLEN != 0)
            len++;
        if (FAIL == bi_new(x, len, sign))
            return;
        printf("x->wordlen = %d\n", (*x)->wordlen);
        int tmp[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
        for (int i = stln - 1; i >= 0; i--)   
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
    else                            // 입력문자가 10진수인 경우
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

/********************
 bi_gen_rand
 원하는 부호와, 최대 워드 길이를 입력하면 그에 맞게
 임의로 배열을 만들어서 구조체를 생성해주는 함수이다. 
 ***********************/
void bi_gen_rand(bigint** x, int sign, int wordlen)   // 구조체를 랜덤하게 생성하는 함수
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
저장되어있는 bigint의 word길이를 출력하는 함수
출력은 int형이며 가독성을 위함.
**********************/
int get_wordlen(const bigint* x) 
{
    return x->wordlen;             
}

/**********************
get_bitlen
저장되어있는 bigint의 bit길이를 출력하는 함수
출력은 int형이며 가독성을 위함.
**********************/
int get_bitlen(const bigint* x)            
{
    word last = x->a[get_wordlen(x) - 1];
    for (int i = WORD_BITLEN - 1; i > 0; i--)
    {
        if (((last >> i) | 0x0) == 1)
            return (i + WORD_BITLEN* (get_wordlen(x)-1));
    }
    return FAIL;
}

/**********************
get_jth_bit
저장되어있는 bigint의 j번째 bit를 출력해주는 함수.
여기서 j번째는 하위비트를 1번째로 보고 계산.
출력은 int형으로 진행.
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
저장되어있는 bigint의 부호를 출력해주는 함수.
가독성을 위한 함수로 출력은 int형으로 진행. 
NEGATIVE인경우 1, NON_NEGATIVE인 경우 0 리턴.
**********************/
int get_sign(const bigint* x)     
{
    return x->sign;
}

/**********************
flip_sign
저장되어있는 bigint의 부호를 바꾸어주는 함수.
NEGATIVE인경우 1, NON_NEGATIVE인 경우 0 으로 저장되기 때문에 
XOR 1을 통해 부호를 변경하는 것이 가능하다.
**********************/
void flip_sign(bigint* x)    
{
    x->sign = 0x1 ^ (x->sign);
}

/**********************
bi_set_minus_one
입력받은 주소에 해당하는 bigint을 음수 1로 설정하는 함수.
-1을 사용에 편의를 위함.
입력을 bigint의 주소로 받음.
word길이를 1, 부호는 NON_NEGATIVE, 저장된 값은 1로 설정
**********************/
void bi_set_minus_one(bigint** x)     
{
    if (FAIL == bi_new(x, 1, NEGATIVE))
        return;
    (*x)->a[0] = 0x1;
}

/**********************
bi_set_one
입력받은 주소에 해당하는 bigint을 양수 1로 설정하는 함수.
지수승 연산등에서 1을 사용하기에 편의를 위함.
입력을 bigint의 주소로 받음.
word길이를 1, 부호는 NON_NEGATIVE, 저장된 값은 1로 설정
**********************/
void bi_set_one(bigint** x)     
{
    if (FAIL == bi_new(x, 1, NON_NEGATIVE))
        return;
    (*x)->a[0] = 0x1;
}

/**********************
bi_set_zero
입력받은 주소에 해당하는 bigint을 양수 0으로 설정하는 함수. (0은 편의상 양수로 설정.)
FOR문 등에서 0이 필요한 경우가 있기에 편의를 위함.
입력을 bigint의 주소로 받음.
word길이를 1, 부호는 NON_NEGATIVE, 저장된 값은 0로 설정
**********************/
void bi_set_zero(bigint** x)   
{
    if (FAIL == bi_new(x, 1, NON_NEGATIVE))
        return;
    (*x)->a[0] = 0x0;
}

/**********************
bi_is_minus_one
입력받은 bigint이 -1인지 확인하는 함수
        필요한 경우가 있기에 편의를 위함.
입력을 bigint을 받아서 숫자를 저장하는 x->a이 1이고 부호가 NEGATIVE인지 확인한다.
맞으면 TRUE, 틀리면 FALSE를 리턴
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
입력받은 bigint이 1인지 확인하는 함수
        필요한 경우가 있기에 편의를 위함.
입력을 bigint을 받아서 숫자를 저장하는 x->a이 1이고 부호가 NON_NEGATIVE인지 확인한다.
맞으면 TRUE, 틀리면 FALSE를 리턴
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
입력받은 bigint이 0인지 확인하는 함수
        필요한 경우가 있기에 편의를 위함.
입력을 bigint을 받아서 숫자를 저장하는 x->a이 0이고 부호가 NON_NEGATIVE인지 확인한다.
맞으면 TRUE, 틀리면 FALSE를 리턴
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


/****************
 bi_compareABS
 두개의 bigint를 입력받아 절댓값을 비교해서
 둘중 어느것이 큰 값인지를 판단하는 함수이다. 
 src1, src2 순서로 입력 받았을때, 절댓값 기준으로
 src1 > src2 인 경우  1
 src1 < src2 인 경우 -1
 src1 = src2 인 경우  0 을 출력한다. 
 *****************/
int bi_compareABS(const bigint* src1, const bigint* src2) // 두 bigint의 절댓값을 비교하는 함수
{
    if (get_wordlen(src1) > get_wordlen(src2))   // src1 > src2
        return 1;                                                              
    else if (get_wordlen(src1) < get_wordlen(src2)) // src1 < src2
        return -1;                                                                
    else                    // get_wordlen(src1) = get_wordlen(src2)
    {
        int j;
        for (j = get_wordlen(src1) - 1; j >= 0; j--)
        {
            if (src1->a[j] > src2->a[j])        // src1 > src2
                return 1;
            else if (src1->a[j] < src2->a[j])   // src1 < src2
                return -1;
        }
    }
    return 0;                                   // src1 = src2
}

/****************
 bi_compare
 두개의 bigint를 입력받아 부호까지 비교해서
 둘중 어느것이 큰 값인지를 판단하는 함수이다. 
 src1, src2 순서로 입력 받았을때, 
 src1 > src2 인 경우  1
 src1 < src2 인 경우 -1
 src1 = src2 인 경우  0 을 출력한다. 
 *****************/
int bi_compare(const bigint* src1, const bigint* src2) // 두 bigint를 비교하는 함수
{
    /*
        A > B : 1
        A < B : -1
        A = B : 0
    */
    if (src1->sign == NEGATIVE && src2->sign == NON_NEGATIVE) // src1은 음수, src2는 0이상
        return -1;
    else if (src1->sign == NON_NEGATIVE && src2->sign == NEGATIVE) // src1은 0이상 , src2는 음수
        return 1;
    else
    {
        int ret = bi_compareABS(src1, src2); // src1, src2의 절댓값 크기 비교
        if (src1->sign == NON_NEGATIVE) // src1, src2 모두 0이상
            return ret;
        else                // src1, src2 둘다 음수
            return ret * (-1);
    }
}