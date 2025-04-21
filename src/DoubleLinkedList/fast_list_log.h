#ifndef LIST_LOG_H
#define LIST_LOG_H


#include <stdio.h>

#include "fast_list_func.h"


#define LIST_NAME(list)           #list

#define LIST_DUMP(list)      dump_list (list, __FILE__, __func__, __LINE__, LIST_NAME (list))

#define LOG_PRINT(LOG_FILE, ...)  do {                                \
                                      fprintf(LOG_FILE, __VA_ARGS__); \
                                      fflush (LOG_FILE);              \
                                                                      \
                                     } while (0)

#define LIST_EL_FORMAT            "%s"

#define LIST_DOT_FILE_NAME        "list_dot_file.dot"

const int MAX_IMAGE_NAME_LENGTH = 32;
const int MAX_COMMAND_LENGTH    = 128;

// Visualization
FILE* open_log_file             (const char* log_file_name);
void  close_log_file            (void);

int create_images_dir           (void);
int create_image                (const char* struct_name);
const char* generate_image_name (const char* struct_name);
const char* generate_image_cmd  (const char* struct_name, const char* image_name);

// Dump the list
ListFuncStatus dump_list        (const List* list_for_dump, const char* file_called, const char* func_called, const int line_called, const char* list_name);
ListFuncStatus print_list_elems (const List* list_for_print); // p rints detailed information about each item in the list.
ListFuncStatus log_list_error   (                           const char* error_text); // writes an error message.

//---------------------------------- Graph dump -------------------------------------------------------------

// Graph visualization
ListFuncStatus dump_list_graph  (                           const List* list_for_graph_dump);
ListFuncStatus print_dot_file   (FILE* graph_dump_file,     const List* list);
ListFuncStatus begin_dot_file   (FILE* dot_file);
ListFuncStatus color_dot_elem   (FILE* dot_file_for_color,  const List* list_for_choose_color, const size_t index);
ListFuncStatus color_dot_dummy  (FILE* dot_file,            const List* list_for_output_dummy);
ListFuncStatus end_dot_file     (FILE* dot_file);
ListFuncStatus print_dot_info   (FILE* dot_file,            const List* list_for_info, const int list_num);
ListFuncStatus print_dot_elems  (FILE* dot_file,            const List* list_for_output_elems, const int list_num);
ListFuncStatus draw_dot_arrows  (FILE* dot_file_for_arrows, const List* list_for_draw_arrows, const int list_nums);
ListFuncStatus center_dot_elems (FILE* dot_file_for_center, const List* list_for_center_elems, const int list_num);


#endif