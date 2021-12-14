//
// Created by Цыпандин Николай Петрович on 11.12.2021.
//

#include "rotate.h"

static coordinates get_coordinates_rotate_right(const struct image *image, uint64_t i, uint64_t j) {
    return (coordinates) {.x = image->height - j - 1, .y = i};
}

static coordinates get_coordinates_rotate_left(const struct image *image, uint64_t i, uint64_t j) {
    return (coordinates) {.x = j, .y = image->width - i - 1};
}

static struct image *rotate_image_90(const struct image *image, rotation_type type) {
    uint64_t new_width = image->height;
    uint64_t new_height = image->width;
    struct image *rotated_image = create_image(new_width, new_height);
    if (!rotated_image)
        return NULL;
    for (uint64_t i = 0; i < image->height; ++i) {
        for (uint64_t j = 0; j < image->width; ++j) {
            struct maybe_pixel pixel = get_pixel(image, i, j);
            coordinates new_coordinates = type(rotated_image, i, j);
            if (!pixel.valid || !set_pixel(rotated_image, pixel.value, new_coordinates.x, new_coordinates.y))
                return NULL;
        }
    }
    return rotated_image;
}

struct image *rotate_image_left(const struct image *image) {
    return rotate_image_90(image, get_coordinates_rotate_left);
}

struct image *rotate_image_right(const struct image *image) {
    return rotate_image_90(image, get_coordinates_rotate_right);
}
