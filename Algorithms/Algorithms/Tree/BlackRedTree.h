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
			*node = new BrNode<T>(parent, node, value);
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
				continue;
			}
			if (newNode->isNeedSimpleRotate()) {
				newNode = newNode->simpleRotate();
				isChanged = true;
				continue;
			}
			if (newNode->isNeedRotate()) {
				newNode->rotate();
				isChanged = true;
				continue;
			}
		} while (isChanged);
	}

	if (_root->isRed)
		_root->isRed = false;
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
	
	node->remove();
}

template<class T>
void BlackRedTree<T>::toJson(std::ostream& out) {
	if (_root != NULL)
		_root->toJson(out);
	else
		out << "null";
}