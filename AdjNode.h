#ifndef _ADJNODE_H
#define _ADJNODE_H

#include "Node.h"

class AdjNode : public Node
{
public:
	Node *out;
	AdjNode( int start, int end, int weight, Node *out = NULL ):Node(start, end, weight), out(out)
	{
		
	}
	
	AdjNode();
	~AdjNode();
	
	Node* get_out_node()
	{
		return this->out;
	}
	
	Node* get_in_node()
	{
		return NULL;
	}
};
	
#endif