class Graph{
	private:
		bool **adjacencyMatrix;
		short int **edgeList;
		short int **adjacencySSList; //subsequent 
		short int **adjacencyACList; //antecendent
		short int **adjacencyPList; //passive
		short int ** graphMatrix;
		int nodesCount;
		int arcsCount;
		void fillAM(int nodesCount);
		void fillEL(int arcsCount);
		void fillASSCL(int nodesCount);
		void fillAACL(int nodesCount);
		void fillAPL(int nodesCount);
		void fillGM(int nodesCount);
	public:
		Graph(int nodesCount, int arcsCount); //filling matrix
		~Graph();
};