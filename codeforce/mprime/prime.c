#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define _log() do{}while(0)
typedef unsigned long long ull;

ull pow2(ull n){
	ull ret = 1;
	for(int i=0; i<n; i++){
		ret *= 2;
	}
	return  ret;
}

ull mroot(ull n){
	return (n%2) ? pow2(n/2) * 1.5 : pow2(n/2);
}

bool check_mprime(ull n){
	ull mp = pow2(n) -1;
	ull limit = mroot(n);	
	printf("mp : %llu\n", mp);
	_log();
	if(mp == 0 || mp == 1 || mp == 2) {
		printf("default prime ");
		return false;
	}
	for(ull i = 3; i<= limit; i+=2){
		if(!(mp % i)) {
		printf("%lld, %lld ", i, mp/i);
		return false;
		}
		_log();
	}
	return true;
}

void p_mprime(int n){
	printf("%s\n", (check_mprime(n)) ? "true" : "false");
}

int main(void){
	ull n;
	clock_t begin, end;
	printf("set num of 2^n -1 : ");	
	scanf("%llu", &n);
	_log();
	begin = clock();
	p_mprime(n);
	end = clock();
	printf("time for calc: %lfsec", (double)(end - begin)/(double)CLOCKS_PER_SEC);
	return 0;
}
