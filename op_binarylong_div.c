//  
//  op_binarylong_div.c
//  Changmin's library
//  
//  Created by �ְ�â�� on 2020/12/06.
//  Copyright 2020 �ְ�â��. All rights reserved.
//  
#include "operation.h"
/*************************** binarylongdivision *****************************************
 bigint src1, src2�� �Է¹޾� binary long division�� �����Ͽ� Q,R�� ����ϴ� �Լ��̴�. 
 �������� src2�� 0 �����̸� �������� �����Ҽ������Ƿ� �Լ��� �������� �ʰ�, invalid�� �����Ѵ�.
 src2�� 0���� ū ����� ��� binary long division�� �̿��Ͽ� src1/src2�� �����ϰ� ���� Q, �������� R�� �����Ѵ�. 
 �̷��� ������ �� ����Ȱ�� valid�� �����Ѵ�.
 (���� �ڵ�) BinaryLongDiv(&Q, &R, src1, src2);
 *****************************************************************************************
 Input: A, B (A��B>0)
 Output: (Q,R) such that A=BQ+R(0��R<B).
 --------------------------------------
1: (Q,R) �� (0,0)
2: for j=n-1 downto 0 do
3:      R �� 2R + aj
4:      if R �� B then
5:          (Q, R) �� (Q + 2j, R - B) 
6:      end if
7: end for
8: return (Q, R) 
***********************************************/
int BinaryLongDiv(bigint** Q, bigint** R, bigint* src1, bigint* src2)
{ 
    if(get_sign(src2) == NEGATIVE || bi_is_zero(src2) == TRUE)      // �Է¹��� src2�� 0 ���϶��
        return INVALID;                                             // �������� �Ұ����ϹǷ� invalid ����
    bigint* temp = NULL; 
    bi_set_zero(R);                                                 // �������� �켱 0����
    int i, n = get_wordlen(src1)*WORD_BITLEN;                       // ��Ʈ ������ ���� ����
    bi_new(Q,n,NON_NEGATIVE);
    for ( i = n-1; i >= 0; i--)                                     // ��ü ��Ʈ �������� ����
    {
        left_shift(*R,1);
        (*R)->a[0] |= get_jth_bit(src1,i);                          // R = 2*R + src1�� i��° ����
        if(bi_compare(*R,src2) != -1)                               // R >= src2
        {
            bi_new(&temp,(i/WORD_BITLEN)+1,NON_NEGATIVE);
            temp->a[get_wordlen(temp)-1] ^= (word)1<<(i%WORD_BITLEN); // temp = 1<<(i%WORD_BITLEN)
            ADD_zzy(Q,temp);                                            // Q += temp
            SUB_zzy(R,src2);                                            // R -= src2
            bi_delete(&temp);
        }
    }
    return VALID;                                                       // ���� ������ valid ����
}