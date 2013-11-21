router.out : router.o TripsRunner.o BinaryHeap.o
	g++ -ansi -Wall -g -pg -o router.out router.o TripsRunner.o BinaryHeap.o

BinaryHeap.o : BinaryHeap.cpp BinaryHeap.h
	g++ -ansi -Wall -g -c BinaryHeap.cpp

router.o : router.cpp TripsRunner.h router.h BinaryHeap.h
	g++ -ansi -Wall -g -c router.cpp

TripsRunner.o : TripsRunner.cpp TripsRunner.h router.h CPUTimer.h BinaryHeap.h
	g++ -ansi -Wall -g -c TripsRunner.cpp

clean : 
	rm -f router.out router.o  TripsRunner.o *.o   
