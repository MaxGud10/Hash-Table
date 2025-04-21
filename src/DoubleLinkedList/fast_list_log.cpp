#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#include "fast_list_log.h"
#include "fast_list_func.h"


FILE* LOG_FILE = open_log_file ("fast_list_log.txt");

FILE* open_log_file (const char *log_file_name) 
{
    assert (log_file_name);

    FILE*   log_file_ptr = fopen (log_file_name, "w");

    assert (log_file_ptr);

    atexit (close_log_file);
    return log_file_ptr;
}

void close_log_file (void) 
{
    if (LOG_FILE)
        fclose (LOG_FILE);

    LOG_FILE = NULL;
}

int create_images_dir (void) 
{
    return system ("mkdir images");
}

int create_image (const char* struct_name) 
{
    return system (generate_image_cmd (struct_name, generate_image_name (struct_name)));
}

const char* generate_image_name (const char *struct_name) 
{
    assert (struct_name);

    static int  image_number = 0;

    static char image_name[MAX_IMAGE_NAME_LENGTH + 1] = {};

    memset (image_name, 0, MAX_IMAGE_NAME_LENGTH + 1);

    sprintf (image_name, "%s_img_%d.png", struct_name, image_number++);

    return image_name;
}

const char* generate_image_cmd (const char* struct_name, const char* image_name) 
{
    assert (struct_name);
    assert (image_name);

    static char command_to_create_image[MAX_COMMAND_LENGTH + 1] = {};

    memset  (command_to_create_image, 0, MAX_COMMAND_LENGTH + 1);
    sprintf (command_to_create_image, "dot %s_dot_file.dot -T png -o images\\%s", struct_name, image_name);

    return command_to_create_image;
}

