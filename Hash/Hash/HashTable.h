#pragma once
#include<iostream>
#include<vector>


using namespace std;

//开放地址法

//使用枚举来表示储存位置的状态
enum State
{
	EXIST,
	EMPTY,
	DELETE
};

//因为是使用了枚举，所以一般的pair无法满足储存哈希表的值，所以需要重新写一个适合哈希表存储的pair
template<class K,class V>
struct HashData
{
	pair<K, V> _kv;
	State _state = EMPTY;//默认为空
};

template<class K,class V>
class HashTable
{
private:
	vector<HashData<K, V>> _tables;
	rsize_t _n;//表中存储的数据个数

public:
	HashTable():_tables(11),_n(0){}

	bool Insert(const pair<K, V>& kv)
	{
		//考虑扩容,负载因子（储存个数/空间大小）大于等于0.7就扩容
		if (_n * 10 / _tables.size() >= 7)
		{
			HashTable<K, V> newht;
			newht._tables.resize(_tables.size() * 2);

			for (auto& data : _tables)
			{
				//旧表数据映射
				if (data._state == EXIST)
				{
					newht.Insert(data._kv);
				}
			}

			_tables.swap(newht._tables);
		}

		size_t hash0 = kv.first % _tables.size();
		size_t hashi = hash0;
		size_t i = 1;

		while (_tables[hashi]._state == EXIST)
		{
			//线性探测
			hashi = (hash0 + i)%_tables.size();
			++i;
		}
		_tables[hashi]._kv = kv;
		_tables[hashi]._state = EXIST;
		++_n;
		return true;
	}

	HashData<K, V>* Find(const K& key)
	{
		if (_tables.empty())
		{
			return nullptr;
		}
		size_t hash0 = key % _tables.size();
		size_t hashi = hash0;
		size_t i = 0;

		while (_tables[hashi]._state != EMPTY)
		{
			if (_tables[hashi]._state == EXIST
				&& _tables[hashi]._kv.first == key)
			{
				return &_tables[hashi];
			}
				++i;
			//线性探测
			hashi = (hash0 + i) % _tables.size();
			
		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		HashData<K, V>* ret = Find(key);

		if (ret)
		{
			ret->_state == DELETE;
			return true;
		}
		else
		{
			return false;
		}
	}
};