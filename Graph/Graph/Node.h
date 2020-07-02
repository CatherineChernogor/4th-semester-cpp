#pragma once
#include <set>
#include <string>

typedef set<Node*>::const_iterator node_iterator;

class Node {
	string name;
	set<Node*> neighbours;
	void addNeighbour(Node* neighbour);
	void removeNeighbour(Node* neighbour);
public:
	Node(const string& aname) : name(aname) {}

	const string& getName() const {
		return name;
	}

	node_iterator nb_begin() const {
		return neighbours.begin();
	}
	node_iterator nb_end() const {
		return neighbours.end();
	}

	friend class Graph;
};


void Node::addNeighbour(Node* neighbour) {
	neighbours.insert(neighbour);
}
void Node::removeNeighbour(Node* neighbour){
	neighbours.erase(neighbours.find(neighbour));
}