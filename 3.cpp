#include "3list.h"
#include "test.h"

void PrintLots(List lstL, List lstP) { //3.2
	int counter;
	Position Lpos, Ppos;
	Lpos = First(lstL);
	Ppos = First(lstP);
	counter = 1;
	cout << "Elements: ";
	while (Lpos != NULL && Ppos != NULL) {
		if (Ppos->element == counter++) {
			cout << Lpos->element << " ";
			Ppos = Advance(Ppos);
		}
		Lpos = Advance(Lpos);
	}
}
/*
int main() {
	//构建两个链表lstL, lstP
	List lstL = MakeEmpty();
	Position p = lstL;
	int i = 2;
	while (i < 15) {
		Insert(i, lstL, p);
		i += 2;
		p = p->next;
	}
	PrintList(lstL);

	List lstP = MakeEmpty();
	Position q;
	q = lstP;
	int j = 1;
	while (j < 7) {
		Insert(j, lstP, q);
		j += 1;
		q = q->next;
	}
	PrintList(lstP);
	PrintLots(lstL, lstP);
}
*/

void SwapWithNextElements(Position p, List lst) {  //3.3 a.通过指针来交换相邻元素（交换p之后的两个节点），使用单链表
	Position first = p->next;
	Position second = first->next;
	first->next = second->next;
	p->next = second;
	second->next = first;
}
/*
int main() {
	List lstL = MakeEmpty();
	Position p = lstL;
	int i = 2;
	while (i < 15) {
		Insert(i, lstL, p);
		i += 2;
		p = p->next;
	}
	PrintList(lstL);
	SwapWithNextElements(lstL, lstL);
	PrintList(lstL);
}
*/

List IntersectionList(List list1, List list2) { //3.4 L1与L2的交集
	Position p1 = First(list1);
	Position p2 = First(list2);
	List result_list = MakeEmpty();
	Position resultp = result_list;

	while (p1 != NULL && p2 != NULL) {
		if (p1->element < p2->element) {
			p1 = Advance(p1);
		}
		else if (p1->element > p2->element) {
			p2 = Advance(p2);
		}
		else {
			Insert(p1->element, result_list, resultp);
			p1 = Advance(p1);
			p2 = Advance(p2);
			resultp = Advance(resultp);
		}
	}
	return result_list;
}

List UnionList(List list1, List list2) { //3.5 L1与L2的并集
	Position p1 = First(list1);
	Position p2 = First(list2);
	List result_list = MakeEmpty();
	Position resultp = result_list;
	int insert_element;

	while (p1 != NULL && p2 != NULL) {
		if (p1->element < p2->element) {
			insert_element = p1->element;
			p1 = Advance(p1);
		}
		else if (p1->element > p2->element) {
			insert_element = p2->element;
			p2 = Advance(p2);
		}
		else {
			insert_element = p1->element;
			p1 = Advance(p1);
			p2 = Advance(p2);
		}
		Insert(insert_element, result_list, resultp);
		resultp =  Advance(resultp);
	}
	while (p1 != NULL) {
		Insert(p1->element, result_list, resultp);
		resultp = Advance(resultp);
		p1 = Advance(p1);
	}
	while (p2 != NULL) {
		Insert(p2->element, result_list, resultp);
		resultp = Advance(resultp);
		p2 = Advance(p2);
	}
	return result_list;
}

/*
int main() {
	//构建两个链表lstL, lstP
	List lstL = MakeEmpty();
	Position p = lstL;
	int i = 2;
	while (i < 15) {
		Insert(i, lstL, p);
		i += 2;
		p = p->next;
	}
	PrintList(lstL);

	List lstP = MakeEmpty();
	Position q;
	q = lstP;
	int j = 2;
	while (j < 7) {
		Insert(j, lstP, q);
		j += 1;
		q = q->next;
	}
	Insert(14, lstP, q);
	PrintList(lstP);

	List interList = IntersectionList(lstL, lstP);
	PrintList(interList);
	List unionList = UnionList(lstL, lstP);
	PrintList(unionList);
}
*/