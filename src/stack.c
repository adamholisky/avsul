/**
 * @file stack.c
 * @author Adam Holisky (adam.holisky@gmail.com)
 * @brief A simple stack implementation. Wrapper around avs list.
 * @version 0.1
 * @date 2026-03-09
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "avsul.h"
#include "avsul/list.h"
#include "avsul/stack.h"

/**
 * @brief Initalize an AVS stack
 * 
 * @return avs_stack* Pointer to the AVS stack, fully allocated. NULL if failure.
 */
avs_stack* avs_stack_init( void ) {    
    avs_init();

    avs_stack *stack = avs_allocate( sizeof(avs_stack) );

    if( stack == NULL ) {
        return NULL;
    }

    stack->list = avs_list_init();

    if( stack->list == NULL ) {
        return NULL;
    }

    return stack;
}

/**
 * @brief Pushes data onto the stack
 * 
 * @param stack Pointer to the stack
 * @param data Data to push onto the stack
 * @return avs_stack* Pointer to the stack, NULL if failure
 */
avs_stack* avs_stack_push( avs_stack *stack, void *data ) {
    avs_list *l = avs_list_push( stack->list, data );

    if( l == NULL ) {
        return NULL;
    }

    return stack;
}

/**
 * @brief Pops data off the stack
 * 
 * @param stack Pointer to the stack
 * @return void* Pointer to the data, NULL if there's no more data left
 */
void* avs_stack_pop( avs_stack *stack ) {
    return avs_list_pop( stack->list );
}

/**
 * @brief Peeks at data on the top of the stack
 * 
 * @param stack Pointer to the stack
 * @return void* Data on the top of the stack, NULL if nothing
 */
void* avs_stack_peek( avs_stack *stack ) {
    return stack->list->head->data;
}

/**
 * @brief Empties the stack
 * 
 * @param stack Pointer to the stack to empty
 */
void avs_stack_empty( avs_stack *stack ) {
    avs_list_empty( stack->list );
}