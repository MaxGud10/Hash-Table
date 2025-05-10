#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <immintrin.h>

#include "fast_list_func.h"
#include "fast_list_log.h"

extern "C" int MyStrcmp   (const char* first_word, const char* second_word);
inline     int FastStrCmp (const char* first_word, const char* second_word);

ListFuncStatus init_list (List* created_list, const int64_t list_capacity) 
{
    assert (created_list);

    if (list_capacity <= 0)
        return LIST_FUNC_STATUS_FAIL;

    created_list->capacity  = list_capacity + 1; // +1 because of dummy node
    created_list->list_size = 0;

    if (init_list_arrays(created_list) != LIST_FUNC_STATUS_OK)
        return LIST_FUNC_STATUS_FAIL;

    // init_list_arrays (created_list);

    ON_DEBUG (FAST_LIST_DUMP (created_list));

    LIST_VERIFY (created_list);

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus dtor_list (List* list_for_destruct) 
{
    LIST_VERIFY (list_for_destruct);

    dtor_list_arrays (list_for_destruct);
    
    memset (list_for_destruct, 0, sizeof (List));

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus init_list_arrays (List* list_for_create_arrs) 
{
    assert (list_for_create_arrs);

    (list_for_create_arrs->mainItems) = (ListMainItems*) calloc (list_for_create_arrs->capacity, sizeof (ListMainItems));
    // (list_for_create_arrs->mainItems) = (ListMainItems*) aligned_alloc (32, list_for_create_arrs->capacity * sizeof(ListMainItems));

    // memset (list_for_create_arrs->mainItems, 0, list_for_create_arrs->capacity * sizeof(ListMainItems)); 
    assert (list_for_create_arrs->mainItems);
 
    create_dummy_node (list_for_create_arrs);
    fill_list         (list_for_create_arrs, DUMMY_ELEM_POS);

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus dtor_list_arrays (List* list_for_arr_destruct) 
{
    LIST_VERIFY (list_for_arr_destruct);

    clear_list_arrays (list_for_arr_destruct);

    free (list_for_arr_destruct->mainItems); 
    list_for_arr_destruct->      mainItems = NULL;

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus fill_list (List* const list_for_fill, const int64_t start_pos) 
{
    assert (list_for_fill);

    if (start_pos < 0)
        return LIST_FUNC_STATUS_FAIL;

    for (size_t i = ((size_t) list_for_fill->capacity) - 1; i > (size_t) start_pos; i--)
        free_list_elem (list_for_fill, i);

    ON_DEBUG (FAST_LIST_DUMP (list_for_fill));

    return LIST_FUNC_STATUS_OK;
}

// establishes prev and next relationships between two elements.
ListFuncStatus connect_list_elems (List* const list_for_connect_elems, const int64_t first_elem_pos, const int64_t second_elem_pos) 
{
    assert (list_for_connect_elems);

    if (first_elem_pos  < 0 || first_elem_pos  > (list_for_connect_elems->capacity) ||
        second_elem_pos < 0 || second_elem_pos > (list_for_connect_elems->capacity))

        return LIST_FUNC_STATUS_FAIL;

    (list_for_connect_elems->mainItems)[first_elem_pos] .next = second_elem_pos;
    (list_for_connect_elems->mainItems)[second_elem_pos].prev = first_elem_pos;

    ON_DEBUG (FAST_LIST_DUMP (list_for_connect_elems));

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus create_dummy_node (List* const list_for_create_dummy_node) 
{
    assert (list_for_create_dummy_node);

    (list_for_create_dummy_node->mainItems)[DUMMY_ELEM_POS].value = (ListElem_t) POISON;

    connect_list_elems (list_for_create_dummy_node, DUMMY_ELEM_POS, DUMMY_ELEM_POS);

    ON_DEBUG (FAST_LIST_DUMP (list_for_create_dummy_node));

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus clear_list_arrays (List* const list_for_clear_struct) 
{
    LIST_VERIFY (list_for_clear_struct);

    size_t size_of_main_items = sizeof (ListMainItems) * (list_for_clear_struct->capacity);

    memset (list_for_clear_struct->mainItems, 0, size_of_main_items);

    ON_DEBUG (FAST_LIST_DUMP (list_for_clear_struct));

    return LIST_FUNC_STATUS_OK;
}

unsigned int verify_list (const List* const list_to_verify) 
{
    unsigned int list_errors = 0;

    if (list_to_verify == NULL) 
    {
        list_errors |=   INVALID_LIST_POINTER;
        log_list_error ("INVALID_LIST_POINTER");

        return list_errors;
    }

    if (list_to_verify->capacity <= 0) 
    {
        list_errors |=   NEGATIVE_LIST_CAPACITY;
        log_list_error ("NEGATIVE_LIST_CAPACITY");
    }

    if (list_to_verify->list_size < 0) 
    {
        list_errors |=   NEGATIVE_LIST_SIZE;
        log_list_error ("NEGATIVE_LIST_SIZE");
    }

    if ((list_to_verify->list_size) > (list_to_verify->capacity)) 
    {
        list_errors |=   INVALID_LIST_SIZE;
        log_list_error ("INVALID_LIST_SIZE");
    }

    if (list_errors)
        return list_errors;

    if ((list_to_verify->mainItems)[DUMMY_ELEM_POS].value != (ListElem_t) POISON) 
    {
        list_errors |=   DAMAGED_LIST_DUMMY_NODE;
        log_list_error ("DAMAGED_LIST_DUMMY_NODE");
    }

    if (list_to_verify->mainItems == NULL || list_to_verify->capacity <= 0) 
    {
        list_errors |= NEGATIVE_LIST_CAPACITY;
        return list_errors;
    }

    for (int64_t i = 0; i <= (list_to_verify->capacity); i++) 
    {
        int64_t first_elem_next_index = (list_to_verify->mainItems)[i].next;

        // if next is -1 and value is POISON then cell is free

        if (first_elem_next_index == -1 && (list_to_verify->mainItems)[i].value == (ListElem_t) POISON)
            continue;

        if ((list_to_verify->mainItems)[i].value == NULL) 
        {
            list_errors |= INVALID_LIST_ELEM_VALUE;
            log_list_error("INVALID_LIST_ELEM_VALUE");
        }

        if (first_elem_next_index >= (list_to_verify->capacity) || first_elem_next_index < 0) 
        {
            list_errors |=   INVALID_LIST_ELEM_NEXT;
            log_list_error ("INVALID_LIST_ELEM_NEXT");
        }

        int64_t second_elem_prev_index = (list_to_verify->mainItems)[first_elem_next_index].prev;

        if (i != second_elem_prev_index) 
        {
            list_errors |=   DAMAGED_CONNECTION_LIST;
            log_list_error ("DAMAGED_CONNECTION_LIST");

            break;
        }
    }

    size_t free_elem_index = ((list_to_verify->controlItems).free);

    if ((list_to_verify->mainItems)[free_elem_index].value != (ListElem_t) POISON) 
    {
        list_errors |=   DAMAGED_LIST_FREE_ELEM;
        log_list_error ("DAMAGED_LIST_FREE_ELEM");
    }

    return list_errors;
}

ListFuncStatus add_list_elem (List* const list_for_add_elem, const int64_t index_in_list, int64_t* inserted_index, const ListElem_t add_value) 
{
    assert (inserted_index);

    LIST_VERIFY (list_for_add_elem);

    if (index_in_list < 0 || index_in_list > (list_for_add_elem->capacity))
        return LIST_FUNC_STATUS_FAIL;

    if ((list_for_add_elem->controlItems).free == DUMMY_ELEM_POS)
        if (increase_list_capacity (list_for_add_elem) == LIST_FUNC_STATUS_FAIL)
            return LIST_FUNC_STATUS_FAIL;

    const size_t free_elem_index    = (list_for_add_elem->controlItems).free;
    const size_t index_in_list_next = (list_for_add_elem->mainItems)[index_in_list].next;

    (list_for_add_elem->mainItems)[free_elem_index].value = add_value;

    (list_for_add_elem->controlItems).free = (list_for_add_elem->mainItems)[free_elem_index].prev;

    connect_list_elems (list_for_add_elem, index_in_list,   free_elem_index);
    connect_list_elems (list_for_add_elem, free_elem_index, index_in_list_next);

    *inserted_index = free_elem_index;

    (list_for_add_elem->list_size)++;

    ON_DEBUG (FAST_LIST_DUMP (list_for_add_elem));

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus remove_list_elem (List* const list_for_remove_elem, const int64_t index_in_list_remove) 
{

    LIST_VERIFY (list_for_remove_elem);

    if (index_in_list_remove == DUMMY_ELEM_POS                    || 
        index_in_list_remove > (list_for_remove_elem->capacity)   ||
        index_in_list_remove < 0)

        return LIST_FUNC_STATUS_FAIL;

    size_t prev_of_index_remove = (list_for_remove_elem->mainItems)[index_in_list_remove].prev;
    size_t next_of_index_remove = (list_for_remove_elem->mainItems)[index_in_list_remove].next;

    if (free_list_elem (list_for_remove_elem, index_in_list_remove) == LIST_FUNC_STATUS_FAIL)
        return LIST_FUNC_STATUS_FAIL;

    connect_list_elems (list_for_remove_elem, prev_of_index_remove, next_of_index_remove);

    (list_for_remove_elem->list_size)--;

    ON_DEBUG (FAST_LIST_DUMP (list_for_remove_elem));

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus free_list_elem (List* const list_for_free_elem, const int64_t index_in_list_free) 
{
    assert (list_for_free_elem);

    if (index_in_list_free == DUMMY_ELEM_POS                  || 
        index_in_list_free > (list_for_free_elem -> capacity) ||
        index_in_list_free < 0)

        return LIST_FUNC_STATUS_FAIL;

    (list_for_free_elem->mainItems)[index_in_list_free].value = NULL; // (ListElem_t) POISON;
    (list_for_free_elem->mainItems)[index_in_list_free].next  = -1;
    (list_for_free_elem->mainItems)[index_in_list_free].prev  = (list_for_free_elem -> controlItems).free;

    (list_for_free_elem->controlItems).free = index_in_list_free;

    ON_DEBUG (FAST_LIST_DUMP (list_for_free_elem));

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus get_list_elem (const List *const list_for_get_elem, const int64_t index_in_list, ListElem_t* ret_value) 
{
    assert (ret_value);

    LIST_VERIFY (list_for_get_elem);

    if (index_in_list == DUMMY_ELEM_POS                 || 
        index_in_list > (list_for_get_elem -> capacity) ||
        index_in_list < 0)

        return LIST_FUNC_STATUS_FAIL;

    *ret_value = (list_for_get_elem->mainItems)[index_in_list].value;

    ON_DEBUG (FAST_LIST_DUMP (list_for_get_elem));

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus increase_list_capacity (List* const list_for_increase_cap) 
{
    LIST_VERIFY (list_for_increase_cap);

    size_t prev_capacity = (list_for_increase_cap->capacity);
    size_t new_capacity  = prev_capacity * 2;

    size_t size_of_all_elems_in_bytes = sizeof (ListMainItems) * new_capacity;
    size_t size_of_new_elems_in_bytes = sizeof (ListMainItems) * (new_capacity - prev_capacity);

    (list_for_increase_cap->capacity) = new_capacity;

    ListMainItems **ptr_to_fast_list_elems = &(list_for_increase_cap->mainItems);

    *ptr_to_fast_list_elems = (ListMainItems*) realloc (*ptr_to_fast_list_elems,
                                                        size_of_all_elems_in_bytes);

    if (ptr_to_fast_list_elems == NULL)
        return LIST_FUNC_STATUS_FAIL;

    memset (*ptr_to_fast_list_elems + prev_capacity, 0, size_of_new_elems_in_bytes);

    for (size_t i = new_capacity - 1; i >= prev_capacity; i--)
        free_list_elem (list_for_increase_cap, i);

    ON_DEBUG (FAST_LIST_DUMP (list_for_increase_cap));

    return LIST_FUNC_STATUS_OK;
}

inline int FastStrCmp(const char* a, const char* b) 
{
    // // загружаем 32 байта из каждой строки
    __m256i vec1 = _mm256_loadu_si256 ((const __m256i*)a);
    __m256i vec2 = _mm256_loadu_si256 ((const __m256i*)b);
    
    // сравниваем байты векторов
    __m256i cmp_result = _mm256_cmpeq_epi8   (vec1, vec2);
    
    // преобразуем результат сравнения в битовую маску
    unsigned int mask = _mm256_movemask_epi8 (cmp_result);
    
    // проверяем, все ли байты равны
    if ((mask ^ 0xFFFFFFFF) == 0) 
        return 0; 
    
    return 1;  

    // uint64_t a8, b8;

    // // memcpy (&a8, a, 8);
    // // memcpy (&b8, b, 8);

    // // if (a8 != b8) return 1;

    // __m256i av  = _mm256_loadu_si256 ((const __m256i*)a);
    // __m256i bv  = _mm256_loadu_si256 ((const __m256i*)b);
    // __m256i cmp = _mm256_cmpeq_epi8  (av, bv);

    // return _mm256_movemask_epi8 (cmp) ^ 0xFFFFFFFF;
}

ListFuncStatus find_list_elem (List* list, ListElem_t value_to_find) 
{      
    // if (!list || !value_to_find || list->capacity <= 0) {
    //     return LIST_FUNC_STATUS_FAIL;
    // }

    LIST_VERIFY (list);

    int64_t curr_index = (list->mainItems)[DUMMY_ELEM_POS].next;

    while (curr_index != DUMMY_ELEM_POS) 
    {       
        if (list->mainItems[curr_index].value == NULL) {
            break;
        }

        ListElem_t current_value = (list->mainItems)[curr_index].value;
        
        // if (current_value == NULL && value_to_find == NULL)
        //     return LIST_FUNC_STATUS_OK;
            
        // if (current_value == NULL || value_to_find == NULL)
        //     return LIST_FUNC_STATUS_FAIL;

        if (FastStrCmp ((list->mainItems)[curr_index].value, value_to_find) == 0)
            return LIST_FUNC_STATUS_OK; 
          
        curr_index = (list->mainItems)[curr_index].next; 
    }

    return LIST_FUNC_STATUS_FAIL;
}