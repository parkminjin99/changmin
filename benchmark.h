
#include "flint.h"
#include "fmpz.h"
#include "ulong_extras.h"
#include "time.h"
#include "changmin_library.h"

void ADD_FLINTvsCM(int wordlen);
void SUB_FLINTvsCM(int wordlen);
void MUL_FLINTvsCM(int wordlen);
void Kara_flag(); // flag¿¡ µû¶ó ¼³Á¤ 
void MULvsKara(); // °ö¼À: schoolbook vs. Karatsuba
void MULvsSQU();  // °ö¼À vs Á¦°ö
void SQUvsKara();
void NAIVEvsBINARYLONGvsMULTIDIV();
void DIV_FLINTvsCM(int wordlen);
void EXPMOD_FLINTvsCM(int wordlen);
