#include"Stack.h"
//插入排序
void InsertSort(int* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int end = i;
		int temp = arr[end + 1];

		while (end >= 0)
		{
			if (temp < arr[end])
			{
				arr[end + 1] = arr[end];
			}
			else
			{
				break;
			}
			end--;
		}

		arr[end + 1] = temp;
	}
}
void PrintSort(int *arr,int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
//交换
void Swap(int *arr1,int *arr2)
{
	int temp = *arr1;
	*arr1 = *arr2;
	*arr2 = temp;
}

//堆排序
//向上调整法
void HeapAdjustUp(int* arr, int child)
{
	int parent = (child - 1) / 2;

	while (child > 0)
	{
		if (arr[child] < arr[parent])
		{
			Swap(&arr[child], &arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}

}

//向下调整法
void HeapAdjustDown(int* arr, int parent,int size)
{

	int child = parent * 2 + 1;

	while (child < size)
	{


		if (child + 1<size && arr[child] < arr[child + 1])
		{
			++child;
		}

		if (arr[child] > arr[parent])
		{
			Swap(&arr[child], &arr[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int *arr,int size)
{
	//建队->大堆，升序从最后一个非叶子节点向前遍历
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		HeapAdjustDown(arr, i, size);
	}

	//排序，每次将堆顶的元素和末尾元素进行交换，然后调整
	for (int i = size - 1; i > 0; i--)
	{
		Swap(&arr[0], &arr[i]);
		HeapAdjustDown(arr, 0, i);
	}
}

//创建一个间隔gap进行预排序，，这个值可以是3
// 每一次循环，更新一次间隔
// 然后对单层循环进行分组处理
// 在当层循环进行插入排序
// 
//希尔排序
//1.预排序
//2.插入排序
void ShellSort(int* arr, int size)
{
	int gap = size;
	
	while (gap > 1)
	{
		//更新间隔
		gap = gap / 3 + 1;

		//单层循环处理所用分组
		for (int i = 0; i < size; i++)
		{
			int temp = arr[i + gap];
		
			int end = i ;

			//在当前分组内进行插入排序

			while (end >= 0 && temp < arr[end])
			{
				arr[end + gap] = arr[end];
				end -= gap;
			}

			arr[end + gap] = temp;
		}
	}
}

//选择排序的思路是：利用双指针，left和right,两个指针，然后创建两个最大和最小的索引,
// 每次循环和索引进行比较,如果找到最小的值，或者最大的，就跟新最大和最小值索引的下标
// 当当次循环结束之后，将最大或者最下的值放在最右边或者最左边A
//选择排序:单向
void  SelectSort_dan(int* arr, int size)
{
	
	for (int i = 0; i < size - 1; i++)
	{
		int minIndex = i;//最小元素索引

		//在末排序中部分寻找最小元素
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[minIndex])
			{
				minIndex = j;
			}
			//将找到的最小元素进行交换
			if (minIndex != i)
			{
				Swap(&arr[i], &arr[minIndex]);
			}
		}

	}
}

//选择排序：双向
void SelectSort_shuang(int* arr, int size)
{
	int left = 0, right = size - 1;
	int maxIndex = right, minIndex = left;

	while (left < right)
	{

		//找到范围内最大最小的元素
		for (int i = left; i <= right; i++)
		{
			if (arr[i] < arr[minIndex])
			{
				minIndex = i;
			}
			if (arr[i] > arr[maxIndex])
			{
				maxIndex = i;
			}
		}

		//将最小元素放在最左边
		if (minIndex != left)
		{
			Swap(&arr[left], &arr[minIndex]);
		}
		// 如果最大元素在左边，需要更新maxIndex
		if (maxIndex == left)
		{
			maxIndex == minIndex;
		}

		//将最大的元素放在最右边
		if (maxIndex != right)
		{
			Swap(&arr[right], &arr[maxIndex]);
		}
		left++;
		right--;
	}
}
//简单实现快排
void _simpleQuickSort(int* arr, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	int keyi = left;
	int begin = left, end = right;

	//先进去单次循环，指定一个keyi值，让keyi值左边的都比它小，右边的都比它大，然后将keyi值放在中间位置作为分界线
	while (begin < end)
	{
		//这里进入条件循环，如果在左边找到了比keyi大的，右边找到了比keyi小的，则不进入循环，则是进行交换
		//右边找最小 
	// 先从右向左找第一个小于基准的元素
		while (begin < end && arr[end] >= arr[keyi])
		{
			end--;
		}

		// 再从左向右找第一个大于基准的元素
		while (begin < end && arr[begin] <= arr[keyi])
		{
			begin++;
		}

		Swap(&arr[begin], &arr[end]);
	}
	//跳出循环后，交换keyi值
	Swap(&arr[keyi], &arr[begin]);
	keyi = begin;

	//再进入递归，对分隔好的两个区间进行排序
	//分割的区间为[begin,keyi-1],key,[keyi+1,end]
	_simpleQuickSort(arr, left, keyi - 1);
	_simpleQuickSort(arr, keyi + 1, right);

}

////三数取中1
//int medianOfThree(int* arr, int left, int right)
//{
//	int mind = left + (right - left) / 2;
//	//确保arr[left]<arr[mind]<arr[right]
//	if (arr[left] > arr[mind])
//	{
//		Swap(&arr[left], &arr[mind]);
//	}
//	if (arr[left] > arr[right])
//	{
//		Swap(&arr[left], &arr[right]);
//	}
//	if (arr[mind] > arr[right])
//	{
//		Swap(&arr[mind], &arr[right]);
//	}
//
//	//将中值放入right-1的位置作为基准
//	Swap(&arr[mind], &arr[right - 1]);
//
//	return arr[right - 1];
//}

//三数取中2
int Getmind(int* arr, int left, int right)
{
	int mind = (left + right) / 2;//left+(right-left)/2

	if (arr[left] < arr[mind])
	{
		if (arr[left] > arr[right])
		{
			return left;
		}
		else if (arr[left] < arr[right])
		{
			return right;
		}
		else if(arr[right]<arr[mind])
		{
			return mind;
		}
	}
	else//arr[left]>arr[mind]
	{
		if (arr[left] < arr[right])
		{
			return left;
		}
		else if (arr[left] > arr[right])
		{
			return right;
		}
		else if(arr[right]>arr[mind])
		{
			return mind;
		}
	}
}
////分区函数
//int partition(int* arr, int left, int right)
//{
//	//使用三数取中法，选择基准
//	int pivot = medianOfThree(arr, left, right);
//
//	int i = left;
//	int j = right - 1;
//
//	while (1)
//	{
//		//从左边向右找大于等于基准的元素
//		while (arr[i++] < pivot);
//
//		//从右向左找等于小于基准的元素
//		while (arr[j--] > pivot);
//
//		if (i < j)
//		{
//			Swap(&arr[i], &arr[j]);
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	//将基准放到正确的位置
//	Swap(&arr[i], &arr[right - 1]);
//	return i;
//}
//快排
void QQQquickSort(int *arr,int left,int right)
{
	if (left >= right)
	{
		return;
	}
	int mind = Getmind(arr, left, right);
	Swap(&arr[left], &arr[mind]);
	int keyi = left;
	int begin = left, end = right;

	//小区间优化,用选择排序
	if (right - left + 1 < 10)
	{
		InsertSort(arr + left, right - left + 1);
	}
	//先进去单次循环，指定一个keyi值，让keyi值左边的都比它小，右边的都比它大，然后将keyi值放在中间位置作为分界线
	while (begin < end)
	{
		//这里进入条件循环，如果在左边找到了比keyi大的，右边找到了比keyi小的，则不进入循环，则是进行交换
		//右边找最小 
	// 先从右向左找第一个小于基准的元素
		while (begin < end && arr[end] >= arr[keyi])
		{
			end--;
		}

		// 再从左向右找第一个大于基准的元素
		while (begin < end && arr[begin] <= arr[keyi])
		{
			begin++;
		}

		Swap(&arr[begin], &arr[end]);
	}
	//跳出循环后，交换keyi值
	Swap(&arr[keyi], &arr[begin]);
	keyi = begin;

	//再进入递归，对分隔好的两个区间进行排序
	//分割的区间为[begin,keyi-1],key,[keyi+1,end]
	QQQquickSort(arr, left, keyi - 1);
	QQQquickSort(arr, keyi + 1, right);


	//if (left < right)
	//{
	//	//当子数组的长度大于3时使用快排
	//	if (right - left > 3)
	//	{
	//		int pi = partition(arr, left, right);
	//		QQQquickSort(arr, left, pi - 1);
	//		QQQquickSort(arr, pi + 1, right);
	//	}
	//	else
	//	{
	//		//对于小于数组，使用插入排序

	//		if (right - left == 1)
	//		{
	//			if (arr[left] > arr[right])
	//			{
	//				Swap(&arr[left], &arr[right]);
	//			}
	//		}
	//		else if (right - left == 2)
	//		{
	//			if (arr[left] > arr[left + 1])
	//			{
	//				Swap(&arr[left], &arr[left + 1]);
	//			}

	//			if (arr[left + 1] > arr[right])
	//			{
	//				Swap(&arr[left + 1], &arr[right]);
	//			}

	//			if (arr[left] > arr[left + 1])
	//			{
	//				Swap(&arr[left], &arr[left + 1]);
	//			}
	//		}
	//	}
	//}
}

//前后指针
int quickSort2(int* arr, int left, int right)
{
	//三数取中
	int Getmind = medianOfThree(arr, left, right);
	Swap(&arr[left], &arr[Getmind]);
	int keyi = left;
	int perv = keyi;
	int cur = perv + 1;

	while (cur <= right)
	{
		if (arr[cur] < arr[keyi]&&++perv!=cur)
		{
			Swap(&arr[perv], &arr[cur]);
		}
		cur++;
	}
	Swap(&arr[perv], &arr[keyi]);
	return perv;
}

//快排非递归，使用栈实现
//void quickSortNoneR(int* arr,int left,int right)
//{
//	ST st;
//	STInit(&st);
//	STPush(&st, left);
//	STPush(&st, right);
//	
//	while (!STEmpty(&st))
//	{
//		int begin = top(&st);
//		STPop(&st);
//		int end = top(&st);
//		STPop(&st);
//
//		int keyi = partition(arr, left, right);
//
//		//分区间调整
//		if (keyi + 1 < end)
//		{
//			STPush(&st, keyi + 1);
//			STPush(&st, end);
//		}
//
//		if (begin < keyi - 1)
//		{
//			STPush(&st, begin);
//			STPush(&st, keyi - 1);
//		}
//	}
//}


//归并排序辅助函数
void _mergeSort(int *arr,int *temp,int begin,int end)
{
	if (begin >= end)
	{
		return;
	}
	//先找中间值
	int mind = (begin + end) / 2;

	_mergeSort(arr, temp, begin, mind);
	_mergeSort(arr, temp, mind + 1, end);
	//此时通过递归，两边区间的顺序已经排好了
	
	//归并
	int begin1 = begin, end1 = mind;
	int begin2 = mind + 1, end2 = end;
	int i = begin;//用于temp的下标

	while (begin1 <= end1&& begin2 <= end2)
	{
		if (arr[begin1] < arr[begin2])
		{
			temp[i++] = arr[begin1++];
		}
		else
		{
			temp[i++] = arr[begin2++];
		}
	}

	while (begin1 <= end1)
	{
		temp[i++] = arr[begin1++];
	}

	while (begin2 <= end2)
	{
		temp[i++] = arr[begin2++];
	}

	memcpy(arr+begin, temp+begin , (end - begin + 1) * sizeof(int));
}
//归并排序
void mergeSort(int* arr, int n)
{
	int* temp = (int*)malloc(sizeof(int) * n);
	if (temp == NULL)
	{
		printf("fail!");
		return;
	}

	_mergeSort(arr, temp, 0, n - 1);
	free(temp);
	temp = NULL;
}
//非递归实现归并排序

void _mergeSortN(int* arr, int* temp, int begin, int end)
{
	int size = sizeof(arr) / sizeof(arr[0]);
	int gap = 1;

	while (gap < size)
	{
		for (int i = 0; i < size; i += 2 * gap)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;

			while (begin1 <= end1 && begin2 <= end2)
			{
				int cut = i;
				//考虑越界问题
				if (begin2 >= size)
				{
					break;
				}

				//begin2没有越界，但是end2越界了
				if (end2 >= size)
				{
					end2 = size - 1;
				}

				if (arr[begin1] < arr[begin2])
				{
					temp[cut++] = arr[begin1++];
				}
				else
				{
					temp[cut++] = arr[begin2++];
				}

				if (begin1 <= end1)
				{
					temp[cut++] = arr[begin1++];
				}

				if (begin2 <= end2)
				{
					temp[cut++] = arr[begin2++];
				}
			}
			memcopy(arr + i, sizeof(int) * (end2 - i + 1));
		}
		gap = 2 * gap;
	}
}

void mergeSortN(int* arr, int n)
{
	int* temp = (int*)malloc(sizeof(int) * n);
	if (temp == NULL)
	{
		printf("fail!");
		return;
	}
	_mergeSortN(arr, temp, 0, n - 1);
	free(temp);
	temp = NULL;
}

int main()
{

	int arr[] = { 2,1,3,5,4,6,9,7,10,8 };
	int n = sizeof(arr) / sizeof(arr[0]);
	/*InsertSort(arr, n);
	/*Print(arr,n);*/
	/*HeapSort(arr, n);
	/*Print(arr, n);*/
	/*ShellSort(arr, n);
	//Print(arr, n);*/
	/*SelectSort_shuang(arr, n);*/
	/*QQQquickSort(arr, 0,n - 1);
	/*PrintSort(arr, n);*/
	/*_simpleQuickSort(arr, 0, n - 1);*/
	/*InsertSort(arr,n);*/
	mergeSort(arr, n);
	PrintSort(arr,n);

	return 0;
}