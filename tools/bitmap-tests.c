#include <stdio.h>
#include <stdlib.h>
#include <bool.h>
#include <stdstr.h>

#include "avsul.h"
#include "avsul/avsul.h"

int main( int argc, char *argv[] ) {
	printf( "in bitmap tests\n" );

	printf( "sizeof(uint32_t): %d\n", sizeof(uint32_t) );
	printf( "sizeof(uint64_t): %d\n", sizeof(uint64_t) );
	printf( "sizeof(size_t): %d\n", sizeof(size_t) );

	vi_bitmap *bitmap = vmalloc( sizeof(vi_bitmap) );

	if( !vi_bitmap_create( bitmap, 512*512 ) ) {
		printf( "Bitmap creating failed.\n" );
		return 1;
	}

	vit_bitmap_run_test( bitmap, 0 );
	vit_bitmap_run_test( bitmap, 3 );
	vit_bitmap_run_test( bitmap, 63 );
	vit_bitmap_run_test( bitmap, 64 );
	vit_bitmap_run_test( bitmap, 65 );

	vi_bitmap_set( bitmap, 512*512 );
	vi_bitmap_set( bitmap, 512*512 + 1 );
	vi_bitmap_set( bitmap, 10 );
	vi_bitmap_set( bitmap, 64 );
	vi_bitmap_set( bitmap, 65 );
	vi_bitmap_set( bitmap, 66 );
	vi_bitmap_set( bitmap, 0 );
	vi_bitmap_set( bitmap, 1 );
	//vi_bitmap_set( bitmap, 42 );
	//vit_bitmap_run_test( bitmap, 512*512*4 + 1 );

	vi_bitmap_for_each_set( bitmap, vit_for_each_callback, NULL );

	return 0;
}

/**
 * @brief Run dev set/clear tests for given bit
 * 
 * @param b bit map struct
 * @param bit bit number
 */
void vit_bitmap_run_test( vi_bitmap *b, uint64_t bit ) {
	printf( "testing bit number %d\n", bit );
	printf( "    started:   bit %d: %d\n", bit, vi_bitmap_test( b, bit ) );
	vi_bitmap_set( b, bit );
	printf( "    after set: bit %d: %d\n", bit, vi_bitmap_test( b, bit ) );
	vi_bitmap_clear( b, bit );
	printf( "    after clr: bit %d: %d\n", bit, vi_bitmap_test( b, bit ) );
}

void vit_for_each_callback( uint64_t bit, void *data ) {
	printf( "Bit #%ld is set.\n", bit );
}