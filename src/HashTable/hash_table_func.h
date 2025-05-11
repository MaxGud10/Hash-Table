#ifndef HASH_TABLE_FUNC_H
#define HASH_TABLE_FUNC_H

#include <stdint.h>
#include <stdio.h>

#include "../DoubleLinkedList/fast_list_func.h"

typedef ListElem_t HashTableElem_t;

const int DEFAULT_LIST_CAPACITY       = 1;
const int DEFAULT_HASH_TABLE_CAPACITY = 1387; // 787 // 2687 
// 2187 // 7853 -+ // 1387

const int MAX_BENCHMARK_COMP_NUM      = 20000;

enum HashTableFuncStatus 
{
    HASH_TABLE_FUNC_STATUS_OK,
    HASH_TABLE_FUNC_STATUS_FAIL
};

struct HashTable 
{
    List*   cell;
    int64_t size;
};

struct Words 
{
    char*   word;
    int64_t num_of_words;
};

// Basic operations
HashTableFuncStatus init_hash_table      (HashTable* hash_table, int64_t hash_table_capacity);
HashTableFuncStatus init_hash_table_data (HashTable* hash_table);
HashTableFuncStatus dtor_hash_tadle_data (HashTable* hash_table);
HashTableFuncStatus dtor_hash_table      (HashTable* hash_table);

// Working with elements
HashTableFuncStatus insert_hash_table  (HashTable* hash_table, const HashTableElem_t data, const int64_t key);
char*               my_strdup32        (const char* word);
HashTableFuncStatus find_in_hash_table (HashTable* hash_table, const HashTableElem_t data);
HashTableFuncStatus clear_hash_table   (HashTable* hash_table);

// Testing and benchmarks
HashTableFuncStatus benchmark_hash_table (HashTable*  hash_table, Words* words);
HashTableFuncStatus read_hash_table_data (const char* input_file_name, HashTable* hash_table, uint32_t (*hash_func) (const HashTableElem_t));

// Analysis
double              eval_hash_table_variance (const HashTable* hash_table); 
HashTableFuncStatus test_hash_functions      (const char* input_file_name);
HashTableFuncStatus test_hash_table_search   (const char* input_file_name);


// Working with data
HashTableFuncStatus init_word_buffer (FILE*  data_file, Words* words);
HashTableFuncStatus dtor_word_buffer (Words* words);

#endif