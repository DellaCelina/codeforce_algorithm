#include <stdio.h>

int X;

int main(void){
	int tc;
	scanf("%d", &tc);
	while(getchar() != '\n');
	for(int i = 0; i < tc; i++){
		char op;
		while((op = getchar()) == 'X');
		switch(op){
		case '+': X++; break;
		case '-': X--; break;
		}
		while(getchar() != '\n');
	}
	printf("%d\n", X);
	return 0;
}
