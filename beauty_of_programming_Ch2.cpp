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
//如下的方法需要比较1.5n次：将相邻的两个元素比较；然后，
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
//方法一：
//遍历每个数组元素，对每个vec[i]调用上面的求两个数之和
//的方法：FindTwoElements2(vec, sum - vec[i]);
//该方法允许一个元素被找多次，例如main函数中：1,1,2符合sum等于4的要求
void FindThreeElements(vector<int>& vec, int sum) {
	for (int i = 0; i < vec.size() / 2; ++i) {
		cout << vec[i] << " ";
		FindTwoElements2(vec, sum - vec[i]);
	}
}

//方法二：
//不允许一个元素找多次，找到一组符合要求的就返回
void FindThreeElements2(vector<int>& vec, int sum) {
	int subsum;
	bool found = false;
	//如果数组无序先对数组排序
	sort(vec.begin(), vec.end()); 

	for (int k = 0; k < vec.size(); ++k) {
		subsum = sum - vec[k];
		int begin = 0, end = vec.size() - 1;
		while (begin < end) {
			if (begin == k)  ++begin;
			if (end == k)  --end;
			if (vec[begin] + vec[end] == subsum) {
				cout << vec[k] << " " << vec[begin] << " " << vec[end] << endl;
				++begin;
				--end;
				return;
			}
			else if (vec[begin] + vec[end] < subsum)
				++begin;
			else
				--end;
		}
	}
	cout << "not found" << endl;
}

//方法三：找出所有符合的三个数
//上面方法二是将三个数的转化为两个数的情况，这里直接遍历
//如果数据没有排序要先排序！！！
vector<vector<int> > FindThreeElements3(vector<int>& vec, int sum) {
	vector<vector<int> > result;
	sort(vec.begin(), vec.end());
	
	for (int a = 0; a < vec.size() - 2; ++a) {
		int b = a + 1, c = vec.size() - 1;
		while (b < c) {
			if (vec[a] + vec[b] + vec[c] < sum)
				++b;
			else if (vec[a] + vec[b] + vec[c] > sum)
				--c;
			else {
				vector<int> temp;
				temp.push_back(vec[a]);
				temp.push_back(vec[b]);
				temp.push_back(vec[c]);
				result.push_back(temp);
				++b;
				--c;
			}
		}
	}
	
	//去除结果集合中重复的
	sort(result.begin(), result.end());
	result.erase(unique(result.begin(), result.end()), result.end());
	return result;
}

//2.12拓展二：找出一个数组中最接近一个给定target的三个数
//上面的拓展中，一定存在a+b+c等于sum，这里要求的是最接近的
//函数返回最接近target的sum值
//如果数据没有排序要先排序！！！
int FindThreeClosest(vector<int>& vec, int target) {
	int result;  //记录最终的sum，即最接近target的三数和
	int min_gap = INT_MAX;  //记录target与sum的最小差值
	vector<int> result_elements(3, 0); //记录最终的三个数
	sort(vec.begin(), vec.end());
	
	for (int a = 0; a < vec.size() - 2; ++a) {
		int b = a + 1, c = vec.size() - 1;
		while (b < c) {
			int sum = vec[a] + vec[b] + vec[c];
			int gap = abs(sum - target);
			if (gap < min_gap) {
				result = sum;
				//更新三个数
				result_elements[0] = vec[a];
				result_elements[1] = vec[b];
				result_elements[2] = vec[c];
				min_gap = gap;
			}
			if (sum < target)  ++b;
			else   --c;
		}
	}
	cout << result_elements[0] << " " << result_elements[1] << " " 
		<< result_elements[2] << " sum: ";
	return result;
}


