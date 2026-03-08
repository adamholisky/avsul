/**
 * @file hash.h
 * @author Adam Holisky (adam.holisky@gmail.com)
 * @brief hash header file
 * @version 0.1
 * @date 2026-03-07
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef AVSUL_HASH_H
#define AVSUL_HASH_H
#ifdef __cplusplus
extern "C" {
#endif

uint32_t avsul_hash_murmur32(const void *data, size_t nbytes);
bool avsul_hash_murmur128(const void *data, size_t nbytes, void *retbuf);

#ifdef __cplusplus
}
#endif
#endif