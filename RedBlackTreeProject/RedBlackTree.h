#pragma once
#include "Node.h"
/*properties of tree:
	The root is black
	Every external node is black
	The children of red node are black
	All external nodes have the same black depth, defined as the number of black ancestors minus one where the node is an ancestor of itself
	*/

template<typename T>
class RedBlackTree
{
	Node<T>* root;
	void trinodeRestructuring(Node<T>* z,Node<T>* v,Node<T>* u);
	void recolorChidren(Node<T>* parrent);
	void deleteNode(Node<T>* parrent);
	void fixTree();
	Node<T>* findMin(Node<T>* z, Node<T>* v, Node<T>* u)const;
	Node<T>* findMid(Node<T>* z, Node<T>* v, Node<T>* u)const;
	Node<T>* findMax(Node<T>* z, Node<T>* v, Node<T>* u)const;
	void disconnect(Node<T>* node);

public:
	RedBlackTree();
	~RedBlackTree();
	Node<T>* getRoot()const;
	void insert(T value);
	void remove(T value);
	
	
};



template<typename T>
inline void RedBlackTree<T>::trinodeRestructuring(Node<T>* z, Node<T>* v, Node<T>* u)
{
	Node<T>* a = findMin(z, v, u);
	Node<T>* b = findMid(z, v, u);
	Node<T>* c = findMax(z, v, u);
	Node<T> oldU = *u;
	Node<T> tempB = *b;
	vector<Node<T>*> children;
	if (z->getLeft() != nullptr)children.push_back(z->getLeft());
	if (z->getRight() != nullptr)children.push_back(z->getRight());

	if (v->getLeft() != nullptr && v->getLeft()==z)children.push_back(z->getLeft());
	if (v->getRight() != nullptr && v->getRight() == z)children.push_back(z->getRight());

	if (u->getLeft() != nullptr && u->getLeft() == v)children.push_back(z->getLeft());
	if (u->getRight() != nullptr && u->getRight() == v)children.push_back(z->getRight());

	disconnect(a);
	disconnect(b);
	disconnect(c);


	u = b;
	u->setParent(oldU.getParent());
	u->setLeft(a);
	u->setRight(c);
	a->setParent(b);
	c->setParent(b);
	c->setLeft(tempB.getRight());

	for (Node<T>* node : children) {
		if (*node < *b) {
			if (*node < *a) a->setLeft(node);
			else a->setRight(node);
		}
		else {
			if (*node < *c) c->setLeft(node);
			else c->setRight(node);
		}
	}
	
	

}

template<typename T>
inline void RedBlackTree<T>::recolorChidren(Node<T>* parrent){
	if (parrent->getLeft() != nullptr)
		parrent->getLeft()->changeColor();
	if (parrent->getRight() != nullptr)
		parrent->getRight()->changeColor();
}

template<typename T>
inline void RedBlackTree<T>::deleteNode(Node<T>* parrent){
	if (parrent == nullptr)return;
	deleteNode(parrent->getLeft());
	deleteNode(parrent->getRight());
	delete parrent;
}

template<typename T>
inline Node<T>* RedBlackTree<T>::findMin(Node<T>* z, Node<T>* v, Node<T>* u) const{
	if (*z < *v && *z < *u)
		return z;
	else if (*v < *z && *v < *u)
		return v;
	else
		return u;
}

template<typename T>
inline Node<T>* RedBlackTree<T>::findMid(Node<T>* z, Node<T>* v, Node<T>* u) const{
	if (*z < *v && *u < *z || *z < *u && *v < *z)
		return z;
	else if (*v < *z && *u < *v || *v < *u && *z < *v)
		return v;
	else
		return u;
}

template<typename T>
inline Node<T>* RedBlackTree<T>::findMax(Node<T>* z, Node<T>* v, Node<T>* u) const{
	if (*v < *z && *u < *z)
		return z;
	else if (*z < *v && *u < *v)
		return v;
	else
		return u;
}

template<typename T>
inline void RedBlackTree<T>::disconnect(Node<T>* node){
	node->setLeft(nullptr);
	node->setRight(nullptr);
	node->setParent(nullptr);
}



template<typename T>
inline RedBlackTree<T>::RedBlackTree()
	:root(nullprt)
{}

template<typename T>
inline RedBlackTree<T>::~RedBlackTree(){
	deleteNode(root);
}

template<typename T>
inline Node<T>* RedBlackTree<T>::getRoot() const{ return root; }


template<typename T>
inline void RedBlackTree<T>::insert(T value){
	Node<T>* newNode = new Node<T>(value);
	if (root == nullptr) {
		root = newNode;
		return;
	}
	Node<T>* current = root;
	
	while (true) {
		if (value < current->getValue()) {
			if (current->getLeft() == nullptr) {
				newNode->setParrent(current);
				current->setLeft(newNode);
				return;
			}
			else current = current->getLeft();
		}
		else {
			if (current->getRight() == nullptr) {
				newNode->setParrent(current);
				current->setRight(newNode);
				return;
			}
			else current = current->getRight();
		}
	}

}

template<typename T>
inline void RedBlackTree<T>::remove(T value){

}
