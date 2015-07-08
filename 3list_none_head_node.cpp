//无头结点单链表的各类操作

#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;

struct LinkList {
	int value;
	LinkList *next;
};

//根据输入建立单链表：链表头部插入
LinkList *BuildList() {
	LinkList *head = NULL;
	int data;
	int i = 0;
	while (scanf("%d", &data) != EOF) {
		//scanf("%d", &data);++i;
		LinkList *new_node = (LinkList *)malloc(sizeof(LinkList));
		if (NULL == new_node) {
			fprintf(stderr, "malloc failed");
			return head;
		}
		new_node->value = data;
		if (head == NULL) {
			new_node->next = NULL;
			head = new_node;
		}
		else {
			new_node->next = head;
			head = new_node;
		}
	}
	return head;
}

//在链表头部插入节点
LinkList *InsertToHead(int value, LinkList *head) {
	LinkList *new_node = (LinkList *)malloc(sizeof(LinkList));
	if (new_node == NULL) {
		fprintf(stderr, "malloc failed");
		return head;
	}
	new_node->value = value;
	new_node->next = NULL;
	if (head == NULL) {
		head = new_node;
	}
	else {
		new_node->next = head;
		head = new_node;
	}
	return head;
}

//链表尾部插入节点
LinkList *InsertToTail(int value, LinkList *head) {
	LinkList *new_node = (LinkList *)malloc(sizeof(LinkList));
	if (new_node == NULL) {
		fprintf(stderr, "malloc failed");
		return head;
	}
	new_node->value = value;
	new_node->next = NULL;

	if (head == NULL)
		head = new_node;
	else {
		LinkList *pnode = head;
		while (pnode->next != NULL)
			pnode = pnode->next;
		pnode->next = new_node;
	}
	return head;
}

//删除某节点
LinkList *DeletebyValue(int value, LinkList* head) {
	if (head == NULL)
		return head;
	LinkList *pToDelete = NULL;
	if (head->value == value) {
		pToDelete = head;
		head = head->next;
	}
	else {
		LinkList *p = head;
		while (p->next != NULL && p->next->value != value)
			p = p->next;
		if (p->next != NULL) {
			pToDelete = p->next;
			p->next = pToDelete->next;
		}
	}
	if (pToDelete != NULL) {
		free(pToDelete);
		pToDelete = NULL;
	}
	return head;
}

unsigned int Length(LinkList *head) {
	unsigned int length = 0;
	LinkList *p = head;
	while (p) {
		++length;
		p = p->next;
	}
	return length;
}

//打印单链表
void PrintList(LinkList *head) {
	LinkList *p = head;
	while (p) {
		printf("%d ", p->value);
		p = p->next;
	}
	printf("\n");
}

//逆序打印单链表：非递归
void RPrintList(LinkList* head) {
	if (NULL == head)
		return;
	stack<int> list_stack;
	while (head) {
		list_stack.push(head->value);
		head = head->next;
	}
	while (!list_stack.empty()) {
		printf("%d ", list_stack.top());
		list_stack.pop();
	}
	printf("\n");
}
//逆序打印单链表：递归
void RPrintListRecursively(LinkList* head) {
	if (NULL == head)
		return;
	else {
		RPrintListRecursively(head->next);
		printf("%d ", head->value);
	}
}
//冒泡排序单链表
LinkList* Sort(LinkList *head) {
	if (NULL == head)
		return head;
	int length = Length(head);
	int unorder_size = length;
	int flag = 1;
	while (flag) {
		flag = 0;
		LinkList *p = head;
		for (int i = 0; p->next && i < unorder_size; ++i) {
			if (p->value > p->next->value) {
				int temp = p->value;
				p->value = p->next->value;
				p->next->value = temp;
				flag = 1;
			}
			p = p->next;
		} 
		--unorder_size;
	}
	return head;
}

//翻转单链表
LinkList* ReverseList(LinkList *head) {
	//其实这里if判断当链表节点个数小于两个的情况
	//不是必须的，因为之后的程序包含这里的判断
	if (NULL == head || NULL == head->next){
		return head;
	}
	LinkList *reverse_head = NULL;  //翻转后链表的头指针
	LinkList *pcurrent = head;      //pcurrent遍历链表
	while (pcurrent) {
		LinkList* temp = pcurrent;
		pcurrent = pcurrent->next;
		temp->next = reverse_head;
		reverse_head = temp;
	}
	return reverse_head;
}

