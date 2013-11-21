router.out : router.o TripsRunner.o BinaryHeap.o HeapObj.o
	g++ -ansi -Wall -g -pg -o router.out router.o TripsRunner.o BinaryHeap.o HeapObj.o

HeapObj.o : HeapObj.cpp HeapObj.h
	g++ -ansi -Wall -g -c HeapObj.cpp

BinaryHeap.o : BinaryHeap.cpp BinaryHeap.h HeapObj.h
	g++ -ansi -Wall -g -c BinaryHeap.cpp

router.o : router.cpp TripsRunner.h router.h BinaryHeap.h HeapObj.h
	g++ -ansi -Wall -g -c router.cpp

TripsRunner.o : TripsRunner.cpp TripsRunner.h router.h CPUTimer.h BinaryHeap.h HeapObj.h
	g++ -ansi -Wall -g -c TripsRunner.cpp

clean : 
	rm -f router.out router.o  TripsRunner.o   
