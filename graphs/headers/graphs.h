#include <vector>
#include <random>
#include <algorithm> 
#include <iostream>

using namespace std;

class Graph{
	private:
		random_device rd;

		vector<vector<bool>> adjacencyMatrix;
		vector<vector<unsigned int>> edgeList;
		vector<vector<unsigned int>> adjacencySSList; //subsequent 
		vector<vector<long int>> adjacencyACList; //antecendent
		vector<vector<unsigned int>> adjacencyPList; //passive
		vector<vector<long int>> graphMatrix;
		int nodesCount;
		int arcsCount;
		bool debug;

		void fillAM();
		bool fillEL();
		bool fillASSCL();
		bool fillAACL();
		bool fillAPL();
		bool fillGM();
	public:
		Graph(unsigned int nodesCount); //filling matrix
};