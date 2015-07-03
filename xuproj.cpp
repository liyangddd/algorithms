#include <iostream>
#include <vector>
#include <iostream>
#include <deque>
#include <time.h>
using namespace std;

//打印内存页面的页分部情况
void print(deque<int> &page_deque) {
	deque<int>::iterator iter = page_deque.begin();
	cout << "\t";
	while (iter != page_deque.end()) {
		cout << *iter << " ";
		++iter;
	}
	cout << endl;
}

//判断将要使用的某页是否在内存中
//FIFO算法使用
bool isInMemory(deque<int> &page_queue, int val) {
	deque<int>::iterator iter_queue = page_queue.begin();
	while (iter_queue != page_queue.end()) {
		if (*iter_queue == val) {
			return true;
		}
		++iter_queue;
	}
	return false;
}

//页面置换算法，先进先出
void FIFO(int pages_memory, vector<int> &vec) {
	deque<int> page_queue = deque<int>();
	unsigned int times_hit = 0;
	unsigned int times_nonhit = 0;
	vector<int>::iterator iter = vec.begin();
	while (iter != vec.end()) {
		if (page_queue.size() < pages_memory) {
			if (false == isInMemory(page_queue, *iter)) {
				times_nonhit += 1;
				page_queue.push_back(*iter);
			}
			else
				times_hit += 1;
			//print(page_queue);
		}
		else if (pages_memory == page_queue.size()) {
			if (isInMemory(page_queue, *iter)){
				times_hit += 1;
			}
			else {
				times_nonhit += 1;
				page_queue.pop_front();
				page_queue.push_back(*iter);
			}
			//print(page_queue);
		} 
		else {}
		iter++;
	}
	cout << "\t FIFO 命中次数：" << times_hit << "\t 未命中次数：" << times_nonhit << "\t 命中比率：" 
		<< (float)times_hit / vec.size() << endl;
}

///页面置换算法，最近最久未使用算法
void LRU(int pages_memory, vector<int> &ivec) {
	deque<int> page_queue = deque<int>();
	unsigned int times_hit = 0;
	unsigned int times_nonhit = 0;
	vector<int>::iterator iter = ivec.begin();
	while (iter != ivec.end()) {
		if (pages_memory > page_queue.size()) {
			deque<int>::iterator iter_queue = page_queue.begin();
			bool isHit = false;
			while (iter_queue != page_queue.end()) {
				if (*iter_queue == *iter) {
					isHit = true;
					break;
				}
				++iter_queue;
			}
			if (isHit) {
				times_hit += 1;
				int lastest_page = *iter_queue;
				if (iter_queue != page_queue.end() - 1) {
					deque<int>::iterator sub_iter_queue = iter_queue;
					while (sub_iter_queue != page_queue.end() - 1) {
						*sub_iter_queue = *(sub_iter_queue + 1);
						++sub_iter_queue;
					}
					*(sub_iter_queue) = lastest_page;
				}
			}
			else {
				times_nonhit += 1;
				page_queue.push_back(*iter);
			}
			//print(page_queue);
		}
		else if (pages_memory == page_queue.size()) {
			deque<int>::iterator iter_queue = page_queue.begin();
			bool isHit = false;
			while (iter_queue != page_queue.end()) {
				if (*iter_queue == *iter) {
					isHit = true;
					break;
				}
				++iter_queue;
			}
			if (isHit) {
				times_hit += 1;
				int lastest_page = *iter_queue;
				if (iter_queue != page_queue.end() - 1) {
					deque<int>::iterator sub_iter_queue = iter_queue;
					while (sub_iter_queue != page_queue.end() - 1) {
						*sub_iter_queue = *(sub_iter_queue + 1);
						++sub_iter_queue;
					}
					*(sub_iter_queue) = lastest_page;
				}
			}
			else {
				times_nonhit += 1;
				page_queue.pop_front();
				page_queue.push_back(*iter);
			}
			//print(page_queue);
		}
		else {}
		++iter;
	}
	cout << "\t LRU 命中次数：" << times_hit << "\t 未命中次数：" << times_nonhit << "\t 命中比率：" 
		<< (float)times_hit / ivec.size() << endl << endl;
}

