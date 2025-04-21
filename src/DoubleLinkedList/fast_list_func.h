#ifndef LIST_FUNC_H
#define LIST_FUNC_H


#include <stdint.h>

#ifndef NDEBUG
    #define LIST_VERIFY(list)   do {                                   \
                                    if (verify_list (list) != 0)    \
                                    {                                  \
                                        LIST_DUMP (list);               \
                                        return LIST_FUNC_STATUS_FAIL;  \
                                    }                                  \
                                } while (0)
#else
    #define LIST_VERIFY(list)
#endif

#define IS_ELEM_TYPE_FLOAT  0

#if IS_ELEM_TYPE_FLOAT

    #define POISON          NAN
#else

    #define POISON          0x50DEAD
#endif


#ifdef DEBUG

    #define ON_DEBUG(...)   __VA_ARGS__
#else

    #define ON_DEBUG(...)
#endif

typedef const char* ListElem_t;

struct ListMainItems 
{
    ListElem_t value;

    int64_t prev;
    int64_t next;
};

struct ListControlItems {

    int64_t free;
};

struct List 
{
    ListControlItems controlItems;

    ListMainItems*   mainItems;

    int64_t capacity;
    int64_t list_size;
};

const int64_t DUMMY_ELEM_POS = 0;

enum ListFuncStatus 
{
    LIST_FUNC_STATUS_OK,
    LIST_FUNC_STATUS_FAIL
};

enum ListErrors 
{
    INVALID_LIST_POINTER,
    INVALID_LIST_SIZE,
    NEGATIVE_LIST_CAPACITY,
    NEGATIVE_LIST_SIZE,
    DAMAGED_LIST_DUMMY_NODE,
    INVALID_LIST_ELEM_NEXT,
    DAMAGED_CONNECTION_LIST,
    DAMAGED_LIST_FREE_ELEM
};

// Basic operations with the list
ListFuncStatus init_list         (List* created_list,        const int64_t list_capacity); // creates a list of the specified capacity
ListFuncStatus dtor_list         (List* list_for_destruct); 
ListFuncStatus init_list_arrays  (List* list_for_create_arrs); // allocates memory for an array of elements
ListFuncStatus create_dummy_node (List* const list_for_create_dummy_node); // Initializes a dummy node
ListFuncStatus dtor_list_arrays  (List* list_for_arrs_destruct);    
ListFuncStatus clear_list_arrays (List* const list_for_clear_struct);
ListFuncStatus fill_list         (List* const list_for_fill, const int64_t start_pos);


// Working with elements
ListFuncStatus add_list_elem    (      List* const list_for_add_elem,    const int64_t index_in_list, int64_t* inserted_index, const ListElem_t add_value); // adds an element after the specified index
ListFuncStatus remove_list_elem (      List* const list_for_remove_elem, const int64_t index_in_list_remove); // deletes an element by index
ListFuncStatus free_list_elem   (      List* const list_for_free_elem,   const int64_t index_in_list_free);
ListFuncStatus get_list_elem    (const List* const list_for_get_elem,    const int64_t index_in_list,                                ListElem_t* ret_value); // returns the value of the element
ListFuncStatus find_list_elem   (      List* list, ListElem_t value_to_find); // searching for an element by value

// Auxiliary functions
ListFuncStatus connect_list_elems     (      List* const list_for_connect_elems, const int64_t first_elem_pos, const int64_t second_elem_pos); // connects two elements
ListFuncStatus increase_list_capacity (      List* const list_for_increase_cap); // Increases the capacity of the list
unsigned int   verify_list            (const List* const list_to_verify);


#endif