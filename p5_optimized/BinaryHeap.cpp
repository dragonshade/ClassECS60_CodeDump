        #include "BinaryHeap.h"

        /**
         * Construct the binary heap.
         * capacity is the capacity of the binary heap.
         */
         
         
         
         
        BinaryHeap::BinaryHeap( int capacity )
          : currentSize(0), array( capacity + 1 )
        {
        }

        /**
         * Insert item x into the priority queue, maintaining heap order.
         * Duplicates are allowed.
         * Throw Overflow if container is full.
         */
         
        void BinaryHeap::insert(   HeapObj*  x )
        {
         
                // Percolate up
            int hole = ++currentSize;
            for( ; hole > 1 && x->dist < array[ hole / 2 ]->dist; hole /= 2 )
                array[ hole ] = array[ hole / 2 ];
            array[ hole ] = x;
        }

        /**
         * Find the smallest item in the priority queue.
         * Return the smallest item, or throw Underflow if empty.
         */
         
          HeapObj*  BinaryHeap::findMin( )  
        {
           
            return array[ 1 ];
        }

        /**
         * Remove the smallest item from the priority queue.
         * Throw Underflow if empty.
         */
         
        void BinaryHeap::deleteMin( )
        {
           
            array[ 1 ] = array[ currentSize-- ];
            percolateDown( 1 );
        }

        /**
         * Remove the smallest item from the priority queue
         * and place it in minItem. Throw Underflow if empty.
         */
         
        void BinaryHeap::deleteMin( HeapObj*  minItem )
        {

            minItem = array[ 1 ];
            array[ 1 ] = array[ currentSize-- ];
            percolateDown( 1 );
        }

        /**
         * Establish heap order property from an arbitrary
         * arrangement of items. Runs in linear time.
         */
         
        void BinaryHeap::buildHeap( )
        {
            for( int i = currentSize / 2; i > 0; i-- )
                percolateDown( i );
        }

        /**
         * Test if the priority queue is logically empty.
         * Return true if empty, false otherwise.
         */
         
        bool BinaryHeap::isEmpty( )  
        {
            return currentSize == 0;
        }

        /**
         * Test if the priority queue is logically full.
         * Return true if full, false otherwise.
         */
         
        bool BinaryHeap::isFull( )  
        {
            return currentSize == array.size( ) - 1;
        }

        /**
         * Make the priority queue logically empty.
         */
         
        void BinaryHeap::makeEmpty( )
        {
            currentSize = 0;
        }

        /**
         * Internal method to percolate down in the heap.
         * hole is the index at which the percolate begins.
         */
         
        void BinaryHeap::percolateDown( int hole )
        {
/* 1*/      int child;
/* 2*/      HeapObj* tmp = array[ hole ];

/* 3*/      for( ; hole * 2 <= currentSize; hole = child )
            {
/* 4*/          child = hole * 2;
/* 5*/          if( child != currentSize && array[ child + 1 ]->dist < array[ child ]->dist )
/* 6*/              child++;
/* 7*/          if( array[ child ]->dist < tmp->dist )
/* 8*/              array[ hole ] = array[ child ];
                else
/* 9*/              break;
            }
/*10*/      array[ hole ] = tmp;
        }
