//
// Created by Цыпандин Николай Петрович on 12.12.2021.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_HEADER_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_HEADER_H

#include <stdint.h>

struct __attribute__((packed)) bmp_header {
    uint16_t bfSignature;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#endif //ASSIGNMENT_IMAGE_ROTATION_BMP_HEADER_H
