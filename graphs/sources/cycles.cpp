#include "../headers/cycles.h"

Cycles::Cycles(unsigned int nodesCount, float saturation, bool nonHamiltonian){
	this->nodesCount = nodesCount;
	this->edgesCount = (nodesCount * (nodesCount - 1) / 2) * saturation;
	this->debug = true;

	fill(nonHamiltonian);
}

void Cycles::insertEdge(int node1, int node2){
		adjacencyList[node1].push_back(node2);
		adjacencyList[node2].push_back(node1);
}

void Cycles::fill(bool nonHamiltonian){
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, nodesCount - 1);
	int firstNode = dist(mt), nextNode, currentEdgesCount = 0;
	vector<int> cycle;
	adjacencyList.resize((nonHamiltonian)?(nodesCount + 1):(nodesCount), vector<unsigned int>(0, 0));

	cycle.push_back(firstNode);
	while(firstNode != nextNode){
		nextNode = dist(mt);
		if(find(cycle.begin(), cycle.end(), nextNode) != cycle.end() && nextNode != firstNode) nextNode = (firstNode + 1 != nodesCount)?(firstNode + 1):(firstNode - 1);
		else cycle.push_back(nextNode);
	}

	for (int i = 1; i < cycle.size(); i++){
		insertEdge(cycle[i - 1], cycle[i]);
		currentEdgesCount++;
	}

	while(currentEdgesCount < edgesCount){
		int nodes[3] = {dist(mt), dist(mt), dist(mt)};
		if(nodes[2] != nodes[1] && nodes[1] != nodes[0] && nodes[2] != nodes[0]){
			if(find(adjacencyList[nodes[2]].begin(), adjacencyList[nodes[2]].end(), nodes[1]) == adjacencyList[nodes[2]].end() && find(adjacencyList[nodes[2]].begin(), adjacencyList[nodes[2]].end(), nodes[0]) == adjacencyList[nodes[2]].end() && find(adjacencyList[nodes[0]].begin(), adjacencyList[nodes[0]].end(), nodes[1]) == adjacencyList[nodes[0]].end()){
				insertEdge(nodes[0], nodes[1]);
				insertEdge(nodes[0], nodes[2]);
				insertEdge(nodes[1], nodes[2]);
				currentEdgesCount += 3;
			}
		}
	}

	if(nonHamiltonian) this->nodesCount++;

		if(debug){
		cout<<"\nadjacencyList \n";
		for(unsigned int i = 0; i < nodesCount; i++){
			cout << i <<"->";
			for(unsigned int j = 0; j < adjacencyList[i].size(); j++) cout << adjacencyList[i][j] <<"->";
			cout <<endl;
		}
	}	
}