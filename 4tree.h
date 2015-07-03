//tree.h
#ifndef TEST_TREE_H
#define  TEST_TREE_H

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

struct TreeNode {
	ElementType element;
	SearchTree left;
	SearchTree right;
};
//创建查找树
SearchTree CreateSearchTree(SearchTree tree);
//将树变为空
SearchTree MakeEmptyTree(SearchTree T);
//根据值来查找节点
Position FindFromTree(ElementType x, SearchTree tree);
//查找树的最大、最小节点
Position FindMin(SearchTree tree);
Position FindMax(SearchTree tree);
//插入、删除节点
SearchTree InsertToTree(ElementType x, SearchTree tree);
SearchTree DeleteFromTree(ElementType x, SearchTree tree);
ElementType RetrieveTree(Position);
//二叉搜索树的遍历
void PreOrderTraversal(SearchTree);
void PreOrderTraversal2(SearchTree);
void PreOrderTraversal3(SearchTree);
void PreOrderTraversalRecursion(SearchTree);
void InOrderTraversal(SearchTree);
void InOrderTraversal2(SearchTree);
void InOrderTraversalRecursion(SearchTree);
void PostOrderTraversal(SearchTree);
void PostOrderTraversal2(SearchTree);
void PostOrderTraversalRecursion(SearchTree);
void LevelTraversal(SearchTree);
void VisitTreeElement(SearchTree);

//以下两个函数需要需找父节点，而这里的搜索树的设计没有
//指向父节点的指针，因此需要编程来寻找父节点，这里没给出实现。
Position FindSuccessor(Position pos); //寻找节点的后继
Position FindPredecessor(Position pos);//寻找节点前驱

Position ConstructBiTree(int *preorder, int *inorder, int len); //由先序和中序遍历构造二叉树
#endif