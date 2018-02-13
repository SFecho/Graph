
CC = g++ 

all: node ol_node adj_Node ol_vertex adj_vertex ol_graph test main

#==============================================

node: Node.cpp 
	$(CC) -c Node.cpp -g -o Node.o

ol_node: OLNode.cpp
	$(CC) -c OLNode.cpp -g -o OLNode.o

adj_Node:
	$(CC) -c AdjNode.cpp -g -o AdjNode.o

#==============================================

ol_vertex: OLVertex.cpp
	$(CC) -c OLVertex.cpp -g -o Vertex.o

adj_vertex: AdjVertex.cpp
	$(CC) -c AdjVertex.cpp -g -o AdjVertex.o

#===============================================	

ol_graph: OLGraph.cpp
	$(CC) -c OLGraph.cpp -g -o OLGraph.o

#===============================================
	
test: test.cpp 
	$(CC) -c test.cpp -g -o test.o	
	
main: Node.o OLNode.o Vertex.o OLGraph.o test.o
	$(CC) Node.o OLNode.o AdjNode.o Vertex.o AdjVertex.o OLGraph.o test.o -p -g -o graph


