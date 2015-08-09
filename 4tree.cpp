//tree.cpp
#include "test.h"
#include "4tree.h"
#include <stack>
#include <queue>

//二叉搜索树的创建
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

//二叉树的清空操作
SearchTree MakeEmptyTree(SearchTree tree) {
	if (tree != NULL) {
		MakeEmptyTree(tree->left);
		MakeEmptyTree(tree->right);
		free(tree);
	}
	return NULL;
}

//二叉树的拷贝
SearchTree CopyTree(SearchTree tree) {
	if (NULL == tree)
		return NULL;
	SearchTree pleft = CopyTree(tree->left);
	SearchTree pright = CopyTree(tree->right);
	tree->left = pleft;
	tree->right = pright;
	return tree;
}

//二叉树的镜像 offerT19
void MirrorTree(SearchTree tree) {
	if (NULL == tree)
		return;
	if (NULL == tree->left && NULL == tree->right)
		return;

	SearchTree temp = tree->left;
	tree->left = tree->right;
	tree->right = temp;

	if (tree->left)
		MirrorTree(tree->left);
	if (tree->right)
		MirrorTree(tree->right);
}

//二叉搜索树的查找
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

//寻找二叉搜索树的最大节点:递归和非递归
Position FindMax(SearchTree tree) {
	if (tree != NULL)
		while (tree->right != NULL)
			tree = tree->right;
	return tree;
}

Position FindMax2 (SearchTree tree) {
	if (tree == NULL)
		return NULL;
	else if (tree->right == NULL)
		return tree;
	else
		return FindMax2(tree->right);
}

//寻找二叉搜索树的最小节点：递归和非递归
Position FindMin(SearchTree tree) {
	if (tree != NULL)
		while (tree->left)
			tree = tree->left;
	return tree;
}

Position FindMin2(SearchTree tree) {
	if (tree == NULL)
		return NULL;
	else if (tree->left == NULL)
		return tree;
	else
		return FindMin(tree->left);
}

//二叉搜索树的插入
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

//二叉搜索树的删除
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

//后序遍历递归算法
void PostOrderTraversalRecursion(SearchTree tree) {
	if (tree == NULL)
		return;
	PostOrderTraversalRecursion(tree->left);
	PostOrderTraversalRecursion(tree->right);
	VisitTreeElement(tree);
}

//层次遍历，入队前访问或出队前访问均可
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

void VisitTreeElement(SearchTree tree) {
	cout << tree->element << " ";
}

//《编程之美》3.10 分层遍历二叉树
//每行输出一层节点的各个元素
//方法一：
//利用vector充当队列，两个指针current和last分别指向vector
//中某层树元素的第一个和最后一个，当current < last时，依次遍历
//本层每个元素
typedef struct Tree{
	Tree* left;
	Tree* right;
	int value; 
} Tree, Node;
void PrintNodeByLevel(Tree* tree) {
	if (tree == NULL)
		return;
	vector<Node*> vec;
	int current = 0, last = 1;
	vec.push_back(tree);
	while (current < vec.size()) {
		last = vec.size();
		while (current < last) {
			cout << vec[current] -> value << " ";
			if (vec[current]->left)
				vec.push_back(vec[current]->left);
			if (vec[current]->right)
				vec.push_back(vec[current]->right);
			++current;
		}
		cout << endl;
	}
}

