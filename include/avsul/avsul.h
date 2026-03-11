/**
 * @file avsul.h
 * @author Adam Holisky (adam.holisky@gmail.com)
 * @brief A Very Simple Utility Library
 * @version 0.1
 * @date 2026-03-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef AVSUL_H
#define AVSUL_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "avsul/bitmap.h"
#include "avsul/list.h"

#ifdef AVSUL_NO_ALLOCATOR
    #define #AVSUL_STATIC_ALLOCATION
#endif


#ifdef __cplusplus
}
#endif
#endif