////2.12拓展三：找出一个数组中和等于target的四个数
//有多个时符合要求的情况，打印所有的情况
//方法一：
//先排序，然后前后指针，时间O(n^3)
void PrintFourElementsResult(vector<vector<int> >& result);
vector<vector<int> > FindFourElements(vector<int>& vec, int target) {
	vector<vector<int> > result;
	if (vec.size() < 4) //元素个数小于四个直接返回空
		return result;

	sort(vec.begin(), vec.end());

	for (int a = 0; a < vec.size() - 3; ++a) {
		for (int b = a + 1; b < vec.size() - 2; ++b) {
			int c = b + 1;
			int d = vec.size() - 1;
			while (c < d) {
				if (vec[a] + vec[b] + vec[c] + vec[d] < target)
					++c;
				else if (vec[a] + vec[b] + vec[c] + vec[d] > target)
					--d;
				else {
					vector<int> temp;
					temp.push_back(vec[a]);
					temp.push_back(vec[b]);
					temp.push_back(vec[c]);
					temp.push_back(vec[d]);
					result.push_back(temp);
					++c;
					--d;
				}
			}
		}
	}
	//去除结果集合中重复的
	sort(result.begin(), result.end());
	result.erase(unique(result.begin(), result.end()), result.end());
	return result;
}

////2.12拓展三：找出一个数组中和等于target的四个数
//有多个时情况时，打印所有的情况
//方法二：使用map
//先排序，然后将两个数的和缓存
//时间复杂度平均O(n^ 2),最坏O(n ^ 4);空间O(n^2)
vector<vector<int> > FindFourElements2(vector<int>& vec, int target) {
	vector<vector<int> > result;
	if (vec.size() < 4)
		return result;
	sort(vec.begin(), vec.end());

	//map用于缓存两个数的和，键：两数的和；值：这两个数的下标
	map<int, vector<pair<int, int> > > cache;
	for (int a = 0; a < vec.size(); ++a) {
		for (int b = a + 1; b < vec.size(); ++b)
			cache[vec[a] + vec[b]].push_back(make_pair(a, b));
	}

	for (int c = 0; c < vec.size(); ++c) {
		for (int d = c + 1; d < vec.size(); ++d) {
			int key = target - vec[c] - vec[d];

			//如果当前的两个数之和与cache中两数之和的和不符合要求，继续
			if (cache.find(key) == cache.end())
				continue;

			vector<pair<int, int> > temp_vec = cache[key];
			for (int k = 0; k < temp_vec.size(); ++k) {
				if (c <= temp_vec[k].second)
					continue;  //有重叠
				vector<int> temp;
				temp.push_back(vec[temp_vec[k].first]);
				temp.push_back(vec[temp_vec[k].second]);
				temp.push_back(vec[c]);
				temp.push_back(vec[d]);
				result.push_back(temp);
			}
		}
	}
	
	//去除结果集中重复的
	sort(result.begin(), result.end());
	result.erase(unique(result.begin(), result.end()), result.end());
	return result;
}

////2.12拓展三：找出一个数组中和等于target的四个数
//有多个时，打印所有的情况
//方法三：使用multimap
//先排序，然后将两个数的和缓存
//时间复杂度平均O(n^ 2);空间O(n^2)
//该函数用于输出四个数时的结果
vector<vector<int> > FindFourElements3(vector<int>& vec, int target) {
	vector<vector<int> > result;
	if (vec.size() < 4)
		return result;
	sort(vec.begin(), vec.end());

	//multimap存放两个数和，以及两个数的下标
	multimap<int, pair<int, int> > cache;
	for (int a = 0; a < vec.size() - 1; ++a) {
		for (int b = a + 1; b < vec.size(); ++b)
			cache.insert(make_pair(vec[a] + vec[b], make_pair(a, b)));
	}

	//取出cache中两个和，如果这两个和的和等于target，而且组成这两对和
	//的四个数互不相同（它们的下标不同），则这四个数就是符合的一个解
	multimap<int, pair<int, int> >::iterator iter;
	for (iter = cache.begin(); iter != cache.end(); ++iter) {
		int subsum = target - iter->first; 
		typedef multimap<int, pair<int,int> >::iterator mul_iter;

		//从cache中找到符合subsum + iter->first等于target的四个数
		pair<mul_iter, mul_iter> range = cache.equal_range(subsum);

		mul_iter iter_in;
		for (iter_in = range.first; iter_in != range.second; ++iter_in) {
			int a = iter->second.first;
			int b = iter->second.second;
			int c = iter_in->second.first;
			int d = iter_in->second.second;
			if (a != c && a != d && b != c && b != d) {
				vector<int> temp;
				temp.push_back(vec[a]);
				temp.push_back(vec[b]);
				temp.push_back(vec[c]);
				temp.push_back(vec[d]);
				//注意这里先将符合要求的四个数排序，以便下边删除重复的
				sort(temp.begin(), temp.end());
				result.push_back(temp);
			}
		}
	}
	sort(result.begin(), result.end());
	result.erase(unique(result.begin(), result.end()), result.end());
	return result;
}

