#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
    int* values;
      
    public:
        
    //Splits leaf to a new leaf and configure that new leaf, returns the pointer to new leaf
    LeafNode* leafSplit(int value);  //*******************
    //Return false if Adoption fails, True if success
    bool Adoption(int value); //**********************
    //push value into a leaf and shift all entries up, return true if success
    bool pushLeaf(int value);
    LeafNode(int LSize, InternalNode *p, BTreeNode *left,BTreeNode *right);
    int getMinimum() const;
    LeafNode* insert(int value); // returns pointer to new Leaf if splits
     // else NULL
    void print(Queue <BTreeNode*> &queue);

}; //LeafNode class

#endif
