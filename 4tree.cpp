//tree.cpp
#include "test.h"
#include "4tree.h"
#include <stack>
#include <queue>

SearchTree CreateSearchTree(SearchTree tree) {
	int tree_element;
	while (cin >> tree_element) {
		if (tree_element == '*')
			break;
		else
			tree = InsertToTree(tree_element, tree);
	}
	return tree;
}

SearchTree MakeEmptyTree(SearchTree tree) {
	if (tree != NULL) {
		MakeEmptyTree(tree->left);
		MakeEmptyTree(tree->right);
		free(tree);
	}
	return NULL;
}

Position FindFromTree(ElementType x, SearchTree tree) {
	if (tree == NULL)
		return NULL;
	if (tree->element < x)
		FindFromTree(x, tree->right);
	else if (x < tree->element)
		FindFromTree(x, tree->left);
	else
		return tree;
}

Position FindMax(SearchTree tree) {
	if (tree != NULL)
		while (tree->right != NULL)
			tree = tree->right;
	return tree;
}

Position FindMin(SearchTree tree) {
	if (tree == NULL)
		return NULL;
	else if (tree->left == NULL)
		return tree;
	else
		return FindMin(tree->left);
}

SearchTree InsertToTree(ElementType x, SearchTree tree) {
	if (tree == NULL) {
		tree = (struct TreeNode*)malloc(sizeof(struct TreeNode));
		if (tree == NULL) {
			cout << "malloc failed" << endl;
		}
		else {
			tree->element = x;
			tree->left = NULL;
			tree->right = NULL;
		}
	}
	else if (x < tree->element)
		tree->left = InsertToTree(x, tree->left);
	else if (x > tree->element)
		tree->right = InsertToTree(x, tree->right);
	return tree;
}

SearchTree DeleteFromTree(ElementType x, SearchTree tree) {
	Position temp;
	if (tree == NULL) {
		cout << "The tree is empty, no element." << endl;
	}
	else if (x < tree->element) {  //寻找要删除的位置
		DeleteFromTree(x, tree->left);
	}
	else if (x > tree->element) {  //寻找要删除的位置
		DeleteFromTree(x, tree->right);
	}
	else if(tree->left && tree->right) {  //找到要删除的位置，该节点有两个孩子
		temp = FindMin(tree->right);
		tree->element = temp->element;
		tree->right = DeleteFromTree(tree->element, tree->right);
	}
	else { //仅有一个子树，或者为叶节点
		temp = tree;
		if (tree->left == NULL)
			tree = tree->right;
		else if (tree->right == NULL)
			tree = tree->left;
		free(temp);
	}
	return tree;
}

/*
先序遍历是在元素入栈前，先访问该元素；
然后将此节点入栈，再遍历其左子树；
遍历完左子树后，从栈中弹出该元素，然后根据该元素的
右子树指针去遍历该节点的右子树结构
*/
//先序遍历的非递归方法（一）
void PreOrderTraversal(SearchTree tree) {
	if (tree == NULL)
		return;
	stack<SearchTree> stk;
	Position cur = tree;

	while (cur != NULL || !stk.empty()) {
		while (cur != NULL) {
			VisitTreeElement(cur);
			stk.push(cur);
			cur = cur->left;
		}
		//if (!stk.empty()) {
		cur = stk.top();
		stk.pop();
		cur = cur->right;
		//}
	}
}

//先序遍历的非递归方法（二）
void PreOrderTraversal2(SearchTree tree) {
	if (tree == NULL)
		return;
	stack<SearchTree> stk;
	stk.push(tree);

	while(!stk.empty()) {
		Position top_node = stk.top();
		VisitTreeElement(top_node);
		stk.pop();
		if (top_node->right)
			stk.push(top_node->right);
		if (top_node->left)
			stk.push(top_node->left);
	}
}

//先序遍历的非递归方法（三）
void PreOrderTraversal3(SearchTree tree) {
	if (tree == NULL)
		return;
	stack<SearchTree> stk;

	while (tree) {
		stk.push(tree);
		VisitTreeElement(tree);
		tree = tree->left;
	}

	while (!stk.empty()) {
		Position top_node_right = stk.top()->right;
		stk.pop();
		while (top_node_right) {
			VisitTreeElement(top_node_right);
			stk.push(top_node_right);
			top_node_right = top_node_right->left;
		}
	}
}

//先序遍历的递归方法
void PreOrderTraversalRecursion(SearchTree tree) {
	if (tree == NULL) {
		return;
	}
	VisitTreeElement(tree);
	PreOrderTraversalRecursion(tree->left);
	PreOrderTraversalRecursion(tree->right);
}

/*
中序遍历遇到一个元素，先将其入栈，并遍历其左子树。
遍历完左子树，从栈中弹出元素并访问，然后按照该元素
指示的其右孩子去遍历右子树。
其实前序和中序遍历仅仅是访问元素的时机不同，前者是
入栈时就访问，后者是在出栈时访问。下面非递归中序遍历
的两种方式分别与前序非递归的第（一）、第（三）种方式类似
*/
//中序遍历的非递归方法（一），类似前序非递归遍历（一）
void InOrderTraversal(SearchTree tree) {
	if (tree == NULL)
		return;
	stack<SearchTree> stk;
	Position cur = tree;
	
	while (cur != NULL || !stk.empty()) {
		while (cur != NULL) {
			stk.push(cur);
			cur = cur->left;
		}
		//if (!stk.empty()) {
			cur = stk.top();
			VisitTreeElement(cur);
			stk.pop();
			cur = cur->right;
		//}
	}
}


