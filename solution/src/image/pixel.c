//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//

#include "pixel.h"

struct maybe_pixel some_pixel(struct pixel i) {
    return (struct maybe_pixel) {.valid = true, .value = i};
}

const struct maybe_pixel none_pixel = {0};
