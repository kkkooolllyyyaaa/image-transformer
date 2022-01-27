//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_PIXEL_H
#define ASSIGNMENT_IMAGE_ROTATION_PIXEL_H

#include  <stdbool.h>
#include <stdint.h>

struct __attribute__((packed)) pixel {
    uint8_t b, g, r;
};
struct maybe_pixel {
    bool valid;
    struct pixel value;
};

struct maybe_pixel some_pixel(struct pixel i);

// external objects, to use same object everywhere
extern const struct maybe_pixel none_pixel;

#endif //ASSIGNMENT_IMAGE_ROTATION_PIXEL_H
