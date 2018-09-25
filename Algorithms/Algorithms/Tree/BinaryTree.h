#pragma once
#include "configs.h"
#include "BinaryNode.h"
#include <string>
#include <iostream>

template<class T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

	void insert(const T& value);
	T* find(const T& value);
	void remove(const T& value);

	void toJson(std::ostream& out);

protected:
	BinaryNode<T>* _root;

	BinaryNode<T>* findNode(const T& value);
	void nodeToJson(BinaryNode<T>* node, std::ostream& out);
};



template<class T>
BinaryTree<T>::BinaryTree() 
	: _root(NULL)
{ }

template<class T>
BinaryTree<T>::~BinaryTree()
{ }

template<class T>
void BinaryTree<T>::insert(const T& value)
{
	BinaryNode<T>* parent = NULL;
	BinaryNode<T>** node = &_root;

	while (true)
	{
		if (*node == NULL) {
			*node = new BinaryNode<T>(parent, value);
			if (_root == NULL)
				_root = *node;
			break;
		}
		else {
			parent = *node;
			if (value < parent->value)
				node = &(parent->left);
			else if (value > parent->value)
				node = &(parent->right);
			else
				break;
		}
	}
}

template<class T>
BinaryNode<T>* BinaryTree<T>::findNode(const T& value) {
	auto node = _root;

	while (true)
	{
		if (node == NULL)
			return NULL;
		else if (node->value == value)
			return node;
		else if (value < node->value)
			node = node->left;
		else
			node = node->right;
	}
}

template<class T>
T* BinaryTree<T>::find(const T& value) {
	auto node = findNode(value);
	return node == NULL ? NULL : &(node->value);
}

template<class T>
void BinaryTree<T>::remove(const T& value) {
	auto node = findNode(value);
	if (node == NULL)
		return;

	// Find if the node is left or right son of it parent.
	auto parent = node->root;
	BinaryNode<T>** son = parent == NULL 
		? &(_root)
		: parent->left == node
			? &(parent->left)
			: &(parent->right);

	if (node->left == NULL && node->right == NULL)
		*son = NULL;
	else if (node->left == NULL) {
		*son = node->right;
		node->right = NULL;
	}
	else if (node->right == NULL) {
		*son = node->left;
		node->left = NULL;
	}
	else {
		auto tempNode = node->left;
		while (tempNode->right != NULL) 
			tempNode = tempNode->right;

		if (tempNode == node->left) {
			*son = tempNode;
			tempNode->right = node->right;
		}
		else {
			tempNode->root->right = tempNode->left;
			*son = tempNode;
			tempNode->left = node->left;
			tempNode->right = node->right;
		}

		node->left = node->right = NULL;
	}

	delete node;
}

template<class T>
void BinaryTree<T>::toJson(std::ostream& out) {
	if (_root != NULL)
		nodeToJson(_root, out);
	else
		out << "{ }";
}

template<class T>
void BinaryTree<T>::nodeToJson(BinaryNode<T>* node, std::ostream& out) {
	out << "{ \"value\": " << node->value;
	if (node->left != NULL) {
		out << ", \"left\":";
		nodeToJson(node->left, out);
	}
	if (node->right != NULL) {
		out << ", \"right\":";
		nodeToJson(node->right, out);
	}

	out << " }";
}