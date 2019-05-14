#include <math.h>
#include "example_core.h"

static uint32_t ExampleGlobalVar = 0;

double PowerOf(const double value, const uint32_t power) {
    return pow(value, power);
}

bool IsOdd(uint32_t n) {
    return (0 != n % 2);
}

uint32_t CounterCoreExample(){
    uint32_t counter;

    EC_CounterInc();
    counter = EC_CounterGet();
    if (0 == counter % 2) {
        return EC_CounterGet();
    }
    else {
        return EC_Factorial(5);
    }
}

uint32_t GlobalVar() {
    return ExampleGlobalVar;
}