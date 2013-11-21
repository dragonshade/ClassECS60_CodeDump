encoder.out : decoder.o encoder.o encoderRunner.o trie.o ModBinaryHeap.o
	g++ -ansi -Wall -g -o encoder.out decoder.o encoder.o encoderRunner.o trie.o ModBinaryHeap.o

HeapObj.o : HeapObj.cpp HeapObj.h
	g++ -ansi -Wall -g -o HeapObj.cpp

ModBinaryHeap.o : ModBinaryHeap.cpp ModBinaryHeap.h trie.h
	g++ -ansi -Wall -g -c ModBinaryHeap.cpp

trie.o : trie.cpp trie.h
	g++ -ansi -Wall -g -c trie.cpp

decoder.o : decoder.cpp decoder.h trie.h
	g++ -ansi -Wall -g -c decoder.cpp

encoder.o : encoder.cpp encoder.h trie.h
	g++ -ansi -Wall -g -c encoder.cpp

encoderRunner.o : encoderRunner.cpp CPUTimer.h encoder.h decoder.h 
	g++ -ansi -Wall -g -c encoderRunner.cpp

clean : 
	rm -f encoder.out decoder.o  encoder.o  encoderRunner.o *.o   
