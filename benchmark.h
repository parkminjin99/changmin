#include "flint.h"
#include "fmpz.h"
#include "ulong_extras.h"
#include "time.h"
#include "changmin_library.h"

void CM();
void FLINT();
void ADD_FLINTvsCM();
void SUB_FLINTvsCM();
void MUL_FLINTvsCM();
void Kara_flag(); // flag¿¡ µû¶ó ¼³Á¤ 
void MULvsKara(); // °ö¼À: schoolbook vs. Karatsuba
void MULvsSQU();  // °ö¼À vs Á¦°ö
//////////////////////////////////////////////////////////////////////////////////////////
void CM_single();
void SQUvsKara();
void NAIVEvsBINARYLONGvsMULTIDIV();
void DIV_FLINTvsCM();
void FLINT_tri();
void EXPMOD_FLINTvsCM();
void EXPMOD_test();