#include "file_worker/file_util.h"
#include "input_format/bmp.h"
#include "transformations/rotate.h"
#include <stdio.h>

static void log(const char *message) {
    fprintf(stderr, "%s\n", message);
}

static void log_stdin(const char *message) {
    printf("%s\n", message);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        log("Invalid count of arguments");
        return 1;
    }
    log_stdin("PROGRAM STARTED");
    FILE *input_file = NULL;
    FILE *output_file = NULL;
    struct image *transformed_image = NULL;
    struct image *read_image = NULL;

    enum io_return_code code = open_file_read(argv[1], &input_file);
    log(io_return_code_string[code]);
    if (code != OPEN_OK)
        return 1;

    enum read_status read_status = from_bmp(input_file, &read_image);
    log(read_status_string[read_status]);
    if (read_status != READ_OK)
        return 1;

    transformed_image = rotate_image(read_image);
    delete_image(read_image);
    close_file(&input_file);

    if (!transformed_image) {
        log("Error, can't transform image");
        return 1;
    } else {
        log("Image is successfully transformed");
    }

    code = open_file_write(argv[2], &output_file);
    log(io_return_code_string[code]);
    if (code != OPEN_OK)
        return 1;

    enum write_status write_status = to_bmp(output_file, transformed_image);
    log(write_status_string[write_status]);
    if (write_status != WRITE_OK)
        return 1;
    log_stdin("SUCCESS");
    delete_image(transformed_image);
    close_file(&output_file);
    log_stdin("PROGRAM ENDS WITH 0 RETURN CODE");
    return 0;
}
