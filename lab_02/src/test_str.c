#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "str.h"

int sign(int x) {
	if (x > 0) {
		return 1;
	}
	if (x < 0) {
		return -1;
	}
	return 0;
}

void test_strlen() {
	const char *fir = "Hello, my friend. I'm from Russia!\n";
	const char *sec = "Please, give me 10 for this task! :)\n";
	assert(my_strlen(fir) == strlen(fir));
	assert(my_strlen(sec) == strlen(sec));
	assert(my_strlen("") == strlen(""));

	printf("strlen was tested successfully!\n");
}

void test_strcpy() {
	char fir[100] = "";
	char sec[100] = "I hope that's correct\n";
	char third[100] = "hello, my friend!\n";
	assert(strcmp(my_strcpy(fir, sec), sec) == 0);
	assert(strcmp(my_strcpy(sec, ""), "") == 0);
	assert(strcmp(my_strcpy(third, fir), fir) == 0);

	printf("strcpy was tested successfully!\n");
}

void test_strcmp() {
	const char *fir = "What do you think about my homework?\n";
	const char *sec = "What do you do?\n";
	const char *third = "What do you";
	assert(sign(my_strcmp(fir, sec)) == sign(strcmp(fir, sec)));
	assert(sign(my_strcmp(fir, third)) == sign(strcmp(fir, third)));
	assert(sign(my_strcmp(sec, third)) == sign(strcmp(sec, third)));
	assert(sign(my_strcmp(third, fir)) == sign(strcmp(third, fir)));
	assert(sign(my_strcmp(sec, fir)) == sign(strcmp(sec, fir)));

	printf("strcmp was tested successfully!\n");
}

void help_test_strcat(const char *fir, const char *sec) {
	char fir1[100];
	char fir2[100];
	strcpy(fir1, fir);
	strcpy(fir2, fir);
	assert(strcmp(my_strcat(fir1, sec), strcat(fir2, sec)) == 0);
}

void test_strcat() {
	char empt[100] = "";
	char fir[100] = "hello!\n";
	char sec[100] = "how are you?\n";
	help_test_strcat(fir, sec);
	help_test_strcat(sec, "");
	help_test_strcat(empt, fir);

	printf("strcat was tested successfully!\n");
}