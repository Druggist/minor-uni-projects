#include "../headers/bst.h" 

void insertBstNode(int value, bstNode *leaf){
	if(leaf != NULL){
		if(value < leaf->value) insertBstNode(value, leaf->left);
		else insertBstNode(value, leaf->right);
	}else{
		leaf = new bstNode;
		leaf->value = value;
		leaf->left = NULL;
		leaf->right = NULL;
	}
}
 
bstNode *searchBstNode(int value, bstNode *leaf){
	if(leaf != NULL) {
    	if(value == leaf->value) return leaf;
		if(value < leaf->value) return search(value, leaf->left);
    	else return search(value, leaf->right);
  	} else return NULL;
}

void destroyBst(bstNode *leaf){
	if(leaf != NULL){
		destroyBst(leaf->left);
		destroyBst(leaf->right);
		delete leaf;
	}
}