        //Ran Xie 
        #ifndef _BINARY_HEAP_H_INCLUDED
        #define _BINARY_HEAP_H_INCLUDED

        #include "dsexceptions.h"

        // BinaryHeap class
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


        class BinaryHeap
        {
          public:
            explicit BinaryHeap( int capacity = 100 );

            bool isEmpty( )  ;
            bool isFull( )  ;
            unsigned int findMin( )  ;

            void insert(   unsigned int x );
            void deleteMin( );
            void makeEmpty( );

          private:
            int  currentSize;  // Number of elements in heap
            unsigned int* array;        // The heap array
            int size; //size 
            void percolateDown( int hole );
        };


        #endif
