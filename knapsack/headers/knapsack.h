#include <iostream>
#include <random>

using namespace std;

struct Element{
	unsigned int weight;
	unsigned int value;
};

class Knapsack{
	private:
		random_device rd;
		Element *elementsArray;
		unsigned int elementsCount;
		unsigned long int knapsackWeight;
		bool debug;

		void printData();
		
		int binaryBit(unsigned long long i, unsigned long int b);
	public:
		Knapsack(unsigned long int weight, unsigned int elements);	
		~Knapsack();
		void bruteForce();

};