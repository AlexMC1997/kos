#include <stdlib.h>
#include "gcc.h"

long labs(long j)
{
    return j < 0 ? -j : j;
}