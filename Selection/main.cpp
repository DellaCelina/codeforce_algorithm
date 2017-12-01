#include "Selection.h"
#include <time.h>
#define LEN 10000

int main(void) {
	uint arr[LEN];
	srand(time(NULL));
	for (int i = 0; i < LEN; i++)
		printf("%u ", arr[i] = rand() % (LEN * 100));
	printf("\n");
	for (int i = 0; i < LEN; i++) {
		printf("%u ", selection(i + 1, arr, LEN));
	}
	return 0;
}