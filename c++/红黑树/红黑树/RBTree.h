#pragma once
#include<iostream>

using namespace std;

template<class K, class V>
ostream& operator<<(ostream& os, const pair<K, V>& kv)
{
	os << kv.first << " " << kv.second << " ";
	return os;
}
//--------------------红黑树的口诀是：左根右，根叶黑，不红红，黑路同。
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
	bool Insert(const pair<K, V>& kv)
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
		// 新增结点，颜色红色给红色
		cur->_col = RED;

		if (parent->_kv < kv)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;

		//判断颜色
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//g red
			//p red    //u red/black
			//这种情况
			//首先判断parent位于grandfather的哪边
			//这种情况下依旧分为两类，位于左边跟右边进行讨论
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//因为uncle的颜色不明，在进行讨论
				if (uncle && uncle->_col == RED)
				{
					//uncle存在且为红色->变色继续向上处理
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//uncle为黑色或者不存在->旋转＋变色

					if (cur == parent->_left)
					{
						//g
						//p    //u
						//c
						//单旋
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//g
						//p    //u
						//c
						//双旋转

						RotateL(parent);
						RotateR(grandfather);

						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			//これから練習しよう!
			else
			{
				// g
				// u p
				Node* uncle = grandfather->_left;
				// 叔叔存在且为红，-》变⾊即可
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					// 继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else // 叔叔不存在，或者存在且为黑
				{
					// 情况⼆：叔叔不存在或者存在且为黑
					// 旋转+变色
					// g
					// u p
					// c
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						// g
						// u p
						// c
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;

		if (subLR)
			subLR->_parent = parent;

		Node* pParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (pParent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent == pParent->_left)
			{
				pParent->_left = subL;
			}
			else
			{
				pParent->_right = subL;
			}
		}
		subL->_parent = pParent;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		Node* pParent = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		//考虑是否为子树
		if (pParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parent == pParent->_left)
			{
				pParent->_left = subR;
			}
			else
			{
				pParent->_right = subR;
			}

			subR->_parent = pParent;
		}
	}

	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < key)
			{
				cur = cur->_right;
			}
			else if (cur->_kv.first > key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
			return nullptr;
		}
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		cout << root->_kv << " ";
		_InOrder(root->_left);
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	Node* _root = nullptr;
};
//实现复用红黑树的框架，并支持insert


