/**
	Kyle Custodio
	KYC180000

	Project 3
*/

#ifndef  NODE_H
#define NODE_H

#include <string>

class Node
{
private:
	std::string title;
	int available;
	int rented;
	Node *left = nullptr;
	Node *right = nullptr;
public:
	Node();
	Node(std::string title);
	Node(std::string title, int available, int rented);
	Node(std::string title, int available, int rented, Node *left, Node *right);

	//Accessors
	std::string getTitle() { return title; }
	int getAvailable() { return available; }
	int getRented() { return rented; }
	Node* getLeft() { return left; }
	Node* getRight() { return right; }

	//Mutators
	void setTitle(std::string title) { this->title = title; }
	void setAvailable(int available) { this->available = available; }
	void setRented(int rented) { this->rented = rented; }
	void setLeft(Node *left) { this->left = left; }
	void setRight(Node *right) { this->right = right; }

	void copyNode(Node n);

	//Operator
	bool operator==(const Node &right);
	bool operator>(const Node &right);
	bool operator<(const Node &right);

	friend std::ostream& operator<<(std::ostream &out, const Node &node);

	~Node();
};

#endif