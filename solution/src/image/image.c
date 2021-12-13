//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//
#include <stdlib.h>
#include "image.h"
#include "pixel.h"

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
    free(image->data);
    free(image);
}

bool set_pixel(struct image image, struct pixel pixel, size_t row, size_t column) {
    size_t pos = row * image.width + column;
    if (!is_valid_pos(image, pos))
        return false;
    image.data[pos] = pixel;
    return true;
}

struct maybe_pixel get_pixel(struct image image, size_t row, size_t column) {
    size_t pos = row * image.width + column;
    if (!is_valid_pos(image, pos))
        return none_pixel;
    return some_pixel(image.data[pos]);
}

static size_t get_image_size(uint64_t width, uint64_t height) {
    return sizeof(struct pixel) * width * height;
}

static bool is_valid_pos(struct image image, size_t pos) {
    return pos < image.width * image.height;
}
