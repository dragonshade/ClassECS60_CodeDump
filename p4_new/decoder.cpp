// Author: Ran Xie

#include "decoder.h"

Decoder::Decoder()
{
  huffman= new Trie('0');
  huffman->root->rightChild=0;
  huffman->root->leftChild=0;
} // Decoder()


Decoder::~Decoder()
{
} // ~Decoder()


void Decoder::decode(const unsigned char* encodedMessage, const int encodedSize, 
  unsigned char* decodedMessage, int *decodedSize)
{
    int pos=0;
    //Read the first unsigned int to know the uncompressed file size
    unsigned int originalSize =*((unsigned int*)&encodedMessage[pos]);
    pos+=4;
    //Read the next unsigned int to know the tree ends at pos Treesize
    unsigned int Treesize= *((unsigned int*)&encodedMessage[pos]); 
    pos+=4;
    *(decodedSize)=originalSize; //Set decoded Size
    //DEBUGG
    //std::cout<<"encoded Size: "<<encodedSize<<std::endl;
    //std::cout<<"original Size: "<<originalSize<<std::endl;
    //std::cout<<"tree size: "<<Treesize<<std::endl;
    //DEBUGG
    //This construct huffman tree 
    TraversalConstruction(encodedMessage,pos,Treesize+4);
    //DEBUGG
   // Print_huffman(huffman->root,0);
    //DEBUGG
    //Since the huffmantree ends at pos=Treesize, we start from there
    //We now start the coding
    pos=Treesize+4;  //huffmantree size + 4 byte(original file size) for starting position for decoding
    //std::cout<<"At starting pos: "<<(int)encodedMessage[pos]<<std::endl;
     
       unsigned char mask= (1 << 7);
       TrieNode* pt = huffman->root;
       unsigned int decode_Index=0;
      //STOP the decoding when the original file size is reached
    while(decode_Index< originalSize)
    {
        //Do this until pt reaches childnode
         while(pt->leftChild!=0 || pt->rightChild!=0)
         {  
               if((encodedMessage[pos] & mask)!=0) //if bit read is 1, go right
                 {
                     pt=pt->rightChild;
                     //std::cout<<"1";
                 }
             else{
                 pt=pt->leftChild;  //if bit read is 0, go left
                 //std::cout<<"0";
                 }
                 
            mask >>= 1; //decrement the mask for lower bits
            
             if(mask==0) //if mask is 0, we need to move to next byte
            {
               pos++;   
               mask=(1 << 7);  //reset the mask
               //std::cout<<"0";
            }
         }
       //if(pt->rightChild==0 && pt->leftChild==0)
        //{
          decodedMessage[decode_Index]= ((LeafNode*)pt)->key; //put the key on the childnode in the decoded msg
         //std::cout<<decodedMessage[decode_Index];
         decode_Index++; //move to the next
         pt=huffman->root; //RESET pt
       // }else {return;}
     }    
} // decode()


void Decoder::TraversalConstruction(const unsigned char *message, int pos,int Treesize)
{
    //pos is the position in the message at the beginning of the tree
    //Treesize is the size of the huffman tree read from the message
    //pt is the temp trienode pointer that gets reset to root after every iteration
    TrieNode* pt;
    //  length(char)(1byte)| encoding(int)(4 bytes)| key(char)(1byte)|...
    //       /|\
    //       pos
   while(pos<Treesize) //THIs will stop at position Treesize
   {
    //std::cout<<"pos: "<<pos<<std::endl;
    pt=huffman->root;
    unsigned char length=message[pos]; // READ THE LENGTH OF ENCODING, to position mask
    pos++;
    unsigned int code= *((unsigned int*)&message[pos]); //READ the encoding
    pos+=4;
    unsigned char k=message[pos];    //Read the key
    pos++;
    unsigned int mask = (1 << ((int)length-1));
    //std::cout<<"key :"<<k<<std::endl;
    //std::cout<<"code :"<<code<<std::endl;
    //std::cout<<"length:"<<(int)length<<std::endl;
    //std::cout<<"mask"<<mask<<std::endl;
    //std::cout<<std::endl;
    
    while(mask>1)
    {
        if(( mask & code )!=0) 
        {
            if(pt->rightChild!=0)
            {
                pt=pt->rightChild;
            }
            else pt=huffman->createRightChild(pt);
        }
        if((mask & code)==0)
        {
            if(pt->leftChild!=0)
            {
                pt=pt->leftChild;
            }
            else pt=huffman->createLeftChild(pt);
        }
        mask >>=1;
    }
    
    if((mask & code)!=0)
    {
        huffman->createRightChildLeaf(pt,k);
    }
    if((mask & code)==0)
    {
        huffman->createLeftChildLeaf(pt,k);
    }
  }
    
}

void Decoder::Print_huffman(TrieNode* root,unsigned int code=0){
  if(root)
  {
    if(root->leftChild==0 && root->rightChild==0)
    {
      std::cout<<"key: "<<((LeafNode*)root)->key<<std::endl;
      std::cout<<"code: "<<code<<std::endl;
    }
    Print_huffman(root->leftChild,(code<<1));
    Print_huffman(root->rightChild,((code<<1)|1));
  }
  
  
}