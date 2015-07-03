#ifndef TEST_STACK_ARR_H
#define TEST_STACK_ARR_H

struct StackRecord;
typedef struct StackRecord *StackArr;

int IsEmptyStackArr(StackArr sa);
int IsFull(StackArr sa);
StackArr CreateStackArr(int capacity);
void DisposeStackArr(StackArr sa);
void MakeEmptyStackArr(StackArr sa);
void PushStackArr(int element, StackArr sa);
int TopArr(StackArr sa);
void PopArr(StackArr sa);
int PopAndTop(StackArr sa);
void PritStackArr(StackArr sa);

#endif