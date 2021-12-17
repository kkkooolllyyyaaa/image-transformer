//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_H

#include "../image/image.h"
#include "../util/util.h"
#include "bmp_header.h"

#include <stdio.h>

static const uint16_t valid_signature;

/*  deserializer   */
enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_CONTINUE
};

extern const char *read_status_string[];

/*  serializer   */
enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR,
    WRITE_CONTINUE
};
extern const char *write_status_string[];

enum read_status from_bmp(FILE *in, struct image **img);

enum write_status to_bmp(FILE *out, const struct image *img);

#endif //ASSIGNMENT_IMAGE_ROTATION_BMP_H
