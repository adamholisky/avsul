/**
 * @file bitmap.h
 * @author Adam Holisky (adam.holisky@gmail.com)
 * @brief Bitmap array header file
 * @version 0.1
 * @date 2026-03-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef AVSUL_BITMAP_H
#define AVSUL_BITMAP_H
#ifdef __cplusplus
extern "C" {
#endif

// We set the max count to (2^32)/2 so we don't do something crazy via an error,
// this means max memory size is limited to 268,435,456 bytes (aka 256 megs)
#define AVSUL_BITMAP_MAX_BIT_COUNT 2147483648

typedef struct {
	uint64_t *fields;
	uint32_t field_count;
	uint64_t bit_count;
} avsul_bitmap;

int vit_bitmap_tests( int argc, char *argv[] );
void vit_bitmap_run_test( avsul_bitmap *b, uint64_t bit );
void vit_for_each_callback( uint64_t bit, void *data );

bool avsul_bitmap_create( avsul_bitmap *b, uint64_t size );
bool avsul_bitmap_test( avsul_bitmap *b, uint64_t bit_num );
bool avsul_bitmap_set( avsul_bitmap *b, uint64_t bit_num );
bool avsul_bitmap_clear( avsul_bitmap *b, uint64_t bit_num );
bool avsul_bitmap_set_to( avsul_bitmap *b, uint64_t bit_num, bool val );
void avsul_bitmap_for_each_set( avsul_bitmap *b, void (*func)(uint64_t, void *), void *data );

#ifdef __cplusplus
}
#endif
#endif