//方法二：
//http://www.cnblogs.com/miloyip/archive/2010/05/12/binary_tree_traversal.html
//每层遍历结束，在队列中插入一个空指针，标志本层结束需要输出换行
void PrintNodeByLevel2(Tree* tree) {
	if (tree == NULL)
		return;

	queue<Node *> q;
	q.push(tree);
	while (!q.empty()) {
		Node * node = q.front();
		q.pop();
		if (node) {
			cout << node->value << " ";
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
		else if (!q.empty()) {
			q.push(NULL);
			cout << endl;
		}
	}
	return;
}


//offerT25
//打印二叉树中和为某一值的路径
void FindPathCore(SearchTree tree, int sum, vector<int>& path, int sum_current);
void FindPath(SearchTree tree, int sum) {
	if (NULL == tree)
		return;
	
	vector<int> path;
	int sum_current = 0;
	FindPathCore(tree, sum, path, sum_current);
}

void FindPathCore(SearchTree tree, int sum, vector<int>& path, int sum_current) {
	sum_current += tree->element;
	path.push_back(tree->element);

	bool isleef = (tree->left == NULL && tree->right == NULL);

	//当达到叶结点，并且该路径和等于输入整数时，输出这个符合要求的路径
	if (isleef && sum_current == sum) {
		cout << "a path: ";
		vector<int>::iterator iter = path.begin();
		while (iter != path.end())
			cout << *iter++ << " ";
		cout << endl;
	}

	if (tree->left)
		FindPathCore(tree->left, sum, path, sum_current);
	if (tree->right)
		FindPathCore(tree->right, sum, path, sum_current);

	//当遍历完一条路径后，要从路径中删除该叶结点并从路径和中减去当前叶结点
	sum_current -= tree->element;
	path.pop_back();
}

//offerT27
//二叉搜素树和双向链表(中序遍历)
void CovertTreetoListCore(SearchTree tree, SearchTree* last_listnode);
SearchTree CovertTreetoList(SearchTree tree) {
	SearchTree last_listnode = NULL;
	CovertTreetoListCore(tree, &last_listnode);
	
	//last_listnode指向双向链表尾部，这里将其指向头部
	SearchTree head_list = last_listnode;
	while (head_list && head_list->left != NULL)
		head_list = head_list->left;

	return head_list;
}

//函数第二个参数是指针的指针
void CovertTreetoListCore(SearchTree tree, SearchTree* last_listnode) {
	if (NULL == tree)
		return;

	SearchTree current = tree;

	if (current->left)
		CovertTreetoListCore(current->left, last_listnode);

	current->left = *last_listnode;
	if (*last_listnode)
		(*last_listnode)->right = current;
	
	*last_listnode = current;

	if (current->right)
		CovertTreetoListCore(current->right, last_listnode);
}

//offerT39
//判断一棵树是不是平衡树（方法一）
bool IsBalancedTreeCore(SearchTree tree, int *depth);
bool IsBalancedTree(SearchTree tree) {
	int depth = 0;
	return IsBalancedTreeCore(tree, &depth);
}

bool IsBalancedTreeCore(SearchTree tree, int *depth) {
	if (NULL == tree) {
		*depth = 0;
		return true;
	}

	int depth_left, depth_right;
	if (IsBalancedTreeCore(tree->left, &depth_left) && 
		IsBalancedTreeCore(tree->right, &depth_right)) {
		int diff = depth_left - depth_right;
		if (diff >= -1 && diff <= 1) {
			*depth = (depth_left > depth_right ? depth_left : depth_right) + 1;
			return true;
		}
	}

	return false;
}


//offerT39
//判断一棵树是不是平衡树（方法二）
//Depth结构用于存储根结点的最大和最小深度
struct Depth {
	int min_depth;
	int max_depth;
};
//函数返回根结点的最大和最小深度
Depth GetDepth(SearchTree tree) {
	if (NULL == tree) {
		Depth empty = {0, 0};
		return empty;
	}

	Depth lhs = GetDepth(tree->left);
	Depth rhs = GetDepth(tree->right);
	Depth depth;
	depth.max_depth = 1 + max(lhs.max_depth, rhs.max_depth);
	depth.min_depth = 1 + min(lhs.min_depth, rhs.min_depth);
	return depth;
}
bool IsBalancedTree2(SearchTree tree) {
	Depth depth = GetDepth(tree);
	//如果根结点的最大深度和最小深度之差不超过1为平衡二叉树
	if (depth.max_depth - depth.min_depth > 1)
		return false;
	else
		return true;
}

//寻找节点后继
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

//offerT6
//由先序和中序遍历构造二叉树
Position ConstructBiTreeCore(int *startPreOrder, int *endPreorder, 
	                         int *startInorder, int *endInorder) {
	int root_value = startPreOrder[0];
	Position root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
	if (root == NULL)
		return NULL;
	root->element = root_value;
	root->right = root->left = NULL;

	if (startPreOrder == endPreorder) {
		if (startInorder == endInorder && *startInorder == *startPreOrder) {
			cout << root->element << " ";
			return root;
		}
		else { //当输入序列不符合要求时，返回NUll之前释放root，以免内存泄露
			free(root);
			throw exception("invalid input");
		}
	}

	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != root_value)
		++rootInorder;

	if (rootInorder == endInorder && *rootInorder != root_value)
		throw exception("invaid input");

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
	cout << root->element << " ";
	return root;
}

