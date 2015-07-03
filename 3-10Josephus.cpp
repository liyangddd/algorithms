#include "test.h"
#include "3list.h"

const int maxn = 10000;
void ArrayJose() {
	bool jose[maxn] = {0};   //设置一个数组来模拟N个人
	int m_count = 0; //记录当前报的数
	int i = 0;  //记录当前遍历的是数组的第几个元素
	int out_count = 0; //记录当前出局的人数
	int n, m;
	cin >> n >> m;
	do 
	{
		++i;
		if (i > n)    //所有人报数完后从头开始报数
			i = 1;
		if (!jose[i])  //若数组元素为0，即这个人没出局
			m_count++;
		if (m_count == m) {  //报数为m的人出局
			m_count = 0;      //重新开始报数
			cout << i << " "; //输出出局人编号
			jose[i] = 1;      //将这个人所在位置标记为出局：1
			out_count++;      //出局人数加1
		}
	} while (out_count != n);
}

List MakeCircleList(int n) {
	List jose = NULL;
	int i = 0;
	Position node, rear;
	for (i = 1; i <= n; i++) {
		node = (struct Node *)malloc(sizeof(struct Node));
		if (node == NULL) {
			cout << "malloc failed." << endl;
			return NULL;
		}
		node->element = i;
		if (jose == NULL) {
			jose = node;
		}
		else {
			rear->next = node;
		}
		rear = node;
	}
	rear->next = jose;
	return jose;
}

void CircleListJose(int n, int m, List jose) {
	int m_count = 0, out_count = 0;
	int i;
	Position q, p = jose;
	q = p;
	while (p->next != p) {
		for (i = 1; i < m; ++i) {
			q = p;
			p = p->next;
		}
		Position start = p->next;
		cout << p->element << " ";
		q->next = p->next;
		free(p);
		p = start;
	}
	cout << p->element << endl;
}

/*
int main()  
{  
	int k=0,joseph[14]={0},ans[14]={0};  
	while (cin>>k) {  
		if (k == 0) break;  
		if (ans[k]) {  
			cout<< "ans[:]  " << ans[k]<<endl;  
			continue;  
		}  
		int n=2*k,m=k+1;  
		for (int i=1;i<=k;i++) {  
			joseph[i] = (joseph[i-1]+m - 1) % (n-i + 1);  
			cout << i <<  "  " << joseph[i] << endl;
			if (joseph[i]<k) {  
				i=0;  
				m++;  
			}  
		}  
		ans[k]=m;  
		cout<<m<<endl;  
	}  
	return 0;  
}  
*/