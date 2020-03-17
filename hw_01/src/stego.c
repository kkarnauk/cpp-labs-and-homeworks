#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stego.h"
#include "bmp.h"

typedef struct location {
	int32_t x;
	int32_t y;
} location;

const int BITS_NUMBER = 5;

uint32_t get_value_by_symbol(char symbol) {
	if (symbol == ' ') {
		return 26;
	} else if (symbol == '.') {
		return 27;
	} else if (symbol == ',') {
		return 28;
	} else {
		return symbol - 'A';
	}
}

char get_symbol_by_value(uint32_t value) {
	if (value < 26) {
		return 'A' + value;
	} else if (value == 26) {
		return ' ';
	} else if (value == 27) {
		return '.';
	} else {
		return ',';
	}
}

int get_pos_color(char color) {
	if (color == 'B') {
		return 0;
	} else if (color == 'G') {
		return 1;
	} else {
		return 2;
	}
}

int read_location(location* loc, int32_t delta_y, FILE* in_file) {
	char color;
	int got = fscanf(in_file, "%d %d %c", &loc->x, &loc->y, &color);
	if (got != 3) {
		return -1;
	}
	loc->y = delta_y - loc->y;
	loc->x = 3 * loc->x + get_pos_color(color);
	return 0;
}

void set_bit(bmp* cur, location loc, int value) {
	if ((cur->data[loc.y][loc.x] & 1) != value) {
		cur->data[loc.y][loc.x] ^= 1; 
	}
}

int get_bit(bmp* cur, location loc) {
	return (cur->data[loc.y][loc.x] & 1);
}

int insert(bmp* cur, char* key_name, char* msg_name) {
	FILE* key_file = fopen(key_name, "r");
	FILE* msg_file = fopen(msg_name, "r");
	if (key_file == NULL || msg_file == NULL) {
		return -1;
	}
	char symbol;
	while (fscanf(msg_file, "%c", &symbol) > 0 && symbol != '\n') {
		uint32_t value = get_value_by_symbol(symbol);
		for (int i = 0; i < BITS_NUMBER; i++) {
			location loc;
			read_location(&loc, cur->height - 1, key_file);
			set_bit(cur, loc, value & 1);
			value >>= 1;
		}
	}
	fclose(key_file);
	fclose(msg_file);

	return 0;
}

int extract(bmp* cur, char* key_name, char* msg_name) {
	FILE* key_file = fopen(key_name, "r");
	FILE* msg_file = fopen(msg_name, "w");
	if (key_file == NULL || msg_file == NULL) {
		return -1;
	}

	int cur_cnt = 0;
	uint32_t value = 0;
	location loc;
	while (read_location(&loc, cur->height - 1, key_file) != -1) {
		value += (get_bit(cur, loc) << cur_cnt);
		cur_cnt++;
		if (cur_cnt == BITS_NUMBER) {
			fprintf(msg_file, "%c", get_symbol_by_value(value));
			value = 0;
			cur_cnt = 0;
		}
	}
	fclose(msg_file);
	fclose(key_file);

	return 0;
}
