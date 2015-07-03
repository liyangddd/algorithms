//单链表实现
#ifndef  TEST_LIST_H
#define TEST_LIST_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node {
	int element;
	Position next;
};

List MakeEmpty();
int IsEmpty(List L);
int IsLast(Position p, List L);
Position Find(int x, List L);
Position FindByRecursion(int x, List L, Position p);  //用递归方法查找
void DeleteByValue(int x, List L);
void DeleteLater(Position p);
Position FindPrevious(int, Position p);
void Insert(int x, List L, Position p);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position p);
void PrintList(List L);
void RPrintList1(List lst);             //逆向输出链表元素，使用自定义栈
void RPrintList2(List lst);             //逆向输出链表元素，使用标准库栈
void RPrintListByRecursion(List lst);  //递归逆向输出链表元素
int Retrive(Position p);
Position NextElement(Position p, List L);
List ReverList(List lst);                       //逆向输出所有元素
Position FindBackwardKthNode1(List lst, unsigned int k); //查找链表倒数第k个节点
Position FindBackwardKthNode2(List lst, unsigned int k); //查找链表倒数第k个节点
List MergerTwoList(List lsta, List lstb);
int InsertTohead(List lst, int value);  //在表头插入元素

#endif