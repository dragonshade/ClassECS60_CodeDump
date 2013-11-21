#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  // students must write this
   bool NoMEANING=pushLeaf(value);


  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()




//This insert an integer into a leaf, count will be updated as well
bool LeafNode::pushLeaf(int value)   //return true if value can be inserted, false to indicate the leaf is full
{
  if(count<leafSize)    //Do this only when there is space to push 
  {
    int pos=0;
    while(value>values[pos] && pos<count)
         {
            pos++;   //Go through array (with pos < count) until integer at pos is greater or equal to value
         }
         for(int i=count-1;i>=pos;i--)
        {
            values[i+1]=values[i]; //bumping the entries after pos further back by 1;
        }
        //now we have make a spot for value at pos,insert value at pos
        values[pos]=value;
        count++; //increment the count
    return true;  //Success insertion
   }
  else {return false;} //leaf full
}




