//
// Created by Цыпандин Николай Петрович on 11.12.2021.
//

#include <fileio.h>
#include <stdio.h>
#include "file_util.h"

enum io_return_code open_file_read(const char *file_name, FILE **file) {
    char *mode = "r";
    return open_file_in_mode(file_name, file, mode);
}

enum io_return_code open_file_write(const char *file_name, FILE **file) {
    char *mode = "w";
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