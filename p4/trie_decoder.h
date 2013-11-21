#ifndef TRIE_DECODER_H
#define	TRIE_DECODER_H

class DTrieNode{
    public:
     int count;
     DTrieNode* leftChild;
     DTrieNode* rightChild;
     int depth; //length of encoding
};

class DLeafNode:public DTrieNode{
    public:
    unsigned char key;
    
};


class DTrie{
    public:
    //METHOD
    DTrie(unsigned char key);
    //For constructing huffman tree from bottom up
    void combine(DTrie* RightTrie);
    //Update depth
    void depthUpdate(DTrieNode*);
    void createLeftChild(DTrieNode* pt);
    void createRightChild(DTrieNode* pt);
    void createLeftChildLeaf(DTrieNode* pt,unsigned char k);
    void createRightChildLeaf(DTrieNode* pt,unsigned char k);
    //DATA
    DTrieNode* root;

};


DTrie::DTrie(unsigned char key)
{
    root= new DLeafNode;
    root->count=0;
    ((DLeafNode*)root)->key=key;
    root->leftChild=0;
    root->rightChild=0;
    root->depth=0;
}

void DTrie::combine(DTrie* RightTrie)
{
    DTrieNode* temp = new DTrieNode;
    temp->leftChild=root;
    temp->rightChild=RightTrie->root;
    temp->count= root->count+RightTrie->root->count;
    root=temp;
    depthUpdate(root);
}


void DTrie::depthUpdate(DTrieNode* root)
{
    if(root!=0)
    {
    depthUpdate(root->rightChild);
    depthUpdate(root->leftChild);
    root->depth++;
    }
}

void DTrie::createLeftChild(DTrieNode* pt)
{
        root->leftChild=new DTrieNode;
        root->leftChild->rightChild=0;
        root->leftChild->leftChild=0;      
}
    
void DTrie::createRightChild(DTrieNode* pt)
{
        root->rightChild=new DTrieNode;
        root->rightChild->rightChild=0;
        root->rightChild->leftChild=0;      
}
    
void DTrie::createLeftChildLeaf(DTrieNode* pt,unsigned char k)
{
        pt->leftChild=new DLeafNode;
        pt->leftChild->rightChild=0;
        pt->leftChild->leftChild=0;
        ((DLeafNode*)pt->leftChild)->key=k;
}
    
void DTrie::createRightChildLeaf(DTrieNode* pt,unsigned char k)
{
        pt->rightChild=new DLeafNode;
        pt->rightChild->rightChild=0;
        pt->rightChild->leftChild=0;
        ((DLeafNode*)pt->rightChild)->key=k;
}

#endif  /* TRIE_DECODER_H */