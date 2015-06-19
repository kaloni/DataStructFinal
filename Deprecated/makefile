all: project

project: main.o heap.o hashtable.o graph.o
	g++ main.o heap.o hashtable.o graph.o -o project

main.o: main.cpp
	c++ -c main.cpp

heap.o: HeapType.cpp
	g++ -c HeapType.cpp

hashtable.o: HashTable.cpp
	g++ HashTable.cpp -o hashtable.o

graph.o: Graph.cpp
	g++ Graph.cpp -o graph.o


