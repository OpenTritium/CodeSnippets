#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned ElementType;

typedef struct Node {
	ElementType element;
	struct Node* next;
} Node, * Link;

typedef struct {
	Node* head;
	Node* tail;
	size_t size;
} LinkList;

/**
 * @brief 正下标从 0 开始，负下标从 -1 开始
 *
 * @param ll
 * @param s_index
 * @return Node*
 */
Node* FindNode(const LinkList* pll, const signed s_index) {
	// 计算下标
	size_t index;
	if (s_index < 0) {
		index = pll->size + s_index + 1;
	} else {
		index = s_index;
	}
	// 单链表只能从头节点遍历
	Node* pn = pll->head;
	for (signed i = 0; i != index; ++i) {
		pn = pn->next;
	}
	return pn;
}

/**
 * @brief 申请结点
 *
 * @param elem
 * @return Link
 */
Link AllocateNode(const ElementType elem) {
	Node* pn = (Node*)malloc(sizeof(Node)); // 申请结点
	assert(pn != NULL);
	// 初始化结点
	pn->next = NULL;
	pn->element = elem;
	return pn;
}

/**
 * @brief 创建链表并初始化第一个结点
 *
 * @param elem
 * @return LinkList
 */
LinkList Init(const ElementType elem) {
	Node* phead = AllocateNode(elem);
	LinkList pll = { phead, phead, 1 };
	return pll;
}

/**
 * @brief 向后添加元素
 *
 * @param ll
 * @param elem
 */
void PushBack(LinkList* pll, const ElementType elem) {
	Node* pnew = AllocateNode(elem);
	pll->tail->next = pnew; // 将链表尾结点指向的结点改为新申请的结点
	pll->tail = pnew;       // 更新链表尾结点
	pll->size++;           // 更新链表长度
}

/**
 * @brief 向前添加元素
 *
 * @param ll
 * @param elem
 */
void PushFront(LinkList* pll, const ElementType elem) {
	Node* pnew = AllocateNode(elem);
	pnew->next = pll->head;
	pll->head = pnew;
	pll->size++;
}

/**
 * @brief 删除末尾结点
 *
 * @param ll
 */
void PopBack(LinkList* pll) {
	assert(pll->size != 1);
	Link l = pll->head->next;
	// 遍历到指向为指向尾结点的结点截止
	while (l->next != pll->tail) {
		l = l->next;
	}
	free(l->next);
	pll->tail = l;
	pll->tail->next = NULL; // 记得将已经释放的尾巴置空
	pll->size--;
}

/**
 * @brief 删除前置结点
 *
 * @param ll
 */
void PopFront(LinkList* pll) {
	assert(pll->size != 1);
	const Link l = pll->head->next;
	free(pll->head);
	pll->head = l;
	pll->size--;
}

/**
 * @brief 插入元素
 *
 * @param ll
 * @param index
 * @param elem
 */
void Insert(LinkList* pll, const signed index, const ElementType elem) {
	if ((index > 0 && index < pll->size) || (index < -1 && index > -1 * (pll->size))) {
		Link before = FindNode(pll, index - 1);
		Link after = before->next;
		before->next = AllocateNode(elem);
		before->next->next = after;
		pll->size++;
	} else if (index == 0 || index == -1 * (pll->size)) {
		PushFront(pll, elem);
	} else if (index == pll->size || index == -1) {
		PushBack(pll, elem);
	} else {
		exit(0);
	}
}

/**
 * @brief 获取结点包含的元素
 *
 * @param ll
 * @param index
 * @return ElementType
 */
ElementType GetVal(const LinkList* pll, const signed index) {
	return FindNode(pll, index)->element;
}

/**
 * @brief 反转链表
 *
 * @param ll
 */
void Inverse(LinkList* pll) {
	pll->tail = pll->head;
	Node* pcurrentNode = pll->head;
	Node* pprevNode = NULL;
	Node* pnextNode = NULL;
	while (pcurrentNode != NULL) {
		pnextNode = pcurrentNode->next;  // 保存下个结点
		pcurrentNode->next = pprevNode;  // 反转
		pprevNode = pcurrentNode;
		pcurrentNode = pnextNode;
	}
	pll->head = pprevNode;
}

/**
 * @brief 依据下标移除元素
 *
 * @param ll
 * @param index
 */
void Remove(LinkList* pll, const signed index) {
	if ((index > 0 && index < pll->size) || (index < -1 && index > -1 * (pll->size))) {
		Node* pbefore = FindNode(pll, index - 1);
		Node* pcurrent = pbefore->next;
		pbefore->next = pcurrent->next;
		free(pcurrent);
		pll->size--;
	} else if (index == 0 || index == -1 * (pll->size)) {
		PopFront(pll);
	} else if (index == pll->size || index == -1) {
		PopBack(pll);
	} else {
		exit(0);
	}
}

/**
 * @brief 清空链表，释放堆内存
 *
 * @param ll
 */
void Clear(LinkList* pll) {
	Link current = pll->head;
	while (current != NULL) {
		Link next = current->next; // 保存下个节点的指针
		free(current);             // 释放当前节点
		current = next;            // 更新当前节点为下个节点
	}
	pll->head = NULL;
	pll->tail = NULL;
	pll->size = 0;
}

int main(void) {
	LinkList ll = Init(5);
	PushFront(&ll, 4);
	PushFront(&ll, 1);
	PushFront(&ll, 1);
	PushBack(&ll, 1);
	PushBack(&ll, 4);
	for (size_t i = 0; i != ll.size; ++i) {
		printf("%d", GetVal(&ll, i));
	}
	printf("\n");
	PopBack(&ll);
	PopFront(&ll);
	Insert(&ll, -1, 9);
	Insert(&ll, -2, 8);
	Insert(&ll, 0, 22);
	for (size_t i = 0; i != ll.size; ++i) {
		printf("%d", GetVal(&ll, i));
	}
	printf("\n");
	Remove(&ll, 2);
	PopBack(&ll);
	PopFront(&ll);
	for (size_t i = 0; i != ll.size; ++i) {
		printf("%d", GetVal(&ll, i));
	}
	Inverse(&ll);
	printf("\n");
	for (size_t i = 0; i != ll.size; ++i) {
		printf("%d", GetVal(&ll, i));
	}
	Clear(&ll);
	return 0;
}
