#include "Node.h"

Node::Node()
{
}

bool Node::operator < (const Node &second) const
{
	return this->weight > second.weight;
}


