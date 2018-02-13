#include "OLGraph.h"
#include "Node.h"
#include "OLNode.h"
#include "AdjNode.h"
#include <queue>
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <utility>
#include <stack>

OLGraph::OLGraph()
{
	this->point_count = 0;
}

int OLGraph::get_point_count()
{
	return this->point_count;
}
 
void OLGraph::add_edge( std::string start, std::string end, int weight)
{
	int origin_count = point_count;	

	if ( this->name_map.find( start ) == this->name_map.end() )
	{
		this->name_map.insert( std::map<std::string, int>::value_type( start, this->point_count ) );
		this->id_map.insert( std::map< int, std::string >::value_type( this->point_count, start ) );
		this->point_count ++ ;	
	}

	if ( this->name_map.find( end ) == this->name_map.end() )
	{
		this->name_map.insert( std::map<std::string, int>::value_type( end, this->point_count ) );
	
		this->id_map.insert( std::map< int, std::string >::value_type( this->point_count, end) );
	
		this->point_count ++ ;	
	}
	
	if( origin_count != this->point_count )
	{
		this->directed.resize(point_count);
		this->undirected.resize(point_count);
		this->visit.resize(point_count);
	}
	
	int start_index = this->name_map.find( start )->second;
	int end_index = this->name_map.find( end )->second;

	//OL构造函数参数为：起始点， 终点， in指针， out指针
	OLNode *direct_node = new OLNode( 
		start_index, 
		end_index, 
		weight, 
		this->directed[end_index].in_edge, 
		this->directed[start_index].out_edge 
		);
		
	this->directed[start_index].out_edge = direct_node;
	directed[start_index].out_degree++;

	this->directed[end_index].in_edge = direct_node;
	directed[end_index].in_degree++;
	
	Node *undirect_node = new AdjNode(start_index, end_index, weight, undirected[start_index].out_edge );
	undirected[start_index].out_edge = undirect_node;
	undirected[start_index].degree++;
	
	undirect_node = new AdjNode(end_index, start_index, weight, undirected[end_index].out_edge );
	undirected[end_index].out_edge = undirect_node;
	undirected[end_index].degree++;
}

OLGraph::~OLGraph()
{
	for (int i = 0; i < point_count; i++)
	{
		while ( directed[i].out_edge != NULL )
		{
			Node *p = directed[i].out_edge;
			directed[i].out_edge = p->get_out_node();
			delete p;
		}
		
		while( undirected[i].out_edge != NULL )
		{
			Node *p = undirected[i].out_edge;
			undirected[i].out_edge = p->get_out_node();
			delete p;
		}
	}
}

void OLGraph::print_directed_out_graph() const
{
	std::cout << "current" << "\t" << "degree" << "\t" << "connection" << std::endl;
	
	for (int i = 0; i < point_count; i++)
	{
		std::cout << id_map.find(i)->second << "\t" << this->directed[i].out_degree << "\t";

		for (Node *ol_node = this->directed[i].out_edge; ol_node != NULL; ol_node = ol_node->get_out_node())
			std::cout << id_map.find(ol_node->end)->second << "\t";
		std::cout << std::endl;
	}
}

void OLGraph::print_directed_in_graph() const
{
	std::cout << "current" << "\t" << "degree" << "\t" << "connection" << std::endl;
	
	for (int i = 0; i < point_count; i++)
	{	
		std::cout << id_map.find(i)->second << "\t";

		std::cout << directed[i].in_degree << "\t";

		for ( Node *ol_node = this->directed[i].in_edge; ol_node != NULL; ol_node = ol_node->get_in_node())
			std::cout << id_map.find(ol_node->start)->second << "\t";
		std::cout << std::endl;
	}
}

void OLGraph::print_undirected_graph() 
{
	std::cout << "current" << "\t" << "connection" << std::endl;
	for (int i = 0; i < (int)this->undirected.size(); i++)
	{
		std::cout << id_map.find(i)->second << "\t";

		for ( Node *adj_node = this->directed[i].out_edge; adj_node != NULL; adj_node = adj_node->get_out_node() )
			std::cout <<  id_map.find(adj_node->end)->second << "\t";
		std::cout << std::endl;
	}
}


