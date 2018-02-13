#include <iostream>
#include "OLGraph.h"
using namespace std;


OLGraph graph;

int main(int argc, char* argv[])
{
/*
	graph.add_edge("1","6", 100);

	graph.add_edge("1", "5", 30);

	graph.add_edge("1", "3", 10);

	graph.add_edge("2", "3", 5);

	graph.add_edge("3", "4", 50);

	graph.add_edge("4", "6", 10);

	graph.add_edge("5", "6", 60);

	graph.add_edge("5", "4", 20);
*/
	graph.add_edge("v1", "v2", 3);
	graph.add_edge("v1", "v3", 2);
	graph.add_edge("v1", "v4", 6);
	graph.add_edge("v2", "v4", 2);
	graph.add_edge("v2", "v5", 4);
	graph.add_edge("v3", "v4", 1);
	graph.add_edge("v3", "v6", 3);
	graph.add_edge("v4", "v5", 1);
	graph.add_edge("v5", "v7", 3);
	graph.add_edge("v6", "v7", 4);
	cout << "点的个数为：" << endl;
	cout << graph.get_point_count() << endl;
	
	cout << "入度表：" << endl;
	
	graph.print_directed_in_graph();
	
	cout << "出度表：" << endl;
	graph.print_directed_out_graph();

	cout << "无向图：" << endl;
	graph.print_undirected_graph();
	
	cout << "最小生成树：" << endl;
	graph.shortest_tree();
	
	cout << "最短路径：" << endl;
	graph.shortest_path("v1");
	
	cout << "深度优先：" << endl;
	graph.DFS("v1", UNDIRECTED_GRAPH);
	
	cout << "广度优先：" << endl;
	graph.BFS("v2", DIRECTED_GRAPH);
	
	cout << "拓扑排序：" << endl;
	graph.top_sort();
	
	cout << "AOE：" << endl;
	graph.AOE();
	
	return 0;
}

