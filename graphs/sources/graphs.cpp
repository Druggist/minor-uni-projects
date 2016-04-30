#include "../headers/graphs.h"

Graph::Graph(unsigned int nodesCount){
	this->nodesCount = nodesCount;
	this->arcsCount = (nodesCount*(nodesCount - 1)) / 4;
	this->debug = true;

	fillAM();
	fillEL();
	fillASSCL();
	fillAACL();
	fillAPL();
	fillGM();
}

void Graph::fillAM(){
	mt19937 mt(rd());
	adjacencyMatrix.resize(nodesCount, vector<bool>(nodesCount, false));
	uniform_int_distribution<int> dist(0, arcsCount * 2 - 1);
	vector<unsigned int> arcs(arcsCount, 0);
	for(unsigned int i = 0; i < arcsCount; i++){
		arcs[i] = dist(mt);
		if(i > 0){
			bool isEqual = false;
			for(long int j = i - 1; j >= 0; j--){
				if(arcs[i] == arcs[j]){ 
					i--;
					isEqual = true;
					break;
				} 
			}
			if(!isEqual) for(long int j = i - 1; j >= 0; j--){
				if(arcs[j + 1] < arcs[j]) swap(arcs[j], arcs[j + 1]);  
				else break;
			}
		}
	}

	for(unsigned int i = 0; i < nodesCount; i++){
		for(unsigned int j = i + 1; j < nodesCount; j++){
			if(!arcs.empty()){
				int pos = (i > 0)?(j + i):(j - 1);
				if(pos == arcs[0]){
					adjacencyMatrix[i][j] = true;
					arcs.erase(arcs.begin());
				}
			}
		}
	}

	if(debug){
		cout <<"\nadjacencyMatrix \n";
		for(unsigned int i = 0; i < nodesCount; i++){
			for(unsigned int j = 0; j < nodesCount; j++) cout<<adjacencyMatrix[i][j];
			cout<<endl;
		}
	}
}

bool Graph::fillEL(){
	if(adjacencyMatrix.empty()) return false;
	edgeList.resize(arcsCount, vector<unsigned int>(2, 0));
	int arc = 0;
	for(unsigned int i = 0; i < nodesCount; i++){
		for(unsigned int j = 0; j < nodesCount; j++){
			if(adjacencyMatrix[i][j]){
				edgeList[arc][0] = i;
				edgeList[arc][1] = j;
				arc++;
			}
		}
	}

	if(debug){
		cout <<"\nedgeList \n";
		for(unsigned int i = 0; i < arcsCount; i++) cout << edgeList[i][0] <<" "<< edgeList[i][1] << endl;
	}
	return true;
}

bool Graph::fillASSCL(){
	if(adjacencyMatrix.empty()) return false;
	adjacencySSList.resize(nodesCount, vector<unsigned int>(0, 0));
	for(unsigned int i = 0; i < nodesCount; i++){
		for(unsigned int j = 0; j < nodesCount; j++){
			if(adjacencyMatrix[i][j]) {
			adjacencySSList[i].push_back(j + 1);
			}
		}
	}

	if(debug){
		cout<<"\nadjacencySubsequentList \n";
		for(unsigned int i = 0; i < nodesCount; i++){
			cout << i + 1<<"->";
			for(unsigned int j = 0; j < adjacencySSList[i].size(); j++) cout << adjacencySSList[i][j] <<"->";
			cout <<endl;
		}
	}	
	return true;
}

bool Graph::fillAACL(){
	if(adjacencyMatrix.empty()) return false;
	adjacencyACList.resize(nodesCount, vector<long int>(0, 0));
	for(unsigned int i = 0; i < nodesCount; i++){
		for(unsigned int j = 0; j < nodesCount; j++){
			if(adjacencyMatrix[i][j]) adjacencyACList[j].push_back(i + 1);
		}
	}

	if(debug){
		cout<<"\nadjacencyAntecendentList \n";
		for(unsigned int i = 0; i < nodesCount; i++){
			cout << i + 1<<"->";
			for(unsigned int j = 0; j < adjacencyACList[i].size(); j++) cout << adjacencyACList[i][j] <<"->";
			cout <<endl;
		}
	}
	return true;
}

bool Graph::fillAPL(){
	if(adjacencyMatrix.empty()) return false;
	adjacencyPList.resize(nodesCount, vector<unsigned int>(0, 0));
	for(unsigned int i = 0; i < nodesCount; i++){
		for(unsigned int j = 0; j < nodesCount; j++){
			if(!adjacencyMatrix[i][j] && !adjacencyMatrix[j][i]) adjacencyPList[i].push_back(j + 1);
		}
	}

	if(debug){
		cout<<"\nadjacencyPasiveList \n";
		for(unsigned int i = 0; i < nodesCount; i++){
			cout << i + 1<<"->";
			for(unsigned int j = 0; j < adjacencyPList[i].size(); j++) cout << adjacencyPList[i][j] <<"->";
			cout <<endl;
		}
	}
	return true;
}

bool Graph::fillGM(){
	if(adjacencySSList.empty()) return false;
	if(adjacencyACList.empty()) return false;
	if(adjacencyPList.empty()) return false;
	graphMatrix.resize(nodesCount, vector<long int>(nodesCount + 3, 0));
	for(unsigned int i = 0; i < nodesCount; i++){
		graphMatrix[i][0] = (!adjacencySSList[i].empty())?(adjacencySSList[i][0]):(0);
		graphMatrix[i][1] = (!adjacencyACList[i].empty())?(adjacencyACList[i][0]):(0);
		graphMatrix[i][2] = (!adjacencyPList[i].empty())?(adjacencyPList[i][0]):(0);

		for(unsigned int j = 0; j < adjacencySSList[i].size(); j++){
			if(j + 1 != adjacencySSList[i].size()) graphMatrix[i][adjacencySSList[i][j] + 2] = adjacencySSList[i][j + 1];
			else graphMatrix[i][adjacencySSList[i][j] + 2] = adjacencySSList[i][j];
		}

		for(unsigned int j = 0; j < adjacencyACList[i].size(); j++){
			if(j + 1 != adjacencyACList[i].size()) graphMatrix[i][adjacencyACList[i][j] + 2] = -1 * adjacencyACList[i][j + 1];
			else graphMatrix[i][adjacencyACList[i][j] + 2] = -1 * adjacencyACList[i][j];
		}

		for(unsigned int j = 0; j < adjacencyPList[i].size(); j++){
			if(j + 1 != adjacencyPList[i].size()) graphMatrix[i][adjacencyPList[i][j] + 2] = adjacencyPList[i][j + 1] + nodesCount;
			else graphMatrix[i][adjacencyPList[i][j] + 2] = adjacencyPList[i][j] + nodesCount;
		}
	}

	if(debug){
		cout<<"\ngraphMatrix \n";
		for(unsigned int i = 0; i < nodesCount; i++){
			for(unsigned int j = 0; j < nodesCount + 3; j++){
				if(graphMatrix[i][j] >= 0) cout << " ";
				cout<<graphMatrix[i][j];
			}
			cout<<endl;
		}
	}	
	return true;
}