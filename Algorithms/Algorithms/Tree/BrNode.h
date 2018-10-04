#pragma once
#include "configs.h"

template<class T>
struct BrNode
{
	BrNode(BrNode<T>* parent, const T& value);
	~BrNode();

	T value;
	bool isBlack;
	BrNode<T> *parent, *left, *right;

	int getBlackHeight();
	bool hasOneChild();
	void replaceMeForParent(BrNode<T>* newNode);
};



template<class T>
BrNode<T>::BrNode(BrNode<T>* parent, const T& value)
	: value(value), parent(parent), left(NULL), right(NULL), isBlack(false)
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
int BrNode<T>::getBlackHeight()
{
	if (left == NULL && right == NULL)
		return isBlack ? 1 : 0;

	int leftHeight = left != NULL
		? left->getBlackHeight()
		: 0;
	int rightHeight = right != NULL
		? right->getBlackHeight()
		: 0;

	return (leftHeight == rightHeight && leftHeight >= 0)
		? leftHeight 
		: -1; // - subtree is not balanced.
}

template<class T>
bool BrNode<T>::hasOneChild()
{
	return (left == NULL && right != NULL)
		|| (left != NULL && right == NULL);
}

template<class T>
void BrNode<T>::replaceMeForParent(BrNode<T>* newNode)
{
	if (parent == NULL)
		return;

	(parent->left == this) ? parent->left : parent->right
		= newNode;
}