#pragma once 
#include <stdint.h>

typedef struct bmp {
	int32_t byte_width, height, width;
	uint8_t* header;
	uint8_t** data;
} bmp;

bmp* create_bmp();

void free_bmp(bmp* cur);

bmp** create_bmps(int n);

void free_bmps(bmp** bmps, int n);

int load_bmp(const char* file_name, bmp* inbmp);

void crop(const bmp* cur, bmp* res, int x, int y, int byte_width, int height);

void rotate(const bmp* cur, bmp* res);

int save_bmp(const char *file_name, const bmp* outbmp);