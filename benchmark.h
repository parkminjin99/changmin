//
//  benchmark.h
//  Changmin's library
//
//  Created by ÃÖ°­Ã¢¹Î on 2020/12/06.
//  Copyright 2020 ÃÖ°­Ã¢¹Î. All rights reserved.
//
#include <float.h>
#include "flint.h"
#include "fmpz.h"
#include "ulong_extras.h"
#include "time.h"
#include "changmin_library.h"

void ADD_FLINTvsCM(int wordlen);                // µ¡¼À¿¬»êºñ±³
void SUB_FLINTvsCM(int wordlen);                // »¬¼À¿¬»êºñ±³
void MUL_FLINTvsCM(int wordlen);                // °ö¼À¿¬»êºñ±³
void DIV_FLINTvsCM(int wordlen);                // ³ª´°¼À¿¬»êºñ±³
void EXPMOD_FLINTvsCM(int wordlen);             // Áö¼ö½Â¸ðµâ·¯¿¬»êºñ±³

void Kara_flag(int wordlen);                    // wordlen¿¡ µû¸¥ Karatsuba ÃÖÀûÀÇ flag 
void MULvsKara(int wordlen);                    // °ö¼À: schoolbook vs. Karatsuba
void MULvsSQU(int wordlen);                     // °ö¼À vs Á¦°ö
void SQUvsKara(int wordlen);                    // Á¦°ö vs karaÁ¦°ö 
void karaMULvskaraSQU(int wordlen);             // KaratsuabaÁ¦°ö vs KaratsuabaÁ¦°ö
void NAIVEvsBINARYLONGvsMULTIDIV(int wordlen);  // ³ª´°¼À Naive vs BinaryLongdiv vs MULtiprecisionDiv
void BINARYLONGvsMULTIDIV(int wordlen);         // BinaryLongdiv vs MULtiprecisionDiv