//该函数用于输出满足条件的四个数的结果集合
void PrintFourElementsResult(vector<vector<int> >& result) {
	if (result.size() == 0)
		cout << "not found" << endl;
	vector<vector<int> >::iterator iter = result.begin();
	while (iter != result.end()) {
		vector<int>::iterator iter_in = (*iter).begin();
		while (iter_in != (*iter).end())
			cout << *iter_in++ << " ";
		cout << endl;
		++iter;
	}
}

int main() {
	int a[] = {1,2,3,4,5,6,7,8,9,10,11};
	vector<int> vec(a, a + sizeof(a) / sizeof(int));
	int value;
	while (cin >> value) {
		//FindTwoElements2(vec, value);
		//FindTwoElements3(vec, value);
		//FindThreeElements2(vec, value);

		//vector<vector<int> > result = FindThreeElements3(vec, value);
		//PrintFourElementsResult(result);

		//int result = FindThreeClosest(vec, value);
		//cout << result << endl;

		//vector<vector<int> > result1 = FindFourElements(vec, value);
		//PrintFourElementsResult(result1);
		//cout << endl;

		vector<vector<int> > result = FindFourElements2(vec, value);
		PrintFourElementsResult(result);
		cout << endl;

		vector<vector<int> > result2 = FindFourElements3(vec, value);
		PrintFourElementsResult(result2);
		cout << endl;
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



/********************************2.16************************************/
//2.16求数组中最长递增子序列 
//http://blog.csdn.net/u013074465/article/details/45442067
//方法一：O(n^ 2)
int LIS(vector<int>& vec) {
	vector<int> longest(vec.size(), 1);
	for (int i = 1; i < vec.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			if (vec[j] < vec[i] && longest[i] < longest[j] + 1)
				longest[i] = longest[j] + 1; 
		}
	}

	int max = longest[0];
	for (int i = 0; i < longest.size(); ++i) {
		if (max < longest[i])
			max = longest[i];
	}
	return max;
}

/*方法二：O(nlogn)
本解法的具体操作如下：
建立一个辅助数组array，依次读取数组元素 x 与数组末尾元素 top比较： 
如果 x > top，将 x 放到数组末尾；
如果 x < top，则二分查找数组中第一个 大于等于x 的数，并用 x 替换它。
遍历结束之后，最长递增序列长度即为栈的大小。

注意c数组的下标代表的是子序列的长度，c数组中的值也是按递增顺序排列的。这才可能用二分查找。

数组array[i]存储的是子序列长度为i的序列最后一个值（该值是该子序列中最大的元素；
如果长度为i的序列有多个，那么array[i]存放这类序列最后元素中的最小一个）
*/
int LIS2(vector<int>& vec) {
	vector<int> temp;
	for (int i = 0; i < vec.size(); ++i) {
		if (temp.empty() || temp.back() < vec[i])
			temp.push_back(vec[i]);
		else {
			int begin = 0, end = temp.size() - 1;
			while (begin < end) {
				int mid = (begin + end) / 2;
				if (temp[mid] < vec[i])
					begin = mid + 1;
				else
					end = mid - 1;
			}
			temp[begin] = vec[i];
		}
	}
	return temp.size();
}

int main() {
	int a[] = {1,-1,2,-3,4,-5,6,-7};
	int a2[] = { 3,5,7,1,2,8};
	vector<int> vec1(a, a + sizeof(a) / sizeof(int));
	vector<int> vec2(a2, a2 + sizeof(a2) / sizeof(int));
	cout << LIS(vec1) << " " << LIS(vec2) << endl;
	cout << LIS2(vec1) << " " << LIS2(vec2) << endl;
}


/********************************2.17************************************/
//2.17数组循环位移
//将“I am a student”翻转为“student a am I”此题方法类似
void reverse(char *str, int begin, int end) {
	for ( ; begin < end; ++begin, --end) {
		char temp = str[begin];
		str[begin] = str[end];
		str[end] = temp;
	}
	return;
}

void RightShiftK(char *str, int length, int k) {
	if (NULL == str || k == 0)
		return;
	if (k < 0)
		k = length + k;
	k = k % length;

	reverse(str, 0, length - k - 1);
	reverse(str, length - k, length - 1);
	reverse(str, 0, length - 1);
}

int main() {
	char str[] = "123abcd";
	RightShiftK(str, strlen(str), -2);
	cout << str << endl;
}

/********************************2.19************************************/
//2.19区间重合判断
//http://blog.csdn.net/linyunzju/article/details/7737060
//该函数用于sort函数中，比较两个区间大小，以便对区间排序
//排序复杂度O(nlogn)
bool Compare(pair<int, int>& p1, pair<int, int>& p2) {
	if (p1.first < p2.first)
		return true;
	else if (p1.first == p2.first && p1.second < p2.second)
		return true;
	return false;
}

//在合并后的区间内二分查找，如果待查找区间在合并后某区间内，那么即符合要求，
//函数返回true，否则返回false
//vec的前n个容器存储合并后的区间，section存储待查找的区间
//查找复杂度O(logn)
bool BinarySearch(vector<pair<int, int> >& vec, int n, pair<int, int>& section) {
	int left = 0, right = n - 1, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (section.first < vec[mid].first)
			right = mid - 1;
		else if (section.second > vec[mid].second)
			left = mid + 1;
		else if (section.first >= vec[mid].first && section.second <= vec[mid].second)
			return true;
	}
	return false;
}

