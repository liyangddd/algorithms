//位图排序
#include <iostream>
#include <bitset>
#define WIDTHWORD 32 //一个整数的宽度是32bit
#define SHIFT 5      
#define MASK 0x1F
#define N 100//对十万个无重复的整数排序
using namespace std;

//bitmap
int bitmap[1 + N / WIDTHWORD];

//将bitmap的第value设置为1
void set(int value) {
	bitmap[value >> SHIFT] |= (1 << (value & MASK));
}

//清除bitmap第value位上的1:设置为0
void clear(int value) {
	bitmap[value >> SHIFT] &= ~(1 << (value & MASK));
}

//测试bitmap第value位是否为1
int test(int value) {
	return bitmap[value >> SHIFT] & (1 << (value & MASK));
}

//int main() {
//	int a[] = {12, 5, 1, 89, 64, 49, 77, 91, 3, 0, 32, 50, 99};
//	int length = sizeof(a) / sizeof(int);
//
//	//C语言方式：
//	//将bitmap所有位设置为0
//	for (int i = 0; i < N; ++i) {
//		clear(i);
//	}
//	//bitmap中将待排序数组中值所在的位设置为1
//	for (int i = 0; i < length; i++)
//		set(a[i]);
//	//输出排序后的结果
//	for (int i = 0; i < N; ++i) {
//		if (test(i))
//			cout << i << " ";
//	}
//	
//	////C++方式：
//	////直接使用C++bitset，申请Nbit的空间，每一位均设置为0
//	//bitset<N> bitmap; 
//
//	////遍历待排序数组，将bitmap中对应位设置为1
//	//for (int i = 0; i < length; i++)
//	//	bitmap.set(a[i], 1);
//
//	////输入排序结果
//	//for (int i = 0; i < N; ++i) {
//	//	if (bitmap[i])
//	//		cout << i << " ";
//	//}
	
//	////假设还是有小于100的不重复整数需要排序，但是
//	////不能申请100位空间，只能申请30位空间，那么，需要
//	////排序的次数如下：
//	//int sort_times = N / 30 + 1;
//
//	//bitset<30> bitmap; //只能申请30位的bitmap
//
//	////那么，四趟排序：第一趟先排序0-29，第二趟排序30-59，
//	////第三趟排序60-89，第四趟排序剩下的。
//	//for (int times = 0; times < sort_times; ++times) {
//	//	bitmap.reset();    //记得每次排序前将bitmap清空为0
//	//	for (int i = 0; i < length; i++) {
//	//		if (a[i] >= 30 * times && a[i] < 30 * (times + 1))
//	//			bitmap.set(a[i] - 30 * times);
//	//	}
//
//	//	for (int i = 0; i < 30; ++i) {
//	//		if (bitmap[i]) {
//	//			cout << i + 30 * times << " ";
//	//		}
//	//	}
//	//}
//	
//}
