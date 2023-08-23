all : test.o hashTable.o
	g++ -g -o test test.o hashTable.o
test.o : test.cpp hashTable.h
	g++ -g -c test.cpp
hashTable.o : hashTable.cpp hashTable.h
	g++ -g -c hashTable.cpp

clean :
	rm -f test test.o hashTable.o