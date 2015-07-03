#include "test.h"

int MaxSubSequenceSum1(const int test[], int N) {
	int startTime = GetTickCount();
	int ThisSum, MaxSum, i, j, k;
	MaxSum = 0;
	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			ThisSum = 0;
			for (k = i; k <= j; k++)
				ThisSum += test[k];
			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	int endTime = GetTickCount();
	cout << "1 time: " << endTime - startTime;
	return MaxSum;
}

int MaxSubSequenceSum2(const int test[], int N) {
	int startTime = GetTickCount();
	int ThisSum, MaxSum, i, j;
	MaxSum = 0;
	for (i = 0; i < N; i++) {
		ThisSum = 0;
		for (j = i; j < N; j++) {
			ThisSum += test[j];

			if (ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	int endTime = GetTickCount();
	cout << "2 time: " << endTime - startTime;
	return MaxSum;
}

int Max3(const int a, const int b, const int c) {
	int max = a;
	int max2 = ((c > b) ? c : b);
	if (max2 > max)
		max = max2;
	return max;
}
int MaxSubSum(const int test[], int Left, int Right) {
	int MaxLeftSum, MaxRightSum;
	int MaxLeftBorderSum, MaxRightBorderSum;
	int LeftBorderSum, RightBorderSum;
	int Center, i;

	if (Left == Right)
		if (test[Left] > 0)
			return test[Left];
		else
			return 0;

	Center = (Left + Right) / 2;
	MaxLeftSum = MaxSubSum(test, Left, Center);
	MaxRightSum = MaxSubSum(test, Center + 1, Right);

	MaxLeftBorderSum = 0;
	LeftBorderSum = 0;
	for (i = Center; i >= Left; i--) {
		LeftBorderSum += test[i];
		if (LeftBorderSum > MaxLeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;
	}

	MaxRightBorderSum = 0;
	RightBorderSum = 0;
	for (i = Center + 1; i <= Right; i++) {
		RightBorderSum += test[i];
		if (RightBorderSum > MaxRightBorderSum)
			MaxRightBorderSum = RightBorderSum;
	}
	return Max3(MaxLeftSum, MaxRightSum, MaxRightBorderSum + MaxLeftBorderSum);
}

int MaxSubSequenceSum3(const int test[], int N) {
	int startTime = GetTickCount();
	int r = MaxSubSum(test, 0, N-1);
	int endTime = GetTickCount();
	cout << "3 time: " << endTime - startTime;
	return r;
}

int MaxSubSequenceSum4(const int test[], int N) {
	int startTime = GetTickCount();
	int ThisSum, MaxSum, j;
	ThisSum = 0;
	MaxSum = 0;
	for (j = 0; j < N; j++) {
		ThisSum += test[j];
		if (ThisSum > MaxSum)
			MaxSum = ThisSum;
		else if (ThisSum < 0)
			ThisSum = 0;
	}
	int endTime = GetTickCount();
	cout << "4 time: " << endTime - startTime;
	return MaxSum;
}
/*
int main() {
	int test1[800] = {44, -11, 33, -3, -9, 3};
	int test2[8000] = {44, -11, 33, -3, -9, 3};
	int test3[80000] = {44, -11, 33, -3, -9, 3};
	int test4[80000] = {44, -11, 33, -3, -9, 3};
	int result1, result2, result3, result4;
	result1 = MaxSubSequenceSum1(test1, sizeof(test1) / sizeof(int));
	cout << " " << result1 << endl;
	result2 = MaxSubSequenceSum2(test2, sizeof(test2) / sizeof(int));
	cout << " " << result2 << endl;
	result3 = MaxSubSequenceSum3(test3, sizeof(test3) / sizeof(int));
	cout << " " << result3 << endl;
	result4 = MaxSubSequenceSum4(test4, sizeof(test4) / sizeof(int));
	cout << " " << result4 << endl;
	return 0;
}
*/