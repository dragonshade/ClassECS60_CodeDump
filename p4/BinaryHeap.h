        #ifndef __BINARY_HEAP_H_INCLUDED__
        #define __BINARY_HEAP_H_INCLUDED__

        #include "dsexceptions.h"
        #include "vector.h"
       // #include "Encoding_mask.h"

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
            explicit BinaryHeap( int capacity = 256 );

            bool isEmpty( ) const;
            bool isFull( ) const;
            const Encoding & findMin( ) const;

            void insert( const Encoding & x );
            void deleteMin( );
            void deleteMin( Encoding & minItem );
            void makeEmpty( );

          private:
            int currentSize;  // Number of elements in heap
            vector<Encoding> array;        // The heap array

            void buildHeap( );
            void percolateDown( int hole );
        };

       // #include "BinaryHeap.cpp"
        #endif
