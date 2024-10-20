all: hashtable

hashtable: main.o HashTable.o
    g++ main.o HashTable.o -o hashtable

main.o: main.cpp
    g++ -c main.cpp

HashTable.o: HashTable.cpp HashTable.h
    g++ -c HashTable.cpp

clean:
    rm -f *.o hashtable
