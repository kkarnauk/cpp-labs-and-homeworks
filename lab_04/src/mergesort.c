#include <stdlib.h>
#include <string.h>

void *get_val(void *start, int pos, size_t element_size) {
	return (void *)((char *)start + pos * element_size);
}

void swap_element(void *fir, void *sec, size_t element_size) {
	for (int i = 0; i < (int)element_size; i++) {
		char tmp = *((char *)fir + i);
		*((char *)fir + i) = *((char *)sec + i);
		*((char *)sec + i) = tmp; 
	}
}

void mergesort_work(void *array, void *buffer, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
	if (elements <= 1) {
		return;
	}
	size_t fir_size = elements / 2;
	size_t sec_size = elements - fir_size;
	void *left = array;
	void *right = (void *)((char *)array + fir_size * element_size);
	mergesort_work(left, buffer, fir_size, element_size, comparator);
	mergesort_work(right, buffer, sec_size, element_size, comparator);
	size_t fir = 0;
	size_t sec = 0;
	while (fir < fir_size && sec < sec_size) { 
		void *fir_val = get_val(left, fir, element_size);
		void *sec_val = get_val(right, sec, element_size);
		if (comparator(fir_val, sec_val) <= 0) {
			swap_element(fir_val, buffer, element_size);
			fir++;
		} else {
			swap_element(sec_val, buffer, element_size);
			sec++;
		}
		buffer = get_val(buffer, 1, element_size);
	}

	while (fir < fir_size) { // if the right one ended
		swap_element(buffer, get_val(left, fir, element_size), element_size);
		buffer = get_val(buffer, 1, element_size);
		fir++;
	}
	while (sec < sec_size) { //if the left one ended
		swap_element(buffer, get_val(right, sec, element_size), element_size);
		buffer = get_val(buffer, 1, element_size);
		sec++;
	}

	buffer = get_val(buffer, -(int)elements, element_size); // go back to the start of buffer
	memcpy(array, buffer, elements * element_size);
}

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void *, const void *)) {
	void *buffer = malloc(elements * element_size);
	if (buffer == NULL) {
		return -1;
	}
	mergesort_work(array, buffer, elements, element_size, comparator);
	free(buffer);
	return 0;
}