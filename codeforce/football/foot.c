#include <stdio.h>

int main(void){
	char ch, flag = '0';
	int cnt = 0;
	while( (ch = getchar()) != '\n'){
		if(ch == flag) cnt++;
		else{
			flag = ch;
			cnt = 1;
		}

		if(cnt >= 7){
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
