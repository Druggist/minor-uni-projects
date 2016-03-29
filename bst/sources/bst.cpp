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
 


void destroyBst(bstNode *leaf){
	if(leaf != NULL){
		destroyBst(leaf->left);
		destroyBst(leaf->right);
		delete leaf;
	}
}