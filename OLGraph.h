#ifndef _OLGRAPH_H
#define _OLGRAPH_H

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include "OLVertex.h"
#include "ADJVertex.h"
#include <list>
#include <map>
#include <string>
#include <queue>

#define DIRECTED_GRAPH 1
#define UNDIRECTED_GRAPH 0


class OLGraph
{
private:
	 
	std::map< std::string, int > name_map; 
	std::map< int, std::string > id_map; 
	std::vector< OLVertex > directed;
	std::vector< AdjVertex > undirected;	
	std::vector< bool > visit;
	int point_count;


public:
	OLGraph();
	int get_point_count();
	void add_edge( std::string start, std::string end, int weight);
	void print_directed_out_graph() const;
	void print_directed_in_graph() const;
	void print_undirected_graph();
	void shortest_tree();
	void shortest_path( std::string start );
	void shortest_path( std::string start, std::string end );
	void DFS( std::string start, bool mode );
	void BFS( std::string start, bool mode );
	void top_sort( std::deque<int> &ls );
	void top_sort();
	void AOE();
	~OLGraph();
};

#endif
