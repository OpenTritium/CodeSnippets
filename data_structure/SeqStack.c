#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned MAX_ELEMENT_QUANTITY = 128; // 128 个元素单位

typedef char *Elements;

typedef char ElementType;

typedef struct {
	Elements data;    // 栈空间开始的内存地址
	ElementType *top; // 顶端的栈元素指针
	unsigned char size;    // 栈元素数量
} sqStack, *pSqStack;

/**
 * @brief 创建栈对象
 *
 * @return 栈对象
 */
sqStack CreateStack(void) {
	const unsigned char STACK_SIZE = MAX_ELEMENT_QUANTITY * sizeof(ElementType);
	const Elements STACK_DATA = (Elements)malloc(STACK_SIZE);
	assert(STACK_DATA != NULL);
	sqStack stk = {STACK_DATA, STACK_DATA, 0};
	return stk;
}

/**
 * @brief 获取栈是否为空
 *
 * @param pStk 栈指针
 * @return true 栈为空
 * @return false 栈不为空
 */
bool IsNull(const pSqStack pStk) {
	return pStk->size == 0;
}

/**
 * @brief 重置一个栈
 *
 * @param pStk 栈指针
 */
void ResetStack(pSqStack pStk) {
	free(pStk->data);
	pStk->size = 0;
	pStk->data = NULL;
	pStk->top = pStk->data;
}

/**
 * @brief 将元素推入栈顶
 *
 * @param pStk
 * @param e 元素
 * @return true 入栈成功
 * @return false 入栈失败
 */
bool Push(pSqStack pStk, const ElementType e) {
	if (pStk->size == MAX_ELEMENT_QUANTITY) {
		printf("Stack was full");
		return false;
	}
	*(pStk->top) = e;
	pStk->size++;
	pStk->top++;
	return true;
}

/**
 * @brief 弹出栈顶元素
 *
 * @param pStk
 * @return true
 * @return false
 */
bool Pop(pSqStack pStk) {
	if (IsNull(pStk) == true) {
		printf("Stack was null");
		return false;
	}
	pStk->top--;
	pStk->size--;
	return true;
}

/**
 * @brief 获取栈顶元素
 *
 * @param pStk 栈指针
 * @return ElementType 栈元素
 */
ElementType GetTop(const pSqStack pStk) {
	return *(pStk->top - 1);
}

int main(void) {
	sqStack stk = CreateStack();
	if (Push(&stk, 'M'))
		printf("入栈成功\n");
	else
		printf("入栈失败\n");
	printf("栈顶元素：%c\n", GetTop(&stk));
	printf("元素个数为：%d\n", stk.size);
	if (Pop(&stk))
		printf("出栈成功\n");
	else
		printf("出栈失败\n");
	printf("栈状态为%s\n", (IsNull(&stk)) ? "空" : "不为空");
	if (Push(&stk, 'N'))
		printf("入栈成功\n");
	else
		printf("入栈失败\n");
	ResetStack(&stk);
	printf("释放堆内存\n");
}
