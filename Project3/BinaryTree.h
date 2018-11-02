#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>

template <class T>
class BinaryTree
{
private:
	Node *root = nullptr;
public:
	void setRoot(Node *root) { this->root = root; }
	Node *getRoot() { return root; }

	Node *min(Node *min);
	Node *insert(Node *root, Node *node);
	Node *search(Node *node, std::string title);
	Node *remove(Node *node, std::string title);
	void printOrder(Node *node, std::ostream &out);
};

template <class T>
Node* BinaryTree<T>::min(Node *node)
{
	Node *current = node;

	while (current->getLeft() != nullptr)
	{
		current = current->getLeft();
	}

	return current;
}

template <class T>
Node* BinaryTree<T>::insert(Node *root, Node *node)
{
	if (root == nullptr)
	{
		return node;
	}

	if (node->getTitle() < root->getTitle())
	{
		root->setLeft(insert(root->getLeft(), node));
	}
	else if (node->getTitle() > root->getTitle())
	{
		root->setRight(insert(root->getRight(), node));
	}

	return node;
}

template <class T>
Node* BinaryTree<T>::search(Node *node, std::string title)
{
	if (node == nullptr || node->getTitle() == title)
	{
		return node;
	}

	if (node->getTitle() < title)
	{
		return search(node->getRight(), title);
	}

	return search(node->getLeft(), title);
}

template <class T>
Node* BinaryTree<T>::remove(Node *node, std::string title)
{
	if (node == nullptr)
	{
		return node;
	}

	if (title < node->getTitle())
	{
		node->setLeft(remove(node->getLeft(), title));
	}
	else if (title > node->getTitle())
	{
		node->setRight(remove(node->getRight(), title));
	}
	else
	{
		if (node->getLeft() == nullptr)
		{
			Node *temp = node->getRight();
			free(node);
			return temp;
		}
		else if (node->getRight() == nullptr)
		{
			Node *temp = node->getLeft();
			free(node);
			return temp;
		}

		Node *temp = min(node->getRight());
		node->setTitle(temp->getTitle());
		node->setAvailable(temp->getAvailable());
		node->setRented(temp->getRented());
		node->setRight(remove(node->getRight(), title));
	}

	return node;
}

template <class T>
void BinaryTree<T>::printOrder(Node *node, std::ostream &out)
{
	if (node == nullptr)
	{
		return;
	}

	printOrder(node->getLeft(), out);

	out << std::setw(30) << std::left << node->getTitle();
	out << std::setw(5) << std::right << node->getAvailable() << std::setw(5) << node->getRented() << std::endl;

	printOrder(node->getRight(), out);
}

#endif