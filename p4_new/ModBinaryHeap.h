        #ifndef __MODBINARY_HEAP_H_INCLUDED__
        #define __MODBINARY_HEAP_H_INCLUDED__

        #include "dsexceptions.h"
        #include "vector.h"
        #include "trie.h"
        // ModBinaryHeap class
        //
        // CONSTRUCTION: with a negative infinity sentinel and
        //               optional capacity (that defaults to 100)
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // deleteMin( minItem )   --> Remove (and optionally return) smallest item
        // Comparable findMin( )  --> Return smallest item
        // bool isEmpty( )        --> Return true if empty; else false
        // bool isFull( )         --> Return true if full; else false
        // void makeEmpty( )      --> Remove all items
        // ******************ERRORS********************************
        // Throws Underflow and Overflow as warranted

        class ModBinaryHeap
        {
          public:
            explicit ModBinaryHeap( int capacity = 257 );

            bool isEmpty( ) const;
            bool isFull( ) const;
             Trie* findMin( ) const;

            void insert(Trie* x );
            void deleteMin( );
            void deleteMin( Trie* minItem );
            void makeEmpty( );

          private:
            int currentSize;  // Number of elements in heap
            vector<Trie*> array;        // The heap array

            void buildHeap( );
            void percolateDown( int hole );
        };

       // #include "ModBinaryHeap.cpp"
        #endif
