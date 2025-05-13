#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

#include "../TextPreparer/text_preparer.h"

#include "hash_func.h"
#include "hash_table_func.h"
#include "hash_table_dsl.h"
#include "hash_table_log.h"

#ifndef VISUAL_STUDIO
    #include <immintrin.h>
#else
    #include <intrin.h>  // espessialy for visual studio msvc  
#endif

#define HASH_ALGORITHM_VAR_PRINT(hash_table, algorithm_name)                                          \
                                    {                                                                 \
                                        printf (algorithm_name ":\n");                                \
                                        log_variance_result (eval_hash_table_variance (hash_table));  \
                                    }

HashTableFuncStatus init_hash_table (HashTable* hash_table, int64_t hash_table_capacity) 
{
    assert (hash_table);

    HASH_TABLE_SIZE_ = hash_table_capacity;

    if (init_hash_table_data (hash_table) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus init_hash_table_data (HashTable* hash_table) 
{    
    assert (hash_table);
    
    HASH_TABLE_CELL_ = (List*) calloc (HASH_TABLE_SIZE_, sizeof (List));
    assert (HASH_TABLE_CELL_);

    for (size_t i = 0; i < ((size_t) HASH_TABLE_SIZE_); i++)         
        init_list (HASH_TABLE_CELL_ + i, DEFAULT_LIST_CAPACITY);

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus dtor_hash_tadle_data (HashTable* hash_table) 
{
    assert (hash_table);
    assert (HASH_TABLE_CELL_);

    for (size_t i = 0; i < ((size_t) HASH_TABLE_SIZE_); i++)
        dtor_list (HASH_TABLE_CELL_ + i);

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus dtor_hash_table (HashTable* hash_table) 
{
    assert (hash_table);

    dtor_hash_tadle_data (hash_table);
    HASH_TABLE_SIZE_ = 0;

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus insert_hash_table (HashTable* hash_table, const HashTableElem_t data, const int64_t key) 
{
    // assert (hash_table);
    if (hash_table == NULL)
    {
        fprintf (stderr, "\nhash_table = NULL\n");
        return HASH_TABLE_FUNC_STATUS_FAIL;
    }

    if (key < 0)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    if (!hash_table || !hash_table->cell) {
        fprintf(stderr, "Hash table not initialized!\n");
        exit(EXIT_FAILURE);
    }
        
    int64_t cell_num = key % HASH_TABLE_SIZE_;
    List*   cell_ptr = HASH_TABLE_CELL_ + cell_num;
    // printf("Inserting '%s': hash = %lu, cell_num = %lu\n", data, murmur_hash (data), cell_num);

    int64_t stub = 0;

    // printf("Before find_list_elem: cell_ptr=%p, data=%p ('%s')\n", 
    //    (void*)cell_ptr, (void*)data, data);

    if (find_list_elem(cell_ptr, data) == LIST_FUNC_STATUS_FAIL) {
        // printf("Adding new element: %s\n", data);
        add_list_elem(cell_ptr, DUMMY_ELEM_POS, &stub, data);
    }
    // if (find_list_elem (cell_ptr, data) == LIST_FUNC_STATUS_FAIL)
    //     add_list_elem  (cell_ptr, DUMMY_ELEM_POS, &stub, data);

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus find_in_hash_table (HashTable* hash_table, const HashTableElem_t data) 
{
    assert (hash_table);

    int64_t cell_num = murmur_hash     (data) % HASH_TABLE_SIZE_;
    // int64_t cell_num = intrinsic_crc32 (data) % HASH_TABLE_SIZE_;
    // int64_t cell_num = crc32_hash      (data) % HASH_TABLE_SIZE_;
    List*   cell_ptr = HASH_TABLE_CELL_ + cell_num;

    if (find_list_elem (cell_ptr, data) == LIST_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus read_hash_table_data (const char* input_file_name, HashTable* hash_table, uint32_t (*hash_func) (const HashTableElem_t)) 
{
    assert (input_file_name);
    assert (hash_table);
    assert (hash_func);

    FILE* data_file = NULL;
    
    if (!(data_file = fopen (generate_prepared_filename (input_file_name), "r"))) // TODO as func
    {        
        if (prepare_text (input_file_name) == PREPARING_FUNC_STATUS_FAIL)
            return HASH_TABLE_FUNC_STATUS_FAIL;

        data_file = fopen (generate_prepared_filename (input_file_name), "r");
    }
    
    char word[MAX_WORD_LENGTH] = {};

    while (!feof (data_file)) 
    {
        int fscanf_status = fscanf (data_file, "%s", word);
        //printf("Read word: '%s', hash: %u\n", word, hash_func(word));

        if (fscanf_status != EOF && fscanf_status != 0)
        insert_hash_table (hash_table, my_strdup32 (word), hash_func (word));
    }

    return HASH_TABLE_FUNC_STATUS_OK;
}

char* my_strdup32 (const char* word) 
{
    assert (word);

    char* word_dup = (char*) calloc (1, 32);

    return strcpy (word_dup, word);
}

HashTableFuncStatus clear_hash_table (HashTable* hash_table) 
{
    assert (hash_table);

    for (size_t i = 0; i < (size_t) HASH_TABLE_SIZE_; i++) 
    {
        List* curr_cell = HASH_TABLE_CELL_ + i;

        (curr_cell->controlItems).free = 0;
         curr_cell->list_size          = 0;

        fill_list          (curr_cell, DUMMY_ELEM_POS);
        connect_list_elems (curr_cell, DUMMY_ELEM_POS, DUMMY_ELEM_POS);
    }                    

    return HASH_TABLE_FUNC_STATUS_OK;
}

double eval_hash_table_variance(const HashTable* hash_table) 
{
    assert(hash_table);

    size_t num_of_elems = 0;
    
    for (size_t i = 0; i < (size_t)HASH_TABLE_SIZE_; i++) 
        num_of_elems += (HASH_TABLE_CELL_ + i)->list_size; 

    const double average  = (double)num_of_elems / (double)HASH_TABLE_SIZE_;

          double variance = 0;

    for (size_t i = 0; i < (size_t)HASH_TABLE_SIZE_; i++) 
    {
        double diff = (double)((HASH_TABLE_CELL_ + i)->list_size) - average;
        
        variance += diff * diff;
    }

    variance /= (double)HASH_TABLE_SIZE_ - 1; 

    return variance;
}

// double eval_hash_table_variance (const HashTable* hash_table) 
// {
//     assert (hash_table);

//     size_t num_of_elems = 0;

//     for (size_t i = 0; i < ((size_t) HASH_TABLE_SIZE_); i++)
//         num_of_elems = ((HASH_TABLE_CELL_ + i) -> list_size);

//     const double average_num_of_elems = ((double) num_of_elems) / ((double) HASH_TABLE_SIZE_);

//     double variance = 0;

//     for (size_t i = 0; i < ((size_t) HASH_TABLE_SIZE_); i++)
//         variance += pow (((double) ((HASH_TABLE_CELL_ + i) -> list_size)) - average_num_of_elems, 2);

//     variance /= ((double) HASH_TABLE_SIZE_) - 1;  

//     return variance;
// }

HashTableFuncStatus test_hash_functions (const char* input_file_name) 
{
    assert (input_file_name);

    HashTable hash_table = {};
    init_hash_table (&hash_table, DEFAULT_HASH_TABLE_CAPACITY);

    if (read_hash_table_data (input_file_name, &hash_table, const_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table);
    HASH_ALGORITHM_VAR_PRINT (&hash_table, "Const hash");
    clear_hash_table         (&hash_table);

    if (read_hash_table_data (input_file_name, &hash_table, first_sym_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table);
    HASH_ALGORITHM_VAR_PRINT (&hash_table, "First symbol hash");
    clear_hash_table         (&hash_table);

    if (read_hash_table_data (input_file_name, &hash_table, len_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table);
    HASH_ALGORITHM_VAR_PRINT (&hash_table, "Length hash");
    clear_hash_table         (&hash_table);

    HashTable hash_table_cap_101 = {};
    init_hash_table (&hash_table_cap_101, 101);

    if (read_hash_table_data (input_file_name, &hash_table_cap_101, ascii_sum_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table_cap_101);
    HASH_ALGORITHM_VAR_PRINT (&hash_table_cap_101, "Ascii sum hash, hash table capacity = 101");

    dtor_hash_table          (&hash_table_cap_101);

    if (read_hash_table_data (input_file_name, &hash_table, ascii_sum_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table);
    HASH_ALGORITHM_VAR_PRINT (&hash_table, "Ascii sum hash, load factor ~= 7");
    clear_hash_table         (&hash_table);

    if (read_hash_table_data (input_file_name, &hash_table, ascii_avg_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table);
    HASH_ALGORITHM_VAR_PRINT (&hash_table, "Ascii sum div len hash");
    clear_hash_table         (&hash_table);

    if (read_hash_table_data (input_file_name, &hash_table, ror_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table);
    HASH_ALGORITHM_VAR_PRINT (&hash_table, "Ror hash");
    clear_hash_table         (&hash_table);

    if (read_hash_table_data (input_file_name, &hash_table, rol_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table);
    HASH_ALGORITHM_VAR_PRINT (&hash_table, "Rol hash");
    clear_hash_table         (&hash_table);

    if (read_hash_table_data (input_file_name, &hash_table, murmur_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table);
    HASH_ALGORITHM_VAR_PRINT (&hash_table, "Murmur hash");
    clear_hash_table         (&hash_table);

    if (read_hash_table_data (input_file_name, &hash_table, crc32_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    dump_load_hash_tableL    (&hash_table);
    HASH_ALGORITHM_VAR_PRINT (&hash_table, "Crc32 hash");

    dtor_hash_table (&hash_table);

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus test_hash_table_search (const char* input_file_name) 
{
    assert (input_file_name);

    HashTable hash_table = {};
    init_hash_table (&hash_table, DEFAULT_HASH_TABLE_CAPACITY);

    // if (read_hash_table_data (input_file_name, &hash_table, crc32_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
    //     return HASH_TABLE_FUNC_STATUS_FAIL;

    if (read_hash_table_data (input_file_name, &hash_table, murmur_hash) == HASH_TABLE_FUNC_STATUS_FAIL)
        return HASH_TABLE_FUNC_STATUS_FAIL;

    FILE* data_file = NULL;

    if (!(data_file = fopen (generate_prepared_filename (input_file_name), "r"))) 
    {
        if (prepare_text (input_file_name) == PREPARING_FUNC_STATUS_FAIL)
            return HASH_TABLE_FUNC_STATUS_FAIL;

        data_file = fopen (generate_prepared_filename (input_file_name), "r");
    }

    Words words_from_file = {};    
    init_word_buffer (data_file, &words_from_file);
    
    int64_t cycle_start = __rdtsc();
 
    benchmark_hash_table (&hash_table, &words_from_file);

    int64_t cycle_end = __rdtsc();

    dtor_word_buffer (&words_from_file);
    
    fclose (data_file);
    data_file = NULL;

    printf ("Hash table find benchmark, %d times\n"
            "Initial CPU cycle     = %" PRId64 "\n"
            "End CPU cycle         = %" PRId64 "\n"
            "Cycles to compute all = %" PRId64 "\n",
            MAX_BENCHMARK_COMP_NUM,
            cycle_start, cycle_end, cycle_end - cycle_start);

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus benchmark_hash_table (HashTable* hash_table, Words* words) 
{
    assert (hash_table);
    assert (words);
    assert (words->word);

    for (size_t i = 0; i < MAX_BENCHMARK_COMP_NUM; i++) 
    {
        char* volatile curr_word = (words->word);

        for (size_t word_num = 0; word_num < ((size_t) words->num_of_words); word_num++) 
        {
            volatile HashTableFuncStatus find_status = find_in_hash_table (hash_table, curr_word);
            curr_word += MAX_WORD_LENGTH;
        }
    }

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus init_word_buffer (FILE* data_file, Words* words) 
{
    assert (data_file);
    assert (words);

    for (; !feof (data_file); (words->num_of_words)++)
        fscanf (data_file, "%*s");

    (words->word) = (char*) calloc ((words->num_of_words), MAX_WORD_LENGTH);

    fseek (data_file, 0, SEEK_SET);

    for (size_t i = 0; !feof (data_file); i++)
        fscanf (data_file, "%s", (words->word) + i * MAX_WORD_LENGTH);

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus dtor_word_buffer (Words* words) 
{
    assert (words);

    free (words->word);
    (words->word) = NULL;   
   
    words->num_of_words = 0;

    return HASH_TABLE_FUNC_STATUS_OK;
}