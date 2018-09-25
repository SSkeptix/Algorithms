#pragma once
#include "configs.h"

template<class T>
struct BinaryNode
{
	BinaryNode(BinaryNode* root, const T& value);
	~BinaryNode();

	T value;
	BinaryNode *root, *left, *right;
};



template<class T>
BinaryNode<T>::BinaryNode(BinaryNode* root, const T& value)
	: value(value), root(root), left(NULL), right(NULL)
{ }

template<class T>
BinaryNode<T>::~BinaryNode()
{ 
	if (left != NULL)
		delete left;
	if (right != NULL)
		delete right;
}