//找出链表倒数第k个节点（k > 0)
LinkList * GetRKthNode(LinkList *head, int k) {
	if (k < 1 || NULL == head)
		return NULL;
	LinkList *first = head;
	LinkList *second = head;

	//如果节点个数小于k返回NULL
	for (int i = 1; i < k; ++i) {
		if (second->next)
			second = second->next;
		else
			return NULL;
	}

	//两个指针同时移动，直到快的second指针走到最后一个节点，
	//此时慢的first指针指向的就是倒数第k个节点
	while (second->next != NULL) { 
		first = first->next;
		second = second->next;
	}
	return first;
}

//返回单链表的中间节点，当链表节点个数为偶数时
//该函数返回链表第n/2 + 1个节点
LinkList *GetMiddleNode (LinkList* head) {
	//链表为空或者仅有一个节点
	if (NULL == head || NULL == head->next)
		return head;

	LinkList *first = head;
	LinkList *second = head;
	while (second->next) {
		first = first->next;
		second = second->next;
		if (second->next) {  //当节点个数为偶数时情况比较特殊
			second = second->next;
		}
	}
	return first;
}

//合并两个有序的单链表：非递归
//链表原来相等的元素都保留
LinkList* MergeList(LinkList* heada, LinkList *headb) {
	if (NULL == heada)
		return headb;
	if (NULL == headb)
		return heada;

	LinkList *head_merge = NULL;

	//比较第一个节点大小，取小者作为合并后第一个节点
	if (heada->value <= headb->value) {
		head_merge = heada;
		//注意下面两条语句顺序不能换，否则heada将指向空
		heada = heada->next;
	}
	else {
		head_merge = headb;
		//注意下面两条语句顺序不能换，否则headb将指向空
		headb = headb->next;
		//head_merge->next = NULL;
	}
	head_merge->next = NULL;

	LinkList *pmerge = head_merge;
	while(heada != NULL && headb != NULL) {
		if (heada->value <= headb->value) {
			pmerge->next = heada;
			heada = heada->next;
			pmerge = pmerge->next;
			
		}
		else {
			pmerge->next = headb;
			headb = headb->next;
			pmerge = pmerge->next;
		}
		pmerge->next = NULL;
	}
	if (heada)
		pmerge->next = heada;
	else if (headb)
		pmerge->next = headb;

	return head_merge;
}

//合并两个有序的单链表：递归
//链表原来相等的元素都保留
LinkList* MergeListRecursively(LinkList *heada, LinkList *headb) {
	if (NULL == heada)
		return headb;
	if (NULL == headb)
		return heada;
	
	LinkList *head_merge = NULL;
	if (heada->value <= headb->value) {
		head_merge = heada;
		head_merge->next = MergeListRecursively(heada->next, headb);
	}
	else {
		head_merge = headb;
		head_merge->next = MergeListRecursively(heada, headb->next);
	}
	return head_merge;
}

//判断链表中是否有环
bool HasCircle(LinkList *head) {
	if (NULL == head)
		return false;
	LinkList *first = head;
	LinkList *second = head;
	while (first && second->next) {
		second = second->next->next;
		first = first->next;
		if (first == second)
			return true;
	}
	return false;
}

//判断两个链表是否相交
bool IsCross(LinkList* heada, LinkList *headb) {
	if (NULL == heada || NULL == headb)
		return false;
	LinkList* taila = heada;
	LinkList* tailb = headb;
	while (taila->next)
		taila = taila->next;
	while (tailb->next)
		tailb = tailb->next;
	return taila == tailb;
}

//找出两个链表相交的第一个节点
LinkList* GetFirstCrossNode(LinkList* heada, LinkList* headb) {
	if (NULL == heada || NULL == headb)
		return NULL;

	int lengtha = 1;
	LinkList* taila = heada;
	while (taila->next) {
		++lengtha;
		taila = taila->next;
	}

	int lengthb = 1;
	LinkList* tailb = headb;
	while (tailb->next) {
		++lengthb;
		tailb = tailb->next;
	}

	//两个链表没有相交
	if (taila != tailb)
		return NULL;

	LinkList* plong = heada; //指向长度大的链表
	LinkList* pshort = headb;//指向长度小的链表
	int diff;
	if (lengthb > lengtha) {
		diff = lengthb - lengtha;
		plong = headb;
		pshort = heada;
	}

	//长链表先向前走，使得两个链表对齐
	for (int i = 0; i < diff; ++i)
		plong = plong->next;

	while (plong && pshort && plong != pshort) {
		plong = plong->next;
		pshort = pshort->next;
	}
	return plong;
}

