#include <stdio.h>
#define SWAP(a, b, type) do{type tmp; tmp = a; a = b; b = tmp;}while(0);

char stdnt[100];
int flag[2][100];
char f_arrd;
int n, t;

void swap_stdnt(){
	int j = 0;
	for(j = 0; flag[f_arrd][j] != -1; j++){
		SWAP(stdnt[flag[f_arrd][j]], stdnt[flag[f_arrd][j]+1], char);
	}
}
void make_flag(){
	char tmp_arrd;
	int a = 0;
	tmp_arrd = (f_arrd == 0) ? 1 : 0;
	for(int j = 0; flag[f_arrd][j] != -1; j++){
		if(flag[f_arrd][j] != 0 && stdnt[flag[f_arrd][j]-1] == 'B')
			if(a == 0 || flag[tmp_arrd][a-1] != flag[f_arrd][j]-1) flag[tmp_arrd][a++] = flag[f_arrd][j] - 1;
		if(flag[f_arrd][j] < n-2 && stdnt[flag[f_arrd][j]+2] == 'G')
			if(a == 0 || flag[tmp_arrd][a-1] != flag[f_arrd][j]+1) flag[tmp_arrd][a++] = flag[f_arrd][j] +1;
	}
	flag[tmp_arrd][a] = -1;
	f_arrd = tmp_arrd;
}

int main(void){
	int j = 0;
	scanf("%d %d", &n ,&t);
	while(getchar() != '\n');
	for(int i = 0; i< n; i++){
		stdnt[i] = getchar();
		if(i != 0 && stdnt[i] == 'G' && stdnt[i-1] == 'B') flag[f_arrd][j++] = i-1;
	}
	stdnt[n] = '\n';
	flag[f_arrd][j] = -1;
	for(int i = 0; i<t; i++){
		swap_stdnt();
		if(i!=t-1) make_flag();
	}
	printf("%s\n", stdnt);
	return 0;
}
