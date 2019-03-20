//
// Created by mantas on 20/03/2019.
//

#ifndef RTSPLIBRARY_BLOCKING_QUEUE_H
#define RTSPLIBRARY_BLOCKING_QUEUE_H

#include <event.h>

#define BLOCKING_QUEUE_INVALID -3
#define BLOCKING_QUEUE_FAILED_TO_ALLOCATE_NODE -2
#define BLOCKING_QUEUE_ALLOCATION_FAILURE -1
#define BLOCKING_QUEUE_OK 0


typedef struct __BlockingQueueNode BlockingQueueNode;
typedef struct __BlockingQueue BlockingQueue;
typedef struct __PointerContainer PointerContainer;

struct __BlockingQueueNode {
    PointerContainer *packet;
    BlockingQueueNode *next;
};

struct __BlockingQueue {
    BlockingQueueNode *head;
    BlockingQueueNode *tail;
    int length;
    pthread_cond_t *condition;
    pthread_mutex_t *mutex;
};

struct __PointerContainer {
    int value;
};

int blocking_queue_alloc(BlockingQueue **queue);

int blocking_queue_node_alloc(BlockingQueueNode **node, PointerContainer **element);

int blocking_queue_append_element(BlockingQueue **queue, PointerContainer **container);

int blocking_queue_get_first_element(BlockingQueue **queue, PointerContainer **container);

#endif //RTSPLIBRARY_BLOCKING_QUEUE_H
