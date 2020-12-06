#include <float.h>
#include "flint.h"
#include "fmpz.h"
#include "ulong_extras.h"
#include "time.h"
#include "changmin_library.h"

void ADD_FLINTvsCM(int wordlen);
void SUB_FLINTvsCM(int wordlen);
void MUL_FLINTvsCM(int wordlen);

void Kara_flag(int wordlen); // flag¿¡ µû¶ó ¼³Á¤ 
void MULvsKara(int wordlen); // °ö¼À: schoolbook vs. Karatsuba
void MULvsSQU(int wordlen);  // °ö¼À vs Á¦°ö
void SQUvsKara(int wordlen); // Á¦°ö vs karaÁ¦°ö 
void NAIVEvsBINARYLONGvsMULTIDIV(int wordlen);
void BINARYLONGvsMULTIDIV(int wordlen);

void DIV_FLINTvsCM(int wordlen);
void EXPMOD_FLINTvsCM(int wordlen);
