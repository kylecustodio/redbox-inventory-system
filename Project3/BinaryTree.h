#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.h"

template <class T>
class BinaryTree
{
private:
	Node *root;
public:
	void setRoot(Node *root) { this->root = root; }
	Node *getRoot() { return root; }

	Node *insert(Node *node, std::string title);
	Node *search(Node *node, std::string title);
	Node *remove(Node *node, std::string title);
};

template <class T>
Node* BinaryTree<T>::insert(Node *node, std::string title)
{
	if (node == nullptr)
	{
		Node *newNode(title);
		return newNode;
	}

	if (title < node->title)
	{
		node->left = insert(node->left, title);
	}
	else if (title > node->title)
	{
		node.right = insert(node->right, title);
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

	if (node->title < title)
	{
		return search(node->right, title);
	}

	if (node->title > title)
	{
		return search(node->left, title);
	}
}

template <class T>
Node* BinaryTree<T>::remove(Node *node, std::string title)
{
	if (node == nullptr)
	{
		return node;
	}

	if (title < node->title)
	{
		node->left = remove(node->left, title);
	}
	else if (title > node->title)
	{
		node.right = remove(node->right, title);
	}
	else
	{
		if (node.left == nullptr)
		{
			Node *temp = node->right;
			free(node);
			return temp;
		}
		else if (node.right == nullptr)
		{
			Node *temp = node->left;
			free(node);
			return temp;
		}

		Node *temp = node->right; //find the min value of this tree
		node->title = temp->title;
		node->rented = temp->rented;
		node->rented = temp->rented;
		node->right = delete(node->right, title);
	}
}

#endif