/**
	Kyle Custodio
	KYC180000

	Project 3
*/

#include "Node.h"
#include "BinaryTree.h"
#include <iostream>
#include <fstream>

using namespace std;

BinaryTree<Node> createTree(ifstream &input);
void readTransaction(ifstream &input, BinaryTree<Node> tree);
void add(string line, BinaryTree<Node> tree);
void remove(string line, BinaryTree<Node> tree);
void rent(string line, BinaryTree<Node> tree);
void returnMovie(string line, BinaryTree<Node> tree);

int main()
{
	ifstream input("inventory.dat");
	BinaryTree<Node> tree = createTree(input);
	input.close();
	input.open("transaction.log");
	readTransaction(input, tree);
	
	//print tree in alpha

	return 0;
}

BinaryTree<Node> createTree(ifstream &input)
{
	BinaryTree<Node> tree;
	string line;
	while (getline(input, line))
	{
		int end = line.rfind('"');
		int num = end + 2;
		int nextNum = num + 2;
		string title = line.substr(0, end);
		string a = line.substr(num, nextNum);
		string r = line.substr(nextNum);
		int available = stoi(a);
		int rented = stoi(r);
		Node *n = tree.insert(tree.getRoot(), title);
		n->setAvailable(available);
		n->setRented(rented);
	}
	return tree;
}

void readTransaction(ifstream &input, BinaryTree<Node> tree)
{
	string line;
	ofstream output("error.log");
	while (getline(input, line))
	{
		//check for proper format

		if (line.rfind("add", 0) == 0)
		{
			add(line, tree);
			continue;
		}
		else if (line.rfind("remove", 0) == 0)
		{
			remove(line, tree);
			continue;
		}
		else if (line.rfind("rent", 0) == 0)
		{
			rent(line, tree);
			continue;
		}
		else if (line.rfind("return", 0) == 0)
		{
			returnMovie(line, tree);
			continue;
		}

		//output to error log
		output << line << endl;
	}
}


void add(string line, BinaryTree<Node> tree)
{
	cout << "add" << endl;

	string title = "title"; //placeholder
	int add = 0; //placeholder
	Node *node = tree.search(tree.getRoot(), title);
	if (!node)
	{
		node = tree.insert(tree.getRoot(), title);
	}
	node->setAvailable(node->getAvailable() + add);
}

void remove(string line, BinaryTree<Node> tree)
{
	cout << "remove" << endl;

	string title = "title"; //placeholder
	int remove = 0; //placeholder
	Node *node = tree.search(tree.getRoot(), title);
	if (node)
	{
		node->setAvailable(node->getAvailable() - remove);
		if (node->getAvailable() <= 0 && node->getRented() <= 0)
		{
			tree.remove(tree.getRoot(), title);
		}
	}
}

void rent(string line, BinaryTree<Node> tree)
{
	cout << "rent" << endl;

	string title = "title"; //placeholder
	Node *node = tree.search(tree.getRoot(), title);

	if (node)
	{
		node->setRented(node->getRented() + 1);
		node->setAvailable(node->getAvailable() - 1);
	}
}

void returnMovie(string line, BinaryTree<Node> tree)
{
	cout << "return" << endl;

	string title = "title"; //placeholder
	int remove = 0; //placeholder
	Node *node = tree.search(tree.getRoot(), title);

	if (node)
	{
		node->setAvailable(node->getAvailable() + 1);
		node->setRented(node->getRented() - 1);
	}
}