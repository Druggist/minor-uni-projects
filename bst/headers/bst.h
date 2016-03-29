#include <cstddef>

struct bstNode{
  int value;
  bstNode *left;
  bstNode *right;
};

void insertBstNode(int value, bstNode *leaf); 
void searchBstNode(int value);
void addBst();
void deleteBstNode();
void destroyBst(bstNode *leaf);