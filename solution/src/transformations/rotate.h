//
// Created by Цыпандин Николай Петрович on 11.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_ROTATE_H
#define ASSIGNMENT_IMAGE_ROTATION_ROTATE_H

#include "../image/image.h"

typedef struct pixel_coordinates {
    uint64_t x, y;
} coordinates;

typedef coordinates (*rotation_type)(const struct image *image, uint64_t i, uint64_t j);

struct image *rotate_image_left(const struct image *image);

struct image *rotate_image_right(const struct image *image);

#endif //ASSIGNMENT_IMAGE_ROTATION_ROTATE_H
