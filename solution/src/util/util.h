//
// Created by Цыпандин Николай Петрович on 13.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_UTIL_H
#define ASSIGNMENT_IMAGE_ROTATION_UTIL_H

#include <stdint.h>
#include <stdlib.h>

static const uint64_t alignment_size;
static const size_t pixel_size;

uint8_t get_padding(uint64_t width);

#endif //ASSIGNMENT_IMAGE_ROTATION_UTIL_H