//中序遍历的非递归方法（二），类似前序非递归遍历（三）
void InOrderTraversal2(SearchTree tree) {
	if (tree == NULL)
		return;
	stack<SearchTree> stk;

	while (tree) {
		stk.push(tree);
		tree = tree->left;
	}

	while (!stk.empty()) {
		Position top_node_right = stk.top()->right;
		VisitTreeElement(stk.top());
		stk.pop();
		while (top_node_right) {
			stk.push(top_node_right);
			top_node_right = top_node_right->left;
		}
	}
}

//中序遍历的递归方法
void InOrderTraversalRecursion(SearchTree tree) {
	if (tree == NULL)
		return;
	InOrderTraversalRecursion(tree->left);
	VisitTreeElement(tree);
	InOrderTraversalRecursion(tree->right);
}

/*
后序遍历遇到一个元素，将其入栈，遍历其左子树。
遍历结束后，不能立即访问栈顶节点，而要遍历右子树。
遍历完右子树后才能访问该元素。另外，当从栈中弹出一个
元素时，还要判断该栈顶元素是从左边返回的（这样要继续
访问其右子树），还是从右边返回的（这时该元素左右子树
均访问过了）。
*/
//后序非递归方法（一）
void PostOrderTraversal(SearchTree tree) {
	stack<SearchTree> stk;
	Position cur = tree;
	Position visited = NULL; //指向前一个访问的节点
	while (cur != NULL || !stk.empty()) {
		while (cur != NULL) { //一直遍历左子树
			stk.push(cur);
			cur = cur->left;
		}
		cur = stk.top();
		//如果当前节点的右树为空或者右树已经访问过了，
		//直接访问该节点并弹出该节点
		if (cur->right == NULL || cur->right == visited) {
			VisitTreeElement(cur);
			visited = cur;
			stk.pop();
			cur = NULL;
		}
		else //否则遍历右子树
			cur = cur->right;
	}
}

//后序非递归方法（二）
void PostOrderTraversal2(SearchTree tree) {
	stack<SearchTree> s1, s2;
	Position cur;
	s1.push(tree);
	while (!s1.empty()) {
		cur = s1.top();
		s1.pop();
		s2.push(cur);
		if (cur->left)
			s1.push(cur->left);
		if (cur->right)
			s1.push(cur->right);
	}
	while (!s2.empty()) {
		VisitTreeElement(s2.top());
		s2.pop();
	}
}

void PostOrderTraversalRecursion(SearchTree tree) {
	if (tree == NULL)
		return;
	PostOrderTraversalRecursion(tree->left);
	PostOrderTraversalRecursion(tree->right);
	VisitTreeElement(tree);
}

//层次遍历，入队前访问
void LevelTraversal(SearchTree tree) {
	queue<SearchTree> q;
	VisitTreeElement(tree);
	q.push(tree);
	while (!q.empty()) {
		Position cur = q.front();
		q.pop();
		if (cur->left) {
			VisitTreeElement(cur->left);
			q.push(cur->left);
		}
		if (cur->right) {
			VisitTreeElement(cur->right);
			q.push(cur->right);
		}
	}
}
#include <queue>
void VisitTreeElement(SearchTree tree) {
	cout << tree->element << " ";
}

//二叉搜索树按照中序遍历时，输出的节点是从小到大排列好的。
//如果各个节点关键字不相等，那么节点x的前驱就是中序遍历的
//x的前一个，后继就是中序遍历的x的后一个节点。
//寻找节点后继的思想：如果节点的右子树不为空，其后继就是右子树的
//最小节点；如果节点x右子树为空，并且该节点有后继节点y，则y是x的
//最底层（最靠近根节点）的祖先节点，并且y的左儿子也是x的祖先。
//没给出寻找节点前驱以及后继的实现
Position FindSuccessor(Position pos) {
	return NULL;
}

Position ConstructBiTreeCore(int *startPreOrder, int *endPreorder, 
	                         int *startInorder, int *endInorder) {
	int root_value = startPreOrder[0];
	Position root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	if (root == NULL)
		return NULL;
	root->element = root_value;
	root->right = root->left = NULL;

	if (startPreOrder == endPreorder) {
		if (startInorder == endInorder && startInorder[0] == startPreOrder[0])
			return root;
		else
			return NULL;
	}

	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != root_value)
		++rootInorder;

	int left_len = rootInorder - startInorder;
	int *leftPreOrderEnd = startPreOrder + left_len;
	if (left_len > 0) {
		root->left = ConstructBiTreeCore(startPreOrder + 1, leftPreOrderEnd, 
			startInorder, rootInorder - 1);
	}
	if (left_len < endPreorder - startPreOrder) {
		root->right = ConstructBiTreeCore(leftPreOrderEnd + 1, endPreorder, 
			rootInorder + 1, endInorder);
	}
	return root;
}
//由先序和中序遍历构造二叉树
Position ConstructBiTree(int *preorder, int *inorder, int len) {
	if (preorder == NULL || inorder == NULL || len <= 0)
		return NULL;
	return ConstructBiTreeCore(preorder, preorder + len - 1,
		inorder, inorder + len - 1);
}
//int main() {
//	SearchTree tree = NULL;
//	tree = CreateSearchTree(tree);
//	PreOrderTraversal(tree);
//	cout << endl;
//	InOrderTraversal(tree);
//	cout << endl;
//	int preorder[] = {1};
//	int inorder[] = {1};
//	Position root = ConstructBiTree(preorder, inorder, sizeof(preorder) / sizeof(int));
//	PreOrderTraversal(root);
//	cout << endl;
//	InOrderTraversalRecursion(root);
//    cout << endl;
//}
//
