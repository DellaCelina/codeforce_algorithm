#include <stdio.h>
#include <string.h>
char poly[20];
unsigned int total;

int main(void){
	unsigned int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s", poly);
		switch(poly[0]){
			case 'T': total += 4;
				break;
			case 'C' : total += 6;
				break;
			case 'O' : total += 8;
				break;
			case 'D' : total += 12;
				break;
			case 'I' : total += 20;
				break;
			default :
				break;
		}
	}
	printf("%u\n", total);
	return 0;
}
