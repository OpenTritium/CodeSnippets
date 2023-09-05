#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef u_int16_t ElementType;
typedef struct Node {
  ElementType element;
  struct Node *next;
} Node, *Link;

typedef struct {
  Node *head;
  Node *tail;
  size_t size;
} LinkList;

/**
 * @brief 正下标从 0 开始，负下标从 -1 开始
 *
 * @param ll
 * @param s_index
 * @return Node*
 */
Node *FindNode(const LinkList *ll, const signed s_index) {
  // 计算下标
  size_t index;
  if (s_index < 0) {
    index = ll->size + s_index + 1;
  } else {
    index = s_index;
  }
  // 单链表只能从头节点遍历
  Node *n = ll->head;
  for (int i = 0; i != index; ++i) {
    n = n->next;
  }
  return n;
}

/**
 * @brief 申请结点
 *
 * @param elem
 * @return Link
 */
Link AllocateNode(const ElementType elem) {
  Node *n = (Node *)malloc(sizeof(Node)); // 申请结点
  assert(n != NULL);
  // 初始化结点
  n->next = NULL;
  n->element = elem;
  return n;
}

/**
 * @brief 创建链表并初始化第一个结点
 *
 * @param elem
 * @return LinkList
 */
LinkList Init(const ElementType elem) {
  Node *head = AllocateNode(elem);
  LinkList ll = {head, head, 1};
  return ll;
}

/**
 * @brief 向后添加元素
 *
 * @param ll
 * @param elem
 */
void PushBack(LinkList *ll, const ElementType elem) {
  Node *new = AllocateNode(elem);
  ll->tail->next = new; // 将链表尾结点指向的结点改为新申请的结点
  ll->tail = new;       // 更新链表尾结点
  ll->size++;           // 更新链表长度
}

/**
 * @brief 向前添加元素
 *
 * @param ll
 * @param elem
 */
void PushFront(LinkList *ll, const ElementType elem) {
  Node *new = AllocateNode(elem);
  new->next = ll->head;
  ll->head = new;
  ll->size++;
}

/**
 * @brief 删除末尾结点
 *
 * @param ll
 */
void PopBack(LinkList *ll) {
  assert(ll->size != 1);
  Link l = ll->head->next;
  // 遍历到指向为指向尾结点的结点截止
  while (l->next != ll->tail) {
    l = l->next;
  }
  free(l->next);
  ll->tail = l;
  ll->tail->next = NULL; // 记得将已经释放的尾巴置空
  ll->size--;
}

/**
 * @brief 删除前置结点
 *
 * @param ll
 */
void PopFront(LinkList *ll) {
  assert(ll->size != 1);
  const Link l = ll->head->next;
  free(ll->head);
  ll->head = l;
  ll->size--;
}

/**
 * @brief 插入元素
 *
 * @param ll
 * @param index
 * @param elem
 */
void Insert(LinkList *ll, const signed index, const ElementType elem) {
  if ((index > 0 && index < ll->size) || (index < -1 && index > -ll->size)) {
    Link before = FindNode(ll, index - 1);
    Link after = before->next;
    before->next = AllocateNode(elem);
    before->next->next = after;
    ll->size++;
  } else if (index == 0 || index == -ll->size) {
    PushFront(ll, elem);
  } else if (index == ll->size || index == -1) {
    PushBack(ll, elem);
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
ElementType GetVal(const LinkList *ll, const signed index) {
  return FindNode(ll, index)->element;
}

/**
 * @brief 依据下标移除元素
 *
 * @param ll
 * @param index
 */
void Remove(LinkList *ll, const signed index) {
  if ((index > 0 && index < ll->size) || (index < -1 && index > -ll->size)) {
    Node *before = FindNode(ll, index - 1);
    Node *current = before->next;
    before->next = current->next;
    free(current);
    ll->size--;
  } else if (index == 0 || index == -ll->size) {
    PopFront(ll);
  } else if (index == ll->size || index == -1) {
    PopBack(ll);
  } else {
    exit(0);
  }
}

/**
 * @brief 清空链表，释放堆内存
 *
 * @param ll
 */
void Clear(LinkList *ll) {
  Link current = ll->head;
  while (current != NULL) {
    Link next = current->next; // 保存下个节点的指针
    free(current);             // 释放当前节点
    current = next;            // 更新当前节点为下个节点
  }
  ll->head = NULL;
  ll->tail = NULL;
  ll->size = 0;
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
  Clear(&ll);
  return 0;
}