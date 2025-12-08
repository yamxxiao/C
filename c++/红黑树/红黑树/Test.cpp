#include"RBTree.h"

int main()
{
	RBTree<int, int>tree;
	int a[] = { 1,6,10 };
	for (auto e : a)
	{
		tree.Insert({ e,e });
	}
	tree.InOrder();
	return 0;
}