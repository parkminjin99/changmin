# changmin
================ 최강창민 library ==========================
#  Assignment1
#
#  Created by 최강창민 on 2020/10/11.
#  Copyright © 2020 최강창민. All rights reserved.
#

===============issue ===================================

void bi show 와 void bi_set_by_string 함수에서 완성되지 않은 base 10에 대한 
내용은 add, mul 함수 구현과 함께 작성할 계획입니다.

==============  bigint.c =================================

void bi show (구조체, 진수표현)  
	구조체에 입력되어 있는 문자를 입력한 진수에 맞도록 화면에 출력하는 함수. 
	가능한 진수 : 2, 10, 16
	현재버전에서는 2, 16에 대한 출력까지 가능.

void bi_delete(저장되어있는 구조체주소) 
	구조체의 메모리를 해제하는 함수.
	필요한 경우 ZEROIZE를 define하여 메모리 해제 전 배열을 0으로 초기화한다.

void bi_new(저장할 구조체주소, 워드길이, 부호)
	입력받은 구조체에 부호, 워드길이를 입력하고, 숫자가 들어갈 배열을 0으로 초기화한다.
	과정에서 해당 구조체가 NULL이 아닐 경우에는 bi_delete로 구조체를 먼저 삭제한 후에 과정을 진행한다. 

void bi_refine(저장되어있는 구조체) 
	입력받은 구조체가 사용하지 않는 상위의 워드를 삭제하는 함수이다. 필요한만큼의 워드만을 남기고 나머지는 할당을 해제한다.
	ex > unsigned char 0x000001020304  ==> 0x01020304

void bi_zeroize(저장되어있는 구조체)
	입력받은 구조체를 0으로 초기화 하는 함수
	초기화이후 refine을 진행한다.

void bi_assign(dst 구조체 주소,  src 구조체)
	dst 구조체를 새로 생성하고, 	array_copy함수를 이용하여 src 구조체 전체를 dst구조체에 복사하는 함수이다. 

void bi_set_by_array(저장할 구조체주소, 입력할 수의 부호, 워드단위로 표현된 입력할 수, 해당문자의 word길이. )
	수의 저장을 위해 새로 구조체를 하나 생성하고, 해당 복사하여 넣는다.   
	구조체의 변수에 부호, 수, 워드길이를 각각 넣는다. 

void bi_set_by_string(저장할 구조체주소, 입력할 수의 부호, 문자로 표현된 입력할 수, 입력할 수의 진수)
	수의 저장을 위해 새로운 구조체를 생성한다.
	입력할 수가 문자 형태로 되어있고, 그것이 어떠한 진수로 표현되어 있는지를 나타낸다. 
	가능한 진수:2,10,16
	현재버전에서는 2,16 진수에 대한 문자열까지 구조체에 저장 가능하다. 

void bi_gen_rand(저장할 구조체주소, 숫자의 부호, 숫자열의 워드 길이)
	구조체를 원하는 부호와 워드길이만큼 임의로 생성하는 함수이다.
	구조체의 변수에 부호, 수, 워드길이를 각각 대입하고 길이에 맞게 refine을 진행한다.

int get_wordlen(저장되어있는 구조체) 
	저장되어있는 숫자가 몇개의 워드를 사용하고 있는지 나타낸다.

int get_bitlen(저장되어있는 구조체)  
	저장되어있는 숫자가 몇 비트를 사용하고 있는지 나타낸다.

int get_jth_bit(저장되어있는 구조체, 출력할 비트의 인덱스) 
	저장되어있는 숫자에서 아래부터 j번째의 비트를 출력한다.
	ex) 구조체에 저장되어있는수 0x12일때, 
	    j  1   2  3  4  5  6  7  8  
	출력  0  1  0  0  1  0  0  0 

int get_sign(저장되어있는 구조체)    
	가독성을 위해 구조체에 저장되어있는 부호를 출력한다.
	출력 : NON_NEGATIVE 0 -> 양수
	        NEGATIVE 1 -> 음수 

void flip_sign(저장되어있는 구조체)
	구조체에 저장되어있는 수의 부호를 반대로 바ㄹ꾸어 준다.

void bi_set_one(저장되어있는 구조체주소)   
	새로 구조체를 만들어 숫자 1을 저장 위한 함수. 입력한 구조체 주소에 저장된다.

void bi_set_zero(저장되어있는 구조체주소)   
	새로 구조체를 만들어 숫자 0을 저장 위한 함수 입력한 구조체 주소에 저장된다.


int bi_is_one(저장되어있는 구조체) 
	입력한 구조체가 1인지 확인하기 위한 함수.
	출력 : 입력한 구조체가 1이면 true를 1이아니라면 false를 출력한다.


int bi_is_zero(저장되어있는 구조체)       
	입력한 구조체가 0인지 확인하기 위한 함수.
	출력 : 입력한 구조체가 0이면 true를 0이아니라면 false를 출력한다.


int bi_compareABS(저장되어있는 구조체1, 저장되어있는 구조체2) 
	구조체 1, 구조체 2를 입력받고 둘 중 큰 값을 나타내주는 함수
	해당 함수는 부호는 고려하지 않는다.
	출력  
	구조체 1 > 구조체2  -> 1
	구조체 1 < 구조체2  -> -1
	구조체 1 = 구조체2  -> 0

int bi_compare(저장되어있는 구조체1, 저장되어있는 구조체2)
	구조체 1, 구조체 2를 입력받고 bi_compareABS함수를 이용하여 둘 중 큰 값을 나타내주는 함수
	해당 함수는 부호가 다른 경우까지 구분가능하다.
	출력  
	구조체 1 > 구조체2  -> 1
	구조체 1 < 구조체2  -> -1
	구조체 1 = 구조체2  -> 0

=================== array.c =========================================

void array_init(워드배열, 워드개수)
	입력받은 워드들을 워드갯수만큼 0으로 초기화하는 함수

void array_copy(워드배열, 워드배열, 워드개수)
	src 배열을 dst 배열에 복사하는 함수. 이때 복사하고자 하는 배열의 개수를 입력받아 해당 개수만큼 복사한다.

void array_rand(워드배열, 워드개수)
	bi_gen_rand에서 사용하는 함수로, 8비트씩 랜덤 숫자열을 출력하면서 입력받은 워드개수만큼 만든다. 


=================== operator.c =========================================

void left_shift(사용할 구조체, shift할 비트수) 
	구조체에 저장되어있는 숫자를 왼쪽으로 지정한 비트수 만큼 shift하는 함수.

void right_shift(사용할 구조체, shift할 비트수) 
	구조체에 저장되어있는 숫자를 오른쪽으로 지정한 비트수 만큼 shift하는 함수.
	과정후 refine을 통해 필요한 만큼의 word만을 남긴다. 

void reduction_2_r(사용할 구조체, modular할 비트수) 
	구조체에 저장되어있는 숫자를 하위 지정한 비트수 만큼 남기는 함수. (mod 2^(지정 비트수))
	과정후 refine을 통해 필요한 만큼의 word만을 남긴다. 

====================== main.c ===========================================

위에서 만든 함수들을 이용하여 예제를 만들어주는 파일.


