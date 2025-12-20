#pragma once
#include"RBTree.h"

template <class T1, class T2>
bool operator< (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return lhs.first < rhs.first || (!(rhs.first < lhs.first) &&
		lhs.second < rhs.second);
}

template<class K,class V>
class map
{
	struct MayKeyOfT
	{
		const K& operator()(const pair<K, V>& kv) {
			return kv.first;
		}
	};
public:
	bool insert(const pair<K, V>& key)
	{
		return _t.Insert(key);
	}
private:
	RBTree<K, pair<K, V>,MayKeyOfT> _t;
};