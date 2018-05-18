#pragma once
#include <iostream>
#include <list>

class Graph
{
	// total number of vertices
	int V;

	// array of lists, one per vertex - indicating edges
	std::list<int>* adjacencyList;

	void dfs(int, bool*);

public:
	Graph(int);
	void addEdge(int, int);
	void bfs(int);
	void dfs(int);
	void dfsI(int);
};
