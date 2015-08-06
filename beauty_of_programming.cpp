/*
《编程之美》代码
*/

/********************************2.8************************************/
//2.8 找符合条件的整数
//给定n，寻找一个最小的整数m，使得m * n的十进制表示中只有0和1
//参考：http://blog.csdn.net/jcwKyl/article/details/3859155
//没有考虑数值溢出的情况

//方法一：
//m从2开始直接枚举，如果n * m中只有1和0，那么即为所求
bool HasOnlyOneAndZero(int value) {
	while (value) {
		//n % 10大于2说明value的十进制中包含的不仅是1和0
		if (value % 10 >= 2) 
			return false;
		value /= 10;
	}
	return true;
}
void FindTheMin1(int n) {
	for (int m = 1; ; m++) {
		if (HasOnlyOneAndZero(m * n)) {
			cout << "m * n: " << m * n << "\tm: " << m << endl;
			break;
		}
	}
	return;
}

//方法二：
//该方法是搜索m * n，找出其中能够被n整除的最小的值，
//那么整除后的结果就是所要求解的m。
//m * n符合要求的值依次为1,10,11,100,101,110,111,……
//位数小于等于k的m * n共有2^k - 1,所以搜索次数为2^k
void FindTheMin2(int n) {
	queue<int> values; //存储m * n的值(1,10,11,100,101,110,111,……)
	values.push(1);

	int value;  //value就是m * n
	while (!values.empty()) {
		value = values.front();
		values.pop();
		if (value % n == 0) {
			cout << "m * n: " << value << "\tm: " << value / n << endl;
			break;
		}
		values.push(value * 10);
		values.push(value * 10 + 1);
	}
	return;
}

//方法三：
//方法二中搜索次数为2^k次
//这里设置一个余数信息的数组，
//数组第i位保留已经出现的最小的mod n为i的m*n
//参考：
//http://blog.csdn.net/zhangwei1120112119/article/details/17764095
//http://www.cnblogs.com/pangxiaodong/archive/2011/09/30/2196177.html
void FindTheMin3(int n) {
	if (n <= 1)
		return;

	//记录已有的余数，vec[i]表示对n的余数为i的最小的满足条件的值
	vector<int> vec(n, -1);
	vec[1] = 1;
	for (int i = 10; ; i *= 10) {
		//记录更新的余数
		vector<int> new_vec(n, -1);

		//高位数值 + 0的情况
		int temp = i % n;
		if (temp == 0) { //找到了，返回
			cout << "n * m: " << i << "\tm: " << i / n <<endl;
			return;
		}
		if (vec[temp] == -1) {
			new_vec[temp] = i;
		}

		//高位数值 + 低位正整数的情况
		for (int j = 1; j < n; ++j) {
			if (vec[j] != -1) {
				int new_index = (temp + j) % n;   //计算出的余数
				if (new_index == 0) {   //找到了，返回
					cout << "n * m: " << i + vec[j] << "\tm: " << (i + vec[j]) / n <<endl;
					return;
				}
				//如果是一个新余数，更新
				if (vec[new_index] == -1 && new_vec[new_index] == -1) {
					new_vec[new_index] = i + vec[j];
					
				}
			}
		}
		for (int i = 0; i < n; i++) {
			if (vec[i] == -1 && new_vec[i] != -1)
				vec[i] = new_vec[i];
		}
		/*for (int i = 0; i < n; ++i)
		cout << vec[i] << " ";
		cout << endl;*/
	}
	return;
}
int main() {
	int n;
	while (cin >> n) {
		FindTheMin2(n);
		FindTheMin3(n);
		//FindTheMin1(n);
	}
	return 0;
}
//上例中：注意：代码中之所以用了两个余数数组，是为了计算出高位
//的所有的新的余数，然后一起保存，如果一个一个的计算，
//那么高位会受到自身的影响。比如：假设当前计算百位，
//假设101被保存在A[7]，当前计算到A[2]，那么在计算100+A[7]
//的时候，实际上算的数值就是100+101=201是非法字符，因此，
//每次计算出的要一次性的保存下去。另外需要注意，对于0每次单独处理，即10+0,100+0的情况。


