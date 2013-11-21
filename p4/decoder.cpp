// Author: Ran Xie

#include "decoder.h"

Decoder::Decoder()
{
    
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
    //This construct huffman tree 
    TraversalConstruction(encodedMessage,pos,Treesize);
    //Since the huffmantree ends at pos=Treesize, we start from there
    //We now start the coding
    pos=Treesize; 
    unsigned char mask= (1 << 7);
    TrieNode* pt = huffman->root;
    unsigned int decode_Index=0;
    
    //STOP the decoding when the original file size is reached
    while(decode_Index< originalSize)
    {
        //Do this until pt reaches childnode
         while(pt->leftChild!=0 && pt->rightChild!=0)
         {  
               if((encodedMessage[pos] & mask)==1) //if bit read is 1, go right
                 {
                     pt=pt->rightChild;
                 }
             else{
                 pt=pt->leftChild;  //if bit read is 0, go left
                 }
                 
            mask >>= 1; //decrement the mask for lower bits
            
             if(mask==0) //if mask is 0, we need to move to next byte
            {
               pos++;   
               mask=(1 << 7);  //reset the mask
            }
         }
    
         decodedMessage[decode_Index]= ((LeafNode*)pt)->key; //put the key on the childnode in the decoded msg
         decode_Index++; //move to the next 
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
    pt=huffman->root;
    unsigned char length=message[pos]; // READ THE LENGTH OF ENCODING, to position mask
    pos++;
    unsigned int code= *((unsigned int*)&message[pos]); //READ the encoding
    pos+=4;
    unsigned char k=message[pos];    //Read the key
    pos++;
    unsigned int mask = (1 << length);
    
    //while((mask & k) !=1)   //shift mask until it hits the most significant bit of the code 000111.. ex
    //{ mask >>= 1;}          //since code always starts with 1
    
    while(mask>1)
    {
        if(( mask & code )==1) 
        {
            if(pt->rightChild!=0)
            {
                pt=pt->rightChild;
            }
            else huffman->createRightChild(pt);
        }
        if((mask & code)==0)
        {
            if(pt->leftChild!=0)
            {
                pt=pt->leftChild;
            }
            else huffman->createLeftChild(pt);
        }
        mask >>=1;
    }
    
    if((mask & code)==1)
    {
        huffman->createRightChildLeaf(pt,k);
    }
    if((mask & code)==0)
    {
        huffman->createLeftChildLeaf(pt,k);
    }
  }
    
}