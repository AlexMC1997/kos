#ifndef _DLL_H
#define _DLL_H

#include "gcc.h"

typedef struct _DLL_Node {
    void* data;
    struct _DLL_Node* left;
    struct _DLL_Node* right;
} gcc_packed DLL_Node;

#endif