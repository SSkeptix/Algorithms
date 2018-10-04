#pragma once
#include "configs.h"

template<class T>
struct BrNode
{
	BrNode(BrNode<T>* parent, const T& value);
	~BrNode();

	T value;
	bool isRed;
	BrNode<T> *parent, *left, *right;

	void toJson(std::ostream& out);
	void replaceMeForParent(BrNode<T>* newNode);

	bool isNeedMoveDownBlackness();
	void moveDownBlackness();

	bool isNeedRotate();
	BrNode<T>* rotate();
};



template<class T>
BrNode<T>::BrNode(BrNode<T>* parent, const T& value)
	: value(value), parent(parent), left(NULL), right(NULL), isRed(true)
{ }

template<class T>
BrNode<T>::~BrNode()
{
	if (left != NULL)
		delete left;
	if (right != NULL)
		delete right;
}

template<class T>
void BrNode<T>::toJson(std::ostream& out) {
	out << "{ \"Value\": " << value
		<< ", \"IsRed\": " << isRed ? "true" : "false";
	if (left != NULL) {
		out << ", \"Left\":";
		left->toJson(out);
	}
	if (right != NULL) {
		out << ", \"Right\":";
		right->toJson(out);
	}

	out << " }";
}

template<class T>
void BrNode<T>::replaceMeForParent(BrNode<T>* newNode)
{
	if (parent == NULL)
		return;

	(parent->left == this) ? parent->left : parent->right
		= newNode;
}

template<class T>
bool BrNode<T>::isNeedMoveDownBlackness()
{
	if (parent == NULL)
		return false;

	auto grandParent = parent->parent;
	if (grandParent == NULL || grandParent->left == NULL || grandParent->right == NULL)
		return false;

	return isRed && grandParent->left->isRed && grandParent->right->isRed;
}

template<class T>
void BrNode<T>::moveDownBlackness()
{
	auto grandParent = parent->parent;

	grandParent->isRed = true;
	grandParent->left->isRed = grandParent->right->isRed = false;
}

template<class T>
bool BrNode<T>::isNeedRotate()
{
	if (parent == NULL)
		return false;

	auto grandParent = parent->parent;
	if (grandParent == NULL)
		return false;

	return isRed && parent->isRed 
		// && grandParent has at least one black node or NULL node.
		&& !(grandParent->left != NULL && grandParent->left->isRed
			&& grandParent->right != NULL && grandParent->right->isRed);
}

template<class T>
BrNode<T>* BrNode<T>::rotate()
{
	auto grandParent = parent->parent;
	BrNode<T> *temp = NULL;

	// We have 3 nodes: grandParent, parent, and node -> now we will restructure them.

	// 1) Sort them.
	BrNode<T>* nodes[3] = { grandParent, parent, this };
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 2; j++)
			if (nodes[i]->value < nodes[j]->value)
				std::swap(nodes[i], nodes[j]);

	// 2) Build sub tree. [0] - leftNode, [1] - root, [2] - right.
	nodes[0]->isRed = true;
	if (nodes[0]->right == nodes[1])
		nodes[0]->right = nodes[1]->left;
	if (nodes[0]->right != NULL)
		nodes[0]->right->parent = nodes[0];

	nodes[2]->isRed = true;

	if (nodes[2]->left == nodes[1])
		nodes[2]->left = nodes[1]->right;
	if (nodes[2]->left != NULL)
		nodes[2]->left->parent = nodes[2];

	grandParent->replaceMeForParent(nodes[1]);
	nodes[1]->parent = grandParent->parent;
	nodes[1]->isRed = false;
	nodes[1]->left = nodes[0];
	nodes[1]->right = nodes[2];

	nodes[0]->parent = nodes[1];
	nodes[2]->parent = nodes[1];

	return nodes[1];
}