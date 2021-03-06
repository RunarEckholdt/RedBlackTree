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
	void fixDoubleRed(Node<T>* grandChild);
	void fixTreeUp(Node<T>* current);
	/*Node<T>* findMin(Node<T>* z, Node<T>* v, Node<T>* u)const;
	Node<T>* findMid(Node<T>* z, Node<T>* v, Node<T>* u)const;
	Node<T>* findMax(Node<T>* z, Node<T>* v, Node<T>* u)const;*/
	void findMaxMidMin(Node<T>*& a, Node<T>*& b, Node<T>*& c, Node<T>* z, Node<T>* v, Node<T>* u);
	void disconnect(Node<T>* node);
	int maxBlackDepth()const;
	int maxBlackDepth(Node<T>* current, int curDepth)const;
	int getBlackDepth(Node<T>* current, int curDepth)const;
	bool isBalanced()const;
	bool isBalanced(Node<T>* current, const int& maxDepth,int curDepth)const;
	int maxDepth(Node<T>* current, int curDepth)const;
	int maxDepth()const;
	void allocatePositionInPrintTree(Node<T>** printTree[] , int treeIndex[] , int curDepth, Node<T>* current,const int& mDepth);
	

public:
	RedBlackTree();
	~RedBlackTree();
	Node<T>* getRoot()const;
	void insert(T value);
	void remove(T value);
	void print()const;
	
	
	
};



template<typename T>
inline void RedBlackTree<T>::trinodeRestructuring(Node<T>* z, Node<T>* v, Node<T>* u)
{
	Node<T>* a = nullptr;
	Node<T>* b = nullptr;
	Node<T>* c = nullptr;

	findMaxMidMin(a, b, c, z, v, u,);

	Node<T> oldU = *u;
	//Node<T> tempB = *b;
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
	//c->setLeft(tempB.getRight());

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
	a->setRed();
	b->setBlack();
	c->setRed();
	
	

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
inline void RedBlackTree<T>::fixDoubleRed(Node<T>* grandChild){
	Node<T>* parrent = grandChild->getParent();
	if (parrent->getSibling() != nullptr) {
		if (parrent->getSibling()->isRed()) {
			recolorChidren(parrent->getParent());
		}
	}
	else {
		trinodeRestructuring(grandChild, parrent, parrent->getParent());
	}
}

template<typename T>
inline void RedBlackTree<T>::fixTreeUp(Node<T>* current){
	if (current == nullptr) return;
	if (current->isRed() && current->getParent()->isRed()) {
		fixDoubleRed(current);
	}
	fixTree(current->getParent());
}

//template<typename T>
//inline Node<T>* RedBlackTree<T>::findMin(Node<T>* z, Node<T>* v, Node<T>* u) const{
//	if (*z < *v && *z < *u)
//		return z;
//	else if (*v < *z && *v < *u)
//		return v;
//	else
//		return u;
//}
//
//template<typename T>
//inline Node<T>* RedBlackTree<T>::findMid(Node<T>* z, Node<T>* v, Node<T>* u) const{
//	if (*z < *v && *u < *z || *z < *u && *v < *z)
//		return z;
//	else if (*v < *z && *u < *v || *v < *u && *z < *v)
//		return v;
//	else
//		return u;
//}
//
//template<typename T>
//inline Node<T>* RedBlackTree<T>::findMax(Node<T>* z, Node<T>* v, Node<T>* u) const{
//	if (*v < *z && *u < *z)
//		return z;
//	else if (*z < *v && *u < *v)
//		return v;
//	else
//		return u;
//}

template<typename T>
inline void RedBlackTree<T>::findMaxMidMin(Node<T>*& a, Node<T>*& b, Node<T>*& c, Node<T>* z, Node<T>* v, Node<T>* u){
	if (*z == *v) {
		if (*z < *u) {
			a = z;
			b = v;
			c = u;
		}
		else {
			a = u;
			b = v;
			c = z;
		}
	}
	else if (*z == *u) {
		if (*z < *v) {
			a = z;
			b = u;
			c = v;
		}
		else {
			a = z;
			b = v;
			c = u;
		}

	}
	else if (*v == *u) {
		if (*u < *z) {
			a = u;
			b = v;
			c = z;
		}
		else {
			a = z;
			b = v;
			c = u;
		}
	}else {
		if (*z < *v && *z < *u)a = z;
		else if (*v < *z && *v < *u)a = v;
		else a = u;

		if (*z < *v && *u < *z || *z < *u && *v < *z) b = z; //if z is the middle value
		else if (*v < *z && *u < *v || *v < *u && *z < *v) b = v;//if v is the middle value
		else b = u;

		if(a != z && b != z) c = z;
		else if(a != v && b != v) c = v;
		else c = u;
	}
	
	
}

template<typename T>
inline void RedBlackTree<T>::disconnect(Node<T>* node){
	node->setLeft(nullptr);
	node->setRight(nullptr);
	node->setParent(nullptr);
}

template<typename T>
inline int RedBlackTree<T>::maxBlackDepth() const
{
	return maxBlackDepth(root,0);
}

template<typename T>
inline int RedBlackTree<T>::maxBlackDepth(Node<T>* current, int curDepth) const
{
	if (current == nullptr)return curDepth;
	int leftDepth;
	int rightDepth;

	if (current->isBlack()) {
		leftDepth = getBlackDepth(current->getLeft(), curDepth + 1);
		rightDepth = getBlackDepth(current->getRight(), curDepth + 1);
	}
	else {
		leftDepth = getBlackDepth(current->getLeft(), curDepth);
		rightDepth = getBlackDepth(current->getRight(), curDepth);
	}

	return (leftDepth < rightDepth) ? rightDepth : leftDepth;
}

template<typename T>
inline int RedBlackTree<T>::getBlackDepth(Node<T>* current, int curDepth)const{
	if (current == nullptr)return curDepth;
	int leftDepth;
	int rightDepth;
	//todo rekursiv black depth
	if (current->isBlack()) {
		leftDepth = getBlackDepth(current->getLeft(), curDepth + 1);
		rightDepth = getBlackDepth(current->getRight(), curDepth + 1);
	}
	else {
		leftDepth = getBlackDepth(current->getLeft(), curDepth);
		rightDepth = getBlackDepth(current->getRight(), curDepth);
	}
}

template<typename T>
inline bool RedBlackTree<T>::isBalanced()const{
	int maxDepth = maxBlackDepth();
	return isBalanced(root, maxDepth, 0);
}

template<typename T>
inline bool RedBlackTree<T>::isBalanced(Node<T>* current, const int& maxDepth, int curDepth) const
{
	if (current == nullptr)
		return (curDepth == maxDepth) ? 1 : 0;

	bool leftBalanced;
	bool rightBalanced;

	if (current->isBlack()) {
		leftBalanced = isBalanced(current->getLeft(), maxDepth, curDepth + 1);
		rightBalanced = isBalanced(current->getRight(), maxDepth, curDepth + 1);
	}
	else {
		leftBalanced = isBalanced(current->getLeft(), maxDepth, curDepth);
		rightBalanced = isBalanced(current->getRight(), maxDepth, curDepth);
	}

	return leftBalanced & rightBalanced;
}

template<typename T>
inline int RedBlackTree<T>::maxDepth(Node<T>* current, int curDepth) const{
	int leftMax = 0;
	int rightMax = 0;
	if (current->getLeft() != nullptr)
		leftMax = maxDepth(current->getLeft(), curDepth + 1);
	if (current->getRight() != nullptr)
		rightMax = maxDepth(current->getRight(), curDepth + 1);
	
	if (leftMax != 0 && rightMax != 0)
		return(leftMax > rightMax) ? leftMax : rightMax;
	else if (leftMax != 0) return leftMax;
	else if (rightMax != 0) return rightMax;
	else return curDepth;
	
}

template<typename T>
inline int RedBlackTree<T>::maxDepth() const
{
	return maxDepth(root,0);
}

template<typename T>
inline void RedBlackTree<T>::allocatePositionInPrintTree(Node<T>** printTree [] , int treeIndex [] , int curDepth, Node<T>* current, const int& mDepth){
	if (current != nullptr) {
		printTree[curDepth][treeIndex[curDepth]] = current;
		treeIndex[curDepth]++;
		allocatePositionInPrintTree(printTree, treeIndex, curDepth + 1, current->getLeft(), mDepth);
		allocatePositionInPrintTree(printTree, treeIndex, curDepth + 1, current->getRight(), mDepth);
	}
	else {
		if (curDepth <= mDepth) {
			printTree[curdepth][treeIndex[curDepth]] = current;
			treeIndex[curDepth]++;
			allocatePositionInPrintTree(printTree, treeIndex, curDepth + 1, nullptr, mDepth);
			allocatePositionInPrintTree(printTree, treeIndex, curDepth + 1, nullptr, mDepth);
		}
	}
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
				break;
			}
			else current = current->getLeft();
		}
		else {
			if (current->getRight() == nullptr) {
				newNode->setParrent(current);
				current->setRight(newNode);
				break;
			}
			else current = current->getRight();
		}
	}
	fixTree(newNode);

}

