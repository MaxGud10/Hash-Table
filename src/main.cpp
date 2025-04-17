#include <stdio.h>
#include <assert.h>

#include "DoubleLinkedList/fast_list_func.h"
#include "DoubleLinkedList/fast_list_log.h"

#include "HashTable/hash_func.h"
#include "HashTable/hash_table_func.h"
#include "HashTable/hash_table_log.h"

#include "TextPreparer/text_preparer.h"

int main (const int argc, const char *argv[]) {

    if (argc < 2 || argc > 2) {

        fprintf (stderr, "Pass only one argument (file to read), please.\n");
        return -1;
    }

    HashTableTestHashes (argv[1]);

    return 0;
}