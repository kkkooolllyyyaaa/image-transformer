//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_PIXEL_H
#define ASSIGNMENT_IMAGE_ROTATION_PIXEL_H

#include  <stdbool.h>
#include <stdint.h>

struct pixel {
    uint8_t b, g, r;
};
struct maybe_pixel {
    bool valid;
    struct pixel value;
};

// Первый случай; создаем функцию в помощь
struct maybe_pixel some_pixel(struct pixel i);

// Второй случай; можно создать не функцию,
const struct maybe_pixel none_pixel;

#endif //ASSIGNMENT_IMAGE_ROTATION_PIXEL_H
