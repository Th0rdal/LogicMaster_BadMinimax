/**
 * @file preprocessing.h
 *
 * This file includes functions for preprocessing.
 * This involves a move calculation worker, a move calculations function and a preprocessing function.
 *
 * */
#ifndef PREPROCESSING_H
#define PREPROCESSING_H

#include <stdlib.h>
#include <stdint.h>

#include "errors.h"
#include "structs/gamestate.h"
#include "structs/position.h"
#include "structs/queue.h"
#include "structs/stack.h"
#include "structs/tree.h"
#include "utility/moveCalculation.h"
#include "minimax/evaluation.h"
#include "config.h"

// MAX_WAIT_TIME is set in minimax.h

/*! represents a move generation thread pool*/
typedef struct {
    HANDLE* threads;
    int maxThreads;
    Queue* queue;
    bool shutdown;
    int64_t workCounter;
    int maxDepth;
    CRITICAL_SECTION lock;
} MoveGenerationThreadPool;

/*!
 * function representing the work a MoveGenerationThreadPool thread does. It works until the shutdown command is issued or the workCounter reaches 0 (which means work done)
 * it gets a new gamestate from the queue, processes it and then updates the workCounter. If the maxDepth is reached, it enqueues the gamestate to the result queue
 *
 * @param args: command args struct pointer with configuration
 * @param gamestate: the starting gamestate
 *
 * @warning ERROR_THREADS_TIMEOUT: if a thread surpasses the max work time defined by MAX_WAIT_TIME
 **/
void preprocessing_start(command_args* args, Gamestate* gamestate);

/*!
 * The function an generation worker thread executes to generate all possible moves
 * For move generation it uses an internal function called calcuolateMoves
 *
 * @param lpParam: The MoveGenerationThreadPool with all needed variables set
 * */
DWORD WINAPI generationWorker(LPVOID lpParam);

/*!
 * initializes all variables of the struct
 *
 * @param args: command args struct pointer with configuration
 *
 * @return: the initialized MoveGenerationThreadPool pointer 
 *
 * @warning ERROR_MEMORY_MALLOC_FAILED: if malloc failed
 * */
MoveGenerationThreadPool* moveGenerationThreadPoolInit(command_args* args);

#endif
