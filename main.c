//
// Created by mantas on 2019-03-20.
//

#include <printf.h>
#include "main.h"
#include "blocking_queue.h"


int main(int argc, char** args) {
    BlockingQueue *queue = NULL;
    blocking_queue_alloc(&queue);
    printf("This is a debug point, carry on");
    return 0;
}