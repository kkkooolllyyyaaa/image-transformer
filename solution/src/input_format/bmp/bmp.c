//
// Created by Цыпандин Николай Петрович on 08.12.2021.
//
#include "bmp.h"
#include "../../util/util.h"

static const uint16_t valid_signature = 19778;

enum read_status from_bmp(FILE *in, struct image **img) {
    enum read_status status;
    struct bmp_header header = {0};

    status = header_read(in, &header);
    if (status != OK_CONTINUE)
        return status;

    status = header_check_valid(&header);
    if (status != OK_CONTINUE)
        return status;

    int32_t width = header.biWidth, height = header.biHeight;
    *img = create_image(width, height);

    status = read_pixels(in, *img);
    if (status != OK_CONTINUE)
        return status;

    return READ_OK;
}

enum write_status to_bmp(FILE *out, const struct image *img) {
    return WRITE_OK;
}

static enum read_status header_read(FILE *in, struct bmp_header *header) {
    if (fread(header, sizeof(struct bmp_header), 1, in)) {
        return OK_CONTINUE;
    }
    return READ_INVALID_HEADER;
}

static enum read_status header_check_valid(struct bmp_header *header) {
    if (header->biWidth <= 0 || header->biHeight <= 0)
        return READ_INVALID_SIGNATURE;
    if (header->bfSignature != valid_signature) {
        return READ_INVALID_SIGNATURE;
    }
    return OK_CONTINUE;
}

static enum read_status read_pixels(FILE *file, struct image *image) {
    const uint64_t width = image->width, height = image->height;
    const uint8_t padding = get_padding(width);
    struct pixel *pixels = image->data;
    for (uint64_t i = 0; i < height; ++i) {
        if (fread(pixels + i * width, sizeof(struct pixel), width, file) != width)
            return READ_INVALID_BITS;
        if (fseek(file, padding, SEEK_CUR))
            return READ_INVALID_BITS;
    }
    return OK_CONTINUE;
}