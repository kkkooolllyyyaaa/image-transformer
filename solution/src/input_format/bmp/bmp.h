//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_H

#include <stdio.h>
#include "../../image/image.h"
#include "bmp_header.h"

static const uint16_t valid_signature;

/*  deserializer   */
enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    OK_CONTINUE
};

/*  serializer   */
enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum read_status from_bmp(FILE *in, struct image **img);

enum write_status to_bmp(FILE *out, const struct image *img);

static enum read_status header_read(FILE *in, struct bmp_header *header);

static enum read_status header_check_valid(struct bmp_header *header);

static enum read_status read_pixels(FILE *file, struct image *image);

#endif //ASSIGNMENT_IMAGE_ROTATION_BMP_H
