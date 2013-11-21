#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"
#include "LeafNode.h"
#include "InternalNode.h"
using namespace std;

BTree::BTree(int ISize, int LSize):internalSize(ISize), leafSize(LSize)
{
 
   root = new LeafNode(LSize, NULL, NULL, NULL);
} // BTree::BTree()


void BTree::insert(const int value)
{
  // students must write this
  static int insertionCounter=0;
  BTreeNode* newNode= ((BTreeNode *) (root->insert(value)));  //This invokes leaf insertion or internal node insertion
  //The returned newNode is a node at the 2nd level.
  //Now we just need to take care of this node.
  insertionCounter++;
  if(insertionCounter==leafSize+1) //Now leaf root needs to be split to create an internal node
  {  
     if(newNode!=NULL) //when leaf splits and root is one of the leaf, this is a special case
      {                 //to be handled in this way
         InternalNode* newRoot= new InternalNode(internalSize,leafSize,NULL,NULL,NULL);
         bool noMEANING=newRoot->pushInternal(newNode);
         noMEANING=newRoot->pushInternal(root);
         root=(InternalNode*) newRoot;
      }
  }
 
 if(insertionCounter>leafSize+1)  //Root is internal node at this point
  {
    InternalNode* tempRoot=(InternalNode*)root;
    
    if(newNode==NULL)  //if not splitting happens
    {  
         tempRoot->update();   
    }
    else //newNode is not NULL
    {
      //if(!tempRoot->pushInternal(newNode)) //if pushInternal fails
      //{
        //need to split root and promote it
        root=tempRoot->insert((BTreeNode* )root,(BTreeNode* )newNode); 
      //} 
    }
  }   
    
} // BTree::insert()


void BTree::print()
{
  BTreeNode *BTreeNodePtr;
  Queue<BTreeNode*> queue(1000);
  queue.enqueue(root);
  while(!queue.isEmpty())
  {
    BTreeNodePtr = queue.dequeue();
    BTreeNodePtr->print(queue);
  } // while
} // BTree::print()
