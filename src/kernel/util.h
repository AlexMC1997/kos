#ifndef _UTIL_H
#define _UTIL_H

#define CHECK_TYPE(type, x) ({\ 
    type _dummy;\ 
    typeof(x) _dummy2;\ 
    (void)(&_dummy == &_dummy2)\
    1;\
})

#endif