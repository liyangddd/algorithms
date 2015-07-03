#ifndef TEST_STACK_H
#define TEST_STACK_H

struct StackNode;
typedef struct StackNode *PtrToNodeStack;
typedef PtrToNodeStack Stack;

int IsEmptyStack(Stack);
Stack CreateStack(void);
void DisposeStack(Stack s);
void MakeEmptyStack(Stack s);
void PushStack(int x, Stack s);
int Top(Stack s);
void Pop(Stack s);
void PrintStack(Stack s);

#endif