#include <iostream>
#include "trie.h"
#include "ModBinaryHeap.h"

using namespace std;

void PrintDepth(TrieNode* root)
{
    if(root!=NULL)
    {
    cout<<root->depth<<endl;
    cout<<root->count<<endl;
    PrintDepth(root->rightChild);
    PrintDepth(root->leftChild);

    }
}


int main()
{
        Trie* A= new Trie('a');
        Trie* B=new Trie('b');
        Trie* C= new Trie('e');
        Trie* D=new Trie('f');
        BinaryHeap bheap(257);
        A->root->count=10;
        B->root->count=100;
        C->root->count=50;
        D->root->count=70;
        bheap.insert(A);
        bheap.insert(B);
        bheap.insert(C);
        bheap.insert(D);
        Trie* Min1=bheap.findMin();
        bheap.deleteMin();
        Trie* Min2=bheap.findMin();
        bheap.deleteMin();
        Min1->combine(Min2);
        bheap.insert(Min1);
        Min1=bheap.findMin();
        bheap.deleteMin();
        Min2=bheap.findMin();
        bheap.deleteMin();
        Min1->combine(Min2);
        bheap.insert(Min1);
        Min1=bheap.findMin();
        bheap.deleteMin();
        Min2=bheap.findMin();
        bheap.deleteMin();
        Min1->combine(Min2);
//       cout<<"A count:"<<A->root->count<<endl;
//       cout<<"B count:"<<B->root->count<<endl;

//        cout<<"new A count:"<<Min1->root->count<<endl;

        PrintDepth(Min1->root);
        cout<<Min1->root->leftChild->depth<<endl;
        cout<<Min1->root->rightChild->rightChild->depth<<endl;
        cout<<Min1->root->rightChild->leftChild->depth<<endl;
        cout<<Min1->root->rightChild->leftChild->rightChild->depth<<endl;
        cout<<Min1->root->rightChild->leftChild->leftChild->depth<<endl;
}
