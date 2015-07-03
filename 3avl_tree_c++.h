#ifndef AVL_TREE_cplusplus_H
#define AVL_TREE_cplusplus_H

#include <iostream>
using namespace std;

template <typename Comparable>
class AvlTree
{
public:
	AvlTree():root(NULL) {}
	AvlTree(const AvlTree &rhs): root(NULL) {
		*this = rhs;
	}
	~AvlTree() {
		makeEmpty();
	}

	const Comparable &findMin() const {
		if (isEmpty())
			cout << "树为空" << endl;
		return findMin(root)->element;
	}

	const Comparable &findMax() const {
		if (isEmpty())
			cout << "树为空" << endl;
		return findMax(root)->element;
	}

	bool contains(const Comparable &x) const {
		return contains(x, root);
	}

	bool isEmpty() const {
		return root == NULL;
	}

	void printTree() const {
		if (isEmpty())
			cout << "Empty tree." << endl;
		else {
			cout << "先序：";
			printTreePreOrder(root);
			cout << endl << "中序：";
			printTreeInOrder(root);
			cout << endl << "后序：";
			printTreePostOrder(root);
		}
		cout << endl;
	}

	void makeEmpty() {
		makeEmpty(root);
	}

	void insert(const Comparable &x) {
		insert(x, root);
	}

	void remove(const Comparable &x) {
		remove(x, root);
	}

	const AvlTree &operator=(const AvlTree &rhs) {
		if (this != &rhs) {
			makeEmpty();
			root = clone(rhs.root);
		}
		return this;
	}
private:
	struct AvlNode 
	{
		Comparable element;
		AvlNode *left;
		AvlNode *right;
		int height;

		AvlNode(const Comparable &theElement, AvlNode *l, AvlNode *r, int h = 0): 
		element(theElement), left(l), right(r), height(h) {}
	};
	AvlNode *root;

	void insert(const Comparable &x, AvlNode* &t) {
		if (t == NULL)
			t = new AvlNode(x, NULL, NULL);
		else if (x < t->element) {
			insert(x, t->left);
			if (height(t->left) - height(t->right) == 2)
				if (x < t->left->element)
					rotateWithLeftChild(t);
				else
					doubleWithLeftChild(t);
		}
		else if (x > t->element) {
			insert(x, t->right);
			if (height(t->right) - height(t->left) == 2)
				if (t->right->element < x)
					rotateWithRightChild(t);
				else
					doubleWithRightChild(t);
		}
		else
			; //要往树中插入已经存在的元素，什么也不做
		t->height = max(height(t->left), height(t->right)) + 1;
	}

	void remove(const Comparable &x, AvlNode* &t) {
		if (t == NULL)
			return;
		if (x < t->element) {
			remove(x, t->left);
			if (height(t->right) - height(t->left) == 2) {
				if (height(t->right->left) > height(t->right->right))
					doubleWithRightChild(t);
				else
					rotateWithRightChild(t);
			}
		}
		else if (x > t->element) {
			if (height(t->left) - height(t->right) == 2) {
				if (height(t->left->right) > height(t->left->left))
					doubleWithLeftChild(t);
				else
					rotateWithLeftChild(t);
			}
		}
		else if (t->left && t->right) { //找到要删除的位置，t有两个孩子
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
			t->height = max(height(t->left), height(t->right)) + 1;
		}
		else {
			AvlNode *oldNode = t;
			t = (t->left == NULL) ? t->right : t->left;
			delete oldNode;
		}

		if (t != NULL)
			t->height = max(height(t->left), height(t->right)) + 1;
	}

	AvlNode *findMin(AvlNode *t) const {
		if (t == NULL)
			return NULL;
		if (t->left == NULL)
			return t;
		return findMin(t->left);
	}

	AvlNode  *findMax(AvlNode *t) const {
		//注释部分为递归
		//if (t == NULL)
		//	return NULL;
		//if (t->right == NULL)
		//	return t;
		//return findMax(t->right);

		//非递归形式
		if (t != NULL)
			while (t->right != NULL)
				t = t->right;
		return t;
	}

	bool contains(const Comparable &x, AvlNode *t) const {
		if (t == NULL)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (x > t->element)
			return contains(x, t->right);
		else
			return true;
	}

/*
	//非迭代操作
	bool contains(const Comparable &x, AvlNode *t) {
		while (t != NULL) {
			if (x < t->element)
				t = t->left;
			else if (x > t->element)
				t = t->right;
			else
				return true;
		}
		return false;
	}
*/

	void makeEmpty(AvlNode* &t) {
		if (t != NULL) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = NULL;
	}

	void printTreePreOrder(AvlNode *t) const {
		if (t != NULL) {
			cout << t->element << " ";
			printTreePreOrder(t->left);
			printTreePreOrder(t->right);
		}
	}

	void printTreeInOrder(AvlNode * t) const {
		if (t != NULL) {
			printTreeInOrder(t->left);
			cout << t->element << " ";
			printTreeInOrder(t->right);
		}
	}

	void printTreePostOrder(AvlNode * t) const {
		if (t != NULL) {
			printTreePostOrder(t->left);
			printTreePostOrder(t->right);
			cout << t->element << " ";
		}
	}

	AvlNode *clone(AvlNode *t) const {
		if (t == NULL)
			return NULL;
		return new AvlNode(t->element, clone(t->left), clone(t->right));
	}

	int height(AvlNode *t) const {
		return t == NULL ? -1 : t->height;
	}

	int max(int lhs, int rhs) {
		return lhs > rhs ? lhs : rhs;
	}

	//单旋转，左-左
	void rotateWithLeftChild(AvlNode * & k2) {
		AvlNode *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2 = k1; 
	}

	//单旋转，右-右
	void rotateWithRightChild(AvlNode * & k1) {
		AvlNode *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1 = k2;
	}

	//双旋转，左-右
	void doubleWithLeftChild(AvlNode * & k3) {
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	//双旋转，右-左
	void doubleWithRightChild(AvlNode * & k3) {
		rotateWithLeftChild(k3->right);
		rotateWithRightChild(k3);
	}
};
#endif