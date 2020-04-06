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
	void trinodeRestructuring();
	void recolorChidren(Node<T>* parrent);
	void deleteChildren(Node<T>* parrent);

public:
	RedBlackTree();
	~RedBlackTree();
	Node<T>* getRoot()const;
	void insert(T value);
	void remove(T value);
	
	
};

template<typename T>
inline void RedBlackTree<T>::trinodeRestructuring()
{
	
}

template<typename T>
inline void RedBlackTree<T>::recolorChidren(Node<T>* parrent){
	if (parrent->getLeft() != nullptr)
		parrent->getLeft()->changeColor();
	if (parrent->getRight() != nullptr)
		parrent->getRight()->changeColor();
}

template<typename T>
inline void RedBlackTree<T>::deleteChildren(Node<T>* parrent){
	if (parrent == nullptr)return;
	deleteChildren(parrent->getLeft());
	deleteChildren(parrent->getRight());
	delete parrent;
}

template<typename T>
inline void RedBlackTree<T>::insert(Node<T>* current, T value){
	if (current == nullptr) {
		
	}
	if(value<current->getValue())

}

template<typename T>
inline RedBlackTree<T>::RedBlackTree(){}

template<typename T>
inline RedBlackTree<T>::~RedBlackTree(){
	deleteChildren(root);
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
				current->setLeft(newNode);
				return;
			}
			else current = current->getLeft();
		}
		else {
			if (current->getRight() == nullptr) {
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
