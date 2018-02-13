#ifndef _ADJVERTEX_h
#define _ADJVERTEX_h
#include "Node.h"
class AdjVertex
{
public:
	int degree;
	Node* out_edge;
	AdjVertex();
	~AdjVertex();
};

#endif