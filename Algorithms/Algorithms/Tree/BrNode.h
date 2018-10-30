#pragma once
#include "configs.h"

template<class T>
struct BrNode
{
	BrNode(BrNode<T>* parent, BrNode<T>** parentPointerToThis, const T& value);
	~BrNode();

	T value;
	bool isRed;
	BrNode<T> *parent, *left, *right;
	BrNode<T> **parentPointerToThis;

	void toJson(std::ostream& out);
	void leaveParent();

	// Set new child for my parent instead of me.
	void replaceMeForParent(BrNode<T>* newNode);
	void setLeft(BrNode<T>* node);
	void setRight(BrNode<T>* node);

	bool isNeedMoveDownBlackness();
	void moveDownBlackness();

	bool isNeedRotate();
	BrNode<T>* rotate();

	bool isNeedSimpleRotate();
	BrNode<T>* simpleRotate();

	short getChildCount();
	BrNode<T>* getOneChildOrNull();
	BrNode<T>* getBrother();

	void removeRedLeaf();
	void removeBlackLeaf();
	void removeBlackNodeWithRedChild();
	void remove();

	bool isCase1();
	bool isCase2();
	bool isCase3();
	bool isCase4();
	bool isCase5();
	bool isCase6();
	BrNode<T>* removeCase1();
	BrNode<T>* removeCase2();
	BrNode<T>* removeCase3();
	BrNode<T>* removeCase4();
	BrNode<T>* removeCase5();
	BrNode<T>* removeCase6();

};

template<class T>
bool IsRed(BrNode<T>* node) {
	return !(node == NULL || !node->isRed);
}

template<class T>
BrNode<T>::BrNode(BrNode<T>* parent, BrNode<T>** parentPointerToThis, const T& value)
	: value(value), parent(parent), parentPointerToThis(parentPointerToThis),
		left(NULL), right(NULL), isRed(true)
{ }