//对vec内的区间排序，然后二分查找，找到true，否则false
//合并后的区段一共有count个，存储在vec的前count个元素中
bool MatchSection(vector<pair<int, int> > &vec, pair<int, int>& section) {
	sort(vec.begin(), vec.end(), Compare);  

	int section_end = vec[0].second;
	int count = 0;       //记录合并后区间的下标
	for (int i = 1; i < vec.size(); ++i) {
		if (section_end >= vec[i].first)
			section_end = vec[i].second;
		else {
			vec[count++].second = section_end;
			vec[count].first = vec[i].first;
			section_end = vec[i].second;
		}
	}
	vec[count++].second = section_end;

	cout << "输入合并区间后的vector的内容，验证：" << endl;
	vector<pair<int, int> >::iterator iter = vec.begin();
	while (iter != vec.end()) {
		cout << (*iter).first << " " << (*iter).second << endl;
		++iter;
	}
	return BinarySearch(vec, count, section);
} 

int main() {
	vector<pair<int,int> > vec;
	vec.push_back(make_pair(2,3));
	vec.push_back(make_pair(1,2));
	vec.push_back(make_pair(4,9));

	if (MatchSection(vec, make_pair(1, 6)))
		cout << "ok" << endl;
	else
		cout << "no" << endl;

	return 0;
}
