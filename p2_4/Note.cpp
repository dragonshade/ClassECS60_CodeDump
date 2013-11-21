void BTree::insert(const int value)
{
    //If root is leaf
    //Do leaf insertion until it splits
    
    //Create internal node
    //Promote root pointer to internal node

    //do leaf insertion until internal node splits
    //update 
  
    //If leaf insert returns Null
    // Case1: nothing needs to be done
    // Case2: Adoption would requrie update of the internal Node
    
    



} // BTree::insert()





LeafNode* LeafNode::insert(int value)
{
    if(count!=leafSize) //if the leaf is not full
    {
     values[count]=value; //insert it to the last spot
     sortLeaf(); //We will sort the leaf after each insertion
     return NULL; // to avoid warnings for now.
    }
    else if(***){  //if leaf is full, look for right and left adoption
            //Sean's rule is to look at left?
        

    }
    else //leaf is full, adoption not possible. time to split
    {
        //create new leaf, parents points to this current node's parent
       // Sean's rule split to the right? so left Sibling is "this" pointer
        BTreeNode* newLeaf=new BTreeNode(leafSize,parent,this,this->rightSibling); 

        //grab the latter half of the leaf and move the entries to new leaf
        //we don't need to sort here it's already in order.
        int pos=0;
        for(int i=(leafSize+1)/2;i<leafSize;i++)
        {  
               newLeaf->values[pos]=values[i];
                pos++;
        }
        return newLeaf; //We only do insertion here, will leave the Internal Node adoption/split to Btree insert()
    }

}  // LeafNode::insert()

void LeafNode::SortLeaf() //Sort the integer in leaf from min to max. we only sort as we split
{


}



//void LeafNode::setMinAndMax()
//{
//    int Min=values[0];
//    int Max=values[0];
//    int MinPos=0;
//    int MaxPos=0;
//    for(int pos=1;pos<count;pos++)  //pick out the min and max 
//    {
//        if(values[pos]<Min)  
//        { 
//            Min=values[pos];
//            MinPos=pos;
//        }
//        if(values[pos]>Max)
//        {
//            Max=values[pos];
//            MaxPos=pos;        
//        }
//    }
//  if(MinPos!=MaxPos){   
//   values[MinPos]=values[0];
//    values[0]=Min;
//    values[MaxPos]=values[count-1];
//    values[count-1]=Max;
//    }
//}
