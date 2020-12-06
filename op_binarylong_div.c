//  
//  op_binarylong_div.c
//  Changmin's library
//  
//  Created by 최강창민 on 2020/12/06.
//  Copyright 2020 최강창민. All rights reserved.
//  
#include "operation.h"
/*************************** binarylongdivision *****************************************
 bigint src1, src2를 입력받아 binary long division을 진행하여 Q,R을 계산하는 함수이다. 
 과정에서 src2가 0 이하이면 나눗셈을 진행할수없으므로 함수를 실행하지 않고, invalid를 리턴한다.
 src2가 0보다 큰 양수인 경우 binary long division을 이용하여 src1/src2를 진행하고 몫을 Q, 나머지를 R로 저장한다. 
 이러한 과정이 잘 진행된경우 valid를 리턴한다.
 (예제 코드) BinaryLongDiv(&Q, &R, src1, src2);
 *****************************************************************************************
 Input: A, B (A≥B>0)
 Output: (Q,R) such that A=BQ+R(0≤R<B).
 --------------------------------------
1: (Q,R) ← (0,0)
2: for j=n-1 downto 0 do
3:      R ← 2R + aj
4:      if R ≥ B then
5:          (Q, R) ← (Q + 2j, R - B) 
6:      end if
7: end for
8: return (Q, R) 
***********************************************/
int BinaryLongDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2)
{ 
    if(get_sign(src2) == NEGATIVE || bi_is_zero(src2) == TRUE)      // 입력받은 src2가 0 이하라면
        return INVALID;                                             // 나눗셈이 불가능하므로 invalid 리턴
    bigint* temp = NULL; 
    bi_set_zero(R);                                                 // 나머지를 우선 0으로
    int i, n = get_wordlen(src1)*WORD_BITLEN;                       // 비트 단위로 연산 진행
    bi_new(Q,n,NON_NEGATIVE);
    for ( i = n-1; i >= 0; i--)                                     // 전체 비트 역순으로 진행
    {
        left_shift(*R,1);
        (*R)->a[0] |= get_jth_bit(src1,i);                          // R = 2*R + src1의 i번째 원소
        if(bi_compare(*R,src2) != -1)                               // R >= src2
        {
            bi_new(&temp,(i/WORD_BITLEN)+1,NON_NEGATIVE);
            temp->a[get_wordlen(temp)-1] ^= (word)1<<(i%WORD_BITLEN); // temp = 1<<(i%WORD_BITLEN)
            ADD_zzy(Q,temp);                                            // Q += temp
            SUB_zzy(R,src2);                                            // R -= src2
            bi_delete(&temp);
        }
    }
    return VALID;                                                       // 연산 진행후 valid 리턴
}