#include "../headers/bst.h" 

bstNode *insertBstNode(int value, bstNode *root){
	if(root != NULL){
		if(value < root->value) root->left = insertBstNode(value, root->left);
		else root->right = insertBstNode(value, root->right);
	}else{
		root = new bstNode;
		root->value = value;
		root->left = NULL;
		root->right = NULL;
	}
	return root;
}

bstNode *searchBstNode(int value, bstNode *root){
	if(root != NULL) {
    	if(value == root->value) return root;
		if(value < root->value) return searchBstNode(value, root->left);
    	else return searchBstNode(value, root->right);
  	} else return NULL;
}

bstNode *deleteBstNode(int value, bstNode *root){
  	if(root == NULL) return root;
  	else if(value < root->value) root->left = deleteBstNode(value, root->left);
  	else if(value > root->value) root->right = deleteBstNode(value, root->right);
  	else {
    	if(root->left == NULL && root->right == NULL){
    		delete root;
      		root = NULL;
    	} else if(root->left == NULL){
      		bstNode *temp = root;
      		root = root->right;
      		delete temp;
    	} else if(root->right == NULL){
    		bstNode *temp = root;
    		root = root->left;
      		delete temp;
    	} else { 
      		bstNode *temp = getRightMinNode(root->right);
      		root->value = temp->value;
      		root->right = deleteBstNode(temp->value, root->right);
    	}
  	}
  	return root;
}

bstNode *getRightMinNode(bstNode *root){
	while(root->left != NULL) root = root->left;
	return root;
}
 
void inOrder(bstNode *root){
  	if(root == NULL) return;
  	inOrder(root->left);
  	cout << root->value << " ";
  	inOrder(root->right);
}

void preOrder(bstNode *root){
  	if(root == NULL) return;
  	cout << root->value << " ";
  	preOrder(root->left);
  	preOrder(root->right);
}

void postOrder(bstNode *root){
	if(root == NULL) return;
	preOrder(root->left);
	preOrder(root->right);
  	cout << root->value << " ";
}

int height(bstNode *root){
	if(root == NULL) return -1;
	int leftHeight, rightHeight;
	leftHeight = height(root->left);
	rightHeight = height(root->right);
  	return max(leftHeight, rightHeight) + 1;
}

void destroyBst(bstNode *root){
	if(root != NULL){
		destroyBst(root->left);
		destroyBst(root->right);
		delete root;
	}
}

