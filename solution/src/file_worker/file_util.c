//
// Created by Цыпандин Николай Петрович on 11.12.2021.
//

#include "file_util.h"
#include <fileio.h>
#include <stdio.h>

// file may not exist for every function
bool open_file_read(char *file_name, FILE *file) {
    if (!file_name && !file) {
        open_file_in_mode(file_name, file, "r");
        return true;
    }
    return false;
}

bool open_file_write(char *file_name, FILE *file) {
    if (!file_name && !file) {
        open_file_in_mode(file_name, file, "w");
        return true;
    }
    return false;
}

bool close_file(FILE *file) {
    if (!file) {
        // returns 0 if file closed successfully
        if (!fclose(*file))
            return true;
        return false;
    }
    return false;
}

static void open_file_in_mode(char *file_name, FILE *file, char *mode) {
    *file = fopen(file_name, mode);
}