template<typename T>
inline void RedBlackTree<T>::remove(T value){

}

template<typename T>
inline void RedBlackTree<T>::print()const{
	int mDepth = maxDepth();
	const int maxDigitsInNumber = 3;
	int bottomWidth = pow(2, mDepth) * maxDigitsInNumber * 2;
	Node<T>*** printTree = new Node<T>** [mDepth + 1];
	int* treeIndex = new int[mDepth + 1];
	for (int i = 0; i <= mDepth; i++) {
		printTree[i] = new Node<T> * [pow(2, i)];
		treeIndex[i] = 0;
	}
	allocatePositionInPrintTree(printTree, treeIndex, 0, root, mDepth);
	for (int i = 0; i <= mDepth; i++) {
		for (int n = 0; n < treeIndex[i]; n++) {
			if (printTree[i][n] != nullptr) {
				if (n == 0)
					cout << setw((bottomWidth / 2) / (pow(2, i)) - maxDigitsInNumber) << "" << setw(maxDigitsInNumber) << printTree[i][n];
				else
					cout << setw((bottomWidth / 2) / (pow(2, i - 1)) - maxDigitsInNumber) << "" << setw(maxDigitsInNumber) << printTree[i][n];
			}
			else {
				if (n == 0)
					cout << setw((bottomWidth / 2) / (pow(2, i)) - maxDigitsInNumber) << "" << setw(maxDigitsInNumber) << "-";
				else
					cout << setw((bottomWidth / 2) / (pow(2, i - 1)) - maxDigitsInNumber) << "" << setw(maxDigitsInNumber) << "-";
			}
		}
		cout << endl;
	}
	cout << endl;
}
