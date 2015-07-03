#include "test.h"
#define MAXLEN 11
//********算法导论，动态规划，钢条分割，P205
//自底向上，仅记录最优解结果
int ButtomUpCutRod(int priceList[], int n) {
	int highest[MAXLEN] = {-1}; //记录每个长度对应的最优解
	highest[0] = 0;             //长度为0的最优解（最大利润）为0
	int j = 0;
	for (j = 1; j <= n; j++) {  
		int highest_j = -1;     //长度为j的最优解
		int i;
		for (i = 1; i <= j; i++) 
			//长度为i的最右解为不切割时，或者为切割长度为i的利润加上长度为j-i的最优解
			highest_j = max(highest_j, priceList[i] + highest[j - i]);
		highest[j] = highest_j;  //记录长度为j的最优解值
	}
	return highest[n];
}

//该函数计算长度为n的钢条的最大利润
int MemorizedCutRod_aux(int priceList[], int n, int highest[]) {
	int highest_n = -1;
	if (highest[n] >= 0)  //如果长度为n的最优解已经被记录了，就直接返回
		return highest[n];  
	if (n == 0)           //长度为0的钢条利润为0
		highest_n = 0;
	else {                //还未记录钢条的利润，则计算之
		int i;
		for (i = 1; i <= n; i++)
			//长度为n的钢条最大利润为不切割，或者为切割长度i的利润加上长苏为n-i的最大利润
			highest_n = max(highest_n, priceList[i] + MemorizedCutRod_aux(priceList, n-i, highest));
	}
	highest[n] = highest_n; //记录长度为n的最大利润
	return highest_n;
}
//自顶向下，仅记录最优解结果
int MemorizedCutRod(int priceList[], int n) {
	int highest[11];
	int i;

	//初始化最大利润列表
	for (i = 0; i < MAXLEN; i++)
		highest[i] = -1;
	return MemorizedCutRod_aux(priceList, n, highest);
}


pair<vector<int>, vector<int> > ButtomUpCutRodSolution(vector<int> &priceList, int n) {
	vector<int> highest; //每个元素依次记录长度递增的钢条最优解结果
	vector<int> solution(priceList.size());  //记录长度为n的钢条的解决方案
	int highest_j = -1;
	highest.push_back(0); //长度为0的钢条最优解为0
	int j;
	for (j = 1; j <= n; j++) {  //依次求长度为1直到长度为n的钢条的最优解
		highest_j = -1;
		int i;
		for (i = 1; i <= j; i++) {  //长度为j的钢条最优解的计算
			if (highest_j < priceList[i] + highest[j - i]) { 
				highest_j = priceList[i] + highest[j - i];
				solution[j] = i;  //记录切割中取得最优解的切割长度
			}
		}
		highest.push_back(highest_j); //记录长度为j的钢条的最优解
	}
	return make_pair(highest, solution);
}
//该算法不仅输出最优解，而且给出最优解的一个切割方案
void printSolution(vector<int> &priceList, int n) {
	pair<vector<int>, vector<int> > ivec  = ButtomUpCutRodSolution(priceList, n);
	cout << "highest price3: " << ivec.first.at(n); //输出最优解
	vector<int> solu = ivec.second;
	cout << "     solution: ";
	while (n > 0) {                  //输出解决方案
		cout << solu[n] << " ";
		n -= solu[n];
	}
	cout << endl;
	vector<int>::iterator iter = solu.begin();
	while (iter != solu.end())
		cout << *(iter++) << " ";
	cout << endl;
	cout << endl << endl;
}
//int main() {
//	int priceList[] = {0,1, 5, 8, 9,10,17,17,20,24,30};
//	vector<int> priceVec(priceList, priceList + sizeof(priceList) / sizeof(int));
//	int n;
//	while (1) {
//		cout << "input length: ";
//		cin >> n;
//		cout << "highest price: " << ButtomUpCutRod(priceList, n);
//		cout << "    highest price2: " << MemorizedCutRod(priceList, n) << endl;
//		printSolution(priceVec, n);
//	}
//}

#define  N 6
void MatrixChainOrder(int PArray[], int m[N][N], int s[N][N]) {
	int temp = 0;
	int i;
	for (i = 1; i < N; i++)
		m[i][i] = 0;
	
	int t;
	for (t = 2; t < N; t++) {
		int i;
		for (i = 1; i < N - t + 1; i++) {
			int j = i + t - 1;
			m[i][j] = 0x2fffffff;
			int k;
			for (k = i; k < j; k++) {
				temp = m[i][k] + m[k+1][j] + PArray[i-1] * PArray[k] * PArray[j];
				if (temp < m[i][j]) {
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}
}

void PrintOptimalParents(int s[N][N], int i, int j) {
	if (i == j)
		cout << "A" << i;
	else {
		cout << "(";
		PrintOptimalParents(s, i, s[i][j]);
		PrintOptimalParents(s, s[i][j] + 1, j);
		cout << ")";
	}
}

//int main() {
//	int p[N] = {30,35,15,5,10,20};
//	int m[N][N] = {0};
//	int s[N][N] = {0};
//	int i, j;
//	MatrixChainOrder(p, m, s);
//	cout << "m value is " << endl;
//	for (i = 1; i < N; ++i) {
//		for (j = 1; j < N; ++j)
//			cout << m[i][j] << " ";
//		cout << endl;
//	}
//	cout << endl;
//	for (i = 1; i < N; ++i) {
//		for (j = 1; j < N; ++j)
//			cout << s[i][j] << " ";
//		cout << endl;
//	}
//	cout << endl << "The result is: "  << endl;
//	PrintOptimalParents(s, 1, N - 1);
//	return 0;
//}