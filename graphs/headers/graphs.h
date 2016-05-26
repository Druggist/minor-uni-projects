#include <vector>
#include <random>
#include <algorithm> 
#include <iostream>

using namespace std;

class Graph{
	private:
		random_device rd;

		vector <bool> visited; 
		
		vector <int> vInC; // number of entering arches for each node
		vector <int> result;	// sort result
		
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

		void AM_DFS(int v);
		void ASSCL_DFS(int v);
		void EL_DFS(int v);

		void AM_BFS(int v);
		void ASSCL_BFS(int v);
		void EL_BFS(int v);
		
	public:
		Graph(unsigned int nodesCount); //filling matrix
		void sort(int mode);

		
};