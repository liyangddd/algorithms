/*
《编程之美》代码
*/

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


//例2.13子数组的最大乘积
int MaxMutiplication(int a[], int length) {
	int *array1 = new int[length];
	int *array2 = new int[length];

	//求解数组正向时的前i项和，存储在array1[i]中
	array1[0] = a[0];
	for (int i = 1; i < length; ++i)
		array1[i] = array1[i- 1] * a[i];

	//求解数组逆向时的后length - i项和，存储在array2[i]中
	array2[length - 1] = a[length - 1];
	for (int i = length - 2; i >= 0; --i)
		array2[i] = array2[i + 1] * a[i];

	//初始化结果为：数组除了第一个元素外的n-1个元素的乘积
	int max_result = array2[1];  
	for (int i = 1; i < length - 1; ++i) {
		if (max_result < (array1[i - 1] * array2[i + 1]))
			max_result = array1[i - 1] * array2[i + 1];
	}

	if (max_result < array1[length - 1])
		max_result = array1[length - 1];
	return max_result;
}

int main() {
	int a[] = {1,4,6,8,-1, -10};
	cout << MaxMutiplication(a, sizeof(a) / sizeof(int)) << endl;
}