Position ConstructBiTree(int *preorder, int *inorder, int len) {
	if (preorder == NULL || inorder == NULL || len <= 0)
		return NULL;
	return ConstructBiTreeCore(preorder, preorder + len - 1,
		inorder, inorder + len - 1);
}

//根据先序遍历和中序遍历求后序遍历(和上题构造二叉树原理一样)
void PrintPostOrderCore(int *startPreorder, int *endPreorder,
	int *startInorder, int *endInorder) {
	int root_value = startPreorder[0];

	//当先序遍历和后序遍历仅有一个元素且该元素相等时，输出
	//否则是非法输入
	if (startPreorder == endPreorder) {
		if (startInorder == endInorder && *startPreorder == *startInorder) {
			cout << root_value << " ";
		}
		else {
			throw exception("invalid input");
		}
	}

	//在中序遍历中寻找根的位置
	int *rootInorder = startInorder;
	while (rootInorder <= endInorder && *rootInorder != root_value)
		++rootInorder;

	//递归遍历左右子树
	int left_length = rootInorder - startInorder;
	int *leftPreorderEnd = startPreorder + left_length;
	if (left_length > 0)
		PrintPostOrderCore(startPreorder + 1, leftPreorderEnd,
		      startInorder, rootInorder - 1);
	if (left_length < endPreorder - startPreorder)
		PrintPostOrderCore(leftPreorderEnd + 1, endPreorder,
		      rootInorder + 1, endInorder);
	
	//左右子树输出完成后，在输出根结点值
	cout << root_value << " ";
}
void PrintPostOrder(int *preorder, int *inorder, int length) {
	if (preorder == NULL || inorder == NULL || length <= 0)
		return;
	PrintPostOrderCore(preorder, preorder + length - 1,
		inorder, inorder + length -1);
}
//offerT24
//判断某个整数数组是不是一个二叉搜索树的后序遍历序列
bool IsPostOrderBST(int array[], int length) {
	if (length < 1 || array == NULL)
		return false;

	int root = array[length - 1];

	int length_left = 0;
	for ( ; length_left < length - 1; ++length_left) {
		if (array[length_left] > root)
			break;
	}

	int pos_right = length_left;
	for ( ; pos_right < length - 1; ++pos_right) {
		if (array[pos_right] < root)
			return false;
	}

	//判断左子树是不是BST的后序遍历序列
	bool result_left = true;
	if (length_left > 0)
		result_left = IsPostOrderBST(array, length_left);

	//判断右子树是不是BST的后序遍历序列
	bool result_right = true;
	if (length_left < length - 1)
		result_right = IsPostOrderBST(array + length_left, length - length_left - 1);

	return (result_left && result_right);
}

//求二叉树中节点个数
int CountTreeNodesNum(SearchTree tree) {
	if (NULL == tree)
		return -1;
	return CountTreeNodesNum(tree->left) + CountTreeNodesNum(tree->right) + 1;
}

