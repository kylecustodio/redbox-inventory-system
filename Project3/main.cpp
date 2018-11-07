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

/**
 *Creates a Binary Tree of type Node with a given input file.
 *
 *@param input file from which the binary tree's information will be pulled from
 *@return Binary Tree of type Node
 */
BinaryTree<Node> createTree(ifstream &input);

/**
 *Reads and processes the transactions onto the Binary Tree with a given input file
 *
 *@param input file from which the transactions will be pulled from
 *@param tree Binary Tree of type Node
 */
void readTransaction(ifstream &input, BinaryTree<Node> tree);

/**
 *Adds copies of movies to the tree.
 *If the Binary Tree does not have a given movie, add it to the tree.
 *
 *@param line the string with info of the transaction
 *@param tree Binary Tree of type Node
 */
void add(string line, BinaryTree<Node> tree);

/**
 *Removes copies of movies to the tree.
 *If the movie has no more copies, remove it from the tree.
 *
 *@param line the string with info of the transaction
 *@param tree Binary Tree of type Node
 */
void remove(string line, BinaryTree<Node> tree);

/**
 *Rents movies.
 *Decrement available copies and increment rented copies by 1.
 *
 *@param line the string with info of the transaction
 *@param tree Binary Tree of type Node
 */
void rent(string line, BinaryTree<Node> tree);

/**
 *Returns movies.
 *Increment available copies and Decrement rented copies by 1.
 *
 *@param line the string with info of the transaction
 *@param tree Binary Tree of type Node
 */
void returnMovie(string line, BinaryTree<Node> tree);

/**
 *Find a substring from the given string between quotation marks.
 *
 *@param line the string with info of the transaction
 */
string parseTitle(string line);

/**
 *Find the first occurence of a number.
 *
 *@param line the string with info of the transaction
 */
int parseInt(string line);

/**
 *Check if a movie is already in the tree.
 *
 *@param line the string with info of the transaction
 *@param tree Binary Tree of type Node
 *@return if the movie is in the tree
 */
bool checkExists(BinaryTree<Node> tree, string line);

int main()
{
	//create tree
	ifstream input("inventory.dat");
	BinaryTree<Node> tree = createTree(input);
	input.close();

	//process transactions
	input.open("transaction.log");
	readTransaction(input, tree);
	input.close();

	//print tree in alphabetical order
	ofstream out("redbox_kiosk.txt");
	tree.printOrder(tree.getRoot(), out);
	out.close();
	return 0;
}

BinaryTree<Node> createTree(ifstream &input)
{
	//creat the tree
	BinaryTree<Node> tree;
	string line;
	getline(input, line);

	//gather info for root node
	string title = parseTitle(line);
	int available = parseInt(line.substr(line.rfind('"')));
	int rented = parseInt(line.substr(line.rfind(',')));

	//set the root of the tree
	tree.setRoot(new Node(title, available, rented));

	while (getline(input, line))
	{
		//gather info for node to insert
		title = parseTitle(line);
		available = parseInt(line.substr(line.rfind('"')));
		rented = parseInt(line.substr(line.rfind(',')));

		//insert node into tree
		tree.insert(tree.getRoot(), new Node(title, available, rented));
	}

	return tree;
}

void readTransaction(ifstream &input, BinaryTree<Node> tree)
{
	string line;
	ofstream output("error.log");
	while (getline(input, line))
	{
		//check for a proper command
		//make sure there are only 3 or 1 characters after the last quotation mark
		string check = line.substr(line.find_last_of('"'));
		int icheck = (int)check.length();

		if (line.rfind("add", 0) == 0 && icheck == 3)
		{
			string check2 = line.substr(0, line.find_first_of('"'));
			int icheck2 = (int)check2.length();
			if (icheck2 == 4) // make sure begginning is "add "
			{
				add(line, tree);
				continue;
			}
		}
		else if (line.rfind("remove", 0) == 0 && icheck == 3)
		{
			string check2 = line.substr(0, line.find_first_of('"'));
			int icheck2 = (int)check2.length();
			//make sure that the movie is in the tree
			if (checkExists(tree, line) && icheck2 == 7) //make sure beginning is "remove "
			{
				remove(line, tree);
				continue;
			}
		}
		else if (line.rfind("rent", 0) == 0 && icheck == 1)
		{
			string check2 = line.substr(0, line.find_first_of('"'));
			int icheck2 = (int)check2.length();
			//make sure that the movie is in the tree
			if (checkExists(tree, line) && icheck2 == 5) //make sure beginning is "rent "
			{
				rent(line, tree);
				continue;
			}
		}
		else if (line.rfind("return", 0) == 0 && icheck == 1)
		{
			string check2 = line.substr(0, line.find_first_of('"'));
			int icheck2 = (int)check2.length();
			//make sure that the movie is in the tree
			if (checkExists(tree, line) && icheck2 == 7) //make sure beginning is "return "
			{
				returnMovie(line, tree);
				continue;
			}
		}

		//output to error log
		output << line << endl;
	}
}


void add(string line, BinaryTree<Node> tree)
{
	//gather info for adding a movie
	string title = parseTitle(line);
	int add = parseInt(line);

	//search for the node
	Node *node = tree.search(tree.getRoot(), new Node(title));

	//if node does not exist in tree, insert it
	if (!node)
	{
		Node *newNode = new Node(title, add, 0);
		node = tree.insert(tree.getRoot(), newNode);
		return;
	}

	//increase available copies by add amount
	node->setAvailable(node->getAvailable() + add);
}

void remove(string line, BinaryTree<Node> tree)
{
	//gather info for movie to remove
	string title = parseTitle(line);
	int remove = parseInt(line);

	//find the node of the movie
	Node *node = tree.search(tree.getRoot(), new Node(title));

	//subtract remove amount
	node->setAvailable(node->getAvailable() - remove);

	//if number of available movies is less than 0, remove the node
	if (node->getAvailable() <= 0 && node->getRented() <= 0)
	{
		tree.remove(tree.getRoot(), node);
	}
}

void rent(string line, BinaryTree<Node> tree)
{
	//gather info for movie to rent
	string title = parseTitle(line);

	//find the node of the movie
	Node *node = tree.search(tree.getRoot(), new Node(title));

	//decrease available amount and increase rented amount by 1
	node->setRented(node->getRented() + 1);
	node->setAvailable(node->getAvailable() - 1);
}

void returnMovie(string line, BinaryTree<Node> tree)
{
	//gather info for movie to return
	string title = parseTitle(line);

	//find the node of the movie
	Node *node = tree.search(tree.getRoot(), new Node(title));

	//increase available amount and decrease rented amount by 1
	node->setAvailable(node->getAvailable() + 1);
	node->setRented(node->getRented() - 1);
}

string parseTitle(string line)
{
	//return string between quotation marks
	int start = line.find_first_of('"');
	int end = line.find_last_of('"');
	return line.substr(start + 1, end - start - 1);
}

int parseInt(string str)
{
	//finds the first occurence of a number
	int num;
	int index = str.find_first_of("0123456789");
	if (index > 0)
	{
		char s = str[index];
		num = atoi(&s);
	}
	return num;
}

bool checkExists(BinaryTree<Node> tree, string line)
{
	//checks to see if a given node exists
	string title = parseTitle(line);
	Node *n = tree.search(tree.getRoot(), new Node(title));
	return n;
}