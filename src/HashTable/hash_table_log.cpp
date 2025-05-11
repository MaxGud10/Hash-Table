#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

#include "../DoubleLinkedList/fast_list_log.h"

#include "hash_table_dsl.h"
#include "hash_table_func.h"
#include "hash_table_log.h"

HashTableFuncStatus graph_dump_hash_table (const HashTable* hash_table) 
{
    assert (hash_table);

    FILE* hash_table_dot = fopen (HASH_TABLE_DOT_FILE_NAME, "w"); 

    begin_dot_file_hash  (hash_table_dot);
    print_dot_hash_table (hash_table_dot, hash_table);
    end_dot_hash_table   (hash_table_dot);

    fclose (hash_table_dot);
    hash_table_dot = NULL;

    create_images_dir ();
    create_image ("hash_table");

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus begin_dot_file_hash (FILE* hash_table_dot) 
{ 
    assert  (hash_table_dot);

    fprintf (hash_table_dot, "digraph HashTable {\n"
                             "rankdir = LR;\n");

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus end_dot_hash_table (FILE* hash_table_dot) 
{
    assert  (hash_table_dot);

    fprintf (hash_table_dot, "}");

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus print_dot_hash_table (FILE* hash_table_dot, const HashTable* hash_table) 
{
    assert (hash_table_dot);
    assert (hash_table);

    for (int64_t i = HASH_TABLE_SIZE_ - 1; i >= 0; i--) 
    {
        fprintf        (hash_table_dot, "subgraph cluster_%zu {\n"
                                        "label = \"cell #%zu\"\n", i, i);                  
        print_dot_file (hash_table_dot, HASH_TABLE_CELL_ + i);
        fprintf        (hash_table_dot, "};\n");
    } 

    return HASH_TABLE_FUNC_STATUS_OK;
}

HashTableFuncStatus dump_load_hash_tableL (const HashTable* hash_table) 
{
    assert (hash_table);

    FILE* load_dump = fopen (generate_dump_filename(), "w");

    for (size_t i = 0; i < (size_t) HASH_TABLE_SIZE_; i++)
    {
        //fprintf(load_dump, "%zu ; %" PRId64 " (free=%d)\n", i, (HASH_TABLE_CELL_ + i)->list_size, (HASH_TABLE_CELL_ + i)->controlItems.free);

        fprintf (load_dump, "%zu ; %" PRId64 "\n",          i, (HASH_TABLE_CELL_ + i)->list_size);
    }
    

    fclose (load_dump);
    load_dump = NULL;

    return HASH_TABLE_FUNC_STATUS_OK;
}

const char* generate_dump_filename (void) 
{
    static char load_file_name[MAX_FILE_NAME_LENGTH] = {};
    static int  file_number                          = 0;

    snprintf (load_file_name, MAX_FILE_NAME_LENGTH, "load_dump_%d.txt", file_number);

    file_number++;

    return load_file_name;
} 

HashTableFuncStatus log_variance_result (const double variance) 
{
    printf ("variance of elements in hash table = %.2lf\n", variance);

    return HASH_TABLE_FUNC_STATUS_OK;
}