#pragma once
#include<iostream>

using namespace std;

// 枚举值表⽰颜⾊
enum Colour
{
	RED,
	BLACK
};
// 这⾥我们默认按key/value结构实现
template<class K, class V>
struct RBTreeNode
{
	// 这⾥更新控制平衡也要加⼊parent指针
	pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Colour _col;
	RBTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{
	}
};
template<class K, class V>
class RBTree
{
typedef RBTreeNode<K, V> Node;
public:
	bool Insert(const pair<K,V>& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
				return true;
			}
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_kv.first < kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_kv.first > kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			cur = new Node(kv);
			// 新增结点。颜⾊红⾊给红⾊
			cur->_col = RED;
			
			if (parent->_kv < key)
			{
				parent->_right = cur;
			}
			else if (parent->_left > key)
			{
				parent->_left = cur;
			}
			cur->_parent = parent;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//快速分割parent
		parent->_left = subLR;

		if (subLR)
		{
			subLR->_parent = parent;
		}
		Node* pParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		//对此时的根节点进行判断
		if (pParent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent == pParent->_right)
			{
				pParent->_right = subL;
			}
			else if (parent == pParent->_right)
			{
				pParent->_left = subL;
			}

			subL->_parent = pParent;
		}
	}
private:
Node* _root = nullptr;
};

