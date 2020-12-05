//
//  changmin_library.h
//  Changmin's library
//
//  Created by 최강창민 on 2020/11/09.
//  Copyright 2020 최강창민. All rights reserved.
//

#ifndef changmin_library_h
#define changmin_library_h

#define MAX_COUNT 40          // 각 연산을 몇회 확인할지 

#define KARA_FLAG 6

#define WORD_BITLEN 8
#if WORD_BITLEN == 64
typedef unsigned long long word;
#define HALF_WORDBIT 0x00000000ffffffff
#define BITMASK 0xffffffffffffffff
#elif WORD_BITLEN == 32
typedef unsigned int word;
#define HALF_WORDBIT 0x0000ffff
#define BITMASK 0xffffffff
#else // WORD_BITLEN == 8
typedef unsigned char word;
#define HALF_WORDBIT 0x0f
#define BITMASK 0xff
#endif

typedef struct {
    int sign;
    int wordlen;
    word* a;
} bigint;

#include "bigint.h"
#include "array.h"
#include "operation.h"
#include "test.h"
#include "benchmark.h"

#endif /* changmin_library_h */