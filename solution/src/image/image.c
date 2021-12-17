//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//

#include "image.h"
#include "pixel.h"

static bool is_valid_pos(struct image image, size_t pos) {
    return pos < image.width * image.height;
}

static size_t get_image_size(uint64_t width, uint64_t height) {
    return sizeof(struct pixel) * width * height;
}

struct image *create_image(uint64_t width, uint64_t height) {
    struct image *image = malloc(sizeof(struct image));
    if (image) {
        image->width = width;
        image->height = height;
        image->data = malloc(get_image_size(width, height));
    }
    return image;
}

void delete_image(struct image *image) {
    if (image) {
        if (image->data)
            free(image->data);
        free(image);
    }
}

bool set_pixel(const struct image *image, struct pixel pixel, size_t row, size_t column) {
    size_t pos = row * image->width + column;
    if (!is_valid_pos(*image, pos))
        return false;
    image->data[pos] = pixel;
    return true;
}

struct maybe_pixel get_pixel(const struct image *image, size_t row, size_t column) {
    size_t pos = row * image->width + column;
    if (!is_valid_pos(*image, pos))
        return none_pixel;
    return some_pixel(image->data[pos]);
}