//已知链表存在环，求进入链表的第一个节点
LinkList* GetFirstCircleNode(LinkList* head) {
	if (NULL == head)
		return NULL;

	//判断两个链表是否有环，没环返回空
	LinkList *first = head;
	LinkList *second = head;
	while (first && second->next) {
		first = first->next;
		second = second->next->next;
		if (first == second)
			break;
	}
	if (NULL == first || NULL == second->next)
		return NULL;

	//将相遇时环中的这个节点作为假设的尾节点，
	//就将原链表变为两个相交的单链表，第一个公共结点即为所求
	LinkList* assumed_tail = first;
	LinkList* head1 = head;
	LinkList* head2 = assumed_tail->next;

	LinkList *pa = head1;
	int length1 = 1;
	while (pa != assumed_tail) {
		pa = pa->next;
		++length1;
	}

	LinkList* pb = head2;
	int length2 = 1;
	while (pb != assumed_tail) {
		pb = pb->next;
		++length2;
	}
	pa = head1;
	pb = head2;
	if (length1 > length2) {
		int diff = length1 - length2;
		while (diff--)
			pa = pa->next;
	}
	else {
		int diff = length2 - length1;
		while (diff--)
			pb = pb->next;
	}
	while (pa != pb) {
		pa = pa->next;
		pb = pb->next;
	}
	return pa;
}

//删除某个指针指向的结点，时间复杂度O(1)
void DeleteTheNode(LinkList *head, LinkList *to_delete) {
	if (NULL == to_delete || NULL == head)
		return;

	//要删除的是最后一个结点
	if (NULL == to_delete->next) {
		if (head == to_delete) { //要删除的是链表仅有的一个结点
			head = NULL;
			free(to_delete);
			to_delete = NULL;  //防止垂悬指针
		}
		else {             //链表有多个结点，要删除尾结点
			LinkList* p = head;
			while (p->next != to_delete)
				p = p->next;
			p->next = NULL;
			free(to_delete);
			to_delete = NULL;    //防止垂悬指针
		}
	} 
	else { //要删除的不是尾结点
		LinkList *pnext = to_delete->next;
		to_delete->value = pnext->value;
		to_delete->next = pnext->next;
		free(pnext);
		pnext = NULL;
	}
}

int main() {

	/*LinkList *head = BuildList();
	head = InsertToHead(9, head);
	head = InsertToTail(100, head);
	head = DeletebyValue(2, head);
	printf("length: %d\n", Length(head));
	PrintList(head);
	head = Sort(head);
	printf("list1: ");PrintList(head);*/

	/*head = ReverseList(head);
	PrintList(head);*/

	/*LinkList* kth = GetRKthNode(head, 1);
	if (kth)
	printf("1th：%d\n", kth->value);*/

	/*LinkList *mid = GetMiddleNode(head);
	if (mid)
		printf("mid : %d\n", mid->value);*/

	/*RPrintListRecursively(head);
	printf("\n");
	RPrintList(head);*/

	//LinkList *head = BuildList();
	//LinkList *headb = BuildList();
	//printf("list2: ");PrintList(headb);
	//LinkList *head_merge = MergeList(head, headb);
	////LinkList *head_merge = MergeListRecursively(head, headb);
	//printf("list merge: ");PrintList(head_merge);

	/*
	//LinkList* head = (LinkList*)malloc(sizeof(LinkList));
	//head->next = head;
	LinkList *head = BuildList();
	LinkList *temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = head;
	if (HasCircle(head)) {
		printf("yes\n");
	}
	else
		printf("no\n");*/
	
	/*LinkList *head = BuildList();
	LinkList *temp = head;
	while (temp->next)
		temp = temp->next;
	LinkList* headb = BuildList();
	temp->next = headb->next->next;
	LinkList* p = GetFirstCrossNode(head, headb);
	if (p)
		printf("%d\n", p->value);*/
}