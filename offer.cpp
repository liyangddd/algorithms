#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

int GreatestSumOfSubarrays2(int *array, int length) {
	int sum = array[0];
	int maxsum = array[0];
	for (int i = 1; i < length; ++i) {
		if (sum <= 0)
			sum = array[i];
		else
			sum += array[i];
		if (sum > maxsum)
			maxsum = sum;
	}
	return maxsum;
}

int GreatestSumOfSubarrays(int *array, int length) {
	int sum = 0;
	int maxsum = 0x80000000;
	for (int i = 0; i < length; ++i) {
		if (sum <= 0)
			sum = array[i];
		else
			sum += array[i];
		if (sum > maxsum)
			maxsum = sum;
	}
	return maxsum;
}

//int main() {
//	int array[] = {5, -2, -3, 9, -1, 2};
//	cout << GreatestSumOfSubarrays(array, sizeof(array) / sizeof(int)) << " " << 
//		GreatestSumOfSubarrays2(array, sizeof(array) / sizeof(int)) << endl;
//}

//KMP算法
void GetNext(char* p,int next[]) {  
	int pLen = strlen(p);  
	next[0] = -1;  
	int k = -1;  
	int j = 0;  
	while (j < pLen - 1) {  
		//p[k]表示前缀，p[j]表示后缀  
		if (k == -1 || p[j] == p[k]) {  
			++k;  
			++j;  
			next[j] = k;  
		}  
		else {  
			k = next[k];  
		}  
	}  
}  
int KmpSearch(char* s, char* p) {  
	int i = 0;  
	int j = 0;  
	int sLen = strlen(s);  
	int pLen = strlen(p);
	int *next = new int[pLen];
	GetNext(p, next);
	while (i < sLen && j < pLen) {  
		//①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++      
		if (j == -1 || s[i] == p[j]) {  
			i++;  
			j++;  
		}  
		else {  
			//②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]      
			//next[j]即为j所对应的next值        
			j = next[j];  
		}  
	}  
	delete[] next;
	if (j == pLen)  
		return i - j;  
	else  
		return -1;  
}  

//int main() {
//	char str[100] = {'\0'};
//	char substr[100] = {'\0'};
//	scanf("%s %s", str, substr);
//	cout << KmpSearch(str, substr) << endl;
//}

//strstr函数
char *strStr(const char *str, const char *substr) {
	if (substr == NULL || str == NULL)
		return NULL;
	if (!*substr)
		return const_cast<char*>(str);
	const char *p1 = str;
	const char *p2 = substr;
	const char *p1_advance = str;
	//p1_advance指针前进strlen(substr)-1位
	//因为当str中还未匹配的位数小于substr的长度时，肯定不可能再匹配成功了
	for (p2 = substr + 1; *p2; ++p2)
		++p1_advance;

	for (p1 = str; *p1_advance; p1_advance++) {
		char *p1_old = (char *)p1;
		p2 = substr;
		while (*p1 && *p2 && *p1 == *p2) {
			++p1;
			++p2;
		}
		if (!*p2)
			return p1_old;
		p1 = p1_old + 1;
	}
	return NULL;
}

//int main() {
//	char str[100] = {'\0'};
//	char substr[100] = {'\0'};
//	scanf("%s %s", str, substr);
//	if (strStr(str, substr) != NULL)
//		printf("true\n");
//	else
//		printf("false\n");
//}

//////////////////////////////////////////////////////////////////
//itoa函数
char* myitoa(int value, char* result, int base) {
	if (base < 2 || base > 36) { *result = '\0'; return result; }
	char string[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	bool minus = false;
	if (value < 0) {
		minus = true;
		value = -value;
	}
	char* ptr = result, *ptr1 = result, tmp_char;
	do {
		cout << "\t" << value % base << endl;
		*ptr++ = string[value % base];
		value /= base;
	} while ( value );
	
	if (minus) {
		*ptr++ = '-';
	}
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}
/**
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukás Chmela
	 * Released under GPLv3.

	 */
	char* lastest_itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}

//int main() {
//	int a;
//	while (true) {
//		cin >> a;
//		cout << -a << endl;
//		char test[36];
//		//cout << itoa(a, test, 2) << endl; //windows的itoa函数
//		cout << myitoa(a, test, 2) << endl; //上述itoa函数
//		//cout << lastest_itoa(a, test, 2) << endl << endl;
//	}
//}

//////////////////////////////////////////////////////////////////
//P250:StrToInt(atoi)
bool flag = false;
int StrToInt(char *str) {
	int minus = false;
	long long result = 0;
	if (str != NULL && *str != '\0') {
		if (*str == '-') {
			minus = true;
			++str;
		}
		else if (*str == '+')
			++str;

		if (*str != '\0') //判断字符串仅为一个“-”或“+”的情况
		{  
			while (*str != '\0') 
			{
				if (*str >= '0' && *str <= '9') 
				{
					int minus_flag = minus ? -1 : 1;
					//result = result * 10 + minus_flag * (*str - '0');
					result = result * 10 + minus_flag * (*str - '0');
					if ((!minus && result > 0x7FFFFFFF) ||
						(minus && result < (signed int)0x80000000)) {
							result = 0;
							break;
					}
					++str;
				}
				else {
					result = 0;
					break;
				}
			}
			if (*str == '\0')
				flag = true;
		}
	}
	return (int)result;
}

