//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//
#include "bmp.h"

static const uint16_t valid_signature = 19778;

const char *read_status_string[] = {
        [READ_OK] = "Image is successfully read",
        [READ_INVALID_SIGNATURE]="Error, BMP file has invalid signature, must be 'BM'",
        [READ_INVALID_BITS]="Error, BMP file is invalid",
        [READ_INVALID_HEADER]="Error, BMP header is invalid"
};

const char *write_status_string[] = {
        [WRITE_OK]= "Image is successfully written",
        [WRITE_ERROR]="Error, can't write BMP",
};

static enum read_status header_read(FILE *in, struct bmp_header *header) {
    if (fread(header, sizeof(struct bmp_header), 1, in) == 1)
        return READ_CONTINUE;
    return READ_INVALID_HEADER;
}

static enum read_status header_check_valid(struct bmp_header *header) {
    if (header->biWidth <= 0 || header->biHeight <= 0)
        return READ_INVALID_SIGNATURE;
    if (header->bfSignature != valid_signature) {
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
    uint32_t bmp_image_size = (image->width * sizeof(struct pixel) + get_padding(image->width)) * image->height;
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
    const uint8_t padding = get_padding(width);
    struct pixel *pixels = image->data;
    for (uint64_t i = 0; i < height; ++i) {
        if (fwrite(pixels + i * width, sizeof(struct pixel), width, file) != width)
            return WRITE_ERROR;
        // write padding bytes
        for (uint64_t j = 0; j < padding; ++j) {
            char trash = 0;
            if (fwrite(&trash, 1, 1, file) != 1)
                return WRITE_ERROR;
        }
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
    if (status != READ_CONTINUE)
        return status;

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
