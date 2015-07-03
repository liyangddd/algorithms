typedef int ElementType;
#ifndef TEST_AVL_TREE_H
#define TEST_AVL_TREE_H

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;
struct AvlNode {
	ElementType element;
	AvlTree left;
	AvlTree right;
	int height;
};

AvlTree MakeEmptyAvlTree(AvlTree avltree);
Position FindAvlTree(ElementType x, AvlTree avltree);
Position FindMinFromAvlTree(AvlTree avltree);
Position FindMaxFromAvlTree(AvlTree avltree);
AvlTree InsertToAvlTree(ElementType x, AvlTree avltree);
AvlTree DeleteFromAvlTree(ElementType x, AvlTree avltree);
ElementType RetrieveAvlTree(Position pos);

#endif