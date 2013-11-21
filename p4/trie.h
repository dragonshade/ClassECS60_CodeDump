#ifndef __TRIE_H_INCLUDED__
#define	__TRIE_H_INCLUDED__

class TrieNode{
    public:
     int count;
     TrieNode* leftChild;
     TrieNode* rightChild;
     int depth; //length of encoding
};

class LeafNode:public TrieNode{
    public:
    unsigned char key;
    
};


class Trie{
    public:
    //METHOD
    Trie(unsigned char key);
    //For constructing huffman tree from bottom up
    void combine(Trie* RightTrie);
    //Update depth
    void depthUpdate(TrieNode*);
    void createLeftChild(TrieNode* pt);
    void createRightChild(TrieNode* pt);
    void createLeftChildLeaf(TrieNode* pt,unsigned char k);
    void createRightChildLeaf(TrieNode* pt,unsigned char k);
    //DATA
    TrieNode* root;

};

#endif  /* TRIE_H */