void OLGraph::shortest_tree()
{
	std::list<int> visited_list;
	std::list<int> unvisited_list;
	std::list< Node > tree;
	if (undirected.empty())
		return;

	for (int i = 0; i < point_count; i++)
	{
		if (undirected[i].out_edge != NULL)
			unvisited_list.push_front(i);
	}

	visited_list.push_front(unvisited_list.front());
	unvisited_list.pop_front();

	Node node;

	while (!unvisited_list.empty())
	{
		node.weight = INT_MAX;
		for (std::list<int>::iterator itr_unvisited = unvisited_list.begin(); itr_unvisited != unvisited_list.end(); itr_unvisited++)
			for (Node* itr_edge = undirected[*itr_unvisited].out_edge; itr_edge != NULL; itr_edge = itr_edge->get_out_node() )
			{
				std::list<int>::iterator itr_point = std::find(visited_list.begin(), visited_list.end(), itr_edge->end);	
				if (itr_point != visited_list.end())
				{
					if (node.weight > itr_edge->weight)
					{
						node.start = *itr_point;
						node.end = *itr_unvisited;
						node.weight = itr_edge->weight;
					}
				}
			}

		if (node.weight != INT_MAX)
		{
			tree.push_back(node);
			unvisited_list.erase( std::find(unvisited_list.begin(), unvisited_list.end(), node.end) );
			visited_list.push_front(node.end);
		}
	}

	std::cout << "start" << "\t" << "end" << "\t" << "weight" << std::endl;

	for (std::list< Node >::iterator itr = tree.begin(); itr != tree.end(); itr++)
		std::cout << id_map.find( itr->start )->second << "\t" << id_map.find( itr->end )->second << "\t" << itr->weight << std::endl;
}

void OLGraph::shortest_path(std::string start)
{
	if ( name_map.find(start) == name_map.end()  )
		return;

	int  *prev = new int[point_count];

	int *distance = new int[point_count];

	std::priority_queue<Node>  prio_queue;

	for (int i = 0; i < (int)visit.size(); i++)
	{
		visit[i] = false;
		prev[i] = -1;
		distance[i] = INT_MAX - 1;
	}

	int start_point = name_map.find( start )->second;

	Node node(start_point, 0, 0);

	distance[start_point] = 0;

	prio_queue.push(node);

	int bef = -1;

	while (!prio_queue.empty())
	{
		Node current = prio_queue.top();
		prio_queue.pop();

		if (visit[current.start] == true)
			continue;

		visit[current.start] = true;

		for ( Node *p = directed[current.start].out_edge; p != NULL; p = p->get_out_node() )
		{
			if (distance[p->end] > p->weight + distance[current.start])
			{
				distance[p->end] = p->weight + distance[current.start];
				prev[p->end] = current.start;
			}

			if (visit[p->end] == false)
			{
				node.start = p->end;
				node.weight = distance[p->end];
				prio_queue.push(node);
			}
		}

#ifdef _TEST_
		printf("%d\t", current.start);
		for (int i = 0; i < distance.size(); i++)
			if (distance[i] == INT_MAX - 1)
				printf("Max\t");
			else
				printf("%d\t", distance[i]);
		for (int i = 0; i < visit.size(); i++)
			visit[i] == true ? printf("T\t") : printf("F\t");
		printf("\n");
#endif

	}
	char display_str[500];
	char num_buff[30];
	std::string display;
	int i, j;
	for (i = (int)directed.size() - 1; i >= 0; i--)
	{
		if (prev[i] == -1)
			continue;
		display.clear();
		display_str[0] = 0;
		for (j = i; prev[j] != -1; j = prev[j])
		{	
			strcat(display_str, id_map.find(j)->second.c_str() ); 	
			strcat(display_str, "<--");
		}
		strcat(display_str, start.c_str() );
		printf("%*s", -28, display_str);
		printf("%d\n", distance[i]);
	}
	delete[] prev;
	delete[] distance;
}

void OLGraph::shortest_path( std::string start, std::string end )
{
	
	
	
}

