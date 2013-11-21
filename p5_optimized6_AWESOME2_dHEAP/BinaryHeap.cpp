        #include "BinaryHeap.h"

        /**
         * Construct the binary heap.
         * capacity is the capacity of the binary heap.
         */
         
        BinaryHeap::BinaryHeap( int capacity )
          : currentSize(0)
        {
            array= new unsigned int[capacity+1];
            size = capacity+1;
        }

        /**
         * Insert item x into the priority queue, maintaining heap order.
         * Duplicates are allowed.
         * Throw Overflow if container is full.
         */
         
        void BinaryHeap::insert(   unsigned int  x )
        {
         
                // Percolate up
            int hole =currentSize;
            ++currentSize;
            for( ; hole != 0 && ((unsigned short) x) < ((unsigned short)array[ (hole-1) / 4 ]); hole = (hole-1)/ 4 )
                array[ hole ] = array[ (hole-1) / 4 ];
            array[ hole ] = x;
        }

        /**
         * Find the smallest item in the priority queue.
         * Return the smallest item, or throw Underflow if empty.
         */
         
          unsigned int  BinaryHeap::findMin( )  
        {
           
            return array[ 0 ];
        }

        /**
         * Remove the smallest item from the priority queue.
         * Throw Underflow if empty.
         */
         
        void BinaryHeap::deleteMin( )
        {
           
            array[ 0 ] = array[--currentSize];
            percolateDown( 0 );
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
/* 2*/      unsigned int tmp = array[ hole ];
            //int index;
            int tmpchild;
           for( ; 4*hole+1 < currentSize; hole = child )  //If there is a first child
            {
/* 4*/          child = 4*hole+1;    //set child to first child
/* 5*/         // index=currentSize-child-1;  //find how many sibling the child has
                tmpchild=child;      //assign a temp index to point at first child
             //   if(index>=4){ index=3;}   //If index >=4, means the hole has 4 children, , set index to 3
              
             //   for(; index>0;index--)  //go thru the child, from child+3 , child +2 , child +1.... find the minimum stored in tmpchild
            //    {
              if(child+3<currentSize && ((unsigned short)array[tmpchild])>((unsigned short)array[child+3])) //if tmp is greater, assigned tmp to lesser sibling
                     {
                        tmpchild=child+3;
                        if(((unsigned short)array[tmpchild])>((unsigned short)array[child+2])) //if tmp is greater, assigned tmp to lesser sibling
                     {
                        tmpchild=child+2;
                     }
                     if(((unsigned short)array[tmpchild])>((unsigned short)array[child+1])) //if tmp is greater, assigned tmp to lesser sibling
                     {
                        tmpchild=child+1;
                     }
                        
                     }
            else if(child+2<currentSize && ((unsigned short)array[tmpchild])>((unsigned short)array[child+2])) //if tmp is greater, assigned tmp to lesser sibling
                     {
                        tmpchild=child+2;
                        if(((unsigned short)array[tmpchild])>((unsigned short)array[child+1])) //if tmp is greater, assigned tmp to lesser sibling
                     {
                        tmpchild=child+1;
                     }
                     }
            else if(child+1<currentSize && ((unsigned short)array[tmpchild])>((unsigned short)array[child+1])) //if tmp is greater, assigned tmp to lesser sibling
                     {
                        tmpchild=child+1;
                     }
                else;
                    
               // }
                child=tmpchild; //set child as min
/* 7*/          if( ((unsigned short)array[ child ]) < ((unsigned short)tmp))
/* 8*/              array[ hole ] = array[ child ];
                else
/* 9*/              break;
            }
/*10*/      array[ hole ] = tmp;



        }
