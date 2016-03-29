#include "../headers/bst.h" 
#include "../headers/data.h" 


void fillBst(bstNode *root){
	for(int i = 0; i < elements; i++) insertBstNode(data[i], root);
}

void fillBstList(bstNode *root){
	sortData();
	fillBst(root);
}

int main(int argc, char *argv[]){
	bstNode *root = NULL;
	generateData();
	fillBst(root);

	destroyBst(root);
	destroyData();
	return 0;
}

