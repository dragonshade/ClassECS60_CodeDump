// Author: Ran Xie

#include "encoder.h"

Encoder::Encoder()
{
    //Innitialized this array of Trie pointers
    //storing index as Trie key
    for(int i=0;i<256;i++)
    {
        table[i]=new Trie((unsigned char)i);
        encodingTable[i].key=(unsigned char)i;
        encodingTable[i].length=0;
        encodingTable[i].count=0;
    }
    actual_sizeOfHuffman=0;
    
    
} // Encoder()


Encoder::~Encoder()
{
} // ~Encoder()

//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
void Encoder::encode(const unsigned char *message, const int size, 
  unsigned char *encodedMessage, 
    int *encodedSize)
{
    //Contrust statistics for the char in message
    Filestat(message,size);
    
    ////***************************************************************DEBUG
    ////***************************************************************DEBUG
    //for(int j=0;j<256;j++)
    //{
    // std::cout<<((LeafNode*)(table[j]->root))->key<<" : " <<table[j]->root->count<<std::endl;   
    //}
    ////***************************************************************DEBUG
    ////***************************************************************DEBUG
    
    //Building HuffmanTree using the statistics
    BottomUpHuffman();
    //Construct Encoding Table
    construct_encodingTable(huffman->root,0);
    //Construct Masking table    
    construct_maskingTable();
    ///DEBUGGING
    //for(int j=0;j<256;j++)
    //{
    //if(encodingTable[j].length!=0)
    //{
    //    std::cout<<encodingTable[j].key<<std::endl;
    // for(int i=0;i<8;i++)
    // {
    //     std::cout<<maskingTable[i][encodingTable[j].key]<<std::endl;
    // }
    //}
    //}
    ///DEBUGGING
    //NOW WE ARE READY TO WRITE ENCODED MESSAGE TO FILE
    
    
    //*****************************************************************************
    //    Format for the encoded message
    // TotalSize|HUffmanTreeSize| int| char.....int|char|message....|000000000|
    //    int          int       codes key                message    leftover bits
    //*****************************************************************************
    //econdedSize = (sum {frequency* encoding length in bits/8}) +1 + huffmanTreesize(in bytes) + 4 bytes
       
    //CALCULATING THE ENCODED FILE SIZE AND HUFFMANTREE SIZE
    
   //BinaryHeap EncodingHeap(257);
    int sum=32; //sum itself is 32 bits
    int huffmanSize=4; //huffmanSize itself its 4 bytes
    for(int i=0;i<256;i++)
    {
        if(encodingTable[i].count!=0)
        {
            sum+= encodingTable[i].count*encodingTable[i].length;   //counts the bit of the encoded message
            //EncodingHeap.insert(encodingTable[i]); //Push them to the heap
            huffmanSize+=6; // char(size)|int|char(6 bytes) 48bits
        }               
    }
    sum= sum+huffmanSize*8;
    sum=(sum+1)/8; //converts to byte, add a few more free bytes
    //encodedMessage =new unsigned char[sum]();   //initialize encodedmessage array to 0;
    *(encodedSize)=sum;  //set encodedSize
    
    
    //Writing HuffmanTree at the beginning of encoding message
    unsigned int encode_index=0;
    //we store the UncompressedFile size here
    *((unsigned int *)&encodedMessage[encode_index])=size;
    encode_index+=4;
    *((unsigned int *)&encodedMessage[encode_index])=huffmanSize;
    encode_index+=4;
    
    
    //STATES: sum(4)|huffmanSize(4)|....  encode_index at 8;
    
    for(int table_index=0;table_index<256;table_index++)
    {
        if(encodingTable[table_index].count!=0)
        {
            encodedMessage[encode_index]=encodingTable[table_index].length;
            encode_index++;
            *((unsigned int *)&encodedMessage[encode_index])=encodingTable[table_index].code;
            encode_index+=4;
            encodedMessage[encode_index]=encodingTable[table_index].key;
            encode_index++;            
        }       
    }
    /////////////////////////DEBUG
    //std::cout<<std::hex;
    // //DEBUGG
    //std::cout<<"compressed size:"<<sum<<std::endl;
    ////DEBUGG
    //std::cout<<"original size:"<<*((unsigned int *)&encodedMessage[0])<<std::endl;
    //std::cout<<"tree size:"<<*((unsigned int *)&encodedMessage[4])<<std::endl;
    //for(unsigned int i=8;i<encode_index;)
    //{
    //    //std::cout<<(int)encodedMessage[i];
    //    i++;
    //    std::cout<<"|"<<(unsigned int)encodedMessage[i];
    //    i+=4;
    //    //std::cout<<encodedMessage[i];
    //    i++;
    //}
    //std::cout<<std::endl;
    //////////////////////DEBUG
    
    int starting_pos=0;
    //Write HuffmanTree at encoded Messange head HUffmanSize|char(size) 1byte|00..000encoding(4byte)|char|....
    //Start writing the encoding message
    for(int message_index=0;message_index<size;message_index++)
    {
        unsigned char k=message[message_index]; //read a char k
       
       while(starting_pos>=8)  //always starts from first byte of the 4 allocated as int
      {
          encode_index++;
          starting_pos-=8;
      }
      //std::cout<<std::endl;
      //std::cout<<"Parsing:"<<k<<"  pos:"<<starting_pos << "  index:"<<encode_index<<" Encoding:"<<maskingTable[starting_pos][k]<<std::endl;

      for(int temp_index=0;temp_index<4;temp_index++)
      {
        ((unsigned char*)((unsigned int*)&encodedMessage[encode_index]))[temp_index] |= ((unsigned char*)&maskingTable[starting_pos][k])[3-temp_index];
        //std::cout<<std::hex;
        //std::cout<<((unsigned int)encodedMessage[encode_index])<<" ";
      }           
      
        starting_pos+=encodingTable[k].length;  //update starting position for the next encode
    }
     
}  // encode()

