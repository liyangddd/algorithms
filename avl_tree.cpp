#include "3avl_tree.h"
#include "test.h"

AvlTree MakeEmptyAvlTree(AvlTree avltree) {
	if (avltree != NULL) {
		MakeEmptyAvlTree(avltree->left);
		MakeEmptyAvlTree(avltree->right);
		free(avltree);
	}
	return NULL;
}

Position FindAvlTree(ElementType x, AvlTree avltree) {
	if (avltree == NULL)
		return NULL;
	if (x < avltree->element)
		return FindAvlTree(x, avltree->left);
	else if (x > avltree->element)
		return FindAvlTree(x, avltree->right);
	else
		return avltree;
}

Position FindMinFromAvlTree(AvlTree avltree) {
	if (avltree == NULL)
		return NULL;
	else if (avltree->left == NULL)
		return avltree;
	else
		return FindMinFromAvlTree(avltree->left);
}

Position FindMaxFromAvlTree(AvlTree avltree) {
	if (avltree == NULL)
		return NULL;
	else if (avltree->right == NULL)
		return avltree;
	else
		return FindMaxFromAvlTree(avltree->right);
}

static int HeightAvlTree(AvlTree avltree) {
	if (avltree == NULL)
		return -1;
	else
		return avltree->height;
}

static int Max(int lhs, int rhs) {
	return lhs > rhs ? lhs : rhs;
}

//左-左插入，使得k2失去平衡，因此需要在k2处单旋转
static Position SingleRotateWithLeft(Position k2) {
	Position k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = Max(HeightAvlTree(k2->left), HeightAvlTree(k2->right)) + 1;
	k1->height = Max(HeightAvlTree(k1->left), HeightAvlTree(k1->right)) + 1;
	return k1;
}

//右-右插入，使得k1失去平衡，因此需要在k1处单旋转
static Position SigleRotateWithRight(Position k1) {
	Position k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = Max(HeightAvlTree(k1->left), HeightAvlTree(k1->right)) + 1;
	k2->height = Max(HeightAvlTree(k2->left), HeightAvlTree(k2->right)) + 1;
	return k2;
}

//左-右插入，使得k3失去平衡，因此在k3处双旋转
//双旋转其实是两次单旋转操作
//先对k3的左子树进行一次右-右单旋转操作
//然后对k3进行一次左-左单旋转操作
static Position DoubleRotateWithLeft1(Position k3) {  //双旋转，递归
	k3->left = SigleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3);
}

static Position DoubleRotateWithLeft2(Position k3) {
	Position k1, k2;
	k1 = k3->left;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k3->left = k2->right;
	k2->right = k3;
	k1->height = Max(HeightAvlTree(k1->left), HeightAvlTree(k1->right)) + 1;
	k3->height = Max(HeightAvlTree(k3->left), HeightAvlTree(k3->right)) + 1;
	k2->height = Max(k1->height, k3->height) + 1;
	return k2;
}

//右-左插入，使得k1失去平衡，因此在k1处双旋转
//双旋转其实是两次单旋转操作
//先对k1的右子树进行一次左-左单旋转操作
//然后对k1进行一次右-右单旋转操作
static Position DoubleRotateWithRight(Position k1) {
	k1->right = SingleRotateWithLeft(k1->right);
	return SigleRotateWithRight(k1);
}

AvlTree InsertToAvlTree(ElementType x, AvlTree avltree) {
	if (avltree == NULL) { //如果树为空，分配空间，插入节点
		avltree = (struct AvlNode*)malloc(sizeof(struct AvlNode));
		if (avltree == NULL) {
			cout << "malloc failed." << endl;
		}
		else {
			avltree->element = x;
			avltree->left = avltree->right = NULL;
		}
	}
	//插入值小于根节点的值，在左子树插入节点
	else if (x < avltree->element) { 
		avltree->left = InsertToAvlTree(x, avltree->left);
		//树失去了平衡，对树进行调整，这几个调整平衡的语句可以封装下
		if (HeightAvlTree(avltree->left) - HeightAvlTree(avltree->right) == 2) {
			if (x < avltree->left->element) //左-左，进行左单旋转
				avltree = SingleRotateWithLeft(avltree);
			else //左-右，双旋转
				avltree = DoubleRotateWithLeft1(avltree);
		}
	}
	//插入值大于根节点的值，在右子树插入节点
	else if (x > avltree->element) {
		avltree->right = InsertToAvlTree(x, avltree->right);
		//树失去了平衡，对树进行调整，这几个调整平衡的语句可以封装下
		if (HeightAvlTree(avltree->right) - HeightAvlTree(avltree->left) == 2) {
			if (x > avltree->right->element)
				avltree = SigleRotateWithRight(avltree); //右-右，单旋转
			else //右-左，双旋转
				avltree = DoubleRotateWithRight(avltree);
		}
	}
	avltree->height = Max(HeightAvlTree(avltree->left), HeightAvlTree(avltree->right)) + 1;
	return avltree;
}

