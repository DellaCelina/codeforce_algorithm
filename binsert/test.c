#include <stdio.h>
#include "binsert.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100000
#define TIMES 10

int ccompare(const char* a, const char* b){
	if(*a > *b) return 1;
	if(*a < *b) return -1;
	else return 0;
}

int main(void){
	char a[MAX];
	float st_time, end_time;
	srand(time(NULL));
	for(int i = 0; i < MAX; i++){
		a[i] = rand();	
	}
	for(int i = 0; i < TIMES; i++){
			st_time = clock();
			binsert_sort((void*)a,MAX , 1, ccompare);
			end_time = clock();
			printf("bi time: %f\n", (end_time - st_time)/CLOCKS_PER_SEC);
			/*for(int i = 0; i<MAX; i++){
				printf("%d ",a[i]);
			}*/
			st_time = clock();
			qsort(a, MAX, 1, ccompare);
			end_time = clock();
			printf("qs time: %f\n", (end_time - st_time)/CLOCKS_PER_SEC);
	}
	return 0;
}
