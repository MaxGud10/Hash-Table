#ifndef HASH_TABLE_LOG_H
#define HASH_TABLE_LOG_H

#define HASH_TABLE_DOT_FILE_NAME  "hash_table_dot_file.dot"

const int MAX_FILE_NAME_LENGTH = 32;

// Visualization
HashTableFuncStatus graph_dump_hash_table (                      const HashTable* hash_table);
HashTableFuncStatus begin_dot_file_hash   (FILE* hash_table_dot);
HashTableFuncStatus end_dot_hash_table    (FILE* hash_table_dot);
HashTableFuncStatus print_dot_hash_table  (FILE* hash_table_dot, const HashTable* hash_table);


HashTableFuncStatus dump_load_hash_tableL  (const HashTable* hash_table);
const char*         generate_dump_filename (void);                             
HashTableFuncStatus log_variance_result    (const double variance);

#endif