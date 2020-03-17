#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "bmp.h"

const int HEADER_SIZE = 54;
const int START_WIDTH = 18;
const int START_HEIGHT = 22;
const int START_SIZE_F = 2;
const int START_SIZE_S = 34;

bmp* create_bmp() {
	bmp* cur = (bmp*)malloc(sizeof(bmp));
	if (cur == NULL) {
		return NULL;
	}
	cur->header = (uint8_t*)malloc(HEADER_SIZE);
	if (cur->header == NULL) {
		free(cur);
		return NULL;
	}
	cur->data = NULL;
	return cur;
}

void free_bmp(bmp* cur) {
	if (cur->header != NULL) {
		free(cur->header);
	}
	if (cur->data != NULL) {
		for (int32_t i = 0; i < cur->height; i++) {
			if (cur->data[i] != NULL) {
				free(cur->data[i]);
			}
		}
		free(cur->data);
	}
	free(cur);
}

void free_bmps(bmp** bmps, int n) {
	for (int i = 0; i < n; i++) {
		free_bmp(bmps[i]);
	}
	free(bmps);
}

bmp** create_bmps(int n) {;
	bmp** bmps = (bmp**)malloc(sizeof(bmp*) * n);
	if (bmps == NULL) {
		return NULL;
	}
	for (int i = 0; i < n; i++) {
		bmps[i] = create_bmp();
		if (bmps[i] == NULL) {
			free_bmps(bmps, i);
			return NULL;
		}
	}
	return bmps;
}

int32_t from_bits_to_int(uint8_t* x) {
	return ((uint32_t)x[3] << 24) + ((uint32_t)x[2] << 16) + ((uint32_t)x[1] << 8) + (uint32_t)x[0];
}

int32_t ceil_to_four(int32_t x) {
	return ((x + 3) / 4) * 4;
}

void change_sizes(bmp* cur, int32_t width, int32_t height) {
	cur->width = width;
	cur->height = height;
	for (int i = 0; i < 4; i++) {
		cur->header[START_WIDTH + i] = ((uint32_t)width & ((1 << 8) - 1));
		cur->header[START_HEIGHT + i] = ((uint32_t)height & ((1 << 8) - 1));
		width >>= 8;
		height >>= 8;
	}
}

void upd_total_size(bmp* cur) {
	uint32_t total_size = HEADER_SIZE + cur->byte_width * cur->height;
	uint32_t image_size = cur->byte_width * cur->height;
	for (int i = 0; i < 4; i++) {
		cur->header[START_SIZE_F + i] = (total_size & ((1 << 8) - 1));
		cur->header[START_SIZE_S + i] = (image_size & ((1 << 8) - 1));
		total_size >>= 8;
		image_size >>= 8;
	}
}
		
int fill_bmp(bmp* cur) {
	cur->width = from_bits_to_int(&cur->header[START_WIDTH]);
	cur->height = from_bits_to_int(&cur->header[START_HEIGHT]);
	cur->byte_width = ceil_to_four(cur->width * 3);

	cur->data = (uint8_t**)malloc(sizeof(uint8_t*) * cur->height);
	if (cur->data == NULL) {
		return -1;
	}

	for (int i = 0; i < cur->height; i++) {
		cur->data[i] = (uint8_t*)malloc(cur->byte_width);

		if (cur->data[i] == NULL) {
			return -1;
		}
		for (int j = 0; j < cur->byte_width; j++) {
			cur->data[i][j] = 0;
		}
	}
	return 0;
}

void prepare_bmp(const bmp* cur, bmp* res, int32_t width, int32_t height) {
	memcpy(res->header, cur->header, HEADER_SIZE);
	change_sizes(res, width, height);
	fill_bmp(res);
	upd_total_size(res);
}

int load_bmp(const char* file_name, bmp* inbmp) {
	FILE* file = fopen(file_name, "rb");
	if (file == NULL) {
		return -1;
	}

	fread(inbmp->header, 1, HEADER_SIZE, file);
	fill_bmp(inbmp);
	for (int32_t i = 0; i < inbmp->height; i++) {
		fread(inbmp->data[i], 1, inbmp->byte_width, file);
	}
	fclose(file);
	return 0;
}

void crop(const bmp* cur, bmp* res, int32_t x, int32_t y, int32_t width, int32_t height) {
	prepare_bmp(cur, res, width, height);
	for (int32_t i = 0; i < height; i++) {
		memcpy(res->data[i], &cur->data[i + y][x * 3], width * 3);
	}
}

void rotate(const bmp* cur, bmp* res) {
	prepare_bmp(cur, res, cur->height, cur->width);
	for (int32_t i = 0; i < res->height; i++) {
		for (int32_t j = 0; j < res->width; j++) {
			for (int k = 0; k < 3; k++) {
				res->data[i][j * 3 + k] = cur->data[j][(cur->width - i - 1) * 3 + k];
			}
		}
	}
}

int save_bmp(const char *file_name, const bmp* outbmp) {
	FILE *file = fopen(file_name, "wb");
	if (file == NULL) {
		return -1;
	}

	fwrite(outbmp->header, 1, HEADER_SIZE, file);
	for (int32_t i = 0; i < outbmp->height; i++) {
		fwrite(outbmp->data[i], 1, outbmp->byte_width, file);
	}
	fclose(file);

	return 0;
}