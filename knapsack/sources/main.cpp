#include "../headers/knapsack.h"

#include <ctime>

int main(int argc, char const *argv[]){
	clock_t begin, end;
	if(argc < 3) return 1;
	int capacity = atoi(argv[1]); //knapsack weight
	int elementsCount = atoi(argv[2]); // elements count
	Knapsack knapsack(capacity, elementsCount);
	
	begin= clock();
	knapsack.bruteForce();
	end= clock();
	cout << "\nTime: " << (double(end - begin) / CLOCKS_PER_SEC) << endl;
	
	return 0;
}