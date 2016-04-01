#include <iostream>
#include <random>

using namespace std;

extern int elements, size;
extern int *data;
extern random_device rd;
extern mt19937 mt;

void setSize(int s);
void generateData();
void sortData();
void destroyData(); 