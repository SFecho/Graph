#pragma once
#include "Node.h"

class OLVertex
{
public:
	int in_degree;
	int out_degree;
	Node* in_edge;
	Node* out_edge;
	OLVertex();
	~OLVertex();
};

