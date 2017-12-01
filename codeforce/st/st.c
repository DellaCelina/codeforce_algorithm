#include <stdio.h>
#include <string.h>

char a[100], b[100];

void lo(char a[]){
	for(int i = 0; i < strlen(a); i++){
		if(a[i] >= 'A' && a[i] <= 'Z') a[i] += 'a' - 'A';
	}
}

int main(void){
	int flag;
	scanf("%s", a);
	scanf("%s", b);
	lo(a);
	lo(b);
	flag = strcmp(a,b);
	if(flag > 0) flag = 1;
	else if (flag == 0) flag = 0;
	else flag = -1;
	printf("%d\n", flag); 
	return 0;
}
