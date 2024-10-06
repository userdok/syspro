#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAX_LINES 5
#define MAX_LENGTH 50

// bubblesort
void sort(char *lines[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (strlen(lines[j]) < strlen(lines[j + 1])) {
				char *temp = lines[j];
				lines[j] = lines[j + 1];
				lines[j + 1] = temp;
			}
		}
	}
}


int main() {
	char ch[MAX_LINES][MAX_LENGTH];
	char *lines[MAX_LINES];
	int i = 0;

	while(i < MAX_LINES) {
		scanf("%s", ch[i]);
		lines[i] = ch[i];
		i++;
	}

	sort(lines, MAX_LINES);

	for (i = 0; i < MAX_LINES; i++) {
		printf("%s\n", lines[i]);
	}

	return 0;
}
