#include "../headers/knapsack.h"

int main(int argc, char const *argv[]){
	clock_t begin, end;
	if(argc < 3) return 1;
	int x = atoi(argv[1]); //knapsack weight
	int y = atoi(argv[2]); // elements count
	Knapsack knapsack(x, y);

	knapsack.bruteForce();
	return 0;
}