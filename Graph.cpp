#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include "Graph.h"

void Graph::dfs(int, bool *)
{
}

Graph::Graph(int v)
{
	this->V == v;
	adjacencyList = new std::list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adjacencyList[v].push_back(w);
}

void Graph::bfs(int sourceVertex)
{
	bool *visited = new bool[V];

	for (int i = 0; i < V; ++i)
	{
		visited[i] = false;
	}

	std::queue<int> bfsV;

	// mark the current node as visited, so enqueue it
	visited[sourceVertex] = true;
	bfsV.push(sourceVertex);

	// iter will be used to get all the adjacent vertices of a vertex, which is effectively a list
	std::list<int>::iterator iter;

	while (!bfsV.empty())
	{
		 Dequeue vertex from the front and print it
		auto s = bfsV.front();
		std::cout << s << std::endl;
		bfsV.pop();

		 enqueue all the adjacent vertices in the adjacency matrix
		for (iter = adjacencyList[s].begin(); iter != adjacencyList[s].end(); ++iter)
		{
			if (!visited[*iter])
			{
				visited[*iter] = true;
				bfsV.push(*iter);
			}
		}
	}
}

void Graph::dfs(int sourceVertex)
{
	// mark all vertices as not visited
	bool *visited = new bool[V];

	for (int i = 0; i < V; ++i)
	{
		visited[i] = false;
	}

	dfs(sourceVertex, visited);
}

void Graph::dfs(int v, bool* visited)
{
	// mark the current node as visited and print it
	visited[v] = true;
	std::cout << v << std::endl;

	// call this recursively for all vertices
	std::list<int>::iterator iter;
	for (iter = adjacencyList[v].begin(); iter != adjacencyList[v].end(); ++iter)
	{
		if (!visited[*iter])
		{
			dfs(*iter, visited);
		}
	}
}

void Graph::dfsI(int sourceVertex)
{
	bool *visited = new bool[V];

	std::stack<int> dfsV;

	// push the current node
	dfsV.push(sourceVertex);

	while (!dfsV.empty())
	{
		sourceVertex = dfsV.top();
		dfsV.pop();

		// stack may contain same vertex twice, so print the popped item only if it was not visited
		if (!visited[sourceVertex])
		{
			std::cout << sourceVertex << std::endl;
			visited[sourceVertex] = true;
		}

		// Now get all the adjacent vertices of the popped vertex 'sourceVertex' & if not visited, push it on the stack
		for (auto iter = adjacencyList[sourceVertex].begin(); iter != adjacencyList[sourceVertex].end(); ++iter)
		{
			if (!visited[*iter])
			{
				dfsV.push(*iter);
			}
		}
	}
}

