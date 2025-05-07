#ifndef TEXT_PREPARER_H
#define TEXT_PREPARER_H

const int TXT_PREP_MAX_FILE_NAME_LENGTH = 64;

const int MAX_WORD_LENGTH               = 32;

enum PreparingFuncStatus 
{
    PREPARING_FUNC_STATUS_OK,
    PREPARING_FUNC_STATUS_FAIL
};

PreparingFuncStatus prepare_text              (const char* input_file_name);
const char*        generate_prepared_filename (const char* input_file_name);


#endif