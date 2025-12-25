#ifndef __BASE_H__
#define __BASE_H__

#include <stdio.h>
#include <stdbool.h>

#if (__ARMCC_VERSION >= 6000000)
#define WEEK __attribute__((weak))
#else
#define WEEK __weak
#endif


#endif