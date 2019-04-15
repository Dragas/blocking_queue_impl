//
// Created by mantas on 2019-03-20.
//

#include <stdlib.h>
#include "blocking_queue_test_suite.h"
#include "stdbool.h"
#include "blocking_queue.h"



void test_blocking_queue_alloc(CuTest *suite) {
    BlockingQueue *queue = NULL;
    int result = blocking_queue_alloc(&queue);
    CuAssertIntEquals(suite, BLOCKING_QUEUE_OK, result);
    CuAssertPtrNotNull(suite, queue);
    free(queue);
}

void test_blocking_queue_append(CuTest *suite) {

    BlockingQueue *queue = NULL;
    int result = blocking_queue_alloc(&queue);
    PointerContainer *container = malloc(sizeof(PointerContainer));
    container->value = 256;
    blocking_queue_append_element(&queue, &container);
    CuAssertIntEquals(suite, 1, queue->length);
    CuAssertPtrNotNull(suite, queue->tail);
    CuAssertPtrNotNull(suite, queue->head);
    free(container);
    free(queue);
}

void test_blocking_queue_head_isnt_equal_tail(CuTest *suite) {
    BlockingQueue *queue = NULL;
    int result = blocking_queue_alloc(&queue);
    PointerContainer *container = malloc(sizeof(PointerContainer));
    container->value = 256;
    blocking_queue_append_element(&queue, &container);
    PointerContainer *container2 = malloc(sizeof(PointerContainer));
    container2->value = 256;
    blocking_queue_append_element(&queue, &container2);
    CuAssertIntEquals(suite, 2, queue->length);
    CuAssertPtrNotEquals(suite, queue->head, queue->tail);

    free(queue);
    free(container);
    free(container2);
}

void test_blocking_queue_returns_put_element(CuTest *suite) {
    BlockingQueue *queue = NULL;
    blocking_queue_alloc(&queue);
    PointerContainer *container = malloc(sizeof(PointerContainer));
    blocking_queue_append_element(&queue, &container);

}

CuSuite* blocking_queue_get_test_suite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, test_blocking_queue_alloc);
    SUITE_ADD_TEST(suite, test_blocking_queue_append);
    SUITE_ADD_TEST(suite, test_blocking_queue_head_isnt_equal_tail);
    SUITE_ADD_TEST(suite, test_blocking_queue_returns_put_element);
    return suite;
}