#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>
#include "avsul/avsul.h"
#include "avsul/hash.h"

const char *test_data = "This is some test data.\n";
const char *test_data_two = "This is some OTHER test data.\n";

static void test_32bit_murmur( void **state ) {
    (void) state;

    uint32_t hash_result = avsul_hash_murmur32( test_data, strlen(test_data) );

    assert_true( hash_result );
}

static void test_32bit_murmur_collision( void **state ) {
    (void) state;

    uint32_t hash_result = avsul_hash_murmur32( test_data, strlen(test_data) );
    uint32_t hash_result_same = avsul_hash_murmur32( test_data, strlen(test_data) );
    uint32_t hash_result_two = avsul_hash_murmur32( test_data_two, strlen(test_data_two) );

    assert_int_equal( hash_result, hash_result_same );
    assert_int_not_equal( hash_result, hash_result_two );
}

static void test_128bit_murmur( void **state ) {
    (void) state;
    char hash_result[16];
    
    bool hash_success = avsul_hash_murmur128( test_data, strlen(test_data), hash_result );

    assert_true( hash_success );
    assert_true( hash_result );
}

static void test_128bit_murmur_collision( void **state ) {
    (void) state;
    char hash_result_a[16];
    char hash_result_b[16];
    char hash_result_c[16];
    
    bool hash_success_a = avsul_hash_murmur128( test_data, strlen(test_data), hash_result_a );
    bool hash_success_b = avsul_hash_murmur128( test_data, strlen(test_data), hash_result_b );
    bool hash_success_c = avsul_hash_murmur128( test_data_two, strlen(test_data_two), hash_result_c );

    assert_true( hash_success_a );
    assert_true( hash_success_b );
    assert_true( hash_success_c );

    assert_memory_equal( hash_result_a, hash_result_b, sizeof(hash_result_a) );
    assert_memory_not_equal( hash_result_a, hash_result_c, sizeof(hash_result_a) );
}

int main( void ) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_32bit_murmur),
        cmocka_unit_test(test_32bit_murmur_collision),
        cmocka_unit_test(test_128bit_murmur),
        cmocka_unit_test(test_128bit_murmur_collision),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
