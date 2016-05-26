#include <vector>
#include <random>
#include <algorithm> 
#include <iostream>

using namespace std;

class Cycles{
	private:
		random_device rd;
		vector<vector<unsigned int>> adjacencyList;

		int nodesCount;
		int edgesCount;
		bool debug;

		void fill(bool nonHamiltonian);
		void insertEdge(int node1, int node2);
		
	public:
		Cycles(unsigned int nodesCount, float saturation, bool nonHamiltonian = false);

		
};