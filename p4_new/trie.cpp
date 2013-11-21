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

TrieNode* Trie::createLeftChild(TrieNode* pt)
{
        TrieNode* temp=new TrieNode;
        temp->rightChild=0;
        temp->leftChild=0;
        pt->leftChild=temp;
        return temp;
}
    
TrieNode* Trie::createRightChild(TrieNode* pt)
{
        TrieNode* temp=new TrieNode;
        temp->rightChild=0;
        temp->leftChild=0;
        pt->rightChild=temp;
        return temp;     
}
    
TrieNode* Trie::createLeftChildLeaf(TrieNode* pt,unsigned char k)
{
        TrieNode* temp=new LeafNode;
        temp->rightChild=0;
        temp->leftChild=0;
        ((LeafNode*)temp)->key=k;
        pt->leftChild=temp;
        return temp;
}
    
TrieNode* Trie::createRightChildLeaf(TrieNode* pt,unsigned char k)
{
         TrieNode* temp=new LeafNode;
        temp->rightChild=0;
        temp->leftChild=0;
        ((LeafNode*)temp)->key=k;
        pt->rightChild=temp; 
        return temp;
}

bool Trie::operator<(const Trie &rhs){return root->count < rhs.root->count;}

bool Trie::operator>(const Trie &rhs){return root->count > rhs.root->count;}

bool Trie::operator==(const Trie &rhs){return root->count == rhs.root->count;}