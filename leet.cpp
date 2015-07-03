#include <string>
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;

class Solution2 {
public:
	int removeDuplicates2_1_1(int array[], int n) {
		if (n == 0)
			return 0;
		int index = 0;
		for (int i = 1; i < n; i++) {
			if (array[index] != array[i])
				array[++index] = array[i];
		}
		return index + 1;
	}

	int removeDuplicates2_1_1_2(int array[], int n) {
		return distance(array, unique(array, array + n));
	}

	int removeDuplicates2_1_2_1(int array[], int n) {
		if (n <= 2) {
			return n;
		}

		int index = 2;
		for (int i = 2; i < n; i++) {
			if (array[i] != array[index - 2])
				array[index++] = array[i];
		}
		return index;
	}

	int removeDuplicates2_1_2_2(int array[], int n) {
		int index = 0;
		for (int i = 1; i < n; i++) {
			if (i < n - 1 && array[i] == array[i - 1] &&
				array[i] == array[i + 1])
				continue;
			array[index++] = array[i];

		}
		return index;
	}

	int Search2_1_3(int array[], int n, int target) {
		int first = 0, last = n;
		while (first != last) {
			const int mid = (first + last) / 2;
			if (array[mid] == target)
				return mid;
			if (array[first] <= array[mid]) {
				if (array[first] <= target && target < array[mid])
					last = mid;
				else
					first = mid + 1;
			}
			else {
				if (array[mid] < target && target <= array[last -1])
					first = mid + 1;
				else
					last = mid;
			}
		}
		return -1;
	}

int find_kth2_1_5(int A[], int m, int B[], int n, int k) {
		if (m > n)
			return find_kth2_1_5(B, n, A, m, k);
		if (m == 0)
			return B[k - 1];
		if (k == 1)
			return (A[0] < B[0] ? A[0] : B[0]);

		int ia = k / 2 < m ? k / 2 : m, ib = k - ia;
		if (A[ia - 1] < B[ib - 1])
			return find_kth2_1_5(A + ia, m - ia, B, n, k - ia);
		else if (A[ia - 1] > B[ib - 1])
			return find_kth2_1_5(A, m, B + ib, n - ib, k - ib);
		else
			return A[ia - 1];
	}
};

//int main() {
//	Solution2 s;
//	int a[] = {9,19,20,200};
//	int b[] = {3,6,7};
//	int k;
//	cin >> k;
//	int lena = sizeof(a) / sizeof(int);
//	int lenb = sizeof(b) / sizeof(int);
//	cout << s.find_kth2_1_5(a, lena, b, lenb, k) << endl;
//}