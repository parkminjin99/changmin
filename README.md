
========================== �ְ�â�� library ==========================
 
   Created by �ְ�â�� on 2020/12/6.
   Copyright 2020 �ְ�â��. All rights reserved.
 
=====================================================================

 �� ���̺귯���� C ����� bignum ������ ������ ���̺귯���̴�. �̶� bignum�̶� 8/32/64bit ������ �̷���� word�� ���� �ش� 1word�δ� ǥ���� �Ұ����� ū ���� �ǹ��Ѵ�. ��, ������ C�� �Լ��δ� �ذ��� �� ������ ū ������ ���� ������ �����ϰ� �Ѵ�. ���� �� ���̺귯���� Window/Linux/Mac OS�� �����Ѵ�.

���߿��� ���δ��б� �������Ⱦ�ȣ���а� �ڹ���, ��â���� �����Ͽ���.

���̺귯���� ���۽� ����ڴ� ������ �׸��� changmin_library.h ���Ͽ��� ���� �����ϴ�.
- 1word�� bit���� (WORD_BITLEN)
    8/32/64�� ���� (default WORD_BITLEN = 64)
- ��ü word�� ���� (Wordlen)
    (defalut Wordlen = 16)
- karatsuba �̿�� flag�� word����(KARA_FLAG)
    (defalut KARA_FLAG = 8, �����ϴ� KARA_FLAG�� 6-10)
- TEST, �ð����� �̿�� �ݺ�Ƚ�� (MAX_COUNT)
    (defalut MAX_COUNT = 1000)

FLINT�� ����Ͽ� ������ �� ������ �ɼ����� -I /usr/local/include/flint/ -lflint -lmpfr -lgmp -lpthread�� �߰��ؾ� �Ѵ�. 
�ӵ� ���� �� �������� ������ ����.
gcc -Wall -O2 *.c -I /usr/local/include/flint/ -lflint -lmpfr -lgmp -lpthread

�� ���̺귯������ �����ϴ� ���� 
 - �� ���� ũ��� 
 - left_shift, right_shift
 - ��ⷯ 2^n
 - ����
 - ����
 - ����
 - ����
 - ������
 - ������ ��ⷯ
