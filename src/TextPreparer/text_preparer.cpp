#include <stdio.h>
#include <assert.h>

#include "text_preparer.h"

PreparingFuncStatus TextPrepare (const char *input_file_name) {

    assert (input_file_name);

    FILE *input_file = fopen (input_file_name, "r");

    if (!input_file) {

        fprintf (stderr, "TextPrepare: No file matching the name \"%s\" was found.\n", input_file_name);
        return PREPARING_FUNC_STATUS_FAIL;
    }

    FILE *output_file = fopen (TextPreparedFileNameGen (input_file_name), "w");
    assert (output_file);

    char word[MAX_WORD_LENGTH] = {};

    for (; !feof (input_file);) {

        int fscanf_status = fscanf (input_file, " %[^-;,.\"*:?\n\r!() ]", word); 

        if (fscanf_status != EOF && fscanf_status != 0)
            fprintf (output_file, "%s\n", word); 

        if (fscanf_status != EOF)
            fgetc (input_file);
    }

    fclose (input_file);
    input_file = NULL;

    fclose (output_file);
    output_file = NULL;

    return PREPARING_FUNC_STATUS_OK;
}

const char *TextPreparedFileNameGen (const char *input_file_name) {

    assert (input_file_name);

    static char file_name[TXT_PREP_MAX_FILE_NAME_LENGTH] = {};

    snprintf (file_name, TXT_PREP_MAX_FILE_NAME_LENGTH, "prep_%s", input_file_name);

    return file_name;
}