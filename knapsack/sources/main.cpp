#include "../headers/knapsack.h"

#include <ctime>

int main(int argc, char const *argv[]){
	clock_t begin, end;
	if(argc < 2) return 1;
	if(argc == 2){
		string fileName = argv[1];
		Knapsack knapsack(fileName);
		begin= clock();
		knapsack.bruteForce();
		end= clock();
		cout << "\nTime: " << (double(end - begin) / CLOCKS_PER_SEC) << endl;
		begin= clock();
		knapsack.binaryAlgorithm();
		end= clock();
		cout << "\nTime: " << (double(end - begin) / CLOCKS_PER_SEC) << endl;
	}else{
		int capacity = atoi(argv[1]); //knapsack weight
		int elementsCount = atoi(argv[2]); // elements count
		Knapsack knapsack(capacity, elementsCount);
	}

	
	return 0;
}