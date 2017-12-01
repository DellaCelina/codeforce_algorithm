#include <stdio.h>


int main(void){
	int tc;
	int total = 0;
	scanf("%d", &tc);
	for(int i = 0; i < tc; i++){
		int set;
		int a, b ,c;
		scanf("%d %d %d", &a, &b, &c);
		if((a + b + c) >= 2) total++;
	}
	printf("%d\n", total);
	return 0;
}
