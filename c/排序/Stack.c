#include"Stack.h"

//初始化
void STInit(ST* st)
{
	st->arr = NULL;
	st->top = st->capacity = 0;
}

//销毁
void STDestroy(ST* st)
{
	free(st);
	st->arr = NULL;
	st->top = 0;
	st->capacity = 0;
}

//入栈
void STPush(ST* st, SLTDataType x)
{
	assert(st);

	int NewCapacity = st->capacity == 0 ? 4 : 2 * st->capacity;

	SLTDataType* tmp = (SLTDataType*)realloc(st->arr, NewCapacity * sizeof(SLTDataType));

	if (tmp == NULL)
	{
		printf("入栈失败！");
		exit(1);
	}
	st->arr = tmp;
	st->capacity = NewCapacity;


	st->arr[st->top] = x;
	st->top++;
}
//出栈
void STPop(ST* st)
{
	assert(st && st->top && st->top > 0);
	st->top--;
}
//判空
bool STEmpty(ST* st)
{
	assert(st);
	return st->top == 0;
}
//栈顶元素
SLTDataType* STTop(ST* st)
{
	assert(st && st->top > 0);

	return st->arr[st->top - 1];
}
//有效个数
int STSize(ST* st)
{
	return st->top;
}

//打印
void Print(ST* st)
{
	while (!STEmpty(st))
	{
		printf("%d ", STTop(st));
		STPop(st);
	}
}