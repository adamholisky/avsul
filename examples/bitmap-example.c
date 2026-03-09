#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "avsul/avsul.h"
#include "avsul/bitmap.h"

void bitmap_run_test( avsul_bitmap *b, uint64_t bit );
void for_each_callback( uint64_t bit, void *data );

int main( int argc, char *argv[] ) {
	printf( "in bitmap tests\n" );

	printf( "sizeof(uint32_t): %ld\n", sizeof(uint32_t) );
	printf( "sizeof(uint64_t): %ld\n", sizeof(uint64_t) );
	printf( "sizeof(size_t): %ld\n", sizeof(size_t) );

	avsul_bitmap *bitmap = malloc( sizeof(avsul_bitmap) );

	if( !avsul_bitmap_create( bitmap, 512*512 ) ) {
		printf( "Bitmap creating failed.\n" );
		return 1;
	}

	bitmap_run_test( bitmap, 0 );
	bitmap_run_test( bitmap, 3 );
	bitmap_run_test( bitmap, 63 );
	bitmap_run_test( bitmap, 64 );
	bitmap_run_test( bitmap, 65 );

	avsul_bitmap_set( bitmap, 512*512 );
	avsul_bitmap_set( bitmap, 512*512 + 1 );
	avsul_bitmap_set( bitmap, 10 );
	avsul_bitmap_set( bitmap, 64 );
	avsul_bitmap_set( bitmap, 65 );
	avsul_bitmap_set( bitmap, 66 );
	avsul_bitmap_set( bitmap, 0 );
	avsul_bitmap_set( bitmap, 1 );
	//avsul_bitmap_set( bitmap, 42 );
	//vit_bitmap_run_test( bitmap, 512*512*4 + 1 );

	avsul_bitmap_for_each_set( bitmap, for_each_callback, NULL );

	return 0;
}

/**
 * @brief Run dev set/clear tests for given bit
 * 
 * @param b bit map struct
 * @param bit bit number
 */
void bitmap_run_test( avsul_bitmap *b, uint64_t bit ) {
	printf( "testing bit number %ld\n", bit );
	printf( "    started:   bit %ld: %d\n", bit, avsul_bitmap_test( b, bit ) );
	avsul_bitmap_set( b, bit );
	printf( "    after set: bit %ld: %d\n", bit, avsul_bitmap_test( b, bit ) );
	avsul_bitmap_clear( b, bit );
	printf( "    after clr: bit %ld: %d\n", bit, avsul_bitmap_test( b, bit ) );
}

void for_each_callback( uint64_t bit, void *data ) {
	printf( "Bit #%ld is set.\n", bit );
}