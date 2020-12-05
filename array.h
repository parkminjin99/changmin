#pragma once
//
//  array.h
//  Changmin's library
//
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//
 
#ifndef array_h
#define array_h

#include <string.h>
#include "changmin_library.h"

void array_init(word* a, int len);                    // 배열을 0으로 초기화하는 함수
void array_copy(word* dst, const word* src, int len); // dst배열에 src배열을 복사하는 함수
void array_rand(word* dst, int wordlen);              // 배열에 랜덤하게 값을 입력하는 함수

#endif /* array_h */