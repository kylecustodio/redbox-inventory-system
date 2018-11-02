/**
	Kyle Custodio
	KYC180000

	Project 3
*/

#include "Node.h"
#include "BinaryTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

BinaryTree<Node> createTree(ifstream &input);
void readTransaction(ifstream &input, BinaryTree<Node> tree);
void add(string line, BinaryTree<Node> tree);
void remove(string line, BinaryTree<Node> tree);
void rent(string line, BinaryTree<Node> tree);
void returnMovie(string line, BinaryTree<Node> tree);
string parseTitle(string line);
int parseInt(string line);

int main()
{
	ifstream input("inventory.dat");
	BinaryTree<Node> tree = createTree(input);
	input.close();

	//input.open("transaction.log");
	//readTransaction(input, tree);
	//input.close();

	//print tree in alpha
	ofstream out("redbox_kiosk.txt");
	tree.printOrder(tree.getRoot(), out);
	out.close();

	system("pause");
	return 0;
}

BinaryTree<Node> createTree(ifstream &input)
{
	BinaryTree<Node> tree;
	string line;
	getline(input, line);
	string title = parseTitle(line);
	int available = parseInt(line.substr(line.find(',')));
	int rented = parseInt(line.substr(line.rfind(',')));
	Node *n = new Node(title, available, rented);
	tree.setRoot(n);
	while (getline(input, line))
	{
		available = parseInt(line.substr(line.find(',')));
		rented = parseInt(line.substr(line.rfind(',')));
		title = parseTitle(line);
		n = new Node(title, available, rented);
		tree.insert(tree.getRoot(), n);
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
	}
}


void add(string line, BinaryTree<Node> tree)
{
	string title = parseTitle(line);
	int add = parseInt(line);
	Node *node = tree.search(tree.getRoot(), title);
	if (!node)
	{
		Node *newNode = new Node(title, add, 0);
		node = tree.insert(tree.getRoot(), newNode);
		return;
	}
	node->setAvailable(node->getAvailable() + add);
}

void remove(string line, BinaryTree<Node> tree)
{
	string title = parseTitle(line);
	int remove = parseInt(line);
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
	string title = parseTitle(line);
	Node *node = tree.search(tree.getRoot(), title);

	if (node)
	{
		node->setRented(node->getRented() + 1);
		node->setAvailable(node->getAvailable() - 1);
	}
}

void returnMovie(string line, BinaryTree<Node> tree)
{
	string title = parseTitle(line);
	Node *node = tree.search(tree.getRoot(), title);

	if (node)
	{
		node->setAvailable(node->getAvailable() + 1);
		node->setRented(node->getRented() - 1);
	}
}

string parseTitle(string line)
{
	int start = line.find_first_of('"');
	int end = line.find_last_of('"');
	return line.substr(start + 1, end - start - 1);
}

int parseInt(string str)
{
	int num;
	int index = str.find_first_of("0123456789");
	if (index > 0)
	{
		char s = str[index];
		num = atoi(&s);
	}
	return num;
}