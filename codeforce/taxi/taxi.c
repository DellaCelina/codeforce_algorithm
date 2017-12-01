#include <stdio.h>

int grps[4];
int taxi;

int main(void){
	int grp;
	scanf("%d", &grp);
	for(int i =0; i< grp; i++){
		int tmp;
		scanf("%d", &tmp);
		grps[tmp-1]++;
	}
	taxi = grps[3] + grps[2] + grps[1]/2;
	grps[0] -= grps[2];
	if(grps[1] & 1) grps[0] -= 2, taxi++;
	if(grps[0] <0) grps[0] = 0;
	taxi += grps[0]/4;
	if(grps[0] & 3) taxi++;
	printf("%d\n", taxi);
	return 0;
}
