
#include "flint.h"
#include "fmpz.h"
#include "ulong_extras.h"
#include "time.h"
#include "changmin_library.h"

void ADD_FLINTvsCM(int wordlen);
void SUB_FLINTvsCM(int wordlen);
void MUL_FLINTvsCM(int wordlen);
void Kara_flag(); // flag�� ���� ���� 
void MULvsKara(); // ����: schoolbook vs. Karatsuba
void MULvsSQU();  // ���� vs ����
void SQUvsKara();
void NAIVEvsBINARYLONGvsMULTIDIV();
void DIV_FLINTvsCM(int wordlen);
void EXPMOD_FLINTvsCM(int wordlen);
