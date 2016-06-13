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

int Knapsack::binaryBit(unsigned long long i, unsigned long int b) {
   int r;
   i>>=b;
   r=i%2;
   return r;
}

void Knapsack::bruteForce(){
    unsigned long int maxValue=0;
    unsigned long int maxWeight=0;
    unsigned long int maxSet=0;
	
	//cout << "Temp data:\n";
    for(unsigned long long i=0;i<(2<<elementsCount);i++){
       unsigned long int Value=0;
       unsigned long int Weight=0;
       for(unsigned long int j=0;j<elementsCount;j++){
          if(binaryBit(i,j)==1){
             Value+=elementsArray[j].value;
             Weight+=elementsArray[j].weight;
          }
		  if(Weight>C) break;
       }
       
       if(Weight<=knapsackWeight && Value>maxValue){
          maxValue=Value;
          maxWeight=Weight;
          maxSet=i;
       }
	   //cout << "\rSet: " << i << " Value: " << Value << " Weight" << Weight;
    }
    //cout << "\nFinal result:\n";
    cout << "Maximum set: " << maxSet << "\nValue:" << maxValue << "\tWeight:" << maxWeight << endl;
}
