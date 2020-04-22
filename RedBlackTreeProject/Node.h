#pragma once
#include <vector>
using namespace std;
template<typename T>
class Node
{
	T value;
	bool colorBlack;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
public:
	Node(T value);
	T getValue()const;
	bool isBlack()const;
	bool isRed()const;
	Node<T>* getLeft()const;
	Node<T>* getRight()const;
	Node<T>* getParent()const;
	void setLeft(Node<T>* child);
	void setRight(Node<T>* child);
	void setParent(Node<T>* parrent);
	void changeColor();
	Node<T>* getSibling()const;
	void setBlack();
	void setRed();
};

template<typename T>
inline Node<T>::Node(T value)
	:value(value),colorBlack(false),left(nullptr),right(nullptr),parrent(nullptr)
{}

template<typename T>
inline T Node<T>::getValue() const{ return value; }

template<typename T>
inline bool Node<T>::isBlack() const{ return colorBlack; }

template<typename T>
inline bool Node<T>::isRed() const{ return !colorBlack; }

template<typename T>
inline Node<T>* Node<T>::getLeft() const{ return left; }

template<typename T>
inline Node<T>* Node<T>::getRight() const{ return right; }

template<typename T>
inline void Node<T>::setLeft(Node<T>* child) { left = child; }

template<typename T>
inline void Node<T>::setRight(Node<T>* child) { right = child; }

template<typename T>
inline void Node<T>::setParent(Node<T>* parent){ this->parent = parent; }

template<typename T>
inline Node<T>* Node<T>::getParent() const{ return parent; }

template<typename T>
inline void Node<T>::changeColor() { colorBlack = !colorBlack; }

template<typename T>
inline Node<T>* Node<T>::getSibling() const {
	if (parrent->getLeft() != this)return parrent->getLeft();
	else return parrent->getRight();
}

template<typename T>
inline void Node<T>::setBlack(){colorBlack = true;}

template<typename T>
inline void Node<T>::setRed(){colorBlack = false;}




template<typename T>
bool operator<(Node<T> a, Node<T> b) {
	return a.getValue() < b.getValue();
}

template<typename T>
bool operator==(Node<T> a, Node<T> b) {
	return a.getValue() == b.getValue();
}