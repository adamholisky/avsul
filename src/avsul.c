#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "avsul.h"

struct avs_globals g_avs_data;

/**
 * @brief Initalize AVS systems to default status:
 * 
 * Memory allocation = libc malloc
 * 
 */
void avs_init( void ) {
    if( g_avs_data.init_has_run ) {
        return;
    }

    g_avs_data.alloc = malloc;
    g_avs_data.free = free;

    g_avs_data.init_has_run = true;
}

/**
 * @brief Retrieve the AVS globals
 * 
 * @return struct avs_globals* 
 */
struct avs_globals *avs_get_globals( void ) {
    return &g_avs_data;
}

/**
 * @brief Set the start of memory for non-dynamic memory allocation
 * 
 * @param start_of_mem Pointer to the start of the memory block
 */
void avs_set_static_allocation_base( void *start_of_mem ) {
    g_avs_data.mem_base = start_of_mem;
}

/**
 * @brief Enable static allocation
 * 
 */
void avs_enable_static_allocation( void ) {
    g_avs_data.static_allocation = true;
}

/**
 * @brief Disable static allocation
 * 
 */
void avs_disable_static_allocation( void ) {
    g_avs_data.static_allocation = false;
}

/**
 * @brief Allocate memory, either static or dynamic
 * 
 * @param size Length of memory to allocate
 * @return void* Pointer to the allocated memory
 */
void *avs_allocate( size_t size ) {
    if( g_avs_data.static_allocation ) {
        // TODO: This...
        return g_avs_data.alloc( size );
    } else {
        return g_avs_data.alloc( size );
    }
}

/**
 * @brief Frees the memory, either static or dynamic
 * 
 * @param mem Pointer to the memory to free
 */
void avs_free( void *mem ) {
    if( g_avs_data.static_allocation ) {
        // TODO: This...
        return g_avs_data.free( mem );
    } else {
        return g_avs_data.free( mem );
    }
}