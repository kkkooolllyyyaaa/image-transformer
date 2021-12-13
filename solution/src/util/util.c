//
// Created by Цыпандин Николай Петрович on 13.12.2021.
//

#include "util.h"

static const uint64_t alignment_size = 4;

uint8_t get_padding(uint64_t width) {
    if (width % alignment_size == 0)
        return 0;
    return alignment_size - width % alignment_size;
}
