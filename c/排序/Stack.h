#pragma once
#include"stdio.h"
#include"stdlib.h"
#include"stdbool.h"
#include"assert.h"
#include"string.h"

typedef int SLTDataType;
typedef struct Stack
{
	SLTDataType* arr;
	int top;
	int capacity;
}ST;

//初始化
void STInit(ST* st);

//销毁
void STDestroy(ST* st);

//入栈
void STPush(ST* st, SLTDataType x);

//出栈
void STPop(ST* st);

//判空
bool STEmpty(ST* st);

//栈顶
SLTDataType* STTop(ST* st);

//有效个数
int STSize(ST* st);

//打印
void Print(ST* st);
