#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "input_format/bmp/bmp.h"
#include "image/image.h"
#include "transformations/rotate.h"
#include "file_worker/file_util.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Invalid count of arguments\n");
        return 1;
    }

    FILE *input_file = NULL;
    FILE *output_file = NULL;
    struct image *transformed_image = NULL;

    if (open_file_read(argv[1], &input_file) == OPEN_OK) {
        struct image *read_image = NULL;
        if (from_bmp(input_file, &read_image) == READ_OK) {
            transformed_image = rotate_image(read_image);
        }
        delete_image(read_image);
        close_file(&input_file);
    }
    if (!transformed_image)
        return 0;

    if (open_file_write(argv[2], &output_file) == OPEN_OK) {
        if (to_bmp(output_file, transformed_image) == WRITE_OK) {
            printf("done");
        }
        delete_image(transformed_image);
        close_file(&output_file);
    }
    return 0;
}