//删除操作类似于二叉树的操作，只是需要将树调整平衡
AvlTree DeleteFromAvlTree(ElementType x, AvlTree avltree) {
	Position temp;
	if (avltree == NULL)
		return NULL;

	//在左子树寻找删除位置，删除后可能导致左子树高度变小，可能要调整树
	if (x < avltree->element) { 
		avltree->left = DeleteFromAvlTree(x, avltree->left);
		//如果右子树高度比左子树高度超过1，那么需要将树调整平衡，这几个调整平衡的语句可以封装下
		if (2 == (HeightAvlTree(avltree->right) - HeightAvlTree(avltree->left))) {
			//如果是右-左型，则要进行左单旋、右单旋；即进行如下双旋操作
			//否则为右-右型，需要进行左单旋操作
			if (HeightAvlTree(avltree->right->left) > HeightAvlTree(avltree->right->right))
				avltree = DoubleRotateWithRight(avltree);
			else 
				avltree = SigleRotateWithRight(avltree);
		}
	}
	//在右子树寻找删除位置，删除后可能导致右子树高度变小，可能要调整树
	else if (x > avltree->element) {
		avltree->right = DeleteFromAvlTree(x, avltree->right);
		//这几个调整平衡的语句可以封装下
		if (2 == (HeightAvlTree(avltree->left) - HeightAvlTree(avltree->right))) {
			if (HeightAvlTree(avltree->left->right) > HeightAvlTree(avltree->left->left))
				avltree = DoubleRotateWithLeft1(avltree);
			else
				avltree = SingleRotateWithLeft(avltree);
		}
	}
	//找到要删除的元素,该节点有两个孩子
	//那么将节点的值用右子树中最小的值A替换，然后在右子树中删除A
	else if (avltree->left && avltree->right){ 
		avltree->element = (FindMinFromAvlTree(avltree->right))->element;
		avltree->right = DeleteFromAvlTree(avltree->element, avltree->right);
	}
	//找到要删除的节点，该节点为叶子节点或仅有一个孩子
	else {
		temp = avltree;
		if (avltree->left == NULL) //当节点只有右孩子或为叶节点时
			avltree = avltree->right;
		else if (avltree->right == NULL) //当节点只有左孩子时
			avltree = avltree->left;
		free(temp);
	}

	if (avltree)
		avltree->height = Max(HeightAvlTree(avltree->right), HeightAvlTree(avltree->left)) + 1;
	return avltree;
}

void VisitElement(AvlTree tree) {
	cout << tree->element << " ";
}

//先序遍历树
void PreOrderTraversal(AvlTree tree) {
	if (tree == NULL)
		return;
	VisitElement(tree);
	PreOrderTraversal(tree->left);
	PreOrderTraversal(tree->right);
}

//中序遍历树
void InOrderTraversal(AvlTree tree) {
	if (tree == NULL)
		return;
	InOrderTraversal(tree->left);
	VisitElement(tree);
	InOrderTraversal(tree->right);
}
//int main() {
//	AvlTree tree = NULL;
//	tree = MakeEmptyAvlTree(tree);
//	tree = InsertToAvlTree(1, tree);
//	tree = InsertToAvlTree(3, tree);
//	tree = InsertToAvlTree(5, tree);
//	tree = InsertToAvlTree(122, tree);
//	tree = InsertToAvlTree(7, tree);
//	tree = InsertToAvlTree(9, tree);
//	tree = InsertToAvlTree(11, tree);
//	tree = InsertToAvlTree(21, tree);
//	Position min = FindMinFromAvlTree(tree);;
//	cout << "删除前，树高：" << HeightAvlTree(tree) << endl;
//	cout << endl << "删除前，先序遍历：" << endl;
//	PreOrderTraversal(tree);
//	cout << endl << "删除前，中序遍历：" << endl;
//	InOrderTraversal(tree);
//	DeleteFromAvlTree(7, tree);
//
//	cout << endl;
//	cout << "删除后，树高：" << HeightAvlTree(tree) << endl;
//	cout << endl << "删除后，先序遍历：" << endl;
//	PreOrderTraversal(tree);
//	cout << endl << "删除后，中序遍历：" << endl;
//	InOrderTraversal(tree);
//}