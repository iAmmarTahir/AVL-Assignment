#pragma once

template <class K,class T>
class AVLNode
{
public:
	K key;
	T * data;
	AVLNode<K, T> * left;
	AVLNode<K, T> * right;
	int height;
	AVLNode();
	AVLNode(const K &_key, T * _data, AVLNode<K, T> * _left, AVLNode<K, T> * _right, int _height);
};

template <class K, class T>
AVLNode<K, T>::AVLNode()
{
	key = 0;
	data = 0;
	left = 0;
	right = 0;
	height = 0;
}

template <class K, class T>
AVLNode<K, T>::AVLNode(const K &_key, T *_data, AVLNode<K, T> * _left, AVLNode<K, T> * _right, int _height)
{
	key = _key;
	data = _data;
	left = _left;
	right = _right;
	height = _height;
}