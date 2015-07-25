/*
《编程之美》代码
*/

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

