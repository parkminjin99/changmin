//
//  array.c
//  Changmin's library
//
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
//

#include "array.h"

void array_init(word* a, int len) // �迭�� 0���� �ʱ�ȭ�ϴ� �Լ�
{
    memset(a, 0, sizeof(word) * len);
}

void array_copy(word* dst, const word* src, int len) // dst�迭�� src�迭�� �����ϴ� �Լ�
{
    memcpy(dst, src, len * sizeof(word));
}

void array_rand(word* dst, int wordlen) // �迭�� �����ϰ� ���� �Է��ϴ� �Լ�
{
    unsigned char* p = (unsigned char*)dst;
    int cnt = wordlen * sizeof(word);
    while (cnt > 0)
    {
        *p = rand() & 0xff;
        p++;
        cnt--;
    }
}