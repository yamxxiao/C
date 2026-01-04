#include"HashTable.h"

//string s = "sdadfsfasfsaksafkasfasfskafsafkasffkf";
//int Test_1(string s)
//{
//	int count[26] = { 0 };
//	//统计次数
//	for (auto ch : s)
//	{
//		count[ch - 'a']++;
//	}
//	for (size_t i = 0; i < s.size(); ++i)
//	{
//		if (count[s[i] - 'a'] == 1)
//			return i;
//	}
//	return -1;
//}
int main()
{
	//直接地址法:
	/*当关键字的范围⽐较集中时，直接定址法就是⾮常简单⾼效的⽅法，⽐如⼀组关键字都在[0, 99]之间，
		那么我们开⼀个100个数的数组，每个关键字的值直接就是存储位置的下标。再⽐如⼀组关键字值都在
		[a, z]的⼩写字⺟，那么我们开⼀个26个数的数组，每个关键字acsii码 - a ascii码就是存储位置的下标。
		也就是说直接定址法本质就是⽤关键字计算出⼀个绝对位置或者相对位置。这个⽅法我们在计数排序
		部分已经⽤过了，其次在string章节的下⾯OJ也⽤过了*/
		
		// 每个字⺟的ascii码-'a'的ascii码作为下标映射到count数组，数组中存储出现的次数
	//int i = Test_1(s);

	//int arr[] = {19,12,56,123,4141,514124,13,53,543,554,22,123,533,551,1234,1112,5};
	//HashTable<int, int> hash;

	//for (auto e : arr)
	//{
	//	hash.Insert({ e,e });
	//}

	/*int a = 8;
	int b = 9;
	int result = a ^ b;
	cout << "a^b=" << result << endl;*/
	Hash_bucket::HashTable<int, int>hash;
	hash.Insert({ 1,1 });
	hash.Insert({ 2,2 });
	hash.Insert({ 13,3 });
	hash.Insert({ 411,4 });
	hash.Insert({ 543,7 });
	hash.Print();
	HashTable<int, int>hash1;
	hash1.Insert({ 123,1 });
	hash1.Insert({ 1223,5 });
	hash1.Insert({ 12313,7 });
	hash1.Insert({ 11123,9 });
	hash1.Insert({ 9,9 });

	hash1.Print();
	return 0;
}