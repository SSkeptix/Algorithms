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
	void nodeToJson(BrNode<T>* node, std::ostream& out);
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
				_root->isBlack = true;
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
	if (parent != NULL && !parent->isBlack) {
		if (parent->parent->hasOneChild()) {
			BrNode<T> *grantParent = parent->parent;

			// We have 3 nodes: grantParent, parent, and node -> now we will restructure them.
			
			// 1) Sort them.
			BrNode<T>* nodes[3] = { grantParent, parent, *node };
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 2; j++)
					if (nodes[i]->value < nodes[j]->value)
						std::swap(nodes[i], nodes[j]);

			// 2) Build sub tree. [0] - leftNode, [1] - root, [2] - right.
			grantParent->replaceMeForParent(nodes[1]);
			nodes[1]->parent = grantParent->parent;
			nodes[1]->isBlack = true;
			nodes[1]->left = nodes[0];
			nodes[1]->right = nodes[2];
			if (_root == grantParent)
				_root = nodes[1];

			nodes[0]->parent = nodes[1];
			nodes[0]->isBlack = false;
			nodes[0]->left = nodes[0]->right = NULL;

			nodes[2]->parent = nodes[1];
			nodes[2]->isBlack = false;
			nodes[2]->left = nodes[2]->right = NULL;
		}
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
		nodeToJson(_root, out);
	else
		out << "{ }";
}

template<class T>
void BlackRedTree<T>::nodeToJson(BrNode<T>* node, std::ostream& out) {
	out << "{ \"Value\": " << node->value
		<< ", \"IsBlack\": " << node->isBlack ? "true" : "false";
	if (node->left != NULL) {
		out << ", \"Left\":";
		nodeToJson(node->left, out);
	}
	if (node->right != NULL) {
		out << ", \"Right\":";
		nodeToJson(node->right, out);
	}

	out << " }";
}