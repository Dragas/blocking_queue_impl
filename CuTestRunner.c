//
// Created by mantas on 2019-03-20.
//

#include <printf.h>
#include "CuTest.h"
#include "blocking_queue_test_suite.h"

int main(int argc, char **argv) {
    CuSuite *suite = CuSuiteNew();
    CuString *output = CuStringNew();
    
    CuSuiteAddSuite(suite, blocking_queue_get_test_suite());
    
    CuSuiteRun(suite);
    
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    
    printf("%s\n", output->buffer);
}