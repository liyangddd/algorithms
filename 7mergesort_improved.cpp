//空间复杂度为O(1)的归并排序
#include <iostream>
using namespace std;

void reverse_array(int a[], int n) {
	int i = 0;
	int j = n - 1;
	while (i < j) {
		swap(a[i], a[j]);
		++i;
		--j;
	}
}

void exchange(int a[], int length, int length_left) {
	reverse_array(a, length_left);
	reverse_array(a + length_left, length - length_left);
	reverse_array(a, length);
}

void Merge(int a[], int begin, int mid, int end) {
	while (begin < mid && mid <= end) {
		int step = 0;
		while (begin < mid && a[begin] <= a[mid])
			++begin;
		while (mid <= end && a[mid] <= a[begin]) {
			++mid;
			++step;
		}
		exchange(a + begin, mid - begin, mid - begin - step);
	}
}
void MergeCore(int a[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeCore(a, left, mid);
		MergeCore(a, mid + 1, right);
		Merge(a, left, mid + 1, right);
	}
}
void MergeSort(int a[], int length) {
	if (a == NULL || length < 1)
		return;
	MergeCore(a, 0, length - 1);
}

int main() {
	int a[] = {1,0,2,9,3,8,4,7,6,5,11,99,22,88,11};
	int length = sizeof(a) / sizeof(int);
	MergeSort(a, length);
	
	for (int i = 0; i < length; i++)
		cout << a[i] << " ";
	cout << endl;
	return 0;
}
