#include "Graph.h"

void Graph::removeNode(Node* node) {
	nodes.erase(node);
	// Remove also from all neighbours list
	for (set<Node*>::iterator it = nodes.begin();
		it != nodes.end(); it++) {
		(*it)->removeNeighbour(node);
	}
}

void Graph::addEdge(Node* begin, Node* end) {
	if (nodes.find(begin) == nodes.end())
		return;
	if (nodes.find(end) == nodes.end())
		return;
	begin->addNeighbour(end);
	end->addNeighbour(begin);
}

void Graph::addNode(Node* node) {
	nodes.insert(node);
}

void Graph::removeEdge(Node* begin, Node* end) {
	begin->removeNeighbour(end);
	end->removeNeighbour(begin);
}
