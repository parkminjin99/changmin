#include <float.h>
#include "flint.h"
#include "fmpz.h"
#include "ulong_extras.h"
#include "time.h"
#include "changmin_library.h"

void ADD_FLINTvsCM(int wordlen);
void SUB_FLINTvsCM(int wordlen);
void MUL_FLINTvsCM(int wordlen);

void Kara_flag(int wordlen); // flag�� ���� ���� 
void MULvsKara(int wordlen); // ����: schoolbook vs. Karatsuba
void MULvsSQU(int wordlen);  // ���� vs ����
void SQUvsKara(int wordlen); // ���� vs kara���� 
void NAIVEvsBINARYLONGvsMULTIDIV(int wordlen);
void BINARYLONGvsMULTIDIV(int wordlen);

void DIV_FLINTvsCM(int wordlen);
void EXPMOD_FLINTvsCM(int wordlen);
