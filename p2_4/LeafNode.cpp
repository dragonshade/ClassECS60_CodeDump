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



void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()



LeafNode* LeafNode::insert(int value)
{
    //if(count==0)  //if leaf is empty go ahead and insert
    //{ values[0]=value;}
    //else
    
       if(!pushLeaf(value)) //if direction insertion fails
        {
          if(!Adoption(value)) //look at possibility of Adoption
            {

                return leafSplit(value); //if adoption doesn't work, do split
            }
        }


  return NULL; // to avoid warnings for now.
}  // LeafNode::insert()


bool LeafNode::Adoption(int value) //if it returns false, then we should split
{
  bool NoMEANING;
  if(leftSibling!=NULL)  //check if leftSibling exists at all
  {  
         if(leftSibling->getCount()<leafSize) // Look to left to see if there is spot (Sean's rule)
         {
           NoMEANING=((LeafNode*)leftSibling)->pushLeaf(values[0]);  //push the min onto the left
  	    count--; //update count
            for(int i=1;i<count+1;i++) {values[i-1]=values[i];}  //min is gone, bump everyone up
            NoMEANING=pushLeaf(value); //now push value in the leaf
            return true;
         }
  }
  
  if(rightSibling!=NULL)   //check if rightSibling exists at all
  {
         if(rightSibling->getCount()<leafSize)//Look to the right for space
        {
	   	   if(value>values[count-1]) //check if value > max
         	   {
			NoMEANING=((LeafNode*)rightSibling)->pushLeaf(value); //If it is, give value to the rightSibling
               
		   }
		   else  //else, give max to the rightSibling and push value in the current leaf
		  {
			NoMEANING=((LeafNode*)rightSibling)->pushLeaf(values[count-1]); //Give max to rightSibling
			count--; //decrement count to remove max
			NoMEANING=pushLeaf(value); //now insert the value since max is gone
		      
  	     	  }
           
          return true;
        }
  }
  return false; //if adoption fails
}

//This basically do Splitting in sean's rule, with new leaf all hooked up. And return pointer to new leaf
LeafNode* LeafNode::leafSplit(int value)
{
   bool NoMEANING;
    LeafNode* newLeaf=new LeafNode(leafSize,NULL,this,rightSibling); //creating independent newLeaf, leaves the configuration to upper layer
   if(rightSibling!=NULL)  //Check if RightSibling exists at all (Root is leaf case, there is no rightSibling)
    {
    rightSibling->setLeftSibling((BTreeNode*)newLeaf); //Set the node on the right of "this" to point to new node
    }
    rightSibling=(BTreeNode*)newLeaf; //Set "this" to point to new node
   
     //We need to insert first then split
     int tempMax;
     if(value<values[count-1]) //if value < max
     {
       tempMax=values[count-1]; //we store the max in temp since max will always be in the new leaf
       count--; //we decrement the count, so we are basically removing max
       NoMEANING=pushLeaf(value); //here we push the value in after removing max
     }
     else{ tempMax=value;}

    int i=0;
    for(int pos=(leafSize+1)/2;pos<leafSize;pos++)
    {   //This copy the values from L/2 roof to the next leaf; It's in order since values[] are always in order
        newLeaf->values[i]=values[pos];
        i++;
        (newLeaf->count)++;  //increment count of elements in the new leaf
	count--; //decrement the count of elements in the old leaf
    }
    //After copying, we now insert the max to the new Leaf;
    NoMEANING=newLeaf->pushLeaf(tempMax);  
    return newLeaf;
}


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
  else {return false;} //leaf full   DEBUGGING
}


