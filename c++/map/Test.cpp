#include<iostream>
#include<assert.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	// 需要parent指针，后续更新平衡因⼦可以看到
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;//平衡因子

	AVLTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{}
};

template<class K, class V>
class AVLTree
{
public:
	typedef AVLTreeNode<K, V> Node;
	//插入，类似二叉搜索树
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
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
			else if(cur->_kv.first>kv.first)
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

		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else if (parent->_kv.first > kv.first)
		{
			parent->_left = cur;
		}
		cur->_parent = parent;
		//更新平衡因子
		//平衡因子的计算->右子树-左子树
		while (parent)
		{
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			if (parent->_bf == 0)
			{
				//更新结束
				break;
			}

			if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//不更新了，旋转处理
				break;
			}
			else
			{
				assert(false);
			}
		}
		return true;
	}
	//右旋转
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		//除了要修改孩子的指针之外，还要修改父亲的 
		if (subLR)
		{
			subLR->_parent = parent;.
		}
		Node* pParent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;
		

		//parent可能是整棵树的根，也可能是子树
		//如果是整棵树的根，就需要修改_root
		//如果是子树，指针要跟上一层的链接

		//不是子树
		if (pParent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else//是子树
		{
			if (parent == pParent->_left)
			{
				pParent->_left = subL;
			}
			else if (parent == pParent->_right)
			{
				pParent->_right = subL;
			}

			subL->_parent = pParent;
		}
		//更新平衡因子
		parent->_bf = subL->_bf = 0;
	}
	//左旋转
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

		parent->_bf = subR->_bf = 0;
	}
private:
	Node* _root = nullptr;
};