/********************************2.10************************************/
//2.10寻找数组中最大值和最小值
//两次遍历数组分别找最大、最小值需要比较2n次
//如下的方法需要比较1.5次：将相邻的两个元素比较；然后，
//将较大的和max比较，更新max；将较小的和min比较，更新min
void FindMaxAndMin (int& max, int& min, vector<int>& vec) {
	if (vec.size() == 0) {  //数组为空
		cout << "empty ";
		return;
	}
	if (vec.size() == 1) {  //数组仅有一个元素
		max = min = vec[0];
		return;
	}

	if (vec[0] > vec[1]) {
		max = vec[0];
		min = vec[1];
	}
	else {
		max = vec[1];
		min = vec[0];
	}
	if (vec.size() == 2)  //数组仅有两个元素
		return;

	int i;
	for (i = 3; i < vec.size(); i += 2) {
		if (vec[i] > vec[i - 1]) {
			if (vec[i] > max)
				max = vec[i];
			if (vec[i - 1] < min)
				min = vec[i - 1];
		}
		else {
			if (vec[i - 1] > max)
				max = vec[i - 1];
			if (vec[i] < min)
				min = vec[i];
		}
	}
	
	//当数组的元素个数为奇数时，最后一个元素要进行比较
	if (i == vec.size()) {
		if (vec[i - 1] > max)
			max = vec[i - 1];
		if (vec[i - 1] < min)
			min = vec[i - 1];
	}
}

int main() {
	int max;// = 0x80000000;
	int min;// = 0x7fffffff;

	vector<int> vec1;
	FindMaxAndMin(max, min, vec1);
	cout << max << " " << min << endl;

	int a2[] = {1};
	vector<int> vec2(a2, a2 + sizeof(a2) / sizeof(int));
	FindMaxAndMin(max, min, vec2);
	cout << max << " " << min << endl;

	int a3[] = {1,2};
	vector<int> vec3(a3, a3 + sizeof(a3) / sizeof(int));
	FindMaxAndMin(max, min, vec3);
	cout << max << " " << min << endl;

	int a4[] = {1,2,3,4};
	vector<int> vec4(a4, a4 + sizeof(a4) / sizeof(int));
	FindMaxAndMin(max, min, vec4);
	cout << max << " " << min << endl;

	int a5[] = {551,52,3,4, -12};
	vector<int> vec5(a5, a5 + sizeof(a5) / sizeof(int));
	FindMaxAndMin(max, min, vec5);
	cout << max << " " << min << endl;

	int a6[] = {1,1,1,1};
	vector<int> vec6(a6, a6 + sizeof(a6) / sizeof(int));
	FindMaxAndMin(max, min, vec6);
	cout << max << " " << min << endl;
}


/********************************2.12************************************/
//2.12快速寻找满足条件的两个数
//在数组中找出两个数，使得这两个数的和等于给定的值，
//假设数组中肯定存在符合要求的一对数

//方法一：穷举法。查找任意两个数，看其之和是否为给定数
//该方法时间复杂度为O(n^2)

//方法二：对数组排序，然后对数组中每个数进行二分查找
//时间复杂度O(nlogn),找出所有的符合要求点对
int binary_search1(vector<int>& vec, int first, int last, int value, int pos) {
	if (first > last)
		return -1;
	int mid = (first + last) / 2;
	
	//当在数组中找到了一个value而且该value不是vec[i]时才是符合要求的
	//例如数组{1,2,3,4}中sum为2的是不存在的，也就是(1,1)不符合要求
	if (vec[mid] == value && mid != pos)
		return mid;
	else if (value < vec[mid])
		binary_search1(vec, first, mid - 1, value, pos);
	else
		binary_search1(vec, mid + 1, last, value, pos);
	return -1;
}