void OLGraph::DFS(std::string start, bool mode)
{
	if ( name_map.find( start )  == name_map.end() )
		return;
	
	std::list<int> list; //DFS path list
	std::stack<int> st;	 //DFS stack
	
	int start_point = name_map.find( start )->second;
	
	std::vector< Node* > pointer( point_count );
	
	Node * p = NULL;
	
	for( int i = 0; i < point_count; i++ )
		visit[i] = false;
	
	switch(mode)
	{
		case DIRECTED_GRAPH:
			for (int i = 0; i < point_count; i++)
				pointer[i] = directed[i].out_edge;
		break;
		
		case UNDIRECTED_GRAPH:
			for (int i = 0; i < point_count; i++)
				pointer[i] = undirected[i].out_edge;
		break;
	}
	
	p = pointer[start_point];
	
	while ( p || !st.empty() )
	{
		while (true)
		{
			if (visit[start_point] == false)
			{
				visit[start_point] = true;
				list.push_back(start_point);
				st.push(start_point);
			}
			while ( pointer[start_point] != NULL && visit[ pointer[start_point]->end ] == true)
			{
				pointer[start_point] = pointer[start_point]->get_out_node();
				p = pointer[start_point];
			}
				
			if (p == NULL)
				break;
			start_point = p->end;
			p = pointer[start_point];
		}
			
		if (!st.empty())
		{
			start_point = st.top();		
			if( pointer[start_point] == NULL )
				st.pop();		
			p = pointer[start_point];
		}
	}
	for (std::list<int>::iterator itr = list.begin(); itr != list.end(); itr++)
		std::cout << id_map.find(*itr)->second << "\t";
	std::cout << std::endl;
}

void OLGraph::BFS(std::string start, bool mode)
{
	if (name_map.find(start) == name_map.end() )
		return;
	
	int start_point = name_map.find(start)->second;
	
	for (int i = 0; i < point_count; i++)
		visit[i] = false;

	std::queue<int> qu;

	qu.push(start_point);
	visit[start_point] = true;

	std::vector< AdjVertex > head(point_count);

	switch(mode)
	{
		case DIRECTED_GRAPH:
			for( int i = 0; i < point_count; i++ )
				head[i].out_edge = directed[i].out_edge;
		break;
		
		case UNDIRECTED_GRAPH:
			for (int i = 0; i < point_count; i++)
				head[i].out_edge = undirected[i].out_edge;
		break;
	}
		
		
	
	while (!qu.empty())
	{
		start_point = qu.front();
		qu.pop();
		for ( Node* p = head[start_point].out_edge; p != NULL; p = p->get_out_node() )
			if (visit[p->end] == false)
			{
				visit[p->end] = true;
				qu.push(p->end);
			}
		std::cout << id_map.find(start_point)->second << "\t";
	}
	std::cout << std::endl;
	
}

void OLGraph::top_sort( std::deque<int> &ls )
{
	int *stack = new int[point_count];
	
	int start;
	
	int top = -1;
	
	for( int i = 0; i < point_count; i++ )
		stack[i] = directed[i].in_degree;
	
	for( int i = 0; i < point_count; i++ )
		if( !stack[i] )
		{
			stack[i] = top;
			top = i;
		}
	
	if( top == point_count )
		return ;
	
	while( top != -1 )
	{
		start = top;
		//std:: cout << id_map.find(start)->second << " " ;
		top = stack[top];
		ls.push_back(start);
		for( Node *p = directed[start].out_edge; p != NULL; p = p->get_out_node() )
		{
			stack[ p->end ]--;
			if(!stack[p->end])
			{
				stack[p->end] = top; /*��������µ����Ϊ0�ĵ㣬��ջ*/
				top = p->end;  
			}
		}
	}
	
	std::cout << std::endl;
	delete[] stack;
}

void OLGraph::top_sort()
{
	int *stack = new int[point_count];
	std::list<int> ls;

	int start;
	
	int top = -1;
	
	
	for( int i = 0; i < point_count; i++ )
	{
		stack[i] = directed[i].in_degree;
	}
	
	
	
	for( int i = 0; i < point_count; i++ )
		if( !stack[i] )
		{
			stack[i] = top;
			top = i;
		}
	
	if( top == point_count )
		return ;
	
	while( top != -1 )
	{
		start = top;
		top = stack[top];
		ls.push_back(start);
		for( Node *p = directed[start].out_edge; p != NULL; p = p->get_out_node() )
		{
			stack[ p->end ]--;
			if(!stack[p->end])
			{
				stack[p->end] = top; /*��������µ����Ϊ0�ĵ㣬��ջ*/
				top = p->end;  
			}
		}
	}
	
	if( (int)ls.size() < point_count )
	{
		delete[] stack;
		return ;
	}
	
	for( std::list<int>::iterator itr = ls.begin(); itr != ls.end(); itr++ )
		std::cout << id_map.find(*itr)->second  << "\t";
	
	std::cout << std::endl;
	
	delete[] stack;
}

