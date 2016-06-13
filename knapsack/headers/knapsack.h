#include <iostream>
#include <random>
#include <fstream>
#include <string>

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
		unsigned long int  max(unsigned long int a, unsigned long int b);

		int binaryBit(unsigned long long i, unsigned long int b);
		unsigned long int  binaryAlgorithm(unsigned long int capacity, unsigned int elements);

	public:
		Knapsack(unsigned long int weight, unsigned int elements);	
		Knapsack(string fileName);	
		void bruteForce();
		void binaryAlgorithm();
		~Knapsack();

};