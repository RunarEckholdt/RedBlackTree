#pragma once
template<typename T>
class Node
{
	T value;
	bool colorBlack;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parrent;
public:
	Node(T value);
	T getValue()const;
	bool isBlack()const;
	bool isRed()const;
	Node<T>* getLeft()const;
	Node<T>* getRight()const;
	Node<T>* getParrent()const;
	void setLeft(Node<T>* child);
	void setRight(Node<T>* child);
	void setParrent(Node<T>* parrent);
	void changeColor();
};

template<typename T>
inline Node<T>::Node(T value)
	:value(value),colorBlack(true),left(nullptr),right(nullptr)
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
inline void Node<T>::setParrent(Node<T>* parrent){ this->parrent = parrent; }

template<typename T>
inline Node<T>* Node<T>::getParrent() const{ return parrent; }

template<typename T>
inline void Node<T>::changeColor() { colorBlack = !colorBlack; }
