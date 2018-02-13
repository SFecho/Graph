#include "OLVertex.h"


OLVertex::OLVertex()
{
	this->in_edge = NULL;
	this->out_edge = NULL;
	this->in_degree = this->out_degree = 0;
}


OLVertex::~OLVertex()
{
	
}
