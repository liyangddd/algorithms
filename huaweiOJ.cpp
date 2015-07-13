#include "cppHeader.h"
#include <math.h>


/*
int main()

//方法一：找到规律就这么简单n/2
void fun1() {
	int n;
	//注意这里输入不确定个整数，以0结束的输入方式
	while (cin >> n, n) {
		if (n < 0)
			break;
		cout << n / 2 << endl;
	}
}

//方法二：
int fun2(int n) {
	int remainder = 0;
	int divisor = 0;
	int count = 0;
	while (n / 3) {
		divisor = n / 3;
		remainder = n % 3;
		count += divisor;
		n = divisor + remainder;
	}
	//如果最后还剩两个空瓶子，可以向老板借一个
	//空瓶子再买一瓶
	if (n % 3 == 2)
		count += 1;
	return count;
}
int main() {
	//fun1();
	int n;
	while (cin >> n) {
		if (n != 0) {
			cout << fun2() << endl;
		}
		else
			break;
	}
	return 0;
}
/*
//称砝码
int main() {
	int n;
	cin >> n;
	int max_wight = 0;
	vector<int> nums(n), wights(n);

	for (int i = 0; i < n; i++)
		cin >> wights[i];
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
		max_wight += wights[i] * nums[i]; //求最大可称重的值
	}

	//set内是可以称重的值，元素互斥单调增
	set<int> s;
	s.insert(max_wight);

	//进行n次循环；
	//对于第i次循环，将set中元素从小到大依次取出，
	//减去k * wights[i]，表示少使用k个质量为wights[i]的砝码
	//也可以作为可称重的值；只要这个值是大于0的即可。
	for (int i = 0; i < n; i++) {
		set<int>::iterator iter = s.begin();
		while (iter != s.end()) {
			for (int k = 1; k <= nums[i] && *iter - k * wights[i] > 0; k++)
				s.insert(*iter - k * wights[i]);
			iter++;
		}
	}
	s.insert(0);
	cout << s.size() << endl;
	return 0;
}
/*
//成绩排名
struct scores {
	string name;
	int score;
};
int main() {
	int n;
	cin >> n;
	int flag_order;
	cin >> flag_order;
	vector<scores*> vec;
	scores *min, *max;
	for (int i = 0; i < n; i++) {
		scores *s = new scores;
		string name;
		cin >> name;
		int data;
		cin >> data;
		s->name = name;
		s->score = data;
		vec.push_back(s);
	}

	if (flag_order == 1) {
		for (int i = 1; i < vec.size(); i++) {
			scores *temp = vec[i];
			int j;
			for (j = i; j > 0 && vec[j - 1]->score > temp->score; --j ) {
				vec[j] = vec[j - 1];
			}
			vec[j] = temp;
		}

		vector<scores*>::iterator iter = vec.begin();
		while (iter != vec.end()) {
			cout << (*iter)->name << " " << (*iter)->score << endl;
			iter++;
		}
	}
	if (flag_order == 0) {
		for (int i = 1; i < vec.size(); i++) {
			scores *temp = vec[i];
			int j;
			for (j = i; j > 0 && vec[j - 1]->score < temp->score; --j ) {
				vec[j] = vec[j - 1];
			}
			vec[j] = temp;
		}
		vector<scores*>::iterator iter = vec.begin();
		while (iter != vec.end()) {
			cout << (*iter)->name << " " << (*iter)->score << endl;
			iter++;
		}
	}
}
/*
//求两个公共子串，并输出
int LCS_length(const string &str1, const string &str2, vector<vector<int> > &veca) {
	int i, j, pos;
	int biggest = 0;
	if (str1 == "" || str2 == "")
		return 0;

	for (i = 0; i <= str1.length(); i++) {
		veca[i][0] = 0;
	}
	for (j = 0; j <= str2.length(); j++) {
		veca[0][j] = 0;
	}
	for (i = 1; i <= str1.length(); i++) {
		for (j = 1; j <= str2.length(); j++) {
			if (str1[i - 1] == str2[j - 1]) {
				veca[i][j] = veca[i - 1][j - 1] + 1;
				if (biggest <veca[i][j]) {
					biggest = veca[i][j];
					pos = j;
				}
			}
			else
				veca[i][j] = 0;
		}
	}
	cout << str2.substr(pos - biggest, biggest) << endl;
	return biggest;
}

int main() {
	string str1, str2;
	getline(cin, str1);
	getline(cin, str2);
	vector<vector<int> > veca(str1.length() + 1, vector<int>(str2.length() + 1));
	LCS_length(str1, str2, veca);
	return 0;
}
/*
//合法IP
int main() {
	string str, temp;
	getline(cin, str);
	string str1, str2, str3, str4;
	int pos1 = str.find(".");
	str1 = str.substr(0, pos1);
	//cout << str1 << endl;

	temp = str.substr(pos1 + 1);
	int pos2 = temp.find(".");
	str2 = temp.substr(0, pos2);
	//cout << str2 << endl;

	temp = temp.substr(pos2 + 1);
	int pos3 = temp.find(".");
	str3 = temp.substr(0, pos3);
	//cout << str3 << endl;

	str4 = temp.substr(pos3 + 1);
	//cout << str4 << endl;

	int num1, num2, num3, num4;
	stringstream stream1(str1);
	stream1 >> num1;
	stringstream stream2(str2);
	stream2 >> num2;
	stringstream stream3(str3);
	stream3 >> num3;
	stringstream stream4(str4);
	stream4 >> num4;
	if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) {
		cout << "NO" << endl;
		return 0;
	}
	
	if ((num1 >= 0 && num1 <= 255) && (num2 >= 0 && num2 <= 255) && 
		(num3 >= 0 && num3 <= 255) && (num4 >= 0 && num4 <= 255)) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
	return 0;
}
*/
/*
//扑克牌大小
int main()  
{  
	string str;  
	getline(cin,str);  
	string str1,str2;  
	char a[13]={'3','4','5','6','7','8','9','10','J','Q','K','A','2'};  
	char b[]={"joker"};  
	char c[]={"JOKER"};  
	char bc[]={"joker JOKER"};  
	int len=str.length();  
	int index=0;  
	int i;  
	for(i=0;i<len;i++)  
	{  
		if(str[i]=='-')  
			index=i;  
	}  
	str1=str.substr(0,index);  
	str2=str.substr(index+1,len-index);  
	int len_str1=str1.length();  
	int index_str1=0;  
	int index_str2=0;  
	int len_str2=str2.length();  
	if(len_str1==1)  
	{  
		if(len_str2==1)  
		{  
			for(i=0;i<7;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
				if(str1[0]==a[i])  
					index_str1=i;  
			}  
			for(i=8;i<13;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
				if(str1[0]==a[i])  
					index_str1=i;  
			}  
			if(index_str1>index_str2)  
				cout<<str1;  
			else  
				cout<<str2;  
		}  
		if(len_str2==2)  
		{  
			index_str2=7;  
			for(i=0;i<7;i++)  
			{  
				if(str1[0]==a[i])  
					index_str1=i;  
			}  
			for(i=8;i<13;i++)  
			{  
				if(str1[0]==a[i])  
					index_str1=i;  
			}  
			if(index_str1>index_str2)  
				cout<<str1;  
			else  
				cout<<str2;  
		}  
		if(len_str2==7||len_str2==11)  
			cout<<str2;   
		if(len_str2==3||len_str2==8||len_str2==9||len_str2==10)  
			cout<<"ERROR";  
		if(len_str2==5)  
		{  
			if(str2[0]=='j'||str2[0]=='J')  
				cout<<str2;  
			else  
				cout<<"ERROR";  
		}  
	}  
	if(len_str1==2)  
	{  
		index_str1=7;  
		if(index_str2==1)  
		{  
			for(i=0;i<7;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
			}  
			for(i=8;i<13;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
			}  
			if(index_str1>index_str2)  
				cout<<str1;  
			else  
				cout<<str2;  
		}  
		if(len_str2==5)  
		{  
			if(str2[0]=='j'||str2[0]=='J')  
				cout<<str2;  
			else  
				cout<<"ERROR";  
		}  
		if(len_str2==7||len_str2==11)  
			cout<<str2;   
		if(len_str2==3||len_str2==8||len_str2==9||len_str2==10)  
			cout<<"ERROR";  
	}  
	if(len_str1==3)  
	{  
		if(len_str2==3)  
		{  
			for(int i=0;i<7;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
				if(str1[0]==a[i])  
					index_str1=i;  
			}  
			for(i=8;i<13;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
				if(str1[0]==a[i])  
					index_str1=i;  
			}  
			if(index_str1>index_str2)  
				cout<<str1;  
			else  
				cout<<str2;  
		}  
		if(len_str2==5)  
		{  
			if(str2[0]=='1')  
			{  
				index_str2=7;  
				for(i=0;i<7;i++)  
				{  
					if(str1[0]==a[i])  
						index_str1=i;  
				}  
				for(i=8;i<13;i++)  
				{  
					if(str1[0]==a[i])  
						index_str1=i;  
				}  
				if(index_str1>index_str2)  
					cout<<str1;  
				else  
					cout<<str2;  
			}  
			if(str2[0]=='j'||str2[0]=='J')  
				cout<<"ERROR";  
		}  
		if(len_str2==1||len_str2==2)  
			cout<<"ERROR";  
		if(len_str2==7||len_str2==11)  
			cout<<str2;  
		if(len_str2==8||len_str2==9||len_str2==10)  
			cout<<"ERROR";  
	}  
	if(len_str1==5)  
	{  
		if(len_str2==1)  
		{  
			if(str1[0]=='j'||str1[0]=='J')  
				cout<<str1;  
			else  
				cout<<"ERROR";  
		}  
		if(len_str2==2)  
			cout<<"ERROR";  
		if(len_str2==3)  
		{  
			if(str1[0]=='1')      
			{  
				index_str1=7;  
				for(i=0;i<7;i++)  
				{  
					if(str2[0]==a[i])  
						index_str2=i;  
				}  
				for(i=8;i<13;i++)  
				{  
					if(str2[0]==a[i])  
						index_str2=i;  
				}  
				if(index_str1>index_str2)  
					cout<<str1;  
				else  
					cout<<str2;  
			}  
			else  
				cout<<"ERROR";  
		}  
		if(len_str2==5)  
		{  
			if(str2[0]=='1')  
				cout<<"ERROR";  
			else  
			{  
				for(int i=0;i<7;i++)  
				{  
					if(str2[0]==a[i])  
						index_str2=i;  
					if(str1[0]==a[i])  
						index_str1=i;  
				}   
				for(i=8;i<13;i++)  
				{  
					if(str2[0]==a[i])  
						index_str2=i;  
					if(str1[0]==a[i])  
						index_str1=i;  
				}  
				if(index_str1>index_str2)  
					cout<<str1;  
				else  
					cout<<str2;  
			}  
		}  
		if(len_str2==7||len_str2==11)  
			cout<<str2;  
		if(len_str2==8||len_str2==9||len_str2==10)  
			cout<<"ERROR";  
	}  
	if(len_str1==7)  
	{  
		if(len_str2<7||len_str2==9||len_str2==10||len_str2==8)  
			cout<<str1;  
		if(len_str2==7)  
		{  
			for(i=0;i<7;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
				if(str1[0]==a[i])  
					index_str1=i;  
			}  
			for(i=8;i<13;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
				if(str1[0]==a[i])  
					index_str1=i;  
			}  
			if(index_str1>index_str2)  
				cout<<str1;  
			else  
				cout<<str2;  
		}  
		if(len_str2==11)  
		{  
			if(str2[0]=='1')  
			{  
				index_str2=7;  
				for(i=0;i<7;i++)  
				{  
					if(str2[0]==a[i])  
						index_str2=i;  
				}  
				for(i=8;i<13;i++)  
				{  
					if(str2[0]==a[i])  
						index_str2=i;  
				}  
				if(index_str1>index_str2)  
					cout<<str1;  
				else  
					cout<<str2;     
			}  
			if(str2[0]=='j')  
				cout<<str2;  
		}  

	}  
	if(len_str1==8)  
	{  
		index_str1=7;  
		if(len_str2==5)  
		{  
			for(i=0;i<7;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
			}  
			for(i=8;i<13;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
			}  
			if(index_str1>index_str2)  
				cout<<str1;  
			else  
				cout<<str2;  
		}  
		if(len_str2==7||len_str2==11)  
			cout<<str2;  
		if(len_str2==1||len_str2==2||len_str2==3||len_str2==9||len_str2==10)  
			cout<<"ERROR";  
	}  
	if(len_str1==9)  
	{  
		if(len_str2==7||len_str2==11||len_str2==10)  
			cout<<str2;  
		if(len_str2==9)  
		{  
			for(i=0;i<3;i++)  
			{  
				if(str2[0]==a[i])  
					index_str2=i;  
				if(str1[0]==a[i])  
					index_str1=i;  
			}  
			if(index_str1>index_str2)  
				cout<<str1;  
			else  
				cout<<str2;  
		}  
		if(len_str2==1||len_str2==2||len_str2==3||len_str2==5||len_str2==8)  
			cout<<"ERROR";  
	}  
	if(len_str1==10)  
	{  
		if(len_str2==7||len_str2==11)  
			cout<<str2;  
		if(len_str2==9)  
			cout<<str1;  
		if(len_str2==10)  
		{  
			if(str1[0]=='6')  
				cout<<str2;  
			if(str1[0]=='7')  
			{  
				if(str2[0]=='6')  
					cout<<str1;  
				else  
					cout<<str2;  
			}  
			if(str1[0]=='8')  
			{  
				if(str2[0]=='6'||str2[0]=='7')  
					cout<<str1;  
				else  
					cout<<str2;  
			}  
			if(str1[0]=='9')  
			{  
				if(str2[0]=='6'||str2[0]=='7'||str2[0]=='8')  
					cout<<str1;  
				else  
					cout<<str2;  
			}  
			if(str1[0]=='1')  
				cout<<str1;  
		}  
		if(len_str2==1||len_str2==2||len_str2==3||len_str2==5||len_str2==8)  
			cout<<"ERROR";  
	}  
	if(len_str1==11)  
	{  
		if(len_str2==11)  
		{  
			if(str2[0]=='1')  
				cout<<str1;  
			else  
				cout<<str2;  
		}  
		else  
			cout<<str1;  
	}  
	return 0;  
} 
/*
void pokMap(map<string, int> &m) {
	int i = 14;
	m["3"] = i--;//14
	m["4"] = i--;
	m["5"] = i--;
	m["6"] = i--;
	m["7"] = i--;//10
	m["8"] = i--;
	m["9"] = i--;
	m["10"] = i--;
	m["J"] = i--;//6
	m["Q"] = i--;
	m["K"] = i--;
	m["A"] = i--;
	m["2"] = i--;
	m["joker"] = i--;
	m["JOKER"] = i--; //0
}
void insert(string &word, vector<int> &svec, map<string,int> &m, vector<string> &pok) {
	//cout << "word " << word << endl;
	//cout << "m[word] " << m[word] << endl;
	pok.push_back(word);
	svec[m[word]]++;
}

void printfBigger(vector<string> &svec) {
	vector<string>::iterator it = svec.begin();
	while (it != svec.end() - 1)
		cout << *it++ << " ";
	cout << *it << endl;
}
int main() {
	string str, word;
	map<string, int> m;
	pokMap(m);
	vector<int> first(15, 0), second(15, 0);
	vector<string> first_pok, second_pok;
	getline(cin, str);
	istringstream stream(str);
	int flag = 1;
	int pos;
	while (stream >> word) {
		if ((pos = word.find('-')) != string::npos) {
			//cout << "pos:  "  << pos << endl;
			insert(word.substr(0, pos), first, m, first_pok);
			insert(word.substr(pos + 1), second, m, second_pok);
			flag = 2;
		}
		if (flag == 1)
			insert(word, first, m, first_pok);
		if (flag == 2 && pos == string::npos)
			insert(word, second, m, second_pok);
	}

	
	if (first[0] == 1 && first[1] == 1) {
		printfBigger(first_pok);
		return 0;
	}
	else if (second[0] == 1 && second[1] == 1) {
		printfBigger(second_pok);
		return 0;
	}
	set<int> four1, four2, three1, three2, two1, two2, one1, one2;
	vector<int>::iterator iter1 = first.begin() + 2, iter2 = second.begin() + 2;
	while (iter1 != first.end() && iter2 != second.end()) {
		if (*iter1 == 4)
			four1.insert(*iter1);
		else if (*iter1 == 3)
			three1.insert(*iter1);
		else if (*iter1 == 2)
			two1.insert(*iter1);
		else if (*iter1 == 1)
			one1.insert(*iter1);

		if (*iter2 == 4)
			four2.insert(*iter2);
		else if (*iter2 == 3)
			three2.insert(*iter2);
		else if (*iter2 == 2)
			two2.insert(*iter2);
		else if (*iter2 == 1)
			one2.insert(*iter2);

		iter1++;
		iter2++;
	}

	//444
	if (four1.size() > four2.size()) {
		printfBigger(first_pok);
		return 0;
	}
	else if (four2.size() > four1.size()) {
		printfBigger(second_pok);
		return 0;
	}
	else {
		set<int>::iterator it1 = four1.begin(), it2 = four2.begin();
		while (it1 != four1.end() && it2 != four2.end()) {
			if (*it1 < *it2)  {
				printfBigger(first_pok);
				return 0;
			}
			else if (*it1 > *it2) {
				printfBigger(second_pok);
				return 0;
			}
			else {
				it1++;
				it2++;
			}
		}	
	}

	//333
	if (three1.size() > three2.size()) {
		printfBigger(first_pok);
		return 0;
	}
	else if (three2.size() > three1.size()) {
		printfBigger(second_pok);
		return 0;
	}
	else {
		set<int>::iterator it1 = three1.begin(), it2 = three2.begin();
		while (it1 != three1.end() && it2 != three2.end()) {
			if (*it1 < *it2)  {
				printfBigger(first_pok);
				return 0;
			}
			else if (*it1 > *it2) {
				printfBigger(second_pok);
				return 0;
			}
			else {
				it1++;
				it2++;
			}
		}	
	}

	//222
	if (two1.size() > two2.size()) {
		printfBigger(first_pok);
		return 0;
	}
	else if (two2.size() > two1.size()) {
		printfBigger(second_pok);
		return 0;
	}
	else {
		set<int>::iterator it1 = two1.begin(), it2 = two2.begin();
		while (it1 != two1.end() && it2 != two2.end()) {
			if (*it1 < *it2)  {
				printfBigger(first_pok);
				return 0;
			}
			else if (*it1 > *it2) {
				printfBigger(second_pok);
				return 0;
			}
			else {
				it1++;
				it2++;
			}
		}	
	}

	//111
	if (one1.size() > one2.size()) {
		printfBigger(first_pok);
		return 0;
	}
	else if (one2.size() > one1.size()) {
		printfBigger(second_pok);
		return 0;
	}
	else {
		set<int>::iterator it1 = one1.begin(), it2 = one2.begin();
		while (it1 != one1.end() && it2 != one2.end()) {
			if (*it1 < *it2)  {
				printfBigger(first_pok);
				return 0;
			}
			else if (*it1 > *it2) {
				printfBigger(second_pok);
				return 0;
			}
			else {
				it1++;
				it2++;
			}
		}	
	}
}
/*删除链表指定的元素
typedef struct ListNode {
	int value;
	struct ListNode *next;
} ListNode;

void insert(ListNode **head, int insert_value, int pre_value) {
	if (head == NULL || *head == NULL)
		return;
	ListNode *p = (*head)->next;
	while (p != NULL && p->value != pre_value) {
		p = p->next;
	}
	if (p != NULL) {
		ListNode *newnode = new ListNode;
		newnode->value = insert_value;
		newnode->next = p->next;
		p->next = newnode;
	}
}

ListNode* deleteListNode(ListNode **head, int value) {
	if (head == NULL || *head == NULL)
		return NULL;
	ListNode *pre = *head;
	while (pre->next != NULL && pre->next->value != value)
		pre = pre->next;
	if (pre->next != NULL) {
		ListNode *temp = pre->next;
		pre->next = temp->next;
		delete(temp);
	}
}

int main() {
	int n, head_value;
	cin >> n >> head_value;
	ListNode *head = new ListNode;
	head->next = NULL;
	ListNode *firstnode = new ListNode;
	firstnode->value = head_value;
	firstnode->next = NULL;
	head->next = firstnode;
	for (int i = 1; i < n; i++) {
		int in_val, pre_val;
		cin >> in_val >> pre_val;
		insert(&head, in_val, pre_val);
	}
	int del_val;
	cin >> del_val;
	deleteListNode(&head, del_val);

	ListNode *p = head->next;
	while (p->next != NULL) {
		cout << p->value << " ";
		p = p->next;
	}
	cout << p->value << endl;
}
/*
//合唱队（求最长递增子序列）
int LonggestIncreaseLength(vector<int> &vec) {
	vector<int> result(vec.size(), 1);
	vector<int> result2(vec.size(), 1);
	for (int i = 1; i < vec.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (vec[i] > vec[j] && result[i] < result[j] + 1)
				result[i] = result[j] + 1;
		}
	}

	for (int i = vec.size() - 2; i >= 0; --i) {
		for (int j = vec.size() - 1; j > i; --j) {
			if (vec[i] > vec[j] && result2[i] < result2[j] + 1)
				result2[i] = result2[j] + 1;
		}
	}
	int max = 0;
	for (int i = 0; i < vec.size(); i++) {
		if (max < result[i] + result2[i])
			max = result[i] + result2[i];
	}
	return vec.size() - max + 1;
}
int main() {
	int n;
	cin >> n;
	if (n <= 0)
		return 0;
	vector<int> ivec(n);
	for (int i = 0; i < n; i++)
		cin >> ivec[i];
	cout << LonggestIncreaseLength(ivec) << endl;
}
/*
//输出单链表倒数第k个节点
typedef struct ListNode {
	int m_nKey;
	ListNode* m_pNext;
} ListNode;

ListNode * FindKthToTail(ListNode** pListHead, unsigned int k) {
	if (pListHead == NULL || *pListHead == NULL)
		return NULL;
	int count = 0;
	ListNode *p = (*pListHead)->m_pNext, *q = (*pListHead)->m_pNext;
	while (k + 1 && p != NULL) {
		p = p->m_pNext;
		--k;
	}
	if (k + 1 > 0)
		return NULL;
	while (p != NULL) {
		p = p->m_pNext;
		q = q->m_pNext;
	}
	return q;
}

int main() {
	int num;
	cin >> num;
	int i = 0;
	ListNode *head = new ListNode;
	ListNode *tail;
	head->m_pNext = NULL;
	tail = head;
	while (i < num) {
		int data;
		cin >> data;
		ListNode* node = new ListNode;
		node->m_pNext = NULL;
		node->m_nKey = data;
		tail->m_pNext = node;
		tail = node;
		++i;
	}
	int k;
	cin >> k;
	ListNode *found = FindKthToTail(&head, k);
	if (found)
		cout << found->m_nKey << endl;
	return 0;
}

/*
//大数加法
string AddLongInteger(string addend, string augend)
{
	if(addend.size() < augend.size())
		return AddLongInteger(augend,addend);

	int i,j,temp,flag = 0;
	for(i = addend.size() - 1,j = augend.size() - 1; i >= 0;i--,j--)
	{
		if(j >= 0)
			temp = addend[i] - '0' + augend[j] - '0' + flag ;
		else
			temp = addend[i] - '0' + flag;
		if(temp > 9)
		{
			flag = 1;
			temp %= 10;
		}
		else flag = 0;

		addend[i] = temp + '0';
	}

	if(flag)
		addend = "1" + addend; 
	return addend;
}

int main()
{
	string str1,str2;
	cin >> str1 >> str2;
	cout << AddLongInteger(str1,str2) << endl;
	return 0;
}
/*
string& AddLongInteger(string &data_str1, string &data_str2) {
	string sum_str = "";
	int len1 = data_str1.length();
	int len2 = data_str2.length();
	int max_len = (len1 > len2 ? len1 : len2);
	vector<int> data1(max_len, 0), data2(max_len, 0);
	vector<int> sum(max_len, 0);
	int i;
	for (i = 0; i < len1; i++) {
		if (!isdigit(data_str1[i])) {
			sum_str = "";
			return sum_str;
		}
		data1[i] = data_str1[len1 - i - 1] - '0';
	}

	for (i = 0; i < len2; i++) {
		if (!isdigit(data_str2[i])) {
			sum_str = "";
			return sum_str;
		}
	}
		data2[i] = data_str2[len2 - i - 1] - '0';
	int flag = 0;

	for (i = 0; i < max_len; i++) {
		sum[i] = (data1[i] + data2[i] + flag) % 10;
		flag = (data1[i] + data2[i] + flag) / 10;
	}
	if (flag != 0) {
		sum_str += "1";
	}
	for (i = max_len - 1; i >= 0; --i)
		sum_str += (sum[i] + '0');
	data_str1 = sum_str;
	return data_str1;
}

int main() {
	string data1, data2, sum_str = "";
	cin >> data1 >> data2;
	cout << AddLongInteger(data1, data2) << endl;
	return 0;
}
/*
int main() {
	string str;
	cin >> str;
	int litte_ocur = 21;
	int count = 1;
	map<char, int> m;
	int i = 0;
	int len = str.length();
	while (i < len) {
		++m[str[i]];
		++i;
	}
	map<char, int>::iterator it = m.begin();
	litte_ocur = it->second;
	while (it != m.end()) {
		if (it->second < litte_ocur) {
			litte_ocur = it->second;
		}
		++it;
	}

	int j = 0;
	string substr = "";
	while (j < len) {
		map<char, int>::iterator iter = m.find(str[j]);
		if (iter != m.end()) {
			if (iter->second > litte_ocur) {
				substr += str[j];
			}

		}
		++j;
	}
	cout << substr << endl;
	return 0;
}

/*
bool isPrime(int n)
{
	int c = 0;
	for(int i=1; i<n/2+1; ++i)
		if(n%i == 0)
			++c;
	if(c == 1)
		return true;
	else
		return false;
}

int main()
{
	int n;
	cin >> n;
	for(int i=2; n!=1; ++i)
	{
		if(isPrime(i) && (n%i == 0))
		{
			cout << i << " ";
			n = n/i;
			i = 1;
		}
	}
	cout << endl;
	return 0;
}
*/
/*
//求最长回文，字符串头或尾部可能有其他字符
int checkHuiWen(string str){
	int length;
	length = str.size();
	for (int i = 0; i < length / 2; i++){
		if (str[i] != str[length - i - 1])
			return 0;
	}
	return 1;
}

string split(string str, int begin, int len){
	string tmp;
	for (int i = 0; i < len; i++){
		tmp+= str[begin + i];
	}
	return tmp;
}
int main(){
	string str,tmp;
	int pos=0;
	int max = 0;
	getline(cin, str);
	int length = str.size();
	for (int i = 0; i < length; i++){
		for (int j = length - i; j > 0; j--){
			tmp = split(str, i, j);
			if (checkHuiWen(tmp) == 1){
				max = max > tmp.size() ? max : tmp.size();
			}
		}
	}

	cout << max;
	return 0;
}
*/
/*
int main() {
	string str;
	getline(cin, str);
	if ("" == str) {
		cout << 0 << endl;
		return 0;
	}
	if (1 == str.size()) {
		cout << 1 << endl;
		return 0;
	}
	string::iterator beg = str.begin();
	string::iterator end = str.end() - 1;
	int longest = 0;
	while (beg < end) {
		if (*beg != *end)
			beg++;
		else {
			beg++;
			end--;
			longest += 2;
			if (beg == end) {
				longest++;
			}
		}
	}

	int longest2 = 0;
	beg = str.begin();
	end = str.end() - 1;
	while (beg < end) {
		if (*beg != *end)
			end--;
		else {
			beg++;
			end--;
			longest2 += 2;
			if (beg == end) {
				longest2++;
			}
		}
	}

	int longest3 = 0;
	beg = str.begin();
	end = str.end() - 1;
	while (beg < end) {
		if (*beg != *end) {
			beg++;
			end--;
		}
		else {
			beg++;
			end--;
			longest3 += 2;
			if (beg == end) {
				longest3++;
			}
		}
	}
	longest = longest > longest2 ? longest : longest2;
	cout << longest << endl;
}
*/
/*
int main() {
	int n;
	cin >> n;
	int i = 0;
	int count = 0;
	while(i <= n) {
		int base = i;
		int result = base * base;
		i++;
		while (base && result) {
			int a = result % 10;
			int b = base % 10;
			//cout << a << " " << b << endl;
			if (a == b) {
				result = result / 10;
				base = base / 10;
			}
			else {
				break;
			}
		}
		if (base == 0)
			count++;
	}
	cout << count << endl;
	return 0;
}
/*
int main() {
	int n;
	scanf("%d", &n);
	int result = 0;
	int i = 0;
	int count = 0, count2 = 0;
	while(i < n) {
		int in;
		scanf("%d", &in);
		if (in < 0)
			count++;
		else if (in > 0) {
			result = result + in;
			count2++;
		}
		else
			;
		i++;
	}
	
	float average =  (float)result / count2;
	if (count2 > 0) {
		if (result % count2 != 0)
			printf("%d %.1f\n", count, average);
		else 
			printf("%d %d\n", count, result /count2);
	}
	else {
		printf("%d\n", count);
	}
	return 0;
}
*/
/*
unsigned int Continumax(char **pOutputstr, char *intputstr) {
	if (intputstr == NULL) {
		*pOutputstr = NULL;
	}
	int max_count = 0;
	int i = 0, count = 0;
	int j;
	int pos = 0;
	while (intputstr[i] != '\0') {
		count = 0;
		if (intputstr[i] >= '0' && intputstr[i] <= '9') {
			pos = i;
			j = i + 1;
			count++;
			while (intputstr[j] != '\0' && 
				intputstr[j] >= '0' && intputstr[j] <= '9') {
					count++;
					j++;
					i++;
			}
		}
		else {
			i++;
		}
		if (max_count < count) {
			max_count = count;
			for (i = 0; i < max_count; i++) {
				(*pOutputstr)[i] = intputstr[pos++];
			}
			(*pOutputstr)[pos] = '\0';
		}
	}
	if (max_count == 0) {
		(*pOutputstr)[pos] = '\0';
	}
	return max_count;
}
int main() {
	char str[1000] = {'\0'};
	cin >> str;
	char *outputstr = (char *)malloc(sizeof(1000));
	int n = Continumax(&outputstr, str);
	if ( n > 0)
	     cout << outputstr << "," << n;
	else
		cout << 0;
	free(outputstr);
	return 0;
}
*/
//int calcCapital(string str){
//	int count=0;
//	if(str.empty()){
//		return 0;
//	}
//	for( string::iterator itr=str.begin();itr!=str.end();itr++ ){
//		if('A'<=*itr&&*itr<='Z') count++;
//	}
//	return count;
//}
//
//int main(){
//	int calcCapital(string str);
//	string str;
//	getline(cin, str);
//	cout<<calcCapital(str);
//}
//int main() {
//	char str[100] = "aadddACdd";
//	cout << CalcCapital(str[]);
//}
//int main() {
//	int n;
//	cin >> n;
//	int count = 0;
//	int i;
//	for (i = 31; i >= 0; i--) {
//		if ((n >> i & 1) == 1)
//			count++;
//	}
//	cout << count;
//	return 0;
//}

//int main() {
//	int n;
//	cin >> n;
//	if (n <= 0)
//		return -1;
//	int i = 1;
//	int sum = 2, result = 2;
//	while (i < n) {
//		sum = sum + 3;
//		result = result + sum;
//		++i;
//	}
//	cout << result;
//	return 0;
//}
//
//int main() {
//	char str[130] = {'\0'};
//	gets_s(str);
//	int strLen = strlen(str);
//	int i = strLen - 1;
//	int count = 0;
//	while (i >= 0 && str[i] != ' ') {
//		++count;
//		--i;
//	}
//	printf("%d", count);
//}
//int main() {
//	char str[102] = {'\0'};
//	char str2[102] = {'\0'};
//	gets_s(str);
//	getline(stdin, str);
//	int strLen = strlen(str);
//	int i = 0;
//	while (str[i] != '\0') {
//		str2[i] = str[strLen - i - 1];
//		i++;
//	}
//	printf("%s",str2);
//	return 0;
//}
