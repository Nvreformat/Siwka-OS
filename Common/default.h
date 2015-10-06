#ifndef DEFAULT_H
#define DEFAULT_H

//Default header, it gets included in every soruce file that is compiled

#include <stddef.h>
#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

#define Init __attribute__((section(".init")))

#endif
