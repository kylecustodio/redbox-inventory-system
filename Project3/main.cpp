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