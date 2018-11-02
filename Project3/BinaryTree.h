#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.h"
#include <string>
#include <iostream>

template <class T>
class BinaryTree
{
private:
	T *root = nullptr;
public:
	void setRoot(T *root) { this->root = root; }
	T *getRoot() { return root; }

	T *min(T *root);
	T *insert(T *root, T *node);
	T *search(T *root, T *node);
	T *remove(T *root, T *node);
	void printOrder(T *root, std::ostream &out);
};

template <class T>
T* BinaryTree<T>::min(T *root)
{
	T *current = root;

	while (current->getLeft() != nullptr)
	{
		current = current->getLeft();
	}

	return current;
}

template <class T>
T* BinaryTree<T>::insert(T *root, T *node)
{
	if (root == nullptr)
	{
		return node;
	}

	if (node < root)
	{
		root->setLeft(insert(root->getLeft(), node));
	}
	else if (node > root)
	{
		root->setRight(insert(root->getRight(), node));
	}

	return node;
}

template <class T>
T* BinaryTree<T>::search(T *root, T *node)
{
	if (!root || root == node)
	{
		return root;
	}

	if (root < node)
	{
		return search(root->getRight(), node);
	}

	return search(root->getLeft(), node);
}

template <class T>
T* BinaryTree<T>::remove(T *root, T *node)
{
	if (!root)
	{
		return root;
	}

	if (node < root)
	{
		root->setLeft(remove(root->getLeft(), node));
	}
	else if (node > root)
	{
		root->setRight(remove(root->getRight(), node));
	}
	else
	{
		if (!root->getLeft())
		{
			T *temp = root->getRight();
			free(root);
			return temp;
		}
		else if (!root->getRight())
		{
			T *temp = root->getLeft();
			free(root);
			return temp;
		}

		T *temp = min(root->getRight());
		root = temp;
		root->setRight(remove(root->getRight(), node));
	}

	return root;
}

template <class T>
void BinaryTree<T>::printOrder(T *root, std::ostream &out)
{
	if (!root)
	{
		return;
	}

	printOrder(root->getLeft(), out);

	out << *root << std::endl;

	printOrder(root->getRight(), out);
}

#endif