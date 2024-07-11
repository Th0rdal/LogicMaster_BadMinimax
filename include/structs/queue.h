#ifndef QUEUE_H
#define QUEUE_H

//this is a THREAT SAVE queue

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include "structs/gamestate.h"
#include "config.h"

static const int QUEUE_SIZE_BASE = 15;
static const int QUEUE_SIZE_MULTIPLIER = 75;
static const int ENQUEUE_WAIT_TIME = 1500;
static const int DEQUEUE_WAIT_TIME = 100;

/*! representing a queue*/
typedef struct {
    Gamestate** data;
    int front;
    int rear;
    int maxSize;
    CRITICAL_SECTION lock;
    CONDITION_VARIABLE condEnqueue; // waiting in enqueue when queue full
    CONDITION_VARIABLE condDequeue; // waiting in dequeue when queue is empty
} Queue;

/*!
 * initializes the queue struct
 *
 * @param maxDepth: a value that will be multiplied with QUEUE_SIZE_BASE to determine the queue size
 *
 * @warning ERROR_MEMORY_MALLOC_FAILED: if malloc fails
 * */
Queue* queueInit(int maxDepth);

/*!
 * adds a Gamestate to the queue
 *
 * @param queue: the queue to add the gamestate to
 * @param gamestate: the gamestate to add
 *
 * @warning WARNING_QUEUE_TOO_SMALL: if the queue is too small
 * @warning WARNING_RESIZING_QUEUE: if the queue is resized 
 * @warning ERROR_MALLOC_REALLOC_FAILED: if the realloc function failed
 * @warning ERROR_QUEUE_TOO_SMALL: if QUEUE_RESIZE is not defined and the queue is full
 * */
void enqueue(Queue* queue, Gamestate* gamestate);

/*!
 * gets the first gamestate of the queue
 *
 * @param queue: the queue to get the gamestate from
 *
 * */
Gamestate* dequeue(Queue* queue);

/*!
 * destroies the queue struct and all fields in it
 *
 * */
void destroyQueue(Queue* queue);
#endif
