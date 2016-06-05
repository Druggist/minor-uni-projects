#include "../headers/knapsack.h"

Knapsack::Knapsack(unsigned long int weight, unsigned int elements){
	debug = true;
	elementsArray = new Element[elements];
	mt19937 mt(rd());
	uniform_int_distribution<unsigned int> randWeight(1, weight);
	uniform_int_distribution<unsigned int> randValue(1, elements);
	
	elementsCount = elements;
	knapsackWeight = weight;

	for(unsigned int i = 0; i < elements; i++){
		elementsArray[i].weight = randWeight(mt);
		elementsArray[i].value = randValue(mt);
	}

	if(debug) printData();
}

void Knapsack::printData(){
	cout<< knapsackWeight << endl << elementsCount << endl;
	for(unsigned int i = 0; i < elementsCount; i++){
		cout<< elementsArray[i].value << " " << elementsArray[i].weight << endl;
	}
}

Knapsack::~Knapsack(){
	delete [] elementsArray;
}
