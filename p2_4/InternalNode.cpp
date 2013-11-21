#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
   keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()



InternalNode* InternalNode::insert(int value)
{
   //Scan the key until the value fits in
    int pos=1;
    while(value>keys[pos] && pos<count)
    {
        pos++;    
    }
    
    //insert value. If children is leafNode, it will do leaf insert,
    //if children is internal node it will call the internalNode insert recursively
    //until it goes down to the leaf. We need the cast it to 
    BTreeNode* node=((BTreeNode*) (children[pos-1]->insert(value)));

    if(node==NULL)
    {  //Nothing big happens simply update the Internal Nodes (adpotion at least)
      for(int i=0;i<count;i++)
      keys[i]=children[i]->getMinimum();
    }
    else{
        //try attach the node to current
        return AttachChildNode(node);              
        }
             
  return NULL; // to avoid warnings for now.
} // InternalNode::insert()


InternalNode* InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
   //if root splits ( which produces node2), we must promote root
   InternalNode* newRoot= new InternalNode(internalSize,leafSize,NULL,NULL,NULL);
  //Since we always split to the right
  newRoot->children[0]=oldRoot;
  newRoot->children[1]=node2;
  newRoot->keys[0]=oldRoot->getMinimum();
  newRoot->keys[1]=node2->getMinimum(); //storing the min of corresponding child.
                                      //GetMin is recursive call all the way down to the leaf
  newRoot->count=2;
  newRoot->updateChildrenLinks();
   return newRoot; //this promotes current root to the newRoot
   
   
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
   
   
   
} // InternalNode::insert()





//This splits an InternalNode and return the new node pointer
InternalNode* InternalNode::splitInternal(BTreeNode* newChild)
{
   update(); //update before doing anything since child min might have changed
   //initializing the newNode and hook neighbors up
   InternalNode* newInternalNode=new InternalNode(internalSize,leafSize,NULL,this,rightSibling);
   
   if(rightSibling!=NULL)  //Check if rightSibling exists at all
   {
    rightSibling->setLeftSibling((BTreeNode*) newInternalNode);
   }
   rightSibling= (BTreeNode*) newInternalNode;
   
    BTreeNode* tempMaxChild;
   //we will store the max as temp, then remove it from the node
   if(newChild->getMinimum()<children[count-1]->getMinimum())
    {
      tempMaxChild=children[count-1];
      count--; //max is remove by decrementing count}
      //now we can insert newChild
      bool NoMEANING=pushInternal(newChild);
    }
    else  //if the newChild is larger than max, save it and do nothing
    {
      tempMaxChild=newChild;
    }
      
   //move half the children starting from (internalSize-1)/2 to internalSize-1
   //To the new node on the right
  for(int i=(internalSize+1)/2;i<internalSize;i++)
  {
      newInternalNode->pushInternal(children[i]);
      count--;
  }
   //Now we can get the max to the new node
   bool NoMEANING=newInternalNode->pushInternal(tempMaxChild);
    updateChildrenLinks();
    newInternalNode->updateChildrenLinks();
    update();
    newInternalNode->update();

  return newInternalNode;
    
}

//This attach a child node to the caller Internal node (does the sorting)
bool InternalNode::pushInternal(BTreeNode * newChild)
{
    update();
    if(count<internalSize) //If there is space 
    {
      int pos=0;
      int newChildmin=newChild->getMinimum();
      //compare the keys with the min of the new node until it finds its place
      while(newChildmin>keys[pos] && pos<count)
      {
        pos++;  
      } 
      //once the position is found, we need to insert newChild in pos
      //shift everything up
      for(int i=count-1;i>=pos;i--)
      {
        keys[i+1]=keys[i];
        children[i+1]=children[i];
      }
      
      //now insert newChild in pos
      keys[pos]=newChildmin;
      children[pos]=newChild;
      count++; //increment count
      return true; //Success!
    }
   else {return false;} //Node is full
}

InternalNode* InternalNode::AttachChildNode(BTreeNode* node)  //this attach node to current internal node
{
   bool NoMEANING;
   if(count>=internalSize)  //If current is full
        {
              //Look for adoption from neighboring nodes
            if(leftSibling!=NULL && leftSibling->getCount()<internalSize) //check if leftSibling exists at all
            {
               //if there is space on the left Sibling
              
                 ((InternalNode*)leftSibling)->pushInternal(children[0]);  //push the first child to the left Sibling since its smallest
                  for(int i=1;i<count;i++)   //shift everyone up by 1
                  {
                     keys[i-1]=keys[i];
                     children[i-1]=children[i];
                  }
                  count--; //decrement count since we have moved the min
                  NoMEANING=pushInternal(node); //now we have space to push node

                  return NULL;              
              
            }
            else if(rightSibling!=NULL && rightSibling->getCount()<internalSize) //Check if rightSibling exists at all
             { 
               //if there is space on the right Sibling
               
                if(node->getMinimum()>keys[count-1]) // if the node has minimum > the last key
                     {NoMEANING=((InternalNode*)rightSibling)->pushInternal(node); //simply push the node to the right Sibling

                     }
                else 
                    { //else push the last children to the right Sibling
                      NoMEANING=((InternalNode*)rightSibling)->pushInternal(children[count-1]);
                      count--; //decrement count since max is gone
                      // then push the node onto current Internal node
                      NoMEANING=pushInternal(node);
                      
                    }
                    return NULL;
               
               
             }
              else //if neighboring are full, split current internal node
              {   //node is the child trying to attach, return the newly split Node
                 return splitInternal(node);
                                               
              }
             
        }
        else
        {
          NoMEANING=pushInternal(node); //if InternalNode not full, just insert
          return NULL;
        }
  
}


void InternalNode::update(){
    for(int i=0;i<count;i++)   //update the entries
    keys[i]=children[i]->getMinimum();
}

void InternalNode::updateChildrenLinks(){
    if(leftSibling!=NULL)  //check if leftSibling exists
    {
      children[0]->setLeftSibling(((InternalNode*)leftSibling)->children[count-1]); //link the min child to left sibling internal node's max child
    }
    else { children[0]->setLeftSibling(NULL);}  //if doesnt exist point min child to NULL
    if(rightSibling!=NULL) //check if rightSibling exists
    {
      children[count-1]->setRightSibling(((InternalNode*)rightSibling)->children[0]); //link the max child to right Sibling internal node's min child
      
    }
    else{children[count-1]->setRightSibling(NULL);} //if doesnt exist point max child to NULL
    
    for(int i=0; i<count-2;i++)
    {
      children[i]->setRightSibling(children[i+1]);
    }
    
    for(int i=count-1;i>0;i--)
    {
      
      children[i]->setLeftSibling(children[i-1]);
    }
  return ;
}