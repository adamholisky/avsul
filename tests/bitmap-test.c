#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <cmocka.h>
#include "avsul.h"
#include "avsul/bitmap.h"

static void test_create_bitmap( void **state ) {
    (void) state;

    avs_init();

    avsul_bitmap *bitmap = avs_allocate( sizeof(avsul_bitmap) );

	assert_true( avsul_bitmap_create( bitmap, 512*512 ) );

    free( bitmap );
}

static void null_test_success( void **state ) {
    (void) state; /* unused */
}

/* A test that will always fail */
static void null_test_fail( void **state ) {
    (void) state; /* unused */
    assert_true(0);
}

int main( void ) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(test_create_bitmap),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
