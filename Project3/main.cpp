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

	return 0;
}

BinaryTree<Node> createTree(ifstream &input)
{
	BinaryTree<Node> tree;
	string title;
	while (cin >> title)
	{
		int available;
		int rent;
		cin >> available;
		cin >> rent;
		Node *n = tree.insert(tree.getRoot(), title);
		n->setAvailable(available);
		n->setRented(rent);
	}
	return tree;
}

void readTransaction(ifstream &input, BinaryTree<Node> tree)
{
	string line;
	while (getline(input, line))
	{
		//check for proper format
		if (line.rfind("add", 0) == 0)
		{
			add(line, tree);
		}
		else if (line.rfind("remove", 0) == 0)
		{
			remove(line, tree);
		}
		else if (line.rfind("rent", 0) == 0)
		{
			rent(line, tree);
		}
		else if (line.rfind("return", 0) == 0)
		{
			returnMovie(line, tree);
		}
	}
}


void add(string line, BinaryTree<Node> tree)
{
	cout << "add" << endl;
}

void remove(string line, BinaryTree<Node> tree)
{
	cout << "remove" << endl;
}

void rent(string line, BinaryTree<Node> tree)
{
	cout << "rent" << endl;
}

void returnMovie(string line, BinaryTree<Node> tree)
{
	cout << "return" << endl;
}