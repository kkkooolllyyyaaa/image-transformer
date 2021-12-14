//
// Created by Цыпандин Николай Петрович on 11.12.2021.
//
#include "file_util.h"

const char *io_return_code_string[] = {
        [OPEN_OK] = "File is successfully opened",
        [CLOSE_OK] ="File is successfully closed",
        [OPEN_ERROR]="Error when file opening",
        [CLOSE_ERROR] ="Error when file closing",
        [FILE_IS_CLOSED_ERROR]="Error, can't work with closed file",
        [INCORRECT_FILE_NAME]="Error, file name can't be null"
};

enum io_return_code open_file_read(const char *file_name, FILE **file) {
    const char *mode = "r";
    return open_file_in_mode(file_name, file, mode);
}

enum io_return_code open_file_write(const char *file_name, FILE **file) {
    const char *mode = "w";
    return open_file_in_mode(file_name, file, mode);
}

enum io_return_code close_file(FILE **file) {
    if (!*file)
        return FILE_IS_CLOSED_ERROR;
    if (fclose(*file))
        return CLOSE_ERROR;
    return CLOSE_OK;
}

static enum io_return_code open_file_in_mode(const char *file_name, FILE **file, const char *mode) {
    if (!file_name)
        return INCORRECT_FILE_NAME;
    *file = fopen(file_name, mode);
    if (!*file)
        return OPEN_ERROR;
    return OPEN_OK;
}
