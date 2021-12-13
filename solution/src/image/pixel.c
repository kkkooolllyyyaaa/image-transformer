//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//

#include "pixel.h"

struct maybe_pixel some_pixel(struct pixel i) {
    struct maybe_pixel maybePixel = {0};
    maybePixel.valid = true;
    maybePixel.value = i;
    return maybePixel;
}

const struct maybe_pixel none_pixel = {0};