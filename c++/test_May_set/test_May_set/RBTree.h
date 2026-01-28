#pragma once
#include<iostream>
using namespace std;

enum Color
{
	RED,
	BLACK
};
template<class T>
struct RBTreeNode
{
	T _data;
	RBTreeNode<T>*_left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Color _col;
	RBTreeNode(const T& data)
		: _data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{}
};
template<class T,class Ref,class Ptr>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> Self;

	Node* _node;
	Node* _root;

	RBTreeIterator(Node* node, Node* root) :_node(node), _root(root) {}

	Self& operator++() {
		if (_node->_right)
		{
			//右不为空，右子树最左节点就是中序的第一个
			Node* leftMost = _node->_right;
			while (leftMost->_left) {

				leftMost = leftMost->_left;
			}
			_node = leftMost;
		}
		else {
			//孩子是父亲左的那个节点
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}
	Self& operator--()
	{
		if (_node == nullptr) // end()
		{
			// --end()，特殊处理，⾛到中序最后⼀个结点，整棵树的最右结点
			Node* rightMost = _root;
			while (rightMost && rightMost->_right)
			{
				rightMost = rightMost->_right;
			}
			_node = rightMost;
		}
		else if (_node->_left)
		{
			// 左⼦树不为空，中序左⼦树最后⼀个
			Node* rightMost = _node->_left;
			while (rightMost->_right)
			{
				rightMost = rightMost->_right;
			}
			_node = rightMost;
		}
		else
		{
			// 孩⼦是⽗亲右的那个祖先
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && cur == parent->_left)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &_node->_data;
	}

	bool operator!=(const Self&s)const
	{
		return _node != s._node;
	}
	bool operator==(const Self& s)const
	{
		return _node == s._node;
	}
};

template<class K,class T,class keyOfT>
class RBTree
{
	typedef RBTreeNode<T>Node;
public:
	typedef RBTreeIterator<T, T&, T*> Iterator;
	typedef RBTreeIterator<T, const T&, const T*> ConstIterator;

	Iterator Begin()
	{
		Node* leftMost = _root;
		while (leftMost && leftMost->_left)
		{
			leftMost = leftMost->_left;
		}
		return Iterator(leftMost, _root);
	}

	Iterator End()
	{
		return Iterator(nullptr, _root);
	}

	ConstIterator Begin()const
	{
		Node* leftMost = _root;
		while (leftMost->_left)
		{
			leftMost = leftMost->_left;
		}
		return ConstIterator(leftMost, _root);
	}

	ConstIterator End()
	{
		return ConstIterator(nullptr, _root);
	}

	RBTree() = default;
	~RBTree()
	{
		Destory(_root);
		_root = nullptr;
	}
	void Destory(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		Destory(root->_left);
		Destory(root->_right);
		delete root;
	}

	pair<Iterator, bool>Insert(const T& data)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_data < data)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_data > data)
			{

				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(Iterator(cur, _root), false);
			}
		}

		Node* newnode = new Node(data);
		Node* cur = newnode;
		cur->_col = RED;
		if (parent->_data < data)
		{
			parent->_right = cur;
		}
		else if (parent->_data > data)
		{
			parent->_left = cur;
		}
		cur->_parent = parent;

		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			// g
			// p u
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					// u存在且为红 -》变⾊再继续往上处理
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					// u存在且为⿊或不存在 -》旋转+变⾊
					if (cur == parent->_left)
					{
						// g
						// p u
						//c
						//单旋
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						// g
						// p u
						// c
						//双旋
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
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
				else // 叔叔不存在，或者存在且为⿊
				{
					// 情况⼆：叔叔不存在或者存在且为⿊
					// 旋转+变⾊
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
		return make_pair(Iterator(newnode, _root), true);
	}
	Iterator Find(const K& key)
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
				return Iterator(cur, _root);
			}
		}
		return End();
	}
private:
	Node* _root = nullptr;
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		Node* parentParent = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;
		if (parentParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subR;
			}
			else
			{
				parentParent->_right = subR;
			}
			subR->_parent = parentParent;
		}
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		Node* parentParent = parent->_parent;
			subL->_right = parent;
		parent->_parent = subL;
		if (parentParent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent == parentParent->_left)
			{
				parentParent->_left = subL;
			}
			else
			{
				parentParent->_right = subL;
			}
			subL->_parent = parentParent;
		}
	}
};