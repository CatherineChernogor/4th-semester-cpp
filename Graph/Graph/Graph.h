#pragma once
#include "Node.h"
using namespace std;


class Graph {
	set<Node*> nodes;
public:
	void addNode(Node* node);
	void removeNode(Node* node);
	void addEdge(Node* begin, Node* end);
	void removeEdge(Node* begin, Node* end);

	node_iterator begin() const {
		return nodes.begin();
	}
	node_iterator end() const {
		return nodes.end();
	}
};




