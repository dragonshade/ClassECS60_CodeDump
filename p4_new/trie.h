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
    TrieNode* createLeftChild(TrieNode* pt);
    TrieNode* createRightChild(TrieNode* pt);
    TrieNode* createLeftChildLeaf(TrieNode* pt,unsigned char k);
    TrieNode* createRightChildLeaf(TrieNode* pt,unsigned char k);
    bool operator<(const Trie &rhs);
    bool operator>(const Trie &rhs);
    bool operator==(const Trie &rhs);
    //DATA
    TrieNode* root;

};

#endif  /* TRIE_H */