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

Node& Node::operator=(Node &right)
{
	title = right.title;
	available = right.available;
	rented = right.rented;
	return *this;
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
