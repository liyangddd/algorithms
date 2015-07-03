#include "test.h"

//该程序未完成
int const N = 10;
int RandInt() {
	srand( (unsigned)time( NULL ) );
	cout << rand() % N << endl;
	return 0;
}

int test1() {
	int test[N] = {-1};
	int used[N] = {0};
	int result = RandInt();
	test[0] = result;
	used[result] = 1;
	int i;
	for (i = 1; i < N; i++) {
		while (result = RandInt() && used[result] != 1 ) {
			test[i] = result;
			used[result] = 1;
		}
	}

	for (i = 0; i < N; i++)
		cout << test[i] << " ";
	cout << endl;
	return 0;
}
/*
int main() {
	test1();
	return 0;
}
*/