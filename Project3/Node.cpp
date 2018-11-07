#include "Node.h"
#include <iomanip>


Node::Node()
{
}

Node::Node(std::string title)
{
	this->title = title;
}

Node::Node(std::string title, int available, int rented)
{
	this->title = title;
	this->available = available;
	this->rented = rented;
}

Node::Node(std::string title, int available, int rented, Node *left, Node *right)
{

	this->title = title;
	this->available = available;
	this->rented = rented;
	this->left = left;
	this->right = right;
}

void Node::copyNode(Node n)
{
	this->title = n.title;
	this->available = n.available;
	this->rented = n.rented;
}

bool Node::operator==(const Node &right)
{
	return title == right.title;
}

bool Node::operator>(const Node &right)
{
	return title > right.title;
}

bool Node::operator<(const Node &right)
{
	return title < right.title;
}

std::ostream& operator<<(std::ostream &out, const Node &node)
{
	out << std::setw(30) << std::left << node.title;
	out << std::setw(5) << std::right << node.available << std::setw(5) << node.rented;
	return out;
}


Node::~Node()
{
}
