#include <stdio.h>
#include <iostream>

long long total;

int main(void){
	int n, m;
	int prv, crt;
	scanf("%d %d", &n, &m);
	scanf("%d", &prv);
	total = prv-1;
	for(int i=1; i<m; i++){
		scanf("%d", &crt);
		if(crt < prv) total += n - (prv - crt);
		else total += crt - prv;
		prv = crt;
	}
	std::cout << total << std::endl;
	return 0;
}
