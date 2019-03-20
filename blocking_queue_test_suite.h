//
// Created by mantas on 2019-03-20.
//

#ifndef BLOCKING_QUEUE_BLOCKING_QUEUE_TEST_SUITE_H
#define BLOCKING_QUEUE_BLOCKING_QUEUE_TEST_SUITE_H

#include "CuTest.h"

CuSuite* blocking_queue_get_test_suite();

void test_blocking_queue_alloc(CuTest *suite);

void test_blocking_queue_append(CuTest *suite);

void test_blocking_queue_head_isnt_equal_tail(CuTest *suite);

#endif //BLOCKING_QUEUE_BLOCKING_QUEUE_TEST_SUITE_H
