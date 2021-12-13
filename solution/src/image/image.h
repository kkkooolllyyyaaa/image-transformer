//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "pixel.h"

struct image {
    uint64_t width, height;
    struct pixel *data;
};

struct image *create_image(uint64_t width, uint64_t height);

void delete_image(struct image *image);

struct maybe_pixel get_pixel(const struct image *image, size_t row, size_t column);

bool set_pixel(const struct image *image, struct pixel pixel, size_t row, size_t column);

static size_t get_image_size(uint64_t width, uint64_t height);

static bool is_valid_pos(struct image image, size_t pos);

#endif //ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
