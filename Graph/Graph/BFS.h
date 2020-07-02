#pragma once
#include <queue>
#include "Graph.h"

class BFS {
	const Graph& graph;
public:
	BFS(const Graph& agraph) : graph(agraph) {}
	bool connected(Node* begin, Node* end);
};

bool BFS::connected(Node* begin, Node* end) {
	std::queue<Node*> nodes;
	nodes.push(begin);
	std::set<Node*> visited;

	while (!nodes.empty()) {
		Node* next = nodes.front(); nodes.pop();
		if (end == next) {
			return true;
		}
		visited.insert(next);

		for (node_iterator it = next->nb_begin(); it != next->nb_end(); it++) {

			if (visited.find(*it) == visited.end())
				nodes.push(*it);
		}
	}
	return false;
}