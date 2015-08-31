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

//方法三：对方法二的改进
//方法二代码冗余度太大，这里的方法没有
//参考：http://blog.chinaunix.net/uid-20630773-id-3211899.html

//该函数是库函数strncmp的实现，可以直接用库函数strncmp
int Strncmp(char *str, char *substr, size_t count) {
	if (str == NULL || substr == NULL)
		return false;

	int result = 0;
	while (count-- && !(result = *str - *substr) && *str) {
		++str;
		++substr;
	}
	return result;
}

bool StrStrShift3(char *str, char *substr) {
	if (str == NULL || substr == NULL)
		return false;

	int len_str = strlen(str);
	int len_substr = strlen(substr);
	if (len_substr > len_str * 2)
		return false;

	for (int i = 0; i < len_str; ++i) {
		//如果str剩下的字符长度大于substr的长度，可不用循环，直接一次比较完成
		if (len_str >= i + len_substr) {
			if (Strncmp(str + i, substr, len_substr) == 0)
				return true;
		}
		else { //否则，还需要将substr的后半部分与str的开始部分接着匹配
			if ((Strncmp(str + i, substr, len_str - i) == 0) && 
				(Strncmp(str, substr + len_str - i, len_substr - len_str + i) == 0))
				return true;
		}
	}
	return false;
}
int main() {
	char str[] = "1234";
	char substr[] = "41";
	if (StrStrShift3(str, substr))
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



//3.11 程序改错（二分查找）
//找出一个有序字符串arr中值等于字符v的元素的序号，
//如果多个元素符合要求，返回序号最大的
//方法一：坏的复杂度为O(n)
int SearchMaxIndex(char *arr, int n, char ch) {
	int left = 0, right = n - 1, mid;
	while (left <= right) {
		mid = left + (right - left) / 2;
		if (arr[mid] == ch) //利用二分查找找到一个ch后退出本层循环
			break;
		else if (arr[mid] < ch)
			left = mid + 1;
		else
			right = mid - 1;
	}

	//如果上层的循环找到了一个ch的话，本层循环线性查找
	//等于ch的、编号最大的那个ch
	//当arr元素中有一半以上的元素等于ch，复杂度为O(n)
	if (left <= right) {
		while (arr[mid] == ch)
			++mid;
		return mid - 1;
	}
	return -1;
}

//方法二：复杂度为O(logn)
int SearchMaxIndex2(char *arr, int n, char ch) {
	int left = 0, right = n - 1, mid;
	while (left < right - 1) {
		mid = left + (right - left) / 2;
		//cout << left << " " << right << " " << mid << endl;
		if (arr[mid] <= ch)
			left = mid;
		else
			right = mid - 1;
	}

	if (arr[right] == ch)
		return right;
	else if (arr[left] == ch)
		return left;
	else
		return -1;
}

//找出一个有序字符串arr中值等于字符v的元素的序号，
//如果多个元素符合要求，返回序号最小的
int SearchMaxIndex3(char *arr, int n, char ch) {
	int left = 0, right = n - 1, mid;
	while (left < right - 1) {
		mid = left + (right - left) / 2;
		if (arr[mid] >= ch)
			right = mid;
		else
			left = mid + 1;
	}

	if (arr[left] == ch)
		return left;
	else if (arr[right] == ch)
		return right;
	else
		return -1;
}

//给定一个有序数组arr，求最小的i使得arr[i]大于v，不存在则返回-1
int SearchMaxIndex4(char *arr, int n, char ch) {
	int left = 0, right = n - 1, mid;
	while (left < right - 1) {
		mid = left + (right - left) / 2;
		if (arr[mid] <= ch)
			left = mid + 1;
		else
			right = mid;
	}
	if (arr[left] > ch)
		return left;
	else if (arr[right] > ch)
		return right;
	else
		return -1;
}

int main() {
	char arr[] = "ac";
	char ch = 'c';
	int pos = SearchMaxIndex4(arr, sizeof(arr) / sizeof(char), ch);
	if (pos == -1)
		cout << "not found" << endl;
	else
		cout << arr[pos] << " " << pos << endl;
}
