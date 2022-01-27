//
// Created by Цыпандин Николай Петрович on 11.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_FILE_UTIL_H
#define ASSIGNMENT_IMAGE_ROTATION_FILE_UTIL_H

#include <stdbool.h>
#include <stdio.h>

enum io_return_code {
    OPEN_OK = 0,
    CLOSE_OK,
    OPEN_ERROR,
    CLOSE_ERROR,
    FILE_IS_CLOSED_ERROR,
    INCORRECT_FILE_NAME
};

const char* get_io_return_code_string(enum io_return_code i_r_c);

enum io_return_code open_file_read(const char *file_name, FILE **file);

enum io_return_code open_file_write(const char *file_name, FILE **file);

enum io_return_code close_file(FILE **file);

#endif //ASSIGNMENT_IMAGE_ROTATION_FILE_UTIL_H
