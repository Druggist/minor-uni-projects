#include "../headers/graphs.h"

Graph::Graph(int nodesCount, int arcsCount){
	this->nodesCount = nodesCount;
	this->nodesCount = nodesCount;
	fillAM(nodesCount);
	fillEL(arcsCount);
	fillASSCL(nodesCount);
	fillAACL(nodesCount);
	fillAPL(nodesCount);
	fillGM(nodesCount);
}

void Graph::fillAM(int nodesCount){

}

void Graph::fillEL(int arcsCount){

}

void Graph::fillASSCL(int nodesCount){

}

void Graph::fillAACL(int nodesCount){

}

void Graph::fillAPL(int nodesCount){

}

void Graph::fillGM(int nodesCount){

}

Graph::~Graph(){
}