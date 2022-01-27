//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//
#include "bmp.h"

#define PADDING_BUFFER_SIZE  4

static const uint16_t SIGNATURE = 19778;
static const uint32_t BF_RESERVED = 0;
static const uint32_t BI_SIZE = 40;
static const uint16_t PLANES = 1;
static const uint16_t BIT_COUNT = 24;
static const uint32_t COMPRESSION = 0;
static const uint32_t XPELS_PER_METER = 2834;
static const uint32_t YPELS_PER_METER = 2834;
static const uint32_t BI_CLR_USED = 0;
static const uint32_t CLR_IMPORTANT = 0;

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

// without: width, height, fileSize, sizeImage
static const struct bmp_header LAYOUT_24_BIT = {
        .bfSignature = SIGNATURE,
        .bfReserved = BF_RESERVED,
        .bOffBits = sizeof(struct bmp_header),
        .biSize = BI_SIZE,
        .biPlanes = PLANES,
        .biBitCount = BIT_COUNT,
        .biCompression = COMPRESSION,
        .biXPelsPerMeter = XPELS_PER_METER,
        .biYPelsPerMeter = YPELS_PER_METER,
        .biClrUsed = BI_CLR_USED,
        .biClrImportant = CLR_IMPORTANT,
};

static const char *const read_status_string[] = {
        [READ_OK] = "Image is successfully read",
        [READ_INVALID_SIGNATURE]="Error, BMP file has invalid signature, must be 'BM'",
        [READ_INVALID_BITS]="Error, BMP file is invalid",
        [READ_INVALID_HEADER]="Error, BMP header is invalid"
};

const char *get_read_status_string(enum read_status r_s) {
    return read_status_string[r_s];
}

static const char *const write_status_string[] = {
        [WRITE_OK]= "Image is successfully written",
        [WRITE_ERROR]="Error, can't write BMP",
};

const char *get_write_status_string(enum write_status w_s) {
    return write_status_string[w_s];
}

static enum read_status header_read(FILE *in, struct bmp_header *header) {
    if (fread(header, sizeof(struct bmp_header), 1, in) == 1)
        return READ_CONTINUE;
    return READ_INVALID_HEADER;
}

static enum read_status header_check_valid(struct bmp_header *header) {
    if (header->biWidth <= 0 || header->biHeight <= 0)
        return READ_INVALID_SIGNATURE;
    if (header->bfSignature != SIGNATURE) {
        return READ_INVALID_SIGNATURE;
    }
    return READ_CONTINUE;
}

static enum read_status read_pixels(FILE *file, struct image *image) {
    const uint64_t width = image->width, height = image->height;
    const uint8_t padding = get_padding(width);
    struct pixel *pixels = image->data;

    for (uint64_t i = 0; i < height; ++i) {
        if (fread(pixels + i * width, sizeof(struct pixel), width, file) != width)
            return READ_INVALID_BITS;
        // move pointer in stream to next line (skip padding bytes)
        if (fseek(file, padding, SEEK_CUR))
            return READ_INVALID_BITS;
    }
    return READ_CONTINUE;
}

static enum write_status init_24bit_header(struct bmp_header *header, const struct image *image) {
    if (!header || !image)
        return WRITE_ERROR;
    const uint32_t bmp_image_size =
            (image->width * sizeof(struct pixel) + get_padding(image->width)) * image->height;
    *header = LAYOUT_24_BIT;
    header->biWidth = (int32_t) image->width;
    header->biHeight = (int32_t) image->height;
    header->biSizeImage = bmp_image_size;
    header->bfileSize = header->bOffBits + header->biSizeImage;
    return WRITE_CONTINUE;
}

static enum write_status header_write(FILE *out, struct bmp_header *header) {
    if (fwrite(header, sizeof(struct bmp_header), 1, out) == 1)
        return WRITE_CONTINUE;
    return WRITE_ERROR;
}

static enum write_status write_pixels(FILE *file, const struct image *image) {
    const uint64_t width = image->width, height = image->height;
    const uint8_t padding_buffer[PADDING_BUFFER_SIZE] = {0};
    const uint8_t padding = get_padding(width);
    struct pixel *pixels = image->data;
    for (uint64_t i = 0; i < height; ++i) {
        if (fwrite(pixels + i * width, sizeof(struct pixel), width, file) != width)
            return WRITE_ERROR;
        // write padding bytes
        if (padding != 0 && !fwrite(&padding_buffer, padding, 1, file))
            return WRITE_ERROR;
    }
    return WRITE_CONTINUE;
}

enum read_status from_bmp(FILE *in, struct image **img) {
    enum read_status status;
    struct bmp_header header = {0};

    status = header_read(in, &header);
    if (status != READ_CONTINUE)
        return status;
    status = header_check_valid(&header);
    if (status != READ_CONTINUE)
        return status;

    int32_t width = header.biWidth, height = header.biHeight;
    *img = create_image(width, height);
    status = read_pixels(in, *img);
    if (status != READ_CONTINUE) {
        delete_image(*img);
        return status;
    }

    return READ_OK;
}

enum write_status to_bmp(FILE *out, const struct image *img) {
    enum write_status status;
    struct bmp_header header = {0};

    status = init_24bit_header(&header, img);
    if (status != WRITE_CONTINUE)
        return status;
    status = header_write(out, &header);
    if (status != WRITE_CONTINUE)
        return status;
    status = write_pixels(out, img);
    if (status != WRITE_CONTINUE)
        return status;
    return WRITE_OK;
}
