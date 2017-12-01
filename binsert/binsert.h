#include <string.h>
#include <stdlib.h>

#define BI_ARR(carr, width, idx) (carr + width * idx)

/*
*Return pointer for insertion.
*/
char* bi_binary_search(const char* idata, char* base, int len, int width, int (*compare)(const void*, const void*)){
	while(len > 1){
		int idx = len/2;
		char* pivot = BI_ARR(base, width, idx);
		if(compare((void*)pivot, (void*)idata) == -1){
			base = BI_ARR(base, width, idx+1);
			if(len & 1) len /= 2;
			else len = len/2 - 1;
		}
		else{
			len = len/2;
		}
	}
	if(compare((void*)base, (void*)idata) == -1) return BI_ARR(base, width, 1);
	else return base;
}


int binsert_sort(void* base, int len, int width, int (*compare)(const void*, const void*)){
	char* arr = (char*)base;
	for(int i = 1; i < len; i++){
		char* tmp = (char*)malloc(width);
		char* idata = BI_ARR(arr, width, i);
		char* loc;
		if(compare(BI_ARR(arr,width,i-1), idata) != 1) continue;
		tmp = (char*)malloc(width);
		memcpy(tmp, idata, width);
		loc = bi_binary_search(tmp, arr, i, width, compare);
		memmove(loc + 1, loc, idata - loc);
		memcpy(loc, tmp, width);
		free(tmp);
	}
}
