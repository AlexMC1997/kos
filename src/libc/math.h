#ifndef _MATH_H
#define _MATH_H 

#include <stddef.h>
#include <stdint.h>
#include "gcc.h"

typedef struct {
    uint64_t significand : 52;
    uint64_t exp : 11;
    uint64_t sgn : 1;
} gcc_packed double_ieee_t;

typedef union {
    double_ieee_t double_ieee;
    double rational;
} double_ieee_ut;

typedef struct {
    uint32_t significand : 23;
    uint32_t exp : 8;
    uint32_t sgn : 1;
} gcc_packed float_ieee_t;

typedef union {
    float_ieee_t float_ieee;
    float rational;
} float_ieee_ut;

#if FLT_EVAL_METHOD == 0
typedef float float_t;
typedef double double_t;
#elif FLT_EVAL METHOD == 1
typedef float float_t;
typedef float float_t;
#elif FLT_EVAL METHOD == 2
typedef double float_t;
typedef double float_t;
#else
typedef float float_t;
typedef double double_t;
#endif

//Max double below infinity.
#define HUGE_VAL (const double_ieee_ut { { .significand = 0x1FFFFFFFFFFFFF, .exp = 2046, .sgn = 0 }}).rational
//Max float below infinity.
#define HUGE_VALF (const float_ieee_ut { { .significand = 0x7FFFFF, .exp = 254, .sgn = 0 } }).rational
//Infinity as a float.
#define INFINITY (const float_ieee_ut { { .significand = 0, .exp = 255, .sgn = 0 } }).rational
//Quiet NaN, no exception.
#define NAN (const float_ieee_ut { { .significand = 0x400001, .exp = 255, .sgn = 0 } }).rational

#define FP_INFINITE 1
#define FP_NAN 2
#define FP_NORMAL 3
#define FP_SUBNORMAL 4
#define FP_ZERO 5

#define MATH_ERRNO 1
#define MATH_ERREXCEPT 2

#define math_errhandling 1

#define fpclassify(x) ({\
if (sizeof(x) == 4) \
    __fpclassify_fl(x); \
else if (sizeof(x) == 8) \
    __fpclassify_db(x); \
})

#define isfinite(x) ({\
int tmp; \
if (sizeof(x) == 4) \
    if (tmp = __fpclassify_fl(x) == FP_NAN ||tmp == FP_INFINITE) \
        0;\
    else \
        1; \
else if (sizeof(x) == 8) \
    if (tmp = __fpclassify_db(x) == FP_NAN ||tmp == FP_INFINITE) \
        0;\
    else \
        1; \
})

static inline gcc_inline int __fpclassify_fl(float x)
{
    float_ieee_ut xu { .rational = x };
    if (!xu.float_ieee.exp) 
        return xu.float_ieee.significand ?  FP_SUBNORMAL : FP_ZERO;
    else if (xu.float_ieee.exp == 255)
        return xu.float_ieee.significand ? FP_NAN : FP_INFINITE;
    else
        return FP_ZERO; 
}

static inline gcc_inline int __fpclassify_db(double x)
{
    double_ieee_ut xu { .rational = x };
    if (!xu.double_ieee.exp) 
        return xu.double_ieee.significand ?  FP_SUBNORMAL : FP_ZERO;
    else if (xu.double_ieee.exp == 255)
        return xu.double_ieee.significand ? FP_NAN : FP_INFINITE;
    else
        return FP_NORMAL; 
}
#endif