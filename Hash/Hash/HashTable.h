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

template<class K,class V,class Hash=HashFunc<K>>
class HashTable
{
private:
	vector<HashData<K, V>> _tables;
	rsize_t _n;//表中存储的数据个数

public:
	HashTable():_tables(11),_n(0){}

	bool Insert(const pair<K, V>& kv)
	{
		if (Find(kv.first))
		{
			return false;
		}
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
		Hash hash;
		size_t hash0 = hash(kv.first) % _tables.size();
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
	void Print();
};
template<class K,class V,class Hash>
void HashTable<K,V,Hash>::Print()
{
    for (size_t i = 0; i < _tables.size(); ++i)
    {
        if (_tables[i]._state == EXIST)
        {
            cout << "[" << _tables[i]._kv.first << ", " << _tables[i]._kv.second << "] ";
        }
    }
    cout << endl;
}
//key不能取模的问题
//当key是string / Date等类型时，key不能取模，那么我们需要给HashTable增加⼀个仿函数，这个仿函
//数⽀持把key转换成⼀个可以取模的整形，如果key可以转换为整形并且不容易冲突，那么这个仿函数
//就⽤默认参数即可，如果这个Key不能转换为整形，我们就需要⾃⼰实现⼀个仿函数传给这个参数，实
//现这个仿函数的要求就是尽量key的每值都参与到计算中，让不同的key转换出的整形值不同。string
//做哈希表的key⾮常常⻅，所以我们可以考虑把string特化⼀下

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

//特化
template<>
struct HashFunc<string>
{
	// 字符串转换成整形，可以把字符ascii码相加即可
	 // 但是直接相加的话，类似"abcd"和"bcad"这样的字符串计算出是相同的
		 // 这⾥我们使⽤BKDR哈希的思路，⽤上次的计算结果去乘以⼀个质数，这个质数⼀般去31, 131
		//等效果会⽐较好

	size_t operator()(const string& key)
	{
		size_t hash = 0;
		for (auto e : key)
		{
			hash *= 131;
			hash += e;
		}
		return hash;
	}
};
//解决冲突的思路
//开放定址法中所有的元素都放到哈希表⾥，链地址法中所有的数据不再直接存储在哈希表中，哈希表
//中存储⼀个指针，没有数据映射这个位置时，这个指针为空，有多个数据映射到这个位置时，我们把
//这些冲突的数据链接成⼀个链表，挂在哈希表这个位置下⾯，链地址法也叫做拉链法或者哈希桶。
//链地址法
namespace Hash_bucket
{
	template<class K,class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		HashNode(const pair<K,V>&kv):_kv(kv),_next(nullptr){}

	};

	template<class K,class V,class Hash=HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;

		inline unsigned long __stl_next_prime(unsigned long n)
		{
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
			53, 97, 193, 389, 769,
			1543, 3079, 6151, 12289, 24593,
			49157, 98317, 196613, 393241, 786433,
			1572869, 3145739, 6291469, 12582917, 25165843,
			50331653, 100663319, 201326611, 402653189, 805306457,
			1610612741, 3221225473, 4294967291
			};
			const unsigned long* first = __stl_prime_list;
			const unsigned long* last = __stl_prime_list +
				__stl_num_primes;
			const unsigned long* pos = lower_bound(first, last, n);
			return pos == last ? *(last - 1) : *pos;
		}

	public:
		HashTable():_tables(__stl_next_prime(0)),_n(0){}

		bool Insert(const pair<K, V>& kv)
		{
			Hash hs;
			size_t hashi = hs(kv.first) % _tables.size();
			// 负载因子==1 扩容
			if (_n == _tables.size())
			{
				vector<Node*> newtables(__stl_next_prime(_tables.size() + 1), nullptr);
				for (size_t i = 0; i < _tables.size(); i++)//遍历旧表
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						//旧表中的节点，挪动新表重新映射的位置
						size_t hashi = hs(cur->_kv.first) % newtables.size();
						//从头插到新表
						cur->_next = newtables[hashi];
						newtables[hashi] = cur;

						cur = next;
					}
					_tables[i] = nullptr;//让旧表被挪动的位置的指针为空
				}
				_tables.swap(newtables);
			}
			//头插
			Node* newnode = new Node(kv);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;
			return true;
		}
		void Print();

		Node* Find(const K& key)
		{
			Hash hs;
			size_t hashi = hs(key) & _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}

		bool Erse(const K& key)
		{
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			Node* prev = nullptr;
			while (cur)
			{
				//判断一下cur所处的位置
				
				if (cur->_kv.first == key)
				{//头部
					if (prev == nullptr)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						//中间
						prev->_next = cur->_next;
					}

					delete cur;
					--_n;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}
		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}
	private:
		vector<Node*> _tables;//指针数组
		size_t _n = 0;
		//记录表中的储存数据
	};
	template<class K, class V, class Hash>
	void HashTable<K, V, Hash>::Print()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			Node* cur = _tables[i];
			cout << "Bucket[" << i << "]: ";
			while (cur)
			{
				cout << "[" << cur->_kv.first << ", " << cur->_kv.second << "] -> ";
				cur = cur->_next;
			}
			cout << "nullptr" << endl;
		}
	}
}
