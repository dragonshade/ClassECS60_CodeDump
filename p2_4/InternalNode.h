#ifndef InternalNodeH
  #define InternalNodeH

#include "BTreeNode.h"

class InternalNode:public BTreeNode
{
  int internalSize;
  BTreeNode **children;
  int *keys;
  
 public:
  void updateChildrenLinks();
  int getCount();
  void setLeftSibling(BTreeNode* left);
  void setRightSibling(BTreeNode* right);
  void update(); //Update keys
  void IncrementCount(int increment);
  InternalNode* splitInternal(BTreeNode* newChild);
  bool pushInternal(BTreeNode * newChild);
  InternalNode* AttachChildNode(BTreeNode* node);
  InternalNode(int ISize, int LSize, InternalNode *p,
    BTreeNode *left, BTreeNode *right);
  int getMinimum()const;
  InternalNode* insert(int value); // returns pointer to new InternalNode
    // if it splits else NULL
  InternalNode* insert(BTreeNode *oldRoot, BTreeNode *node2);
 // void insert(BTreeNode *oldRoot, BTreeNode *node2); // if root splits use this
  void insert(BTreeNode *newNode); // from a sibling
  void print(Queue <BTreeNode*> &queue);
}; // InternalNode class

#endif
