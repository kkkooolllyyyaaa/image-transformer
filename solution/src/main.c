#include "file_worker/file_util.h"
#include "input_format/bmp.h"
#include "transformations/rotate.h"
#include <stdio.h>

#define ERROR_CODE 1

static void log(const char *message);

static void log_stdin(const char *message);

static void clean_up(struct image *image, FILE *file);

int main(int argc, char **argv) {
    if (argc != 3) {
        log("Invalid count of arguments");
        return ERROR_CODE;
    }
    log_stdin("PROGRAM STARTED");

    FILE *input = NULL;
    char *input_filename = argv[1];
    enum io_return_code code = open_file_read(input_filename, &input);
    log(io_return_code_string[code]);
    if (code != OPEN_OK)
        return ERROR_CODE;

    struct image *read_image = NULL;
    enum read_status read_status = from_bmp(input, &read_image);
    log(read_status_string[read_status]);
    if (read_status != READ_OK)
        return ERROR_CODE;

    struct image *transformed_image = rotate_image_left(read_image);
    clean_up(read_image, input);
    if (transformed_image) {
        log("Image is successfully transformed");
    } else {
        log("Error, can't transform image");
        return ERROR_CODE;
    }

    FILE *output = NULL;
    char *output_filename = argv[2];
    code = open_file_write(output_filename, &output);
    log(io_return_code_string[code]);
    if (code != OPEN_OK)
        return ERROR_CODE;

    enum write_status write_status = to_bmp(output, transformed_image);
    log(write_status_string[write_status]);
    if (write_status != WRITE_OK)
        return ERROR_CODE;
    log_stdin("SUCCESS");
    clean_up(transformed_image, output);
    log_stdin("PROGRAM ENDS WITH 0 RETURN CODE");
    return 0;
}

static void log(const char *message) {
    fprintf(stderr, "%s\n", message);
}

static void log_stdin(const char *message) {
    printf("%s\n", message);
}

static void clean_up(struct image *image, FILE *file) {
    delete_image(image);
    close_file(&file);
}
