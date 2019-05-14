
#include "example_core.h"
#include <stdio.h>
#include <stdlib.h>

static uint32_t EC_Counter = 0;

void EC_CounterInc() { 
    EC_Counter++;
}

uint32_t EC_CounterGet() {
    return EC_Counter;
}

uint32_t EC_Factorial(uint32_t n) {
    uint32_t res = 1, i;
    
    for (i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}