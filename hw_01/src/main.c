#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "bmp.h"
#include "stego.h"

int crop_rotate(char* in_name, char* out_name, int32_t x, int32_t y, int32_t width, int32_t height) {
	bmp** bmps = create_bmps(3);
	if (bmps == NULL) {
		return -1;
	}
	if (load_bmp(in_name, bmps[0]) != 0) {
		free_bmps(bmps, 3);
		return -1;
	}
	if (x + width - 1 >= bmps[0]->width || y + height - 1 >= bmps[0]->height || x < 0 || y < 0) {
		free_bmps(bmps, 3);
		return -1;
	}
	crop(bmps[0], bmps[1], x, bmps[0]->height - y - height, width, height);
	rotate(bmps[1], bmps[2]);
	if (save_bmp(out_name, bmps[2]) != 0) {
		free_bmps(bmps, 3);
		return -1;
	}
	free_bmps(bmps, 3);
	return 0;
}

int insert_message(char* in_name, char* out_name, char* key_name, char* msg_name) {
	bmp* img = create_bmp();
	if (img == NULL) {
		return -1;
	}
	if (load_bmp(in_name, img) != 0) {
		free_bmp(img);
		return -1;
	}
	if (insert(img, key_name, msg_name) != 0) {
		free_bmp(img);
		return -1;
	}
	if (save_bmp(out_name, img) != 0) {
		free_bmp(img);
		return -1;
	}
	free_bmp(img);
	return 0;
}

int extract_message(char* in_name, char* key_name, char* msg_name) {
	bmp* img = create_bmp();
	if (img == NULL) {
		return -1;
	}
	if (load_bmp(in_name, img) != 0) {
		free_bmp(img);
		return -1;
	}
	if (extract(img, key_name, msg_name) != 0) {
		free_bmp(img);
		return -1;
	}
	free_bmp(img);
	return 0;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		return -1;
	}
	if (strcmp(argv[1], "crop-rotate") == 0) {
		if (argc < 8) {
			return -1;
		}
		return crop_rotate(argv[2], argv[3], atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
	} else if (strcmp(argv[1], "insert") == 0) {
		if (argc < 6) {
			return -1;
		}
		return insert_message(argv[2], argv[3], argv[4], argv[5]);
	} else if (strcmp(argv[1], "extract") == 0) {
		if (argc < 5) {
			return -1;
		}
		return extract_message(argv[2], argv[3], argv[4]);
	}
	return -1;
}