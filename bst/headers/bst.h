#include <cstddef>
#include <iostream>

using namespace std;

struct bstNode{
  int value;
  bstNode *left;
  bstNode *right;
};

bstNode *insertBstNode(int value, bstNode *root); 
bstNode *insertAvlNode(int a, int b, bstNode *root);
bstNode *searchBstNode(int value, bstNode *root);
bstNode *deleteBstNode(int value, bstNode *root);
bstNode *getRightMinNode(bstNode *root);


void destroyBst(bstNode *root);
int inOrder(bstNode *root, int i);
void preOrder(bstNode *root);
void postOrder(bstNode *root);
int height(bstNode *root);