void produce_random(int max_num, int pages_num, vector<int> &vec_rand) {
	srand(time(0));
	int i = 0;
	cout << "Pages: ";
	while (i < max_num) {
		int val = 1 + rand() % pages_num;
		cout << val << " ";
		vec_rand.push_back(val);
		++i;
	}
	cout << endl;
}

//int main() {
//	int pages_num; //用于计算页面编号
//	int max_num; //待调入页面的个数
//	int min_pages_memory, max_pages_memory; //内存的空间：页面个数
//	int i;
//	vector<int> ivec;
//	ivec.push_back(2);ivec.push_back(3);ivec.push_back(2);ivec.push_back(1);ivec.push_back(5);
//	ivec.push_back(1);ivec.push_back(4);ivec.push_back(5);ivec.push_back(3);ivec.push_back(2);
//	ivec.push_back(5);ivec.push_back(2);
//	
//	//for (int i = 0; i < 10; i++) {
//	//	int a;
//	//	cin >> a;
//	//	ivec.push_back(a);
//	//}
//	
//	for (int i = 1; i < 6; i++) {
//		cout << "---" << i << endl; 
//		FIFO(i, ivec);
//		LRU(i, ivec);
//	}
//	//cout << "内存页面的范围、待调用页面的个数、页面编号";
//	//cin >> min_pages_memory >> max_pages_memory >> max_num >> pages_num;
//	//for (i = min_pages_memory; i <= max_pages_memory; ++i) {
//	//	cout << "------当前内存页面个数：" << i << "--------" << endl; 
//	//	produce_random(max_num, pages_num, ivec);
//	//	FIFO(i, ivec);
//	//	LRU(i, ivec);
//	//	cout << endl;
//	//}
//
//	return 0;
//}
/*
#include<stdio.h>
#include<Windows.h>
#include<time.h>
#define MAX 50

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define MAX 256
static int step = 0;
static int e = 0;

struct Queue
{
	int num1;
	int num2;
	int used;
	int op;
} que[5];

struct MulBuff
{
	int A[MAX];
	int B[MAX];
	int num;
} multBuff;

struct AddBuff
{
	int buff[MAX];
	int s;
	int l;
	int num;
} addBuff;

void print(Queue que[])
{
	for (int i = 0; i < 5; i++)
	{
		if (que[i].used == 0)
		{
			printf("NULL\t");
		}
		else{
			if (que[i].op == 0)
			{
				printf("%d+%d\t", que[i].num1, que[i].num2);
			}
			else{
				printf("%d*%d\t", que[i].num1, que[i].num2);
			}
		}
	}
	printf("\n");
}

int isEnd(MulBuff multBuff, AddBuff addBuff)
{
	if (multBuff.num + que[4].used + que[3].used + que[2].used + que[1].used + que[0].used == 0 && addBuff.num == 1)
		return 1;
	else return 0;
}

void goNext(Queue que[], int a, int b)
{
	que[b].op = que[a].op;
	que[b].num1 = que[a].num1;
	que[b].num2 = que[a].num2;
	que[b].used = que[a].used;
	que[a].used = 0;
}

void go(Queue que[], AddBuff *addBuff, MulBuff *multBuff)
{
	if (que[4].used == 1)
	{
		if (que[4].op == 0)
		{
			if ((addBuff->l + 1) % MAX == addBuff->s)
			{
				printf("AddBuff is Full!");
				return;
			}
			addBuff->buff[addBuff->l] = que[4].num1 + que[4].num2;
			addBuff->num++;
			addBuff->l++;
			que[4].used = 0;
		}
		else{
			if (addBuff->l + 1 % MAX == addBuff->s)
			{
				printf("AddBuff is Full!");
				return;
			}
			addBuff->buff[addBuff->l] = que[4].num1 * que[4].num2;
			addBuff->num++;
			addBuff->l++;
			que[4].used = 0;
		}
	}

	if (addBuff->num >= 2)
	{
		goNext(que, 2, 4);
		goNext(que, 1, 2);
		goNext(que, 0, 1);

		que[0].op = 0;
		que[0].num1 = addBuff->buff[addBuff->s];
		addBuff->s = (addBuff->s + 1) % MAX;
		que[0].num2 = addBuff->buff[addBuff->s];
		addBuff->s = (addBuff->s + 1) % MAX;
		que[0].used = 1;
		addBuff->num = addBuff->num - 2;

		if (que[4].used == 0 && que[3].used)
			goNext(que, 3, 4);
	}
	else if (multBuff->num > 0)
	{
		goNext(que, 3, 4);
		goNext(que, 0, 3);
		que[0].op = 1;
		que[0].num1 = multBuff->A[multBuff->num - 1];
		que[0].num2 = multBuff->B[multBuff->num - 1];
		que[0].used = 1;
		multBuff->num--;

		if (que[2].used == 0 && que[1].used)
			goNext(que, 1, 2);
		if (que[4].used == 0 && que[2].used)
			goNext(que, 2, 4);

	}
	else{
		if (que[4].used == 0)
		{
			if (que[2].used)
			{
				goNext(que, 2, 4);
			}
			else if (que[3].used)
			{
				goNext(que, 3, 4);
			}
		}

		if (que[2].used == 0 && que[1].used == 1)
		{
			goNext(que, 1, 2);
		}

		if (que[0].used)
		{
			if (que[0].op == 0 && que[1].used == 0)
			{
				goNext(que, 0, 1);
			}
			else if (que[0].op == 1 && que[3].used == 0)
			{
				goNext(que, 0, 3);
			}
		}
	}
}

int main()
{
	srand(time(0));

	int n;

	for (int i = 0; i < 5; i++)
	{
		que[i].used = 0;
	}
	for (int i = 0; i < MAX; i++)
	{
		multBuff.A[i] = rand() % 16 + 1;
		multBuff.B[i] = rand() % 16 + 1;
		addBuff.buff[i] = -1;
	}

	scanf_s("%d", &n);
	multBuff.num = n;
	addBuff.num = addBuff.l = addBuff.s = 0;

	while (!e)
	{
		step++;
		go(que, &addBuff, &multBuff);
		print(que);
		Sleep(300);
		e = isEnd(multBuff, addBuff);
	}

	printf("\n\n共%d\n", step - 1);
	system("PAUSE");
	return 0;
}

/*
typedef struct
{
	int num1;
	int num2;
	bool exist;
} Pair;

int Buffer[MAX], bufferSize;
int qhead, qtail;
Pair AddQueue[4], MulQueue[3];
int A[MAX], B[MAX];

void AddToBuffer(int x);
int GetFromBuffer();
bool CheckAddPipe();
bool CheckMulPipe();

int main()
{
	srand(time(0));
	int addTick, mulTick, mulLabel;
	int n;
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	{
		A[i] = rand() % 16 + 1;
		B[i] = rand() % 16 + 1;
	}
	for (int i = 0; i < n; i++)
		cout << A[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << B[i] << " ";
	cout << endl;

	bufferSize = 0;
	qhead = 1;
	qtail = 0;
	addTick = 0;
	mulTick = 0;
	mulLabel = 0;
	printf("\n", n);
	for (int i = 0; i<4; i++)
		AddQueue[i].exist = 0;
	for (int i = 0; i<3; i++)
		MulQueue[i].exist = 0;
	while (1)
	{
		int product;
		if (MulQueue[2].exist == true)
		{
			product = MulQueue[2].num1 * MulQueue[2].num2;
			MulQueue[2].exist = false;
			AddToBuffer(product);
		}
		if (CheckMulPipe() == 0 && bufferSize == n)
			break;
		mulTick++;
		MulQueue[2] = MulQueue[1];
		MulQueue[1] = MulQueue[0];
		MulQueue[0].exist = false;
		if (mulLabel<n)
		{
			MulQueue[0].num1 = A[mulLabel];
			MulQueue[0].num2 = B[mulLabel];
			MulQueue[0].exist = true;
			mulLabel++;
		}
		if (MulQueue[0].exist == true)
		{
			printf_s("%d*%d\t", MulQueue[0].num1, MulQueue[0].num2);
		}
		else
		{
			printf_s("NULL\t");
		}
		printf_s("NULL\t");
		printf_s("NULL\t");
		if (MulQueue[1].exist == true)
		{
			printf_s("%d*%d\t", MulQueue[1].num1, MulQueue[1].num2);
		}
		else
		{
			printf_s("NULL\t");
		}
		if (MulQueue[2].exist == true)
		{
			printf_s("%d*%d\t\n", MulQueue[2].num1, MulQueue[2].num2);
		}
		else
		{
			printf_s("NULL\t\n");
		}
		Sleep(300);
	}
	while (1)
	{
		int tsum;
		if (AddQueue[3].exist)
		{
			tsum = AddQueue[3].num1 + AddQueue[3].num2;
			AddQueue[3].exist = 0;
			AddToBuffer(tsum);
		}
		if (CheckAddPipe() == 0 && bufferSize == 1)
			break;
		addTick++;
		AddQueue[3] = AddQueue[2];
		AddQueue[2] = AddQueue[1];
		AddQueue[1] = AddQueue[0];
		AddQueue[0].exist = 0;
		if (bufferSize >= 2)
		{
			AddQueue[0].num1 = GetFromBuffer();
			AddQueue[0].num2 = GetFromBuffer();
			AddQueue[0].exist = 1;
		}
		if (AddQueue[0].exist == true)
		{
			printf_s("%d+%d\t", AddQueue[0].num1, AddQueue[0].num2);
		}
		else
		{
			printf_s("NULL\t");
		}
		if (AddQueue[1].exist == true)
		{
			printf_s("%d+%d\t", AddQueue[1].num1, AddQueue[1].num2);
		}
		else
		{
			printf_s("NULL\t");
		}
		if (AddQueue[2].exist == true)
		{
			printf_s("%d+%d\t", AddQueue[2].num1, AddQueue[2].num2);
		}
		else
		{
			printf_s("NULL\t");
		}
		printf_s("NULL\t");

		if (AddQueue[3].exist == true)
		{
			printf_s("%d+%d\t\n", AddQueue[3].num1, AddQueue[3].num2);
		}
		else
		{
			printf_s("NULL\t\n");
		}


		Sleep(300);
	}
	printf("\n共%d\n\n", addTick + mulTick);


	system("pause");
	return 0;
}

void AddToBuffer(int x)
{
	Buffer[qhead] = x;
	qhead = (qhead + 1) % MAX;
	bufferSize++;
}

int GetFromBuffer()
{
	qtail = (qtail + 1) % MAX;
	bufferSize--;
	return Buffer[qtail];
}

bool CheckAddPipe()
{
	bool b = 0;
	for (int i = 0; i<4; i++)
	{
		b = b || AddQueue[i].exist;
	}
	return b;
}

bool CheckMulPipe()
{
	bool b = 0;
	for (int i = 0; i<3; i++)
	{
		b = b || MulQueue[i].exist;
	}
	return b;
}

/*
* input: 
*		 @num_seq, the number(s) to caculate
*        @sleep_time, time for timer to sleep
* output:
*        a.information of number(s) in queue
*        b.processes of addition
*		 c.steps of addition
*/

