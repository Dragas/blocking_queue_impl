//
// Created by mantas on 20/03/2019.
//

#include <pthread.h>
#include <stdlib.h>
#include "blocking_queue.h"



int blocking_queue_alloc(BlockingQueue **queue) {
    BlockingQueue *working = *queue;
    if(working == NULL)
         working = *queue = malloc(sizeof (BlockingQueue));
    if(working == NULL)
        return BLOCKING_QUEUE_ALLOCATION_FAILURE;
    working->length = 0;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);
    working->mutex = &mutex;
    working->condition = &condition;
    working->head = NULL;
    working->tail = NULL;
    return BLOCKING_QUEUE_OK;
}

int blocking_queue_node_alloc(BlockingQueueNode **node, PointerContainer **element) {
    BlockingQueueNode *working = *node;
    if(working == NULL)
        working = *node = malloc(sizeof(BlockingQueueNode));
    if(working == NULL)
        return BLOCKING_QUEUE_ALLOCATION_FAILURE;
    working->packet = *element;
    return BLOCKING_QUEUE_OK;
}

int blocking_queue_append_element(BlockingQueue **queue, PointerContainer **container) {
    BlockingQueue *working_queue = *queue;
    if(working_queue == NULL && blocking_queue_alloc(queue) == BLOCKING_QUEUE_ALLOCATION_FAILURE)
        return BLOCKING_QUEUE_ALLOCATION_FAILURE;
    BlockingQueueNode *node;
    if(blocking_queue_node_alloc(&node, container) == BLOCKING_QUEUE_ALLOCATION_FAILURE)
        return BLOCKING_QUEUE_FAILED_TO_ALLOCATE_NODE;
    if(working_queue->head == NULL)
        working_queue->head = node;
    if(working_queue->tail != NULL)
        working_queue->tail->next = node;
    working_queue->tail = node;
    working_queue->length++;
    pthread_cond_signal(working_queue->condition);
    return BLOCKING_QUEUE_OK;
}

int blocking_queue_get_first_element(BlockingQueue **queue, PointerContainer **container) {
    BlockingQueue *working = *queue;
    if(working == NULL) {
        return BLOCKING_QUEUE_INVALID;
    }
    if(working->head == NULL) {
        int res = pthread_cond_wait(&working->condition, &working->mutex);
        if(res != 0)
            return BLOCKING_QUEUE_FAILED_TO_AQCUIRE_LOCK;
    }
    if(working->head == NULL)
        return BLOCKING_QUEUE_EMPTY;
    *container = working->head->packet;
    BlockingQueueNode *next = working->head->next;
    blocking_queue_node_dealloc(&working->head);
    working->head = next;
    working->length--;
    return BLOCKING_QUEUE_OK;
}

int blocking_queue_dealloc(BlockingQueue **queue, DeallocationFunction element_dealloc_function) {
    BlockingQueue *working = *queue;
    if(working == NULL)
        return BLOCKING_QUEUE_OK;
    pthread_mutex_lock(&working->mutex);
    PointerContainer *container = NULL;
    while(working->head != NULL) {
        blocking_queue_get_first_element(&working, &container);
        if(element_dealloc_function != NULL)
            element_dealloc_function(container);
    }
    pthread_mutex_unlock(&working->mutex);
    pthread_mutex_destroy(&working->mutex);
    pthread_cond_destroy(&working->condition);
    return BLOCKING_QUEUE_OK;
}

int blocking_queue_node_dealloc(BlockingQueueNode **node) {
    BlockingQueueNode *working = *node;
    if(working == NULL)
        return BLOCKING_QUEUE_OK;
    free(working);
    return BLOCKING_QUEUE_OK;
}
