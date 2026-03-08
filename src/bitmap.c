/**
 * @file bitmap.c
 * @author Adam Holisky (adam.holisky@gmail.com)
 * @brief A very simple bitmap array
 * @version 0.1
 * @date 2026-03-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <bool.h>
#include <stdstr.h>

#include "avsul.h"
#include "avsul/bitmap.h"

/**
 * @brief Create a bitmap of the given size
 * 
 * @param size 1 through (max of size_t) bit fields. NOT 0-based.
 * @return bool true if successful, false otherwise
 */
bool avsul_bitmap_create( avsul_bitmap *b, uint64_t size ) {
	if( b == NULL ) {
		printf( "avsul_bitmap *b is NULL. Failing.\n" );
		return false;
	}

	if( size < 1 ) {
		printf( "Size must be 1 or greater. Failing.\n" );
		return false;
	}

	if( size >= AVSUL_BITMAP_MAX_BIT_COUNT ) {
		printf( "Size must be under %ld, got %ld. Failing.\n", AVSUL_BITMAP_MAX_BIT_COUNT, size );
		return false;
	}

	b->field_count = size / 64;

	if( size % 64 != 0 ) {
		b->field_count++;
	}

	b->fields = vmalloc( sizeof(uint64_t) * b->field_count );
	if( b->fields == NULL ) {
		printf( "b->fields is NULL. Failing.\n" );
		return false;
	}
	b->bit_count = size;

	memset( b->fields, 0, b->field_count * (64/8) );

	printf( "size: %ld    field_count: %ld\n", size, b->field_count );

	return true;
}

/**
 * @brief Tests the state of the given bit
 * 
 * @param b Pointer to the bitmap struct
 * @param bit_num bit number to test
 * @return true Bit is set
 * @return false Bit is unset
 */
bool avsul_bitmap_test( avsul_bitmap *b, uint64_t bit_num ) {
	uint32_t field = bit_num / 64;
	uint64_t bit = bit_num % 64;

	if( b == NULL ) {
		printf( "avsul_bitmap *b is NULL. Failing.\n" );
		return false;
	}

	if( bit_num > b->bit_count ) {
		printf( "Bit number exceeded allocated size. bit_num = %d, max = %d.\n", bit_num, b->bit_count );
		return false;
	}

	return (b->fields[field] & (1UL<<bit)) >= 1 ? true : false;
}

/**
 * @brief Sets the given bit
 * 
 * @param b Pointer to the bitmap struct
 * @param bit_num bit number to set
 * @return true Success
 * @return false Failure
 */
bool avsul_bitmap_set( avsul_bitmap *b, uint64_t bit_num ) {
	return avsul_bitmap_set_to( b, bit_num, true );
}

/**
 * @brief Clears the given bit
 * 
 * @param b Pointer to the bitmap struct
 * @param bit_num bit number to clear
 * @return true Success
 * @return false Failure
 */
bool avsul_bitmap_clear( avsul_bitmap *b, uint64_t bit_num ) {
	return avsul_bitmap_set_to( b, bit_num, false );
}

/**
 * @brief Sets a bit to the given state
 * 
 * @param b Pointer to the bitmap struct
 * @param bit_num bit number to set
 * @param val true (1) or false (0)
 * @return true Success
 * @return false Failure
 */
bool avsul_bitmap_set_to( avsul_bitmap *b, uint64_t bit_num, bool val ) {
	uint32_t field = bit_num / 64;
	uint64_t bit = bit_num % 64;

	if( b == NULL ) {
		printf( "avsul_bitmap *b is NULL. Failing.\n" );
		return false;
	}

	if( bit_num > b->bit_count ) {
		printf( "Bit number exceeded allocated size. bit_num = %d, max = %d.\n", bit_num, b->bit_count );
		return false;
	}

	// intentionally omitting field size check for speed sake, given b ought to be configured right by now
	
	if( val ) {
		// Set bit
		b->fields[field] = b->fields[field] | (1UL<<bit);
	} else {
		// Clear bit
		b->fields[field] = b->fields[field] & (0UL<<bit);
	}

	//printf( "setting field: %ld    bit: %d    set: %d (%llX)    field data: 0x%llX\n", field, bit, val, (1UL<<bit),b->fields[field] );
	return true;
}

/**
 * @brief Iterate through each bitmap value, sending the bit to the given callback
 * 
 * @param b AVSUL bitmap array
 * @param func pointer to the callback function
 * @param data data to pass to the callback function
 */
void avsul_bitmap_for_each_set( avsul_bitmap *b, void (*func)(uint64_t, void *), void *data ) {
	if( b == NULL ) {
		printf( "avsul_bitmap *b is NULL. Failing.\n" );
		return;
	}

	for( uint64_t i = 0; i < b->bit_count; i++ ) {
		if( avsul_bitmap_test(b,i) ) {
			func( i, data );
		}
	}
}