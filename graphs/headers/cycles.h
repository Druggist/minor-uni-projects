#include <vector>
#include <random>
#include <algorithm> 
#include <iostream>

using namespace std;

class Cycles{
	private:
		random_device rd;
		vector<vector<unsigned int>> adjacencyList;
		vector<unsigned int> result;

		int nodesCount;
		unsigned int edgesCount;
		bool debug;

		void fill(bool nonHamiltonian);
		void insertEdge(int node1, int node2);
		void printResult();

		bool hamiltonCycleStep(int v);
		void eulerCycleStep(int v);
		
	public:
		Cycles(unsigned int nodesCount, float saturation, bool nonHamiltonian = false);
		bool findHamiltonCycle(int v);
		void findEulerCycle(int v);
};