int binary_search2(vector<int>& vec, int value, int pos) {
	int length = vec.size();
	int first = 0, last = length - 1, mid;
	while (first < last) {
		mid = (first + last) / 2;
		if (vec[mid] == value && mid != pos)
			return mid;
		else if (vec[mid] < value)
			first = mid + 1;
		else
			last = mid - 1;
	}
	return -1;
}
void FindTwoElements2(vector<int> &vec, int sum) {
	sort(vec.begin(), vec.end());
	int value;
	bool found = false;
	for (int i = 0; i < vec.size(); ++i) {
		value = sum - vec[i];
		int found_pos = -1;
		/*if ((found_pos = binary_search1(vec, 0, vec.size(), value, i)) != -1)
		cout << "found: " << vec[found_pos] << " " << vec[i] << endl;*/
		if ((found_pos = binary_search2(vec, value, i)) != -1) {
			cout << "found: " << vec[found_pos] << " " << vec[i] << endl;
			found = true;
		}
	}
	if (!found)
		cout << "not found" << endl;
}

//方法三：对数组排序，然后两个指针分别从数组首尾进行遍历
//该方法找到一对符合要求的就返回
//对数组排序时间为O(nlogn),但是两个指针遍历仅需要O(n)
void FindTwoElements3(vector<int> &vec, int sum) {
	sort(vec.begin(), vec.end());
	int begin = 0, end = vec.size() - 1;
	while (begin < end) {
		if (vec[begin] + vec[end] == sum) {
			cout << "found: " << vec[begin] << " " << vec[end] << endl;
			return;
		}
		else if (vec[begin] + vec[end] > sum)
			--end;
		else
			++begin;
	}
	cout << "not found" << endl;
	return;
}

//2.12拓展：找出三个数之和
//遍历每个数组元素，对每个vec[i]调用上面的求两个数之和
//的方法：FindTwoElements2(vec, sum - vec[i]);
void FindThreeElements(vector<int>& vec, int sum) {
	for (int i = 0; i < vec.size() / 2; ++i) {
		cout << vec[i] << " ";
		FindTwoElements2(vec, sum - vec[i]);
	}
}
int main() {
	int a[] = {1,2,3,4,5,6,7,8};
	vector<int> vec(a, a + sizeof(a) / sizeof(int));
	int value;
	while (cin >> value) {
		//FindTwoElements2(vec, value);
		//FindTwoElements3(vec, value);
		FindThreeElements(vec, value);
	}
}



/********************************2.13************************************/
//例2.13子数组的最大乘积
int MaxMutiplication(int a[], int length) {
	int *array1 = new int[length];
	int *array2 = new int[length];

	//求解数组正向时的前i项积，存储在array1[i - 1]中
	array1[0] = a[0];
	for (int i = 1; i < length; ++i)
		array1[i] = array1[i- 1] * a[i];

	//求解数组逆向时的后length - i项积，存储在array2[i]中
	array2[length - 1] = a[length - 1];
	for (int i = length - 2; i >= 0; --i)
		array2[i] = array2[i + 1] * a[i];

	//初始化结果为：数组除了第一个元素外的n-1个元素的乘积
	int max_result = array2[1];  
	for (int i = 1; i < length - 1; ++i) {
		//array1[i - 1] * array2[i + 1]结果就是数组中除了下标为i的数，其他n-1个数的乘积
		if (max_result < (array1[i - 1] * array2[i + 1]))
			max_result = array1[i - 1] * array2[i + 1];
	}

        //将max_result与“除了最后一项的其他n-1项的乘积”比较
	if (max_result < array1[length - 1])
		max_result = array1[length - 1];
	return max_result;
}

int main() {
	int a[] = {1,4,6,8,-1, -10};
	cout << MaxMutiplication(a, sizeof(a) / sizeof(int)) << endl;
}

