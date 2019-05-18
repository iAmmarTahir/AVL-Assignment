#pragma once
#include "AVLNode.h"
#include <Windows.h>
#include <string>

using namespace std;

#define ALLOWED_IMBALANCE 1


void PlaceCursor(int x, int y)
{
	COORD c;
	c.X = x, c.Y = y;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}

int GetYCoordinates()
{
	CONSOLE_SCREEN_BUFFER_INFO c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(h, &c))
	{
		return c.dwCursorPosition.Y;
	}
}

template <class K, class T>
class AVLTree
{
private:
	AVLNode<K, T> * root;

public:
	AVLTree();
	~AVLTree();
	bool Insert(const K &key,T *element);
	bool Insert(AVLNode<K, T> * &ptr,const K &key,T *element);
	void rightRotate(AVLNode<K, T> *&x);
	void leftRotate(AVLNode<K, T> *&x);
	void leftRightRotate(AVLNode<K, T> *&x);
	void rightLeftRotate(AVLNode<K, T> *&x);
	int height(AVLNode<K, T> *ptr);
	int height() { return height(root); }
	int Max(int a, int b);
	void balance(AVLNode<K, T> * &ptr);
	bool lookUp(const K &key);
	bool lookUp(AVLNode<K, T> * ptr, const K &key);
	void printInorder();
	void printInorder(AVLNode<K, T> * ptr);
	void Visit(AVLNode<K, T> * ptr);
	void clear(AVLNode<K, T> * &ptr);
	bool deleteNode(const K &key);
	bool deleteNode(AVLNode<K, T> *&ptr, const K &key);
	void deleteByCopying(AVLNode<K, T> *&ptr);
	AVLNode<K, T> * Max(AVLNode<K, T> *&ptr, AVLNode<K, T> *&parent);
	void printTree(AVLNode<K, T> * ptr, int &x, int y)
	{
		if (ptr == 0)
			return;
		printTree(ptr->left, x, y + 4);
		PlaceCursor(x, y);
		cout << ptr->key;
		x += 4;
		printTree(ptr->right, x, y + 4);
	}
	void printTree()
	{
		int x = 0;
		printTree(root, x, GetYCoordinates());
	}
};

template <class K, class T>
AVLTree<K, T>::AVLTree()
{
	root = 0;
}

template <class K, class T>
AVLTree<K, T>::~AVLTree()
{
	clear(root);
}

template <class K, class T>
bool AVLTree<K, T>::Insert(const K &key, T *element)
{
	return Insert(root, key, element);
}

template <class K, class T>
bool AVLTree<K, T>::Insert(AVLNode<K, T> * &ptr,const K &key, T *element)
{
	if (ptr == 0)
	{
		ptr = new AVLNode<K, T>();
		ptr->data = element;
		ptr->key = key;
		return true;
	}
	else
	{
		if (ptr->key < key)
		{
			Insert(ptr->right, key, element);
		}
		else if (ptr->key > key)
		{
			Insert(ptr->left, key, element);
		}
		else
		{
			return false;
		}
	}
	balance(ptr);
}

template <class K, class T>
void AVLTree<K, T>::rightRotate(AVLNode<K, T> *& x)
{
	AVLNode<K, T> * orphan = x->left->right;
	AVLNode<K, T> * y = x->left;

	y->right = x;
	x->left = orphan;

	x->height = height(x);
	y->height = height(y);

	x = y;
}

template <class K, class T>
void AVLTree<K, T>::leftRotate(AVLNode<K, T> *& x)
{
	AVLNode<K, T> * orphan = x->right->left;
	AVLNode<K, T> * y = x->right;
	y->left = x;
	x->right = orphan;

	x->height = height(x);
	y->height = height(y);

	x = y;
}

template <class K, class T>
void AVLTree<K, T>::leftRightRotate(AVLNode<K, T> *& x)
{
	leftRotate(x->left);
	rightRotate(x);
}

template <class K, class T>
void AVLTree<K, T>::rightLeftRotate(AVLNode<K, T> *& x)
{
	rightRotate(x->right);
	leftRotate(x);
}

