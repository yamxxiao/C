#pragma once
#include"RBTree.h"
template<class K>
class set
{
	struct setKeyOfT
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};
public:
	bool insert(const K& key)
	{
		return _t.Insert(key);
	}
private:
	RBTree<K, K, setKeyOfT> _t;
};
