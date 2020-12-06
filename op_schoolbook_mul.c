//  
//  op_schoolbook_mul.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/12/06.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"
/******************* Schoolbook MUL *******************
 schoolbook방식으로 구현한 곱셈연산이다.
 사용자는 MUL함수만을 사용하여 schoolbook방식의 곱셈 사용이 가능하다.
 (예제 코드) MUL(&dst, src1, src2);
******************************************************/

/****************** MUL_1word_zxy(A,B) : 1워드의 곱셈  **************************
Input: A, B ∈ [0,W)
Output: C = A*B ∈ [0,W^2)
---------------------------------------------------------------------------
1: A1,A0 ← A>>(w/2), A mod 2^(w/2)      |   7: T ← C0
2: B1,B0 ← B>>(w/2), B mod 2^(w/2)      |   8: C0 ← (C0 + (T0<<(w/2)) mod 2^w
3: T1,T0 ← A1*B0, A0*B1                 |   9: C1 ← C1 + (T1<<(w/2)) + (T0>>(w/2)) + (C0 < T)
4: T0 ← (T1 + T0) mod 2^w               |   10: C ← (C1<<w) + C0
5: T1 ← T0 < T1                         |   11: return C
6: C1,C0 ← A1*B1, A0*B0
****************************************************************************/
void MUL_1word_zxy(word* dst, const word* src1, const word* src2)
{
    word A[2], B[2], temp[2], t;
    A[1] = (*src1)>>(WORD_BITLEN/2);        // A1 = src1 >> w/2
    A[0] = (*src1)&HALF_BITMASK;            // A0 = src1 & 2^(w/2)
    B[1] = (*src2)>>(WORD_BITLEN/2);        // B1 = src2 >> w/2
    B[0] = (*src2)&HALF_BITMASK;            // B0 = src2 & 2^(w/2)

    temp[1] = A[1]*B[0];
    temp[0] = (A[0]*B[1])+(temp[1]);        // temp0 = A1*B0 + A0*B1
    if(temp[0] < temp[1])   temp[1] = 1;    // carry발생 시 temp1 = 1
    else temp[1] = 0;

    dst[1] = A[1]*B[1];                     // dst1 = A1*B1
    dst[0] = A[0]*B[0];                     // dst0 = A0*B0
    t = dst[0];

    dst[0] += temp[0]<<(WORD_BITLEN/2);     // dst0 = A0*B0 + temp0<<w/2
    dst[1] += (temp[1]<<(WORD_BITLEN/2)) + (temp[0]>>(WORD_BITLEN/2)); // dst1 = temp1<<w/2 + temp0>>w/2
    if(dst[0] < t)  dst[1]++;               // carry발생
} 

/****************** schoolbook_MULC(C,A,B) : 부호가 동일한 두 정수의 곱셈  **************************
Input: A, B ∈ [0,W)
Output: C = A*B ∈ [0,W^2)
---------------------------------------------------------------------------
1: C ← 0    
2: for j = 0 to n-1 do
3:      for i = 0 to m-1 do
4:          T ← Aj*Bi
5:          T ← T << w(i+j)
6:          C ← ADDC(C,T)
7:      end for
8: end for
9: return C
****************************************************************************/
void schoolbook_MULC(bigint** dst, const bigint* src1, const bigint* src2) // schoolbook multiplication 
{
    word temp[2];
    int n = get_wordlen(src1), m = get_wordlen(src2), i, j;
    bi_new(dst, n+m, NON_NEGATIVE);                         // src1*src2은 n+m만큼의 wordlen이 필요함 
    bigint* temp_bigint = NULL;
    bi_new(&temp_bigint, n+m, NON_NEGATIVE);
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < m; j++)
        {
            MUL_1word_zxy(temp, &src1->a[i], &src2->a[j]); // temp = src1->a[i] * src2->a[j]
            temp_bigint->a[i+j] = temp[0];                  // temp_bigint = temp << (i+j)*w
            temp_bigint->a[i+j+1] = temp[1];
            ADD_zzy(dst,temp_bigint);                       // dst += temp_bigint
            temp_bigint->a[i+j] = 0;                        // temp_bigint 초기화 
            temp_bigint->a[i+j+1] = 0;
        }
    }
    bi_delete(&temp_bigint);
}

/*************** MUL_zxy(C, A, B) : 임의의 두 정수 A,B의 곱 *******************
Input: A, B ∈ Z
Output: C = AB
1: if A = 0 or B = 0 then     |   10: if B = 1 then 
2:      return 0              |   11:     return A
3: end if                     |   12: end if
4: if A = 1 then              |   13: if B = -1 then
5:      return B              |   14:     return -A
6: end if                     |   15: end if
7: if A = -1 then             |   16: C ← MULC(|A|,|B|)
8:      return -B             |   17: return (-1)^(sign(A)+sign(B))*C
9: end if                      
**************************************************************************/
void MUL_zxy(bigint** dst, const bigint* src1, const bigint* src2) 
{
    if(bi_is_zero(src1) == TRUE || bi_is_zero(src2) == TRUE) // src1 = 0 or src2 = 0
        bi_set_zero(dst);
    else if (bi_is_one(src1) == TRUE)       // src1 = 1
        bi_assign(dst, src2);       
    else if(bi_is_minus_one(src1) == TRUE)  // src1 = -1
    {
        bi_assign(dst, src2);
        flip_sign(*dst);
    }
    else if(bi_is_one(src2) == TRUE)        // src2 = 1
        bi_assign(dst,src1);
    else if(bi_is_minus_one(src2) == TRUE)  // src2 = -1
    {
        bi_assign(dst, src1);
        flip_sign(*dst);
    }
    else
    {
        schoolbook_MULC(dst,src1,src2);     // dst = |src1|*|src2|
        (*dst)->sign = get_sign(src1)^get_sign(src2); // dst의 부호 결정 
        // src1의 부호 1 0 1 0 
        // src2의 부호 1 0 0 1
        // dst의 부호  0 0 1 1 -> 양 양 음 음 
    }
}
void MUL_zzy(bigint** dst, const bigint* src) 
{
    bigint* temp = NULL;
    bi_assign(&temp, *dst);
    MUL_zxy(dst, temp, src);
    bi_delete(&temp);
}