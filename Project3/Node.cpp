#include "Node.h"



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

Node::~Node()
{
}
