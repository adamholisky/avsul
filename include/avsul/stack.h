/**
 * @file stack.h
 * @author Adam Holisky (adam.holisky@gmail.com)
 * @brief Stack header file
 * @version 0.1
 * @date 2026-03-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef AVSUL_STACK_H
#define AVSUL_STACK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "avsul/list.h"

typedef struct {
    avs_list *list;
} avs_stack;

avs_stack* avs_stack_init( void );
avs_stack* avs_stack_push( avs_stack *stack, void *data );
void* avs_stack_pop( avs_stack *stack );
void* avs_stack_peek( avs_stack *stack );
void avs_stack_empty( avs_stack *stack );

#ifdef __cplusplus
}
#endif
#endif