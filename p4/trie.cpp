#include "trie.h"

Trie::Trie(unsigned char key)
{
    root= new LeafNode;
    root->count=0;
    ((LeafNode*)root)->key=key;
    root->leftChild=0;
    root->rightChild=0;
    root->depth=0;
}

void Trie::combine(Trie* RightTrie)
{
    TrieNode* temp = new TrieNode;
    temp->leftChild=root;
    temp->rightChild=RightTrie->root;
    temp->count= root->count+RightTrie->root->count;
    root=temp;
    depthUpdate(root);
}


void Trie::depthUpdate(TrieNode* root)
{
    if(root!=0)
    {
    depthUpdate(root->rightChild);
    depthUpdate(root->leftChild);
    root->depth++;
    }
}

void Trie::createLeftChild(TrieNode* pt)
{
        root->leftChild=new TrieNode;
        root->leftChild->rightChild=0;
        root->leftChild->leftChild=0;      
}
    
void Trie::createRightChild(TrieNode* pt)
{
        root->rightChild=new TrieNode;
        root->rightChild->rightChild=0;
        root->rightChild->leftChild=0;      
}
    
void Trie::createLeftChildLeaf(TrieNode* pt,unsigned char k)
{
        pt->leftChild=new LeafNode;
        pt->leftChild->rightChild=0;
        pt->leftChild->leftChild=0;
        ((LeafNode*)pt->leftChild)->key=k;
}
    
void Trie::createRightChildLeaf(TrieNode* pt,unsigned char k)
{
        pt->rightChild=new LeafNode;
        pt->rightChild->rightChild=0;
        pt->rightChild->leftChild=0;
        ((LeafNode*)pt->rightChild)->key=k;
}