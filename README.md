git test12345
========================== 최강창민 library ===========================
 ddld
   Created by 최강창민 on 2020/12/6.
   Copyright 2020 최강창민. All rights reserved.
박밍굴곰마오
=====================================================================

 본 라이브러리는 C 기반의 bignum 연산이 가능한 라이브러리이다. 이때 bignum이란 8/32/64bit 단위로 이루어진 word에 대해 해당 1word로는 표현이 불가능한 큰 수를 의미한다. 즉, 기존의 C의 함수로는 해결할 수 없었던 큰 정수에 대한 연산을 가능하게 한다. 한편 본 라이브러리는 Window/Linux/Mac OS를 지원한다.

개발에는 국민대학교 정보보안암호수학과 박민진, 전창열이 참여하였다.

라이브러리를 동작시 사용자는 다음의 항목을 changmin_library.h 파일에서 설정 가능하다.
- 1word의 bit길이 (WORD_BITLEN)
    8/32/64중 선택 (default WORD_BITLEN = 64)
- 전체 word의 길이 (Wordlen)
    (defalut Wordlen = 16)
- karatsuba 이용시 flag의 word길이(KARA_FLAG)
    (defalut KARA_FLAG = 8, 권장하는 KARA_FLAG는 6-10)
- TEST, 시간측정 이용시 반복횟수 (MAX_COUNT)
    (defalut MAX_COUNT = 1000)

FLINT를 사용하여 컴파일 시 컴파일 옵션으로 -I /usr/local/include/flint/ -lflint -lmpfr -lgmp -lpthread을 추가해야 한다. 
속도 측정 시 컴파일은 다음과 같다.
gcc -Wall -O2 *.c -I /usr/local/include/flint/ -lflint -lmpfr -lgmp -lpthread

본 라이브러리에서 제공하는 연산 
 - 두 수의 크기비교 
 - left_shift, right_shift
 - 모듈러 2^n
 - 덧셈
 - 뺄셈
 - 곱셈
 - 제곱
 - 나눗셈
 - 지수승 모듈러
