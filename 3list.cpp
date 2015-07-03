#include "3list.h"
#include "test.h" 
#include "3stack_arr.h"
#include <stack>

List MakeEmpty() {
	List L = (struct Node *)malloc(sizeof(struct Node));
	if (L == NULL) {
		cout << "mallco failed." << endl;
		return NULL;
	}
	L->next = NULL;
	return L;
}

int IsEmpty(List L) {
	return L->next == NULL;
}

Position Header(List L) {
	return L;
}

Position First(List L) {
	return L->next;
}

Position Advance(Position p) {
	return p->next;
}

int Retrive(Position p) {
	return p->element;
}

int IsLast(Position p, List L) {
	return p->next == NULL;
}

Position Find(int x, List L) {
	Position p;
	p = L->next;
	while (p != NULL && p->element != x)
		p = p->next;
	return p;
}

Position FindByRecursion(int x, List L, Position p) {
	if (p != NULL) {
		if (p->element == x)
			return p;
		else
			return FindByRecursion(x, L, p->next);
	}
	return NULL;
}

void DeleteByValue(int x, List L) {
	Position p, tmp;
	p = FindPrevious(x, L);
	if (!IsLast(p, L)) {
		tmp = p->next;
		p->next = tmp->next;
		free(tmp);
	}
}

void DeleteLater(Position p) {
	Position delete_pos = p->next;
	p->next = delete_pos->next;
	free(delete_pos);
}

Position FindPrevious(int x, List L) {
	Position p;
	p = L;
	while (p->next != NULL && p->next->element != x)
		p = p->next;
	return p;
}

void Insert(int x, List L, Position p) {
	Position tmp;
	tmp = (struct Node*)malloc(sizeof(struct Node));
	if (tmp == NULL) {
		cout << "malloc failed." << endl;
		return;
	}
	tmp->element = x;
	tmp->next = p->next;
	p->next = tmp;
}

void DeleteList(List L) {
	Position p, tmp;
	p = L->next;
	L->next = NULL;
	while (p != NULL) {
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

void PrintList(List L) {
	Position p;
	p = L->next;
	cout << "Elements of List: ";
	while (p != NULL) {
		cout << p->element << " ";
		p = p->next;
	}
	cout << endl;
}


void RPrintList1(List lst) {
	Position pos = lst->next;
	StackArr sa = CreateStackArr(20);
	while (pos != NULL) {
		PushStackArr(pos->element, sa);
		pos = pos->next;
	}
	while (!IsEmptyStackArr(sa)) {
		cout << PopAndTop(sa) << " ";
	}
	cout << endl;
}

void RPrintList2(List lst) {
	Position pos = lst->next;
	stack<int> sa;
	while (pos != NULL) {
		sa.push(pos->element);
		pos = pos->next;
	}
	while (!sa.empty()) {
		cout << sa.top() << " ";
		sa.pop();
	}
	cout << endl;
}
void RPrintListByRecursion(Position pos) {
	if (pos == NULL) {
		return;
	}
	else {
		RPrintListByRecursion(pos->next);
		cout << pos->element << " ";
	}
}

List ReverList(List lst) {
	//Position pre_pos = NULL, cur_pos = lst, next_pos = lst->next;
	Position pre_pos = NULL, cur_pos = lst->next, next_pos = cur_pos->next;
	while (next_pos != NULL) {
		cur_pos->next = pre_pos;
		pre_pos = cur_pos;
		cur_pos = next_pos;
		next_pos = next_pos->next;
	}
	cur_pos->next = pre_pos;
	lst->next = cur_pos;
	return lst;
}

//查找链表倒数第k个节点,先遍历求总节点数，然后找倒数k个
Position FindBackwardKthNode1(List lst, unsigned int k) {
	Position pos = lst->next;
	if (IsEmpty(lst) || k <= 0) {
		return NULL;
	}
	unsigned int count_node = 0;
	while (pos != NULL) {
		count_node++;
		pos = pos->next;
	}
	cout << "count_node : " << count_node << endl;
	if (k > count_node)
		return NULL;
	pos = lst;
	int i;
	for (i = 0; i <= count_node - k; i++) {
		pos = pos->next;
	}
	return pos;
}

//查找链表倒数第k个节点,设置两个指针pos1和pos2，先让pos2前进k，
//然后pos1和pos2一起前进，那么当pos2到指针末尾后，pos1所指的就是倒数第k个
Position FindBackwardKthNode2(List lst, unsigned int k) {
	Position pos1, pos2;
	pos1 = pos2 = lst;
	int i;
	for (i = 0; i < k; i++) {
		pos2 = pos2->next;
	}
	while (pos2 != NULL) {
		pos2 = pos2->next;
		pos1 = pos1->next;
	}
	return pos1;
}

List MergerTwoList(List lsta, List lstb) {
	List merger_lst = NULL;
	Position posa = lsta->next;
	Position posb = lstb->next;
	if (lsta->next == NULL)
		return lstb;
	if (lstb->next == NULL)
		return lsta;
	if (posa->element < posb->element) { //如果lsta的首元素小于lstb的，将合并链表的头指针指向lsta的首元素
		merger_lst = lsta;
		posa = posa->next;
	}
	else { //如果lstb的首元素小于lsta的，将合并链表的头指针指向lstb的首元素
		merger_lst = lstb;
		posb = posb->next;
	}
	Position pos_merger = merger_lst->next; //指向合并后链表的最后一个节点
	while (posa != NULL && posb != NULL) {
		if (posa->element < posb->element) {
			pos_merger->next = posa;
			pos_merger = posa;
			posa = posa->next;
		}
		else {
			pos_merger->next = posb;
			pos_merger = posb;
			posb = posb->next;
		}
	}
	if (posa != NULL) {
		pos_merger->next = posa;
	}
	if (posb != NULL) {
		pos_merger->next = posb;
	}

	return merger_lst;
}

void simpleDelete(List L, int value) {
	Position p, temp;
	p = L;
	if (p->next == NULL) {
		cout << "list is empty." << endl;
		return;
	}
	while (p->next != NULL && p->next->element != value)
		p = p->next;
	if (p->next) {
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}

int InsertTohead(List lst, int value) {
	if (lst == NULL) {
		return -1;
	}
	Position p = (struct Node *)malloc(sizeof(struct Node));
	if (p == NULL)
		return -1;
	p->element = value;
	p->next = lst->next;
	lst->next = p;
	return 0;
}

int InsertToTail(List lst, int value) {
	if (lst == NULL)
		return -1;
	Position p = lst;
	while (p->next)
		p = p->next;
	Position new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL)
		return -1;
	new_node->element = value;
	new_node->next = NULL;
	p->next = new_node;
	return 0;
}


//int main() {
//	List lsta = MakeEmpty();
//	InsertToTail(lsta, 7);
//	InsertTohead(lsta, 2);
//	InsertTohead(lsta, 1);
//	InsertToTail(lsta, 11);
//
//	PrintList(lsta);
//	simpleDelete(lsta, 199);
//	PrintList(lsta);
//	RPrintList2(lsta);
//}



