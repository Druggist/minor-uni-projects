#include <cstddef>

struct bstNode{
  int value;
  bstNode *left;
  bstNode *right;
};

void insertBstNode(int value, bstNode *leaf); 
bstNode *searchBstNode(int value, bstNode *leaf);
void addBst();
void deleteBstNode();
void destroyBst(bstNode *leaf);