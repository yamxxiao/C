#pragma once
#include<iostream>

using namespace std;

enum Colour
{
	RED,
	BLACK
};
template<class T>
struct RBTreeNode
{
	T _data;
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Colour _col;
	RBTreeNode(const T& data)
		: _data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
	{
}
};
// 实现步骤：
// 1、实现红⿊树
// 2、封装map和set框架，解决KeyOfT
		// 3、iterator
		// 4、const_iterator
		// 5、key不⽀持修改的问题
		// 6、operator[]

template<class K,class T,class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T, T&, T*>Iterator;
	typedef RBTreeIterator<T, const T&, const T*>ConstIterator;

	Iterator begin()
	{
		Node* leftMost = _root;
		while (leftMost && leftMost->_left)
		{
			leftMost = leftMost->_left;
		}
		return Iterator(leftMost, _root);
	}

	Iterator end()
	{
		return Iterator(nullptr, _root);
	}

	ConstIterator Begin()const
	{
		Node* leftMost = _root;
		while (leftMost && leftMost->_left)
		{
			leftMost = leftMost->_left;
		}
		return ConstIterator(leftMost, _root);
	}

	ConstIterator End()const
	{
		return ConstIterator(nullptr, _root);
	}
	RBTree() = default;

	~RBTree()
	{
		Destroy(_root);
		_root = nullptr;
	}

	void Destroy(Node* root)
	{
		if (_root == nullptr)
		{
			return nullptr;
		}

		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}
	pair<Iterator, bool>Insert(T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return std::make_pair(Iterator(_root, _root), true);
		}
		KeyOfT kot;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kot(cur->_data) < kot(data))
			{
				parent = cur;
				cur = cur->_right;
			}

			else if (kot(cur->_data) > kot(data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return std::make_pair(Iterator(cur, _root), false);
			}
		}

		cur = new Node(data);
		Node* newnode = cur;
		// 新增结点。颜⾊红⾊给红⾊
		cur->_col = RED;
		if (kot(parent->_data) < kot(data))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;
		//对颜色进行讨论
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			//g
			//p   u

			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle&& uncle->_col = RED)
				{
					//u存在，且u的颜色为红色->变色处理，往上变色
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;

					parent = cur->_parent;
				}
				else//uncle为黑色或者uncle不存在->旋转＋变色
				{
					if (cur == parent->_left)
					{
						//g
						//p   u
						//c
						//单旋
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//g
						//p  u
						///c

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
				Node* uncle = grandfather->_left;
				//判断uncle,先变颜色
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					//向上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle为黑色，或者不存在，旋转＋变色处理
				{
					if (cur == parent->_right)
					{
						//g
						//u  p
							//c
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//g
						// u  p
							//c
						//双旋转
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}

			}
		}

	}

	//bool Insert(const T* data)
	//{
	//	if (_root == nullptr)
	//	{
	//		_root = new Node(data);
	//		_root->_col = BLACK;
	//		return true;
	//	}
	//	KeyOfT kot;
	//	Node* cur = _root;
	//	Node* parent = nullptr;

	//	while (cur)
	//	{
	//		if (kot(cur->_data) <kot(data))
	//		{
	//			parent = cur;
	//			cur = cur->_right;
	//		}
	//		else if (kot(cur->_data) > kot(data))
	//		{
	//			parent = cur;
	//			cur = cur->_left;
	//		}
	//		else
	//		{
	//			return false;
	//		}

	//		cur = new Node(data);
	//		Node* newnode = cur;
	//		//新增节点，颜色给红色

	//		newnode->_col = RED;

	//		if (kot(parent->_data) < kot(data))
	//		{
	//			parent->_right = cur;
	//		}
	//		else
	//		{
	//			parent->_left = cur;
	//		}
	//		cur->_parent = parent;

	//		return true;
	//	}

	//}

private:
	Node* _root = nullptr;
	
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

		if (pParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (pParent->_left = parent)
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
			if (pParent->_left = parent)
			{
				pParent->_left = subL;
			}
			else
			{
				pParent->_right = subL;
			}

			subL->_parent = pParent;
		}
	}
};

//支持iterator的实现
template<class T,class Ref,class Ptr>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T, Ref, Ptr> Self;

	Node* _node;
	Node* _root;

	RBTreeIterator(Node* node,Node* root):_node(node),_root(root){}

	Self& operator++()
	{
		if (_node->_right)
		{
			//右不为空，右子树最左节点就是中序第一个
			Node* leftMost = _node->_right;

			while (leftMost->_left)
			{
				leftMost = leftMost->_left;
			}

			_node = leftMost;
		}
		else
		{
			//孩子是父亲左的那个祖先
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
		if (_node == nullptr)//end()
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
			//左子树不为空，中序左子树最后一个
			Node* rightMost = _node->_right;
			while (rightMost->_right)
			{
				rightMost = rightMost->_right;
			}
			_node = rightMost;
		}
		else
		{
			//孩子是父亲最右的那个祖先
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

	bool operator!=(const Self& s)const
	{
		return _node->_data!=_node->_data
	}

	bool operator==(const Self& s)const
	{
		return _node->_data == _node->_data;
	}
};
