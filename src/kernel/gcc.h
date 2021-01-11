#ifndef _GCC_H
#define _GCC_H

#define attr_inline __attribute__((__always_inline__)) 
#define attr_no_opt __attribute__((__optimize__("O0"))) 
#define attr_packed __attribute__((__packed__)) 

#endif