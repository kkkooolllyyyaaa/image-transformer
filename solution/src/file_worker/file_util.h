//
// Created by Цыпандин Николай Петрович on 11.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_FILE_UTIL_H
#define ASSIGNMENT_IMAGE_ROTATION_FILE_UTIL_H

#include <stdbool.h>

// file may not exist for every function
bool open_file_read(char *file_name, FILE *file);

bool open_file_write(char *file_name, FILE *file);

bool close_file(FILE *file);

static void open_file_in_mode(char *file_name, FILE *file, char *mode);

#endif //ASSIGNMENT_IMAGE_ROTATION_FILE_UTIL_H
