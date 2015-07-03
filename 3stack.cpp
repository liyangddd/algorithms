#include "3stack.h"
#include "test.h"

struct StackNode {
	int element;
	PtrToNodeStack next;
};

int IsEmptyStack(Stack s) {
	return s->next == NULL;
}

Stack CreateStack() {
	Stack s;
	s = (struct StackNode *) malloc(sizeof(StackNode));
	if (s == NULL) {
		cout << "malloc failed." << endl;
		return NULL;
	}
	s->next = NULL;
	MakeEmptyStack(s);
	return s;
}

void MakeEmptyStack(Stack s) {
	if (s == NULL)
		cout << "Must use CreateStack first." << endl;
	else
		while (!IsEmptyStack(s))
			Pop(s);
}

void Pop(Stack s) {
	PtrToNodeStack first_node;
	if (IsEmptyStack(s))
		cout << "Empty stack. Can not pop." << endl;
	else {
		first_node = s->next;
		s->next = s->next->next;
		free(first_node);
	}
}

int Top(Stack s) {
	if (IsEmptyStack(s)) {
		cout << "Empty stack. Can not get Top element." << endl;
		return 0;
	}
	else
		return s->next->element;

}

void PushStack(int x, Stack s) {
	PtrToNodeStack tmp;
	tmp = (struct StackNode *) malloc(sizeof(struct StackNode));
	if (NULL == tmp) {
		cout << "malloc failed."  << endl;
		return;
	}
	tmp->element = x;
	tmp->next = s->next;
	s->next = tmp;
}

void DisposeStack(Stack s) {
	MakeEmptyStack(s);
	free(s);
}

void PrintStack(Stack s) {
	PtrToNodeStack tmp;
	tmp = s->next;
	while (tmp != NULL) {
		cout << tmp->element;
		tmp = tmp->next;
	}
	cout << endl;
}

/*
int main() {
	Stack stk = CreateStack();
	PushStack(3, stk);
	PrintStack(stk);
	return 0;
}
*/