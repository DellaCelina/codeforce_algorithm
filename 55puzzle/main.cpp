#include "puzzle.h"

#define PUZZLE_N 6

int main() {
	ofstream file;
	Puzzle pz(PUZZLE_N);
	clock_t start, end;
	start = clock();
	pz.Solve();
	end = clock();
	printf("\n\n Solve:\n");
	pz.PrintStack(file);
	printf("time: %f", float(end - start) / CLOCKS_PER_SEC);
	return 0;
}