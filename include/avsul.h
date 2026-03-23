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

struct avs_globals {
    bool init_has_run;
    bool static_allocation;

    void *mem_base;
    void *mem_top;

    void * (*alloc)(size_t);
    void (*free)(void *);
};

void avs_init( void );
struct avs_globals *avs_get_globals( void );

void avs_set_static_allocation_base( void *start_of_mem );
void avs_enable_static_allocation( void );
void avs_disable_static_allocation( void );

void *avs_allocate( size_t size );
void avs_free( void *mem );

#ifdef __cplusplus
}
#endif
#endif