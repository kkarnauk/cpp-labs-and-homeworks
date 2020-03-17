#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

int comparator_int(const void *first, const void *second) {
	return *(int *)first - *(int *)second; 
}

int comparator_char(const void *first, const void *second) {
	return *(char *)first - *(char *)second;
}

int comparator_string(const void *first, const void *second) { //we sort char**
	return strcmp(*(char **)first, *(char **)second);
}

int sort_ints(int *data, int len) {
	if (mergesort(data, len, sizeof(data[0]), comparator_int) == -1) {
 			printf("Error: memory allocation failed.");
 			free(data);
 			return 1;
 	}
 	for (int i = 0; i < len; i++) {
 		printf("%d", data[i]);
 		if (i != len - 1) {
 			printf(" "); // it's in order not to write an extra space
 		}
 	}
 	free(data);

 	return 0;
} 

int sort_chars(char *data, int len) {
	if (mergesort(data, len, sizeof(data[0]), comparator_char) == -1) {
		printf("Error: memory allocation failed.");
		free(data);
		return 1;
	}
	for (int i = 0; i < len; i++) {
		printf("%c", data[i]);
		if (i != len - 1) {
			printf(" ");
		}
	}
	free(data);

	return 0;
}

int sort_strings(char **data, int len) {
	if (mergesort(data, len, sizeof(data[0]), comparator_string) == -1) {
		printf("Error: memory allocation failed.");
		return 1; //we don't free the memory because we didn't <<malloc>> it
	}
	for (int i = 0; i < len; i++) {
		printf("%s", data[i]);
		if (i != len - 1) {
			printf(" ");
		}
	}

	return 0;
}

int main(int argv, char *argc[]) {
	int len = argv - 2; // length
	char *type = argc[1];
	if (*type == 'i') { // for ints
 		int *data = (int *)malloc(len * sizeof(int));
 		for (int i = 0; i < len; i++) {
 			data[i] = atoi(argc[i + 2]);
 		}
 		return sort_ints(data, len);
	} else if (*type == 'c') { // for chars
		char *data = (char *)malloc(len * sizeof(char));
		for (int i = 0; i < len; i++) {
			data[i] = *argc[i + 2];
		}
		return sort_chars(data, len);
	} else if (*type == 's') { // for strings
		return sort_strings(&argc[2], len);
	}

	return 0;
}