#pragma once
//
//  array.h
//  Changmin's library
//
//  Created by �ְ�â�� on 2020/11/09.
//  Copyright 2020 �ְ�â��. All rights reserved.
//
 
#ifndef array_h
#define array_h

#include <string.h>
#include "changmin_library.h"

void array_init(word* a, int len);                    // �迭�� 0���� �ʱ�ȭ�ϴ� �Լ�
void array_copy(word* dst, const word* src, int len); // dst�迭�� src�迭�� �����ϴ� �Լ�
void array_rand(word* dst, int wordlen);              // �迭�� �����ϰ� ���� �Է��ϴ� �Լ�

#endif /* array_h */