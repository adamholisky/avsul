/**
 * @file list-example.c
 * @author Adam Holisky (adam.holisky@gmail.com)
 * @brief A Very Simple list data structure example code
 * @version 0.1
 * @date 2026-03-10
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <stdio.h>
#include <string.h>
#include <avsul.h>
#include <avsul/list.h>

void print_node( avs_node *n );
int compare_test_list_data( void *a, void *b );

int main( int argc, char *argv[] ) {
    avs_list *l = avs_list_init();

    avs_list_append( l, "Archer" );
    avs_list_append( l, "April" );
    avs_list_append( l, "Pike" );
    avs_list_append( l, "Kirk" );
    avs_list_append( l, "Decker" );
    avs_list_append( l, "Spock" );

    printf( "List start: \n" );
    avs_list_for_each( l, print_node );

    printf( "Remove head: \n" );
    avs_list_remove( l, l->head );
    avs_list_for_each( l, print_node );

    printf( "Remove tail: \n" );
    avs_list_remove( l, l->tail );
    avs_list_for_each( l, print_node );

    printf( "Remove Decker: \n" );
    avs_node *n_decker = avs_list_find_data( l, "Decker", compare_test_list_data );

    if( n_decker != NULL ) {
        avs_list_remove( l, n_decker );
        avs_list_for_each( l, print_node );
    } else {
        printf( "Couldn't find Decker. Oops.\n" );
    }

    printf( "Remove Pike: \n" );
    avs_node *n_pike = avs_list_find_data( l, "Pike", compare_test_list_data );

    if( n_pike != NULL ) {
        avs_list_remove( l, n_pike );
        avs_list_for_each( l, print_node );
    } else {
        printf( "Couldn't find Pike. Oops.\n" );
    }

    printf( "Insert AFTER april:\n" );
    avs_node *n_april = avs_list_find_data( l, "April", compare_test_list_data );
    avs_list_insert_after( l, n_april, "Riker" );
    avs_list_for_each( l, print_node );

    printf( "Insert AFTER tail:\n" );
    avs_list_insert_after( l, l->tail, "Picard" );
    avs_list_for_each( l, print_node );

    printf( "Insert AFTER mid:\n" );
    avs_node *n_riker = avs_list_find_data( l, "Riker", compare_test_list_data );
    avs_list_insert_after( l, n_riker, "Garret" );
    avs_list_for_each( l, print_node );
    
    return 0;
}

void print_node( avs_node *n ) {
    if( n->data != NULL ) {
        printf( "Node data: \"%s\"\n", (char *)n->data );
    }
}

int compare_test_list_data( void *a, void *b ) {
    return strcmp( (char *)a, (char *)b );
}

