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
	public:
		Graph(int nodesCount, arcsCount); //filling matrix
		~Graph();

}