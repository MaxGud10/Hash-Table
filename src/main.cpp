#include <stdio.h>
#include <assert.h>

#include "DoubleLinkedList/fast_list_func.h"
#include "DoubleLinkedList/fast_list_log.h"

#include "HashTable/hash_func.h"
#include "HashTable/hash_table_func.h"
#include "HashTable/hash_table_log.h"

#include "TextPreparer/text_preparer.h"

// void test_hash_func() 
// {
//     const char* test_words[] = {"apple", "banana", "orange", NULL};
    
//     for (int i = 0; test_words[i] != NULL; i++) 
//     {
//         printf("Word: %s\n", test_words[i]);
//         printf("  const_hash: %u\n", const_hash(test_words[i]));
//         printf("  first_sym_hash: %u\n", first_sym_hash(test_words[i]));
//         printf("  len_hash: %u\n", len_hash(test_words[i]));
//         printf("  ascii_sum_hash: %u\n", ascii_sum_hash(test_words[i]));
//         printf("  ascii_avg_hash: %u\n", ascii_avg_hash(test_words[i]));
//         printf("  rol_hash: %u\n", rol_hash(test_words[i]));
//         printf("  ror_hash: %u\n", ror_hash(test_words[i]));
//         printf("  murmur_hash: %u\n", murmur_hash(test_words[i]));
//         printf("  crc32: %u\n", crc32_hash (test_words[i]));
//     }
// }

int main (const int argc, const char *argv[]) 
{
    if (argc < 2 || argc > 2) 
    {

        fprintf (stderr, "Pass only one argument (file to read), please.\n");
        return -1;
    }      
    

    //test_hash_func();

    // test_hash_functions (argv[1]);

    test_hash_table_search (argv[1]);

    return 0;
}