template <class K, class T>
int AVLTree<K, T>::height(AVLNode<K, T> *ptr)
{
	if (ptr == 0)
		return -1;
	else
		return ptr->height;
}

template <class K, class T>
int AVLTree<K, T>::Max(int a, int b)
{
	return a < b ? b : a;
}

template <class K, class T>
void AVLTree<K, T>::balance(AVLNode<K, T> *&ptr)
{
	if (ptr)
	{
		if (height(ptr->left) - height(ptr->right) > ALLOWED_IMBALANCE)
		{
			if (height(ptr->left->left) >= height(ptr->left->right))
			{
				rightRotate(ptr);
			}
			else
			{
				leftRightRotate(ptr);
			}
		}
		else if (height(ptr->right) - height(ptr->left) > ALLOWED_IMBALANCE)
		{
			if (height(ptr->right->right) >= height(ptr->right->left))
			{
				leftRotate(ptr);		
			}
			else
			{
				rightLeftRotate(ptr);
			}
		}
		ptr->height = Max(height(ptr->left), height(ptr->right)) + 1;
	}
}

template <class K, class T>
bool AVLTree<K, T>::lookUp(const K &key)
{
	return lookUp(root, key);
}

template <class K, class T>
bool AVLTree<K, T>::lookUp(AVLNode<K, T> * ptr, const K &key)
{
	if (ptr == 0)
		return false;
	else
	{
		if (ptr->key < key)
			lookUp(ptr->right, key);
		else if (ptr->key > key)
			lookUp(ptr->left, key);
		else
			return true;
	}
}

template <class K, class T>
void AVLTree<K, T>::printInorder()
{
	printInorder(root);
}

template <class K, class T>
void AVLTree<K, T>::printInorder(AVLNode<K, T> * ptr)
{
	if (ptr)
	{
		printInorder(ptr->left);
		Visit(ptr);
		printInorder(ptr->right);
	}
}

template <class K, class T>
void AVLTree<K, T>::Visit(AVLNode<K, T> * ptr)
{
	cout.setf(ios::left);
	cout.width(10);
	cout << ptr->key;
	cout << *ptr->data;
}

template <class K, class T>
void AVLTree<K, T>::clear(AVLNode<K, T> * &ptr)
{
	if (ptr)
	{
		clear(ptr->left);
		clear(ptr->right);
		delete ptr;
	}
}

template <class K, class T>
bool AVLTree<K, T>::deleteNode(const K &key)
{
	return deleteNode(root, key);
}

template <class K, class T>
bool AVLTree<K, T>::deleteNode(AVLNode<K, T> *&ptr, const K &key)
{
	if (ptr)
	{
		if (ptr->key > key)
		{
			deleteNode(ptr->left, key);
		}
		else if (ptr->key < key)
		{
			deleteNode(ptr->right, key);
		}
		else
		{
			deleteByCopying(ptr);
		}
		balance(ptr);
		return true;
	}
	else
	{
		return false;
	}
	
}

template <class K, class T>
void AVLTree<K, T>::deleteByCopying(AVLNode<K, T> *&ptr)
{
	if (ptr->left == 0)
	{
		AVLNode<K, T> * temp = ptr;
		ptr = ptr->right;
		delete temp;
	}
	else if (ptr->right == 0)
	{
		AVLNode<K, T> * temp = ptr;
		ptr = ptr->left;
		delete temp;
	}
	else
	{
		AVLNode<K, T> * parent = ptr;
		AVLNode<K, T> * temp = ptr;
		temp = temp->left;
		temp = Max(temp, parent);
		ptr->data = temp->data;
		if (parent == ptr)
			parent->left = temp->left;
		else
			parent->right = temp->left;
		delete temp;
	}
}

template <class K, class T>
AVLNode<K, T> * AVLTree<K, T>::Max(AVLNode<K, T> *&ptr, AVLNode<K, T> *&parent)
{
	while (ptr->right)
	{
		parent = ptr;
		ptr = ptr->right;
	}
	return ptr;
}