void OLGraph::AOE()
{
	int zero_in_point_count = 0;
	int zero_out_point_count = 0;
	
	for( int i = 0; i < point_count; i++ )
	{
		if( directed[i].in_degree == 0 )
		{
			zero_in_point_count ++;
		
		}
		if(directed[i].out_degree == 0)
			zero_out_point_count ++;
	}
	
	if( zero_in_point_count != 1 || zero_out_point_count != 1 )
		return ;
	
	std::deque<int> ls;
	top_sort(ls);
	
	if( ls.size() < point_count )
		return ;
	
	std::stack<int> back_ls;
	for( std::deque<int>::iterator itr = ls.begin(); itr != ls.end(); itr++ )
		back_ls.push(*itr);
	
	int *prev = new int[point_count];
	
	int *earliest_tbl = new int[point_count];
	int *lastest_tbl = new int[point_count];
	
	for( int i = 0; i < point_count; i++ )
	{
		earliest_tbl[i] = INT_MIN;
		lastest_tbl[i] = INT_MAX;
		prev[i] = -1;
	}
	
	int start = -1;
	
	earliest_tbl[ ls.front() ] = 0;

	int back_point = ls.back();
	

	
	while( !ls.empty() )
	{
		start = ls.front();
		ls.pop_front();
		
		for( Node *p = directed[start].out_edge; p != NULL; p = p->get_out_node() )
			if( earliest_tbl[ p->end ] < earliest_tbl[start] + p->weight )
				earliest_tbl[ p->end ] = earliest_tbl[start] + p->weight;
	}
		
	lastest_tbl[back_ls.top()] = earliest_tbl[ back_ls.top() ];
	
	
	while( !back_ls.empty() )
	{	
		start = back_ls.top();
		back_ls.pop();
		for( Node *p = directed[start].in_edge; p != NULL; p = p->get_in_node() )
			if( lastest_tbl[ p->start ] > lastest_tbl[start] - p->weight )
				lastest_tbl[ p->start ] = lastest_tbl[start] - p->weight;
	}
	
	//事件的最早发生时间
	std::list<Node> earliest_edge;
	
	//事件的最早发生时间
	std::list<Node> lastest_edge;
	
	Node temp;
	
	for( int i = 0; i < point_count; i++ )
	{
		
		for( Node *p = directed[i].out_edge; p ; p = p->get_out_node() )
		{
			temp.start = p->start;
			temp.end = p->end;
			temp.weight = earliest_tbl[p->start];
			earliest_edge.push_back( temp );
	
			temp.weight = lastest_tbl[p->end] - p->weight;  
			
			lastest_edge.push_back( temp );
		}
	}

#ifdef _TEST_	
	for( int i = 0; i < point_count; i++ )
		std::cout << earliest_tbl[i] << "\t";
	std::cout << std::endl;
	
	for( int i = 0; i < point_count; i++ )
		std::cout << lastest_tbl[i] << "\t";
	std::cout << std::endl;
#endif
	
	std::cout << "begin\t" << "end\t" << "start_time" << std::endl;
	for( 
		std::list<Node>::iterator itr1 = earliest_edge.begin(), itr2 = lastest_edge.begin();
		itr1 != earliest_edge.end() && itr2 != lastest_edge.end();
		itr1++, itr2++
	)
	{
		if( itr1->weight != itr2->weight )
			continue;
		std::cout << id_map.find(itr1->start)->second << "\t" << id_map.find(itr1->end)->second << "\t"  << itr1->weight << std::endl;
		
	}
	
	delete[] lastest_tbl;
	delete[] prev;
	delete[] earliest_tbl;
}
