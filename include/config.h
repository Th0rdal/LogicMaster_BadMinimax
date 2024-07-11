#ifndef CONFIG_H
#define CONFIG_H

#define MAX_WAITTIME 10000 // sets the maximal time the program waits for the threads to finish the calculations
#define QUEUE_RESIZE
#define STACK_RESIZE

#include <stdbool.h>

/*!
 * represents the possible input formats that could be used to pass the gamestate to the program
 * */
typedef enum {
    FEN,
    NONE
}INPUTFORMAT; 

/*!
 * represents all arguments that can be set in the command line.
 * This is filled right at the start of the program and should not change afterwards
 * */
typedef struct command_args {
    INPUTFORMAT inputFormat;
    bool opponentMovesFlag;
    bool onlyPossibleMoves;
    char inputString[1024];
    int maxDepth;
    int maxThreads;
}command_args;

#endif
