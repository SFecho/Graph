#pragma once
#include <stdio.h>
class Node
{
public:
	int start;
	int end;
	int weight;

	Node();

	virtual ~Node()
	{
		
	}

	Node(int start, int end, int weight) :start(start), end(end), weight(weight)
	{

	}
	
	virtual Node* get_in_node()
	{
		return NULL;
	}
	
	virtual Node* get_out_node()
	{
		return NULL;
	}

	bool operator < (const Node &second) const; 	
};

