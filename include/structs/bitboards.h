#ifndef BITBOARDS_H
#define BITBOARDS_H

#include <stdint.h>
#include <stdio.h>

#include "position.h"

/*! represents a single board state */
typedef struct {
   uint64_t occupancy;
   
   uint64_t pawn;
   uint64_t knight;
   uint64_t bishop;
   uint64_t rook;
   uint64_t queen;
   uint64_t king;

   uint64_t color[2]; // index black = 0, index white = 1

   // this HAS to be FF unless the king is in check (for calculations)
   uint64_t possibleMovesAfterCheck; // only has interesting value if checkChecked is true & currently a check
} Bitboards;

/*! represents each file as a struct. Used for calculations*/
typedef struct {
    const uint64_t fileA;
    const uint64_t fileB;
    const uint64_t fileC;
    const uint64_t fileD;
    const uint64_t fileE;
    const uint64_t fileF;
    const uint64_t fileG;
    const uint64_t fileH;
    const int size;
    const uint64_t boards[8];
    const uint64_t reverseBoards[8];
} FileBitboards;

/*! represents each row as a struct. Used for calculations*/
typedef struct {
    const uint64_t rank1;
    const uint64_t rank2;
    const uint64_t rank3;
    const uint64_t rank4;
    const uint64_t rank5;
    const uint64_t rank6;
    const uint64_t rank7;
    const uint64_t rank8;
    const int size;
    const uint64_t boards[8];
    const uint64_t reverseBoards[8];
    const short pawnPromotionRank[2];
    const short pawn2SquareMoveRank[2];
} RankBitboards;

/*! represents each diagonal as a struct. Used for calculations*/
typedef struct { // diagonals go from left bottom to right top e.g., A1 - H8
    const uint64_t diagonal1; //A8
    const uint64_t diagonal2; //A7-B8
    const uint64_t diagonal3; //A6-C8
    const uint64_t diagonal4; //A5-D8
    const uint64_t diagonal5; //A4-E8
    const uint64_t diagonal6; //A3-F8
    const uint64_t diagonal7; //A2-G8
    const uint64_t diagonal8; //A1-H8
    const uint64_t diagonal9; //B1-H7
    const uint64_t diagonal10; //C1-H6
    const uint64_t diagonal11; //D1-H5
    const uint64_t diagonal12; //E1-H4
    const uint64_t diagonal13; //F1-H3
    const uint64_t diagonal14; //G1-H2
    const uint64_t diagonal15; //H1
    const int size;
    const uint64_t boards[15];
                          
} DiagonalBitboards;

/*! represents a mode dictionary for any piece. Array position 0 equals field H1, going left and up*/
typedef struct {
    const int size;
    const uint64_t boards[64];
} MoveDictionary;

/*! a struct containing important special fields*/
typedef struct {
    const uint64_t queenCastle[2]; // mask for all squares that need to be looked at for queen castling
    const uint64_t kingCastle[2]; // mask for all squares that need to be looked at for king castling
    const Position queenCastlePositions[2][2];
    const Position kingCastlePositions[2][2];
    const short pawn1SquareAdd[2];
    const short pawn2SquareAdd[2];
    const short pawnCaptureRight[2];
    const short pawnCaptureLeft[2];
    const short qCastleRookPositions[2][2];
    const short kCastleRookPositions[2][2];
    const uint64_t kCastleRookBitboard[2];
    const uint64_t qCastleRookBitboard[2];
} SpecialMoveDictionary;

/*
 * creates and initializes a bitboard struct. All values will be initialized with 0.
 *
 * @return: initialized bitboard
 *
 */
Bitboards bitboardsInit();

extern const FileBitboards fileBitboards; /*! initialized to the file*/
extern const RankBitboards rankBitboards; /*! initialized to the rank*/
extern const DiagonalBitboards diagonalBitboards; /*! initialized to the diagonal*/
extern const DiagonalBitboards antiDiagonalBitboards; /*! initialized to the anti diagonal*/
extern const MoveDictionary knightMoveDictionary; /*! initialized to contain all moves a knight can do from a given position*/
extern const MoveDictionary kingMoveDictionary; /*! initialized to contain all moves the king can do from a given position (excluding castling)*/
extern const MoveDictionary positionDictionary; /*! converts a given position as int to a bitboard with only the given position as a 1 */
extern const SpecialMoveDictionary specialMoveDictionary; /*! initialized for all special positions (castling, pawn 2 moves, etc...) */

#endif
