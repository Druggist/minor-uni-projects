#include "../headers/data.h"  

int elements, size;
int *data;

random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> dist(-10000000, 10000000); //set random range

void setSize(int s){
	elements = s;
	size = (elements / 10) * 11;
}

void generateData(){
	if(elements >= 10){
		destroyData();
		data = new int[size];
		for(int i = 0; i < size; i++){
			data[i] = dist(mt);
			/*for(int j = 0; j < i; j++) {
				if(data[i] == data[j]){
					i--;
					break;
				}
			}*/
		}
	}
}

void sortData(){
	int gap, temp;
    for (gap = elements / 2; gap > 0; gap /= 2){
        for (int i = gap; i < elements; i++){
            for (int j = i - gap; j >= 0 && data[j] > data[j + gap]; j -= gap) {
                temp = data[j];
                data[j] = data[j + gap];
                data[j + gap] = temp;
            }
        }
    }
}

void destroyData(){
	delete[] data;
}