/*
int step = 0;  //count how many steps for caculation

class AdditionInt {  //addition class
private:
	int num1;
	int num2;

public:
	AdditionInt() {
		num1 = -1;
		num2 = -1;
	}
	AdditionInt(int a, int b) {
		num1 = a;
		num2 = b;
	}

	int calculate_sum() {
		return num1 + num2;
	}

	void print_result() {
		if (num1 == -1 && num2 == -1) {
			cout << " Null\t";
		}
		else
			cout << " " << num1 << "+" << num2  << "\t";
	}
};

int main() {
	int num_seq;
	int temp;
	int sleep_time;

	list<int> list_int; //numbers to add
	list<AdditionInt*> list_proc; //process of addition
	AdditionInt* protemp;
	cout << "input num of sequence: ";
	cin >> num_seq;

	// deal with ugly input datas.
	if (num_seq <= 0) {  
		cout << "no number(s) to caculate, finish." << endl;
		return 0;
	}
	if (num_seq == 1) {
		cout << "just one number, do not need caculate" << endl;
		return 0;
	}
	cout << "input sleep time(ms)：";
	cin >> sleep_time;
	cout << endl;

	cout << "All numbers: ";
	int i = 0;
	for ( ; i < num_seq; i++) {
		list_int.push_back(rand() % 16 + 1);
	}

	list<int>::iterator iter = list_int.begin();
	while (iter != list_int.end()) {
		cout << *iter++ << " ";
	}
	cout << endl << endl;

	list_proc.push_front(new AdditionInt);
	list_proc.push_front(new AdditionInt);
	list_proc.push_front(new AdditionInt);
	list_proc.push_front(new AdditionInt);

	cout << "\t  P3\t  P2\t  P1\t  P0\t  QueueInfo" << endl;

	void printStepInfo(list<AdditionInt*> &list_proc, list<int> &list_int);
	void printStepInfo(list<int> &list_int);

	while (true) {
		Sleep(sleep_time);    // timer
		int max = -3;

		protemp = list_proc.front();
		list_proc.pop_front();

		if (protemp->calculate_sum() <= -2) { // head of addition process is empty
			printStepInfo(list_int);
			if (list_int.size() >= 2) {  //have more than one numbers in list_int
				temp = list_int.front();
				list_int.pop_front();
				list_proc.push_back(new AdditionInt(temp, list_int.front()));
				list_int.pop_front();
			}
			else {  //less than number is list_int
				list_proc.push_back(new AdditionInt());
				list<AdditionInt*>::iterator iter = list_proc.begin();
				while (iter != list_proc.end()) {
					if ((*iter)->calculate_sum() > max)
						max = (*iter)->calculate_sum();
					iter++;
				}
			}

			if (max == -2) {  // no numbers to caculate: step 0 or end.
				if (step == 0) {
					cout << "Step " << step << "\t";
					printStepInfo(list_proc, list_int);
				}
				cout << "---------------The End--------------";
				break;
			}
			printStepInfo(list_proc, list_int);
		}
		else { //head of addition process is not empty
			// still number(s) in process 3
			list_int.push_back(protemp->calculate_sum());
			printStepInfo(list_int);

			if (list_int.size() >= 2) {  
				temp = list_int.front();
				list_int.pop_front();
				list_proc.push_back(new AdditionInt(temp, list_int.front()));
				list_int.pop_front();
			}
			else {
				list_proc.push_back(new AdditionInt());
				for (list<AdditionInt*>::iterator iter = list_proc.begin();
					iter != list_proc.end(); iter++) {
						if ((*iter)->calculate_sum() > max)
							max = (*iter)->calculate_sum();
				}
				if (max == -2) {
					//cout << "here" << endl;
					step--;
				}
			}
			printStepInfo(list_proc, list_int);
		}
		step++;  // finish of once addition step
	}
	cout << endl << endl << step << " Steps" << endl;
}

void printStepInfo(list<AdditionInt*> &list_proc, list<int> &list_int) {
	cout << "Step " << step + 1 << "\t";
	for (list<AdditionInt*>::iterator iter = list_proc.begin();
		iter != list_proc.end(); iter++) {
			(*iter)->print_result();
	}
	cout << "  ";

	if (list_int.size() == 0) {
		cout << "--" << endl;
	}
	else {
		for (list<int>::iterator iter = list_int.begin();
			iter != list_int.end(); iter++) {
				cout << *iter << " ";
		}
		cout << endl;
	}
}

void printStepInfo(list<int> &list_int) {
	if (list_int.size() != 0) {
		cout << "\t\t\t\t\t  ";
		for (list<int>::iterator iter = list_int.begin();
			iter != list_int.end(); iter++) {
				cout << *iter << " ";
		}
		cout << endl;
	}
}
*/