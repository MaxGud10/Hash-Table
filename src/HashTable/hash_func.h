#ifndef HASH_FUNC_H
#define HASH_FUNC_H

#include <stdint.h>

#include "hash_table_func.h"

const uint32_t MAGIC_NUM_1 = 0xcc9e2d51;
const uint32_t MAGIC_NUM_2 = 0x1b873593;
const uint32_t MAGIC_NUM_3 = 0xe6546b64;
const uint32_t MAGIC_NUM_4 = 0x85ebca6b;
const uint32_t MAGIC_NUM_5 = 0xc2b2ae35;
const int      MAGIC_NUM_6 = 5;

const int MAGIC_NUM_FOR_ROL_1 = 15;
const int MAGIC_NUM_FOR_ROL_2 = 13;

const int MAGIC_NUM_FOR_BIT_SHIFT_1 = 16;
const int MAGIC_NUM_FOR_BIT_SHIFT_2 = 13;

uint32_t const_hash     (const HashTableElem_t value);
uint32_t first_sym_hash (const HashTableElem_t value);
uint32_t len_hash       (const HashTableElem_t value);
uint32_t ascii_sum_hash (const HashTableElem_t value);
uint32_t ascii_avg_hash (const HashTableElem_t value);
uint32_t ror_hash       (const HashTableElem_t value);
uint32_t rol_hash       (const HashTableElem_t value);
uint32_t murmur_hash    (const HashTableElem_t value);
uint32_t crc32_hash     (const HashTableElem_t value);


uint32_t my_rol          (const uint32_t number, int num_to_rol);
uint32_t my_ror          (const uint32_t number, int num_to_ror);
uint32_t intrinsic_crc32 (const HashTableElem_t value);

#endif