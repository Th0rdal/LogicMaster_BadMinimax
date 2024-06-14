#ifndef POSITION_H
#define POSITION_H

#include <stdint.h>
#include <stdlib.h>

#include "errors.h"

typedef struct { // initialized to 0
    short rank; // row
    short file; //column
} Position;

Position positionInit();
void checkPositionValues(Position* position);
void setPositionFromShort(Position* position, short number);
Position* getAllPiecePositions(uint64_t bitboard, short pieces);
void convertCharArrayToPosition(char* fenChar, Position* position);

#endif