template<class T>
BrNode<T>::~BrNode() {
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
void BrNode<T>::leaveParent() {
	*parentPointerToThis = NULL;
	parentPointerToThis = NULL;
	parent = NULL;
}

template<class T>
void BrNode<T>::replaceMeForParent(BrNode<T>* newNode) {
	*parentPointerToThis = newNode;
	newNode->parent = parent;
	newNode->parentPointerToThis = parentPointerToThis;
	parentPointerToThis = NULL;
	parent = NULL;
}

template<class T>
void BrNode<T>::setLeft(BrNode<T>* node) {
	if (node != NULL) {
		node->parent = this;
		node->parentPointerToThis = &left;
	}
	left = node;
}

template<class T>
void BrNode<T>::setRight(BrNode<T>* node) {
	if (node != NULL) {
		node->parent = this;
		node->parentPointerToThis = &right;
	}
	right = node;
}

template<class T>
bool BrNode<T>::isNeedMoveDownBlackness() {
	if (parent == NULL)
		return false;

	auto grandParent = parent->parent;
	if (grandParent == NULL || grandParent->left == NULL || grandParent->right == NULL)
		return false;

	return isRed && grandParent->left->isRed && grandParent->right->isRed;
}

template<class T>
void BrNode<T>::moveDownBlackness() {
	auto grandParent = parent->parent;

	grandParent->isRed = true;
	grandParent->left->isRed = grandParent->right->isRed = false;
}

template<class T>
bool BrNode<T>::isNeedRotate() {
	if (parent == NULL)
		return false;

	auto grandParent = parent->parent;
	if (grandParent == NULL)
		return false;

	return isRed && parent->isRed &&
		((this == parent->left && parent == parent->parent->left)
			|| (this == parent->right && parent == parent->parent->right));
}

template<class T>
BrNode<T>* BrNode<T>::rotate() {
	auto grandParent = parent->parent;

	// We have 3 nodes: grandParent, parent, and node -> now we will restructure them.

	// 1) Sort them.
	std::vector<BrNode*> nodes = { grandParent, parent, this };
	std::sort(nodes.begin(), nodes.end(), [](BrNode* a, BrNode* b) { 
		return a->value < b->value;
	});

	// 2) Build sub tree. [0] - leftNode, [1] - root, [2] - right.
	grandParent->replaceMeForParent(nodes[1]);
	
	nodes[0]->isRed = true;
	if (nodes[0]->right == nodes[1])
		nodes[0]->setRight(nodes[1]->left);

	nodes[2]->isRed = true;
	if (nodes[2]->left == nodes[1])
		nodes[2]->setLeft(nodes[1]->right);

	nodes[1]->isRed = false;
	nodes[1]->setLeft(nodes[0]);
	nodes[1]->setRight(nodes[2]);

	return nodes[1];
}

template<class T>
bool BrNode<T>::isNeedSimpleRotate() {
	if (parent == NULL)
		return false;

	auto grandParent = parent->parent;
	if (grandParent == NULL)
		return false;

	return isRed && parent->isRed && 
		((this == parent->left && parent == parent->parent->right)
			|| (this == parent->right && parent == parent->parent->left));
}

template<class T>
BrNode<T>* BrNode<T>::simpleRotate() {
	auto _parent = parent;
	parent->replaceMeForParent(this);

	if (value < _parent->value)
	{
		auto temp = right;
		setRight(_parent);
		_parent->setLeft(temp);
	}
	else {
		auto temp = left;
		setLeft(_parent);
		_parent->setRight(temp);
	}
	return _parent;
}

template<class T>
short BrNode<T>::getChildCount() {
	int count = 0;
	if (left != NULL)
		count++;
	if (right != NULL)
		count++;
	return count;
}

template<class T>
BrNode<T>* BrNode<T>::getOneChildOrNull() {
	return left != NULL ? left : right;
}

template<class T>
BrNode<T>* BrNode<T>::getBrother() {
	if (parent == NULL)
		return NULL;
	return parent->left != this
		? parent->left
		: parent->right;
}

template<class T>
void BrNode<T>::remove() {
	short childCount = getChildCount();

	// If node is leaf or preleaf.
	if (childCount < 2) {
		if (isRed)
			removeRedLeaf();
		else {
			if (childCount == 0)
				removeBlackLeaf();
			else
				removeBlackNodeWithRedChild();
		}
		return;
	}

	// Find max value in left branch.
	auto node = left;
	while (node->right != NULL)
		node = node->right;

	value = node->value;
	node->remove();
}

template<class T>
void BrNode<T>::removeRedLeaf() {
	leaveParent();
	delete this;
}

template<class T>
void BrNode<T>::removeBlackNodeWithRedChild() {
	auto childNode = getOneChildOrNull();
	childNode->isRed = false;
	replaceMeForParent(childNode);
	left = right = NULL;
	delete this;
}

template<class T>
void BrNode<T>::removeBlackLeaf() {
	auto node = this;
	while (node != NULL)
	{
		if (node->isCase1()) {
			node = node->removeCase1();
			continue;
		}
		else if (node->isCase2()) {
			node = node->removeCase2();
			continue;
		}
		else if (node->isCase3()) {
			node = node->removeCase3();
			continue;
		}
		else if (node->isCase4()) {
			node = node->removeCase4();
			continue;
		}
		else if (node->isCase5()) {
			node = node->removeCase5();
			continue;
		}
		else if (node->isCase6()) {
			node = node->removeCase6();
			continue;
		}
	}

	leaveParent();
	delete this;
}

// Node is root.
template<class T>
bool BrNode<T>::isCase1() {
	return parent == NULL;
}

template<class T>
BrNode<T>* BrNode<T>::removeCase1() {
	return NULL;
}

// Parent is black && brother is red && brother's childs are black.
template<class T>
bool BrNode<T>::isCase2() {
	auto brother = getBrother();
	return !parent->isRed && brother->isRed
		&& !IsRed(brother->left) && !IsRed(brother->right);
}

template<class T>
BrNode<T>* BrNode<T>::removeCase2() {
	auto brother = getBrother();
	auto x = brother->left;
	auto y = brother->right;
	
	parent->isRed = true;
	brother->isRed = false;

	parent->replaceMeForParent(brother);
	brother->setLeft(parent);
	brother->setRight(y);

	parent->setRight(x);

	return this;
}

// Parent is black && brother is black && brother's childs are black.
template<class T>
bool BrNode<T>::isCase3() {
	auto brother = getBrother();
	return !parent->isRed && !IsRed(brother)
		&& !IsRed(brother->left) && !IsRed(brother->right);
}

template<class T>
BrNode<T>* BrNode<T>::removeCase3() {
	getBrother()->isRed = true;
	return parent;
}

// Parent is red && brother is black && brother's childs are black.
template<class T>
bool BrNode<T>::isCase4() {
	auto brother = getBrother();
	return parent->isRed && !brother->isRed && !IsRed(brother->left) && !IsRed(brother->right);
}

template<class T>
BrNode<T>* BrNode<T>::removeCase4() {
	parent->isRed = false;
	getBrother()->isRed = true;

	return NULL;
}

// Brother is black && brother->left is red && brother->right is black.
template<class T>
bool BrNode<T>::isCase5() {
	auto brother = getBrother();
	return !brother->isRed && IsRed(brother->left) && !IsRed(brother->right);
}

template<class T>
BrNode<T>* BrNode<T>::removeCase5() {
	auto brother = getBrother();
	auto x = brother->left;

	x->isRed = false;
	brother->isRed = true;
	brother->setLeft(x->right);
	parent->setRight(x);
	x->setRight(brother);
	
	return this;
}

// Brother is black && brother->right is red.
template<class T>
bool BrNode<T>::isCase6() {
	auto brother = getBrother();
	return !brother->isRed && IsRed(brother->right);
}

template<class T>
BrNode<T>* BrNode<T>::removeCase6() {
	auto brother = getBrother();
	auto x = brother->left;
	auto y = brother->right;

	parent->replaceMeForParent(brother);
	brother->setLeft(parent);
	brother->setRight(y);

	parent->setRight(x);

	brother->isRed = parent->isRed;
	parent->isRed = false;
	y->isRed = false;

	return NULL;
}