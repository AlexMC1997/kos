#ifndef _UTIL_H
#define _UTIL_H

#define check_type(type, x) ({\ 
    type _dummy;\ 
    typeof(x) _dummy2;\ 
    (void)(&_dummy == &_dummy2)\
    1;\
})

//Aligns val to mod.
#define align(val, mod) (val - (val % mod))

#endif