//求二叉树第k层结点树(根为第1层)
int GetTreeNodesNumKthLevel(SearchTree tree, int k) {
	if (NULL == tree || k < 1)
		return 0;
	if (1 == k)
		return 1;
	int num_left = GetTreeNodesNumKthLevel(tree->left, k - 1);
	int num_right = GetTreeNodesNumKthLevel(tree->right, k - 1);
	return num_left + num_right;
}

//求叶结点个数
int GetLeafNum(SearchTree tree) {
	if (NULL == tree)
		return 0;
	if (!tree->left && !tree->right)
		return 1;
	int leaf_left = GetLeafNum(tree->left);
	int leaf_right = GetLeafNum(tree->right);
	return leaf_left + leaf_right;
}

//求二叉树的深度
int GetNodeDeepth(SearchTree tree) {
	if (tree == NULL)
		return 0;
	int deepth_left = GetNodeDeepth(tree->left);
	int deepth_right = GetNodeDeepth(tree->right);
	return deepth_right > deepth_left ? (deepth_right + 1): (deepth_left + 1);
}

//求二叉树中结点的最大距离(方法一)
struct Result {
	int max_distance;
	int max_depth;
};

Result GetMaxDistanceCore(SearchTree tree);
int GetMaxDistance(SearchTree tree) {
	return GetMaxDistanceCore(tree).max_distance;
}

Result GetMaxDistanceCore(SearchTree tree) {
	if (NULL == tree) {
		//最大深度初始化为-1是因为调用这对其加1，然后变为0
		Result empty = {0, -1};
		return empty;
	}

	Result lhs = GetMaxDistanceCore(tree->left);
	Result rhs = GetMaxDistanceCore(tree->right);
	Result result;
	result.max_depth = max(lhs.max_depth + 1, rhs.max_depth + 1);
	result.max_distance = max(max(lhs.max_distance, rhs.max_distance), 
		                      lhs.max_depth + rhs.max_depth + 2);

	return result;
}

//求二叉树中结点的最大距离(方法二)
int GetMaxDistance2(TreeNode * pRoot){
	if (pRoot == NULL)
		return 0;

	return max(GetNodeDeepth(pRoot->left) + GetNodeDeepth(pRoot->right), 
		max(GetMaxDistance2(pRoot->left), GetMaxDistance2(pRoot->right)));
}

//二叉树A和B，判断A和B是否相等
bool EqualBinaryTree(SearchTree treea, SearchTree treeb) {
	if (treea == NULL && treeb == NULL)
		return true;
	if ((!treea && treeb) || (treea && !treeb))
		return false;

	if (treea->element == treeb->element) {
		return EqualBinaryTree(treea->left, treeb->left) &&
			EqualBinaryTree(treea->right, treeb->right);
	}
	return false;
} 

//二叉树A和B，判断可以旋转的A和B是否相等,旋转是指左右子树可交换
bool EqualBinaryTree2(SearchTree treea, SearchTree treeb) {
	if (treea == NULL && treeb == NULL)
		return true;
	if ((!treea && treeb) || (treea && !treeb))
		return false;

	if (treea->element == treeb->element) {
		return (EqualBinaryTree2(treea->left, treeb->left) && 
			EqualBinaryTree2(treea->left, treeb->left)) || 
			(EqualBinaryTree2(treea->left, treeb->right) && 
			EqualBinaryTree2(treea->right, treeb->left));
	}
	return false;
}

//offerT18
//二叉树A和B，判断B是不是A的子结构
bool SubTreeCore(SearchTree treea, SearchTree treeb) {
	if (treeb == NULL)
		return true;
	if (treea == NULL)
		return false;
	if (treea->element != treeb->element)
		return false;
	return SubTreeCore(treea->left, treeb->left) &&
		SubTreeCore(treeb->right, treeb->right);
}

bool IsSubTree(SearchTree treea, SearchTree treeb) {
	bool result = false;
	if (treea && treeb) {
		if (treea->element == treeb->element)
			result = SubTreeCore(treea, treeb);
		if (!result)
			result = IsSubTree(treea->left, treeb);
		if (!result)
			result = IsSubTree(treea->right, treeb);
	}
	return result;
}

//判断二叉树是不是完全二叉树
bool IsCompletedTree(SearchTree tree) {
	if (NULL == tree)
		return false;
	bool result = true;
	bool must_leaf = false;
	
	queue<SearchTree> nodes;
	nodes.push(tree);
	while (!nodes.empty()) {
		SearchTree node = nodes.front();
		nodes.pop();
		
		//如果某节点只有左子树，那么按照层次遍历时
		//其后结点必须全为叶子结点，否则该树不是完全二叉树
		if (must_leaf) {
			if (node->left || node->right) {
				result = false;
				break;
			}
		}
		else {
			if (node->left && node->right) {
				nodes.push(node->left);
				nodes.push(node->right);
			}
			else if (node->left && ! node->right) {
				must_leaf = true;
				nodes.push(tree->left);
			}
			else if (!node->left && node->right) {
				result = false;
				break;
			}
			else
				must_leaf = true;
		}
	}
	return true;
}


//int main() {

	/*SearchTree tree = NULL;
	tree = CreateSearchTree(tree);
	PreOrderTraversal(tree);
	cout << endl;
	InOrderTraversal(tree);
	cout << endl;
	cout << "max: " << FindMax(tree)->element << " " << FindMax2(tree)->element << endl;
	cout << "min: " << FindMin(tree)->element << " " << FindMin2(tree)->element << endl;*/
	/*int preorder[] = {1};
	int inorder[] = {2};
	Position root = ConstructBiTree(preorder, inorder, sizeof(preorder) / sizeof(int));
	PreOrderTraversal(root);
	cout << endl;
	InOrderTraversalRecursion(root);
	cout << endl;*/

	////二叉树A和B，判断A和B是否相等
	////二叉树A和B，判断B是不是A的子结构
	//SearchTree treea = NULL;
	//int a[] = {1, 2, 3, 4, 5};
	//for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
	//	treea = InsertToTree(a[i], treea);

	//int b[] = { 2, 3, 1};
	//SearchTree treeb = NULL;
	//for (int i = 0; i < sizeof(b) / sizeof(int); ++i)
	//	treeb = InsertToTree(b[i], treeb);
	////if (EqualBinaryTree(treea, treeb))
	////	cout << "yes" << endl;
	////else
	////	cout << "no" << endl;
	//if (IsSubTree(treea, treeb))
	//	cout << "yes" << endl;
	//else
	//	cout << "no" << endl;

	////打印二叉树中和为某一值的路径
	//SearchTree tree = NULL;
	//tree = CreateSearchTree(tree);
	//int sum = 5;
	//FindPath(tree, sum);

	/*SearchTree tree = NULL;
	tree = CreateSearchTree(tree);
	cout << GetMaxDistance(tree) << endl;*/

	/*SearchTree tree = NULL;
	tree = CreateSearchTree(tree);
	cout << GetMaxDistance(tree) << " " << GetMaxDistance2(tree) << endl;
	IsBalancedTree2(tree);
	if (IsBalancedTree(tree))
	cout << "balance" << endl;
	else
	cout << "no" << endl;*/
	
	//int a[] = {1,2,4,7,3,5,6,8};
	//int b[] = {4,7,2,1,5,3,8,6};
	////PrintPostOrder(a, b, sizeof(a) / sizeof(int));
	////int a[] = {1, 2};int b[] = {2,1};
	//SearchTree tree = ConstructBiTree(a, b, sizeof(a) / sizeof(int));
	//cout << endl;
	//PreOrderTraversal(tree);
	//cout << endl;
	//PostOrderTraversal(tree);
	//cout << endl;

//}

