//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_H

#include "pixel.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct image {
    uint64_t width, height;
    struct pixel *data;
};

struct image *create_image(uint64_t width, uint64_t height);

void delete_image(struct image *image);

struct maybe_pixel get_pixel(const struct image *image, size_t row, size_t column);

bool set_pixel(const struct image *image, struct pixel pixel, size_t row, size_t column);

#endif //ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