ListFuncStatus dump_list (const List* list_for_dump, const char* file_called, const char* func_called, const int line_called, const char* list_name) 
{
    LOG_PRINT (LOG_FILE, "List[0x%p] \"%s\" from %s(%d) %s() \n", list_for_dump, list_name,
                          file_called, line_called, func_called);

    LOG_PRINT (LOG_FILE, "free = %"     PRId64 "\n", (list_for_dump->controlItems).free);
    LOG_PRINT (LOG_FILE, "size = %"     PRId64 "\n", (list_for_dump->list_size   ));
    LOG_PRINT (LOG_FILE, "capacity = %" PRId64 "\n", (list_for_dump->capacity    ));

    LOG_PRINT (LOG_FILE, "Elements:\n");

    print_list_elems (list_for_dump);

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus print_list_elems (const List* list_for_print) 
{
    assert (list_for_print);

    for (size_t i = 0; i < (size_t) (list_for_print->capacity); i++) 
    {
        LOG_PRINT (LOG_FILE,     "Element %zu: \n",              i);

        if ((list_for_print->mainItems)[i].value != (ListElem_t) POISON)
            LOG_PRINT (LOG_FILE, "value = " LIST_EL_FORMAT "\n", (list_for_print->mainItems)[i].value);
        else
            LOG_PRINT (LOG_FILE, "value = (POISON)\n");

        LOG_PRINT (LOG_FILE,     "next = %" PRId64 "\n",         (list_for_print->mainItems)[i].next);
        LOG_PRINT (LOG_FILE,     "prev = %" PRId64 "\n\n",       (list_for_print->mainItems)[i].prev);
    }

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus log_list_error (const char* error_text) 
{
    assert (error_text);

    LOG_PRINT (LOG_FILE, "An error %s occurred. \n", error_text);

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus print_dot_file (FILE* graph_dump_file, const List* list) 
{
    assert (graph_dump_file);

    LIST_VERIFY (list);

    static int list_num = 0;

    print_dot_info   (graph_dump_file, list, list_num);
    print_dot_elems  (graph_dump_file, list, list_num);

    center_dot_elems (graph_dump_file, list, list_num);
    draw_dot_arrows  (graph_dump_file, list, list_num);

    list_num++;

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus dump_list_graph (const List* list_for_graph_dump) 
{
    LIST_VERIFY (list_for_graph_dump);

    FILE* graph_dump_file = fopen (LIST_DOT_FILE_NAME, "w");

    if (graph_dump_file == NULL)
        return LIST_FUNC_STATUS_FAIL;

    begin_dot_file (graph_dump_file                     );
    print_dot_file (graph_dump_file, list_for_graph_dump);
    end_dot_file   (graph_dump_file                     );

    fclose (graph_dump_file);
            graph_dump_file = NULL;

    create_images_dir ();
    create_image      ("list");

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus begin_dot_file (FILE* dot_file) 
{
    assert (dot_file);

    fprintf(dot_file, "digraph G{\n"
                      "rankdir = LR;\n"
                      "graph [bgcolor = white];\n");

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus end_dot_file (FILE *dot_file) 
{
    assert (dot_file);

    fprintf(dot_file, "\n}\n");

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus print_dot_info (FILE *dot_file, const List *list_for_info, const int list_num) 
{
    assert (dot_file);

    fprintf(dot_file, "Linfo_%d [shape = record, style = filled, fillcolor = \"yellow\","
                      "label = \"FREE: %" PRId64 " | SIZE: %" PRId64 " | CAPACITY: %" PRId64 "\","
                      "fontcolor = \"black\", fontsize = 22];\n",
                      list_num, (list_for_info->controlItems).free, 
                                list_for_info->list_size,
                                list_for_info->capacity);

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus color_dot_dummy (FILE* dot_file, const List* list_for_output_dummy) 
{
    assert (dot_file);
    assert (list_for_output_dummy);

    fprintf(dot_file, "fillcolor = gray, color = black, ");

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus color_dot_elem (FILE* dot_file_for_color, const List* list_for_choose_color, const size_t index) 
{
    assert (dot_file_for_color);
    assert (list_for_choose_color);

    if ((list_for_choose_color->mainItems)[index].value == (ListElem_t) POISON)
        fprintf (dot_file_for_color, "fillcolor = \"crimson\", color = black,");

    else
        fprintf (dot_file_for_color, "fillcolor = \"lightgreen\", color = darkgreen,");

    return LIST_FUNC_STATUS_OK;
}


ListFuncStatus print_dot_elems (FILE* dot_file, const List* list_for_output_elems, const int list_num) 
{
    assert (dot_file);
    assert (list_for_output_elems);

    for (size_t i = 0; i < (size_t) (list_for_output_elems->capacity); i++) 
    {
        fprintf (dot_file, "L%zu_%d [shape=Mrecord, style=filled, ", i, list_num);

        if (i != DUMMY_ELEM_POS)
            color_dot_elem (dot_file, list_for_output_elems, i);

        else
            color_dot_dummy (dot_file, list_for_output_elems);

        fprintf (dot_file, " label=\" ");

        if ((list_for_output_elems->mainItems)[i].value == (ListElem_t) POISON) 
        {
            fprintf(dot_file, "index: %zu | value: (POISON) | next: %" PRId64 "| prev: %" PRId64 "\" ];\n",
                              i,
                              (list_for_output_elems->mainItems)[i].next,
                              (list_for_output_elems->mainItems)[i].prev);
        }

        else 
        {
            fprintf(dot_file, "index: %zu | value: " LIST_EL_FORMAT "| next: %" PRId64 "| prev: %" PRId64 "\" ];\n",
                              i,
                              (list_for_output_elems->mainItems)[i].value,
                              (list_for_output_elems->mainItems)[i].next,
                              (list_for_output_elems->mainItems)[i].prev);
        }
    }

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus draw_dot_arrows (FILE* dot_file_for_arrows, const List* list_for_draw_arrows, const int list_num) 
{
    assert (dot_file_for_arrows);
    assert (list_for_draw_arrows);

    for (size_t i = 0; i < (size_t) (list_for_draw_arrows->capacity); i++) 
    {
        if ((list_for_draw_arrows->mainItems)[i].next  == -1 &&
            (list_for_draw_arrows->mainItems)[i].value == (ListElem_t) POISON)

            fprintf (dot_file_for_arrows, "L%zu_%d -> L%" PRId64 "_%d [weight = 0, color = \"red\"];\n",
                                          i, list_num, (list_for_draw_arrows->mainItems)[i].prev, list_num);

        else 
        {
            fprintf (dot_file_for_arrows, "L%zu_%d -> L%" PRId64 "_%d [weight = 0, color = \"blue\"];\n",
                                          i, list_num, (list_for_draw_arrows->mainItems)[i].next, list_num);

            fprintf (dot_file_for_arrows, "L%zu_%d -> L%" PRId64 "_%d [weight = 0, color = \"green\"];\n",
                                          i, list_num, (list_for_draw_arrows->mainItems)[i].prev, list_num);
        }
    }

    return LIST_FUNC_STATUS_OK;
}

ListFuncStatus center_dot_elems (FILE* dot_file_for_center, const List* list_for_center_elems, const int list_num) 
{
    assert (dot_file_for_center);
    assert (list_for_center_elems);

    fprintf (dot_file_for_center, "Linfo_%d -> L0_%d [color = \"white\", style = invis];\n", list_num, list_num);

    for (size_t i = 0; i < (size_t) (list_for_center_elems -> capacity) - 1; i++) 
    {
        fprintf (dot_file_for_center, "L%zu_%d -> L%zu_%d [color = \"white\", style = invis];\n",
                                      i, list_num, i + 1, list_num);
    }

    return LIST_FUNC_STATUS_OK;
}