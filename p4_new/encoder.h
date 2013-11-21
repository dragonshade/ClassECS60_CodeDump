#ifndef __ENCODER_H_INCLUDED__
#define	__ENCODER_H_INCLUDED__
#include <iostream> //DEBUGG
#include "trie.h"
#include "ModBinaryHeap.h"

class Encoding{
 public:
    unsigned char key;
    int length;
    unsigned int code;
    int count;
};

class Encoder
{
public:
  Encoder();
  void encode(const unsigned char *message, const int size, 
    unsigned char *encodedMessage, int *encodedSize);
  ~Encoder();
private:
    //Filestat scans thru the file and collect char count in table.
    void Filestat(const unsigned char *message, const int size);
    void construct_encodingTable(TrieNode* root,unsigned int code);
    void construct_maskingTable();
    void BottomUpHuffman();
    Trie* huffman;
    Trie* table[256];
    Encoding encodingTable[256];  //we can sort items by length
    unsigned int maskingTable[8][256]; //bit mask [starting pos][char]
    
     //This records the number of character actually appears
    int actual_sizeOfHuffman;
    
    
};


#endif	/* ENCODER_H */

