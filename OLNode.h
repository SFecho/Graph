#pragma once
#include "Node.h"
#include <iostream>

class OLNode: public Node
{
public:
	Node * in;
	Node * out;

	OLNode();

	~OLNode();

	OLNode(int start, int end, int weight, Node * in = NULL, Node * out = NULL) :
		Node(start, end, weight), in(in), out(out)
	{

	}
	
	virtual Node* get_out_node()
	{
		return this->out;
	}
	
	virtual Node* get_in_node()
	{
		return this->in;
	}
};

