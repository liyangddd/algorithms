#include "3stack_arr.h"
#include "test.h"

struct StackRecord {
	int capacity;
	int top;
	int *array;
};

StackArr CreateStackArr(int max) {
	StackArr sa;
	sa = (struct StackRecord *)malloc(sizeof(struct StackRecord));
	if (NULL == sa) {
		cout << "malloc failed." << endl;
		return NULL;
	}
	sa->array = (int *)malloc(sizeof(int) * max);
	if (sa->array == NULL) {
		cout << "malloc failed." << endl;
		return NULL;
	}
	sa->capacity = max;
	MakeEmptyStackArr(sa);
	return sa;
}

void DisposeStackArr(StackArr sa) {
	if (sa != NULL) {
		free(sa->array);
		free(sa);
	}
}

int IsEmptyStackArr(StackArr sa) {
	return sa->top == -1;
}

int IsFull(StackArr sa) {
	return sa->top == sa->capacity -1;
}

void MakeEmptyStackArr(StackArr sa) {
	sa->top = -1;
}

void PushStackArr(int element, StackArr sa) {
	if (IsFull(sa)) {
		cout << "The stack is full." << endl;
	}
	else
		sa->array[++sa->top] = element;
}

int PopAndTop(StackArr sa) {
	if (!IsEmptyStackArr(sa)) {
		return sa->array[sa->top--];
	}
	cout << "The stack is empty. Can not pop." << endl;
	return 0;
}

void PopArr(StackArr sa) {
	if (IsEmptyStackArr(sa)) {
		cout << "Stack is Empty. Can not pop." << endl;
		return;
	}
	else
		sa->top--;
}

int TopArr(StackArr sa) {
	if (!IsEmptyStackArr(sa))
		return sa->array[sa->top];
	cout << "Stack is Empty. Can not get top element." << endl;
	return 0;
}


/*
返回栈空间大小
*/
int CapacityStackArr(StackArr sa) {
	return sa->capacity;
}

int SizeStackArr(StackArr sa) {
	return sa->top + 1;
}
/*
int main() {
	char in;
	StackArr sa = CreateStackArr(20);
	char symbol_left[] = "{([";
	char symbol_right[] = "]})";
	while (cin >> in) {
		if (strchr(symbol_left, in) != NULL) {
			PushStackArr(in, sa);
		}
		else if (strchr(symbol_right, in) != NULL) {
			char top = TopArr(sa);
			switch(top) {
			case '[':
				if (in == ']') {
					printf("%c is matched.\n", in);
					PopArr(sa);
				}
				else {
					printf("Not matched.\n");
					return 1;
				}
				break;
			case '(':
				if (in == ')'){
					printf("%c is matched.\n", in);
					PopArr(sa);
				}
				else {
					printf("Not matched.\n");
					return 1;
				}
				break;
			case '{':
				if (in == '}'){
					printf("%c is matched.\n", in);
					PopArr(sa);
				}
				else {
					printf("Not matched.\n");
					return 1;
				}
				break;
			}
		}
	}
	return 0;
}
*/