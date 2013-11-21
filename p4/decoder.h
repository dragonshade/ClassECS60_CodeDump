#ifndef __DECODER_H_INCLUDED__
#define	__DECODER_H_INCLUDED__
#include "trie.h"

class Decoder
{
public:
  Decoder();
  ~Decoder();
  void decode(const unsigned char* encodedMessage, const int encodedSize, 
    unsigned char* decodedMessage, int *decodedSize);
  
   //Traversal construction of huffman tree top down from file
    void TraversalConstruction(const unsigned char *message, int pos,int Treesize);
private:
    Trie* huffman;
};

#endif	/* DECODER_H */

