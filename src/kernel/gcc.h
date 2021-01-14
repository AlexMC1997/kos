#ifndef _GCC_H
#define _GCC_H

#define gcc_inline __attribute__((__always_inline__)) 
#define gcc_no_opt __attribute__((__optimize__("O0"))) 
#define gcc_packed __attribute__((__packed__)) 

#endif