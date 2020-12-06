#include <float.h>
#include "flint.h"
#include "fmpz.h"
#include "ulong_extras.h"
#include "time.h"
#include "changmin_library.h"

void ADD_FLINTvsCM(int wordlen);                //���������
void SUB_FLINTvsCM(int wordlen);                //���������
void MUL_FLINTvsCM(int wordlen);                //���������

void Kara_flag(int wordlen);                    // wordlen�� ���� Karatsuba ������ flag 
void MULvsKara(int wordlen);                    // ����: schoolbook vs. Karatsuba
void MULvsSQU(int wordlen);                     // ���� vs ����
void SQUvsKara(int wordlen);                    // ���� vs kara���� 
void karaMULvskaraSQU(int wordlen);             // Karatsuaba���� vs Karatsuaba����
void NAIVEvsBINARYLONGvsMULTIDIV(int wordlen);  // ������ Naive vs BinaryLongdiv vs MULtiprecisionDiv
void BINARYLONGvsMULTIDIV(int wordlen);         // BinaryLongdiv vs MULtiprecisionDiv

void DIV_FLINTvsCM(int wordlen);                // �����������
void EXPMOD_FLINTvsCM(int wordlen);             // �����¸�ⷯ�����
