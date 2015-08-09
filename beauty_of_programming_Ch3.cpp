//3.1 字符串位移包含的问题
//方法一：
//substr若是str位移后的子串，那么substr肯定是str+str的子串
//所以substr匹配str+str成功，则就是符合题意的
//所用的辅助空间为2*strlen(str)
bool StrStrShift1(char *str, char *substr) {
	if (str == NULL || substr == NULL)
		return false;
	int length_str = strlen(str);

	//申请double_str存放str+str
	char *double_str = (char *)malloc(length_str * 2 + 1);
	if (NULL == double_str)
		return false;
	strncpy(double_str, str, length_str);
	strncpy(double_str + length_str, str, length_str);
	double_str[length_str * 2] = '\0';

	if (strstr(double_str, substr) != NULL)
		return true;
	else
		return false;
}

//方法二：
//不适用额外的辅助空间(除了单个变量)
//当pstr遍历到尾部还没有匹配，就再从str头部开始匹配
bool StrStrShift2(char *str, char *substr) {
	if (str == NULL || substr == NULL)
		return false;

	char *pstr = str;  //指向str的指针
	char *psub = substr;  //指向substr的指针
	int times = 1;
	
	//第一趟匹配
	int length_str = strlen(str);
	for ( ; *pstr != '\0'; ++pstr) {
		char *pstr_old = pstr;
		psub = substr;
		while (*pstr && *psub && *pstr == *psub) {
			++pstr;
			++psub;
		}
		if (*psub == '\0')
			return true;
	}

	//pstr走到尾部还没有匹配成功，就将pstr指向str头部开始第二趟匹配
	//psub则接着上一次匹配的位置继续匹配
	//下面这部分程序和上面的匹配很类似，几乎一样
	pstr = str;
	++psub;
	for ( ; *pstr != '\0'; ++pstr) {
		char *pstr_old = pstr;
		//第二趟匹配的第一次匹配时，psub接着上一次的位置开始匹配
		if (pstr != str) 
			psub = substr;

		while (*pstr && *psub && *pstr == *psub) {
			++pstr;
			++psub;
		}
		if (*psub == '\0')
			return true;
	}
	
	return false;
}

int main() {
	char str[] = "1234";
	char substr[] = "41";
	if (StrStrShift2(str, substr))
		cout << "ok" << endl;
	else
		cout << "no" << endl;
}


//3.10 分层遍历二叉树
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
