#pragma once
#include "configs.h"
#include "BrNode.h"
#include <string>
#include <iostream>

template<class T>
class BlackRedTree
{
public:
	BlackRedTree();
	~BlackRedTree();

	void insert(const T& value);
	T* find(const T& value);
	void remove(const T& value);

	void toJson(std::ostream& out);

protected:
	BrNode<T>* _root;

	BrNode<T>* findNode(const T& value);
};



template<class T>
BlackRedTree<T>::BlackRedTree()
	: _root(NULL)
{ }

template<class T>
BlackRedTree<T>::~BlackRedTree()
{ }

template<class T>
void BlackRedTree<T>::insert(const T& value)
{
	BrNode<T> *parent = NULL;
	BrNode<T> **node = &_root;

	while (true)
	{
		if (*node == NULL) {
			*node = new BrNode<T>(parent, value);
			if (_root == *node)
				_root->isRed = false;
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

	// Balance tree part.
	if (parent != NULL && parent->isRed) {
		BrNode<T> *newNode = *node;

		bool isChanged;
		do
		{
			isChanged = false;
			if (newNode->isNeedMoveDownBlackness()) {
				newNode->moveDownBlackness();
				newNode = newNode->parent->parent;
				isChanged = true;
			}
			if (newNode->isNeedRotate()) {
				if (newNode->parent->parent == _root)
					_root = newNode->rotate();
				else
					newNode->rotate();
				isChanged = true;
			}
		} while (isChanged);

		if (_root->isRed)
			_root->isRed = false;
	}
}

template<class T>
BrNode<T>* BlackRedTree<T>::findNode(const T& value) {
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
T* BlackRedTree<T>::find(const T& value) {
	auto node = findNode(value);
	return node == NULL ? NULL : &(node->value);
}

template<class T>
void BlackRedTree<T>::remove(const T& value) {
	auto node = findNode(value);
	if (node == NULL)
		return;

	// Find if the node is left or right son of it parent.
	auto parent = node->parent;
	BrNode<T> **son = parent == NULL
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
			tempNode->parent->right = tempNode->left;
			*son = tempNode;
			tempNode->left = node->left;
			tempNode->right = node->right;
		}

		node->left = node->right = NULL;
	}

	delete node;
}

template<class T>
void BlackRedTree<T>::toJson(std::ostream& out) {
	if (_root != NULL)
		_root->toJson(out);
	else
		out << "{ }";
}