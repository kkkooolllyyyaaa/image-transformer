//
// Created by Цыпандин Николай Петрович on 11.12.2021.
//

#include "rotate.h"

struct image *rotate_image(const struct image *image) {
    uint64_t new_width = image->height;
    uint64_t new_height = image->width;
    struct image *rotated_image = create_image(new_width, new_height);
    if (!rotated_image)
        return NULL;

    for (uint64_t i = 0; i < image->height; ++i) {
        for (uint64_t j = 0; j < image->width; ++j) {
            struct maybe_pixel pixel = get_pixel(image, i, j);
            if (pixel.valid) {
                set_pixel(rotated_image, pixel.value, new_height - j - 1, new_width - i - 1);
            } else {
                return NULL;
            }
        }
    }
    return rotated_image;
}