class Solution {
public:
	int atoi(const char *str) {
		int num = 0;
		int sign = 1;
		const int n = strlen(str);
		int i = 0;
		while (str[i] == ' ' && i < n) i++;
		if (str[i] == '+') {
			i++;
		} else if (str[i] == '-') {
			sign = -1;
			i++;
		}
		for (; i < n; i++) {
			if (str[i] < '0' || str[i] > '9')
				break;
			if (num > INT_MAX / 10 ||
				(num == INT_MAX / 10 &&
				(str[i] - '0') > INT_MAX % 10)) {
					return sign == -1 ? INT_MIN : INT_MAX;
			}
			num = num * 10 + str[i] - '0';
		}
		return num * sign;
	}
};
////32位系统最大正整数：2147483647(2^31 - 1)
//int main() {
//	string str;
//	char test[20] = {'\0'};
//	while (true) {
//		cin >> str;
//		sprintf(test, str.c_str());
//		Solution sl;
//		cout << sl.atoi(test) << endl;
//		cout << StrToInt(test) << endl << endl;
//	}
//}
//T8
int Min(int *numbers, int length) {
	if (numbers == NULL || length <= 0)
		throw exception("Invalid parameters");

	int first = 0;
	int last = length;
	int mid = first;
	if (numbers[first] < numbers[last - 1])
		return 0;
	while (first != last) {
		mid = (first + last) / 2;
		if (last - first == 1) {
			mid = last;
			break;
		}
		if (numbers[first] <= numbers[mid])
			first = mid;
		else if (numbers[last] >= numbers[mid])
			last = mid;
	}
	return mid;
}

int Min2(int *numbers, int length) {
	int index1 = 0;
	int index2 = length - 1;
	int indexMid = index1;
	while (numbers[index1] >= numbers[index2]) {
		if (index2 - index1 == 1) {
			indexMid = index2;
			break;
		}
		indexMid = (index1 + index2) / 2;
		if (numbers[indexMid] >= numbers[index1])
			index1 = indexMid;
		else if (numbers[indexMid] <= numbers[index2])
		    index2 = indexMid;
	}
	return numbers[indexMid];
}

int MinInOrder(int* numbers, int index1, int index2)
{
	int result = numbers[index1];
	for(int i = index1 + 1; i <= index2; ++i)
	{
		if(result > numbers[i])
			result = numbers[i];
	}

	return result;
}
int Min3(int* numbers, int length)
{
	if(numbers == NULL || length <= 0)
		throw new std::exception("Invalid parameters");

	int index1 = 0;
	int index2 = length - 1;
	int indexMid = index1;
	while(numbers[index1] >= numbers[index2])
	{
		// 如果index1和index2指向相邻的两个数，
		// 则index1指向第一个递增子数组的最后一个数字，
		// index2指向第二个子数组的第一个数字，也就是数组中的最小数字
		if(index2 - index1 == 1)
		{
			indexMid = index2;
			break;
		}

		// 如果下标为index1、index2和indexMid指向的三个数字相等，
		// 则只能顺序查找
		indexMid = (index1 + index2) / 2;
		if(numbers[index1] == numbers[index2] && numbers[indexMid] == numbers[index1])
			return MinInOrder(numbers, index1, index2);

		// 缩小查找范围
		if(numbers[indexMid] >= numbers[index1])
			index1 = indexMid;
		else if(numbers[indexMid] <= numbers[index2])
			index2 = indexMid;
	}

	return numbers[indexMid];
}
//int main() {
//	//int a[] = {6,7,8,9,0,1,2};
//	//int a[] = {0,1,2,9};
//	int a[] = {9,7,6,4,1};
//	int len = sizeof(a) / sizeof(int);
//	cout << Min2(a, len) << endl;
//}

/*
//T4
void reassemble_array(int arr1[], int len1, int arr2[], int len2) {
	int i = len1 - 1;
	int j = len2 - 1;
	int index_new = len1 + len2 - 1;
	if (arr1 == NULL || arr2 == NULL)
		return;
	while (i >= 0 && j >= 0) {
		if (arr1[i] > arr2[j]) {
			arr1[index_new--] = arr1[i--];
		}
		else if (arr1[i] < arr2[j]) {
			arr1[index_new--] = arr2[j--];
		}
	    else if (arr1[i] == arr2[j]) {
			arr1[index_new--] = arr2[j--];
		}
		cout << index_new << endl;
	}
	while (i >= 0) {
		arr1[index_new--] = arr1[i--];
	}
	while (j >= 0) {
		arr1[index_new--] = arr2[j--];
	}
}
int main() {
	int a[100];
	int b[] = {3,4,7,8,9,10, 20, 300};
	reassemble_array(a, 0, b, sizeof(b) / sizeof(int));
	int i = 0;
	while (i != 100) {
		cout << a[i++] << " ";
	}
}
*/
/*
//T4
void ReplaceBlank(char str[], int all_len) {
	int i = 0;
	int len = 0;
	int count_blank = 0;
	if (str == NULL || all_len <= 0) {
		cout << "1" << endl;
		return;
	}
	while (str[i] != '\0') {
		++len;
		if (str[i] == ' ')
			++count_blank;
		++i;
	}
	if (count_blank == 0) {
		cout << "2" << endl;
		return;
	}

	int len2 = len + count_blank * 2;
	if (len2 > all_len) {
		cout << "3" << endl;
		return;
	}
	int index_new = len2;
	int index_orig = len;
	while (index_orig >= 0 && index_new > index_orig) {
		if (str[index_orig] == ' ') {
			str[index_new--] = '0';
			str[index_new--] = '2';
			str[index_new--] = '%';
		}
		else {
			str[index_new--] = str[index_orig];
		}
		--index_orig;
	}
	str[len2] = '\0';
}
int main() {
	char test[100] = "aaaa";
	ReplaceBlank(test, 100);
	cout << test << endl;
}
*/