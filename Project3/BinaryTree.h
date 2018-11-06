#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>
#include <iostream>

template <class T>
class BinaryTree
{
private:
	T *root;
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

	//find left most leaf
	while (current->getLeft())
	{
		current = current->getLeft();
	}

	return current;
}

template <class T>
T* BinaryTree<T>::insert(T *root, T *node)
{
	//base case
	if (!root)
	{
		root = node;
	}

	//what we're inserting belongs on the left
	if (*node < *root)
	{
		root->setLeft(insert(root->getLeft(), node));
	}
	//what we're inserting belongs on the right
	else if (*node > *root)
	{
		root->setRight(insert(root->getRight(), node));
	}

	return root;
}

template <class T>
T* BinaryTree<T>::search(T *root, T *node)
{
	//base case
	if (!root || *root == *node)
	{
		return root;
	}

	//what we're searching for is on the right
	if (*root < *node)
	{
		return search(root->getRight(), node);
	}

	//what we're searching for is on the left
	return search(root->getLeft(), node);
}

template <class T>
T* BinaryTree<T>::remove(T *root, T *node)
{
	//base case
	if (!root)
	{
		return root;
	}

	//what we're deleting is on the left
	if (*node < *root)
	{
		root->setLeft(remove(root->getLeft(), node));
	}
	//what we're deleting is on the right
	else if (*node > *root)
	{
		root->setRight(remove(root->getRight(), node));
	}
	//we've found what we're deleting
	else
	{
		//0 children
		if (!root->getLeft() && !root->getRight())
		{
			delete root;
			root = nullptr;
		}
		//1 child
		else if (!root->getLeft())
		{
			T *temp = root->getRight();

			root->setTitle(temp->getTitle());
			root->setAvailable(temp->getAvailable());
			root->setRented(temp->getRented());
			root->setLeft(temp->getLeft());
			root->setRight(temp->getRight());

			delete temp;

			return root;
		}
		else if (!root->getRight())
		{
			T *temp = root->getLeft();

			root->setTitle(temp->getTitle());
			root->setAvailable(temp->getAvailable());
			root->setRented(temp->getRented());
			root->setLeft(temp->getLeft());
			root->setRight(temp->getRight());

			delete temp;

			return root;
		}
		//2 children
		else
		{
			T *temp = min(root->getRight());

			root->copyNode(*temp);

			root->setRight(remove(root->getRight(), root));
		}
	}

	return root;
}

template <class T>
void BinaryTree<T>::printOrder(T *root, std::ostream &out)
{
	//we've reached the end of a leaf
	if (!root)
	{
		return;
	}

	//process left
	printOrder(root->getLeft(), out);

	//process node
	out << *root << std::endl;

	//process right
	printOrder(root->getRight(), out);
}

#endif