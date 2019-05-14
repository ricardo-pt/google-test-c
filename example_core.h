
#ifndef __EXAMPLE_CORE_H__
#define __EXAMPLE_CORE_H__

#include <stdint.h>
#include <stdbool.h>

void EC_CounterInc();
uint32_t EC_CounterGet();
uint32_t EC_Factorial(uint32_t n);

#endif /* __EXAMPLE_CORE_H__ */