//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
void Encoder::Filestat(const unsigned char *message, const int size)
{
    //Scan through the file and map the char to the proper spot on the table(hashing)
    //increment the counts.
    for(int i=0; i<size; i++)
    {
        table[message[i]]->root->count++;
        encodingTable[message[i]].count++;
    }
    
}

//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
//this construct encodingTable to store the length and code of each char.
void Encoder::construct_encodingTable(TrieNode* root,unsigned int code=0)  //code always starts with 1
{
    //Traverse the tree and generate code for keys
    //Then store them in Encoding encodingTable[256]
    if(root)
    {
        if(root->leftChild==0 && root->rightChild==0)
        {
         encodingTable[((LeafNode*)root)->key].code=code;
         encodingTable[((LeafNode*)root)->key].length=root->depth;
         //std::cout<<"key: "<<((LeafNode*)root)->key <<" code : "<<code<<" legnth: "<<root->depth<<std::endl;
        }
        construct_encodingTable(root->rightChild, ((code <<1) | 1));
        construct_encodingTable(root->leftChild, (code <<1));
    }
}

//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
//this shifts bits to construct masking table
void Encoder::construct_maskingTable()
{
    for(int i=0;i<256;i++)
    {
        for(int j=0;j<8;j++)
        {
            //at j=0,  code << 32-length bits
            //at j=k,  code << 32-length -k bits
            unsigned int code_shifted_to_end=(encodingTable[i].code << (32-encodingTable[i].length));
            maskingTable[j][encodingTable[i].key]= (code_shifted_to_end >> j);
        }
    }
}

//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
//************************************************************************
//this build huffman tree bottom up from the leaf nodes
void Encoder::BottomUpHuffman()
{
    ModBinaryHeap bheap(257);
    for(int i=0;i<256;i++)
    {
        if(table[i]->root->count!=0) //ignore all char that do not appear
        { 
            bheap.insert(table[i]);
            actual_sizeOfHuffman++;
        }
    }
    
    while(1)
    {
       Trie* Min1=bheap.findMin();
       bheap.deleteMin();
       if(bheap.isEmpty())  //when the heap is empty, we have built Min1 the huffman tree
       {
         huffman=Min1;  //assign the huffman tree to point at Min1
         return;
       }
       Trie* Min2=bheap.findMin();
       bheap.deleteMin();
       Min2->combine(Min1);
       
       bheap.insert(Min2);
    }
}
