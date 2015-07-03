#include <string>
#include <iostream>
#include <vector>
#include <sstream>  
#include <set>
using namespace std;  

/*
//判断ip
int JudgeIP(string &str, vector<int> &vec) {  
	string temp;
	string str1, str2, str3, str4;  
	int pos1 = str.find(".");  
	str1 = str.substr(0, pos1);  

	temp = str.substr(pos1 + 1);  
	int pos2 = temp.find(".");  
	str2 = temp.substr(0, pos2);  

	temp = temp.substr(pos2 + 1);  
	int pos3 = temp.find(".");  
	str3 = temp.substr(0, pos3);  

	str4 = temp.substr(pos3 + 1);  
	int pos4 = str4.find(".");

	if (pos1 == string::npos || pos2 == string::npos || 
		pos3 == string::npos || pos4 != string::npos) {  
		return -1;  
	}  
	unsigned int num1, num2, num3, num4;  
	stringstream stream1(str1);  
	stream1 >> num1;  
	stringstream stream2(str2);  
	stream2 >> num2;  
	stringstream stream3(str3);  
	stream3 >> num3;  
	stringstream stream4(str4);  
	stream4 >> num4;   

	if ((num1 >= 0 && num1 <= 255) && (num2 >= 0 && num2 <= 255) &&   
		(num3 >= 0 && num3 <= 255) && (num4 >= 0 && num4 <= 255)) {  
			vec.push_back(num1);
			vec.push_back(num2);
			vec.push_back(num3);
			vec.push_back(num4);
			return 1;
	}  
	else {  
		return -1; 
	}  
} 

int main() {
	bool flag = true;
	string str_mask, str_ip1, str_ip2;
	cin >> str_mask >> str_ip1 >> str_ip2;
	vector<int> vec_mask, vec_ip1, vec_ip2;
	int a = JudgeIP(str_mask, vec_mask);
	int b = JudgeIP(str_ip1, vec_ip1);
	int c = JudgeIP(str_ip2, vec_ip2);
	if (a == -1 || b == -1 || c == -1) {
		cout << 1 << endl;
		return 0;
	}
	for (int i = 0; i < 4; i++) {
		if ((vec_mask[i] & vec_ip1[i]) != (vec_mask[i] & vec_ip2[i]))
			flag = false;
	}
	if (flag)
		cout << 0 << endl;
	else
		cout << 2 << endl;
	return 0;
}
/*
//求三个数的最小值
int min(int a, int b, int c) {
	if (a > b) {
		if (b > c)
			return c;
		else
			return b;
	}
	if (a > c) {
		if (c > b)
			return b;
		else
			return c;
	}
	if (b > c) {
		if (c > a)
			return a;
		else
			return c;
	}
}

//使用动态规划求解方法
int StringDistance(string &str1, int start1, int end1,
	string &str2, int start2, int end2) {
	if (start1 > end1) {
		if (start2 > end2)
			return 0;
		else
			return end2 - start2 + 1;
	}

	if (start2 > end2) {
		if (start1 > end1)
			return 0;
		else
			return end1 - start1 + 1;
	}

	if (str1[start1] == str2[start2])
		return StringDistance(str1, start1 + 1, end1, str2, start2 + 1, end2);
	else {
		int t1 = StringDistance(str1, start1 + 1, end1, str2, start2, end2);
		int t2 = StringDistance(str1, start1, end1, str2, start2 + 1, end2);
		int t3 = StringDistance(str1, start1 + 1, end1, str2, start2 + 1, end2);
		return min(t1, t2, t3) + 1;
	}
}

//递归求解方法
int StringDistance(string &str1, string &str2) {
	int len1 = str1.length(), len2 = str2.length();
	vector<vector<int> > ivec(len1 + 1, vector<int>(len2 + 1));

	//下面初始化的含义：
	//当str1长度为0时，那么两个字符串的距离就是str2的长度
	//同样，当str2长度为0， 那么两个字符串距离就是str1的长度
	for (int i = 0; i < len1 + 1; ++i)
		ivec[i][0] = i;
	for (int i = 0; i < len2 + 1; ++i)
		ivec[0][i] = i;

	for(int i = 1; i <= len1; ++i) {
		for (int j = 1; j <= len2; ++j) {
			if (str1[i - 1] == str2[j - 1])
				ivec[i][j] = ivec[i - 1][j -1];
			else
				ivec[i][j] = min(ivec[i][j - 1], ivec[i - 1][j], ivec[i - 1][j - 1]) + 1;
		}
	}
	return ivec[len1][len2];
}
int main() {
	string str1, str2;
	cin >> str1 >> str2;
	//int dis = StringDistance(str1, 0, str1.length() - 1,	str2, 0, str2.length() - 1);
	int dis = StringDistance(str1, str2);
	cout << dis << endl;
}
/*
//放苹果
int main() {
	int apple, plate;
	cin >> apple >> plate;
	if (apple < 0 || apple > 10 || plate < 1 || plate > 10) {
		cout << -1 << endl;
		return -1;
	}
	vector<vector<int> > ivec(11, vector<int>(11, 0));
	for (int i = 0; i < 11; i++) {
		ivec[0][i] = 1;
		ivec[i][1] = 1;
	}
	for (int i = 1; i <= 10; ++i) {
		for (int j = 1; j <= 10; ++j) {
			if (j <= i)
				ivec[i][j] = ivec[i][j - 1] + ivec[i - j][j];
			else
				ivec[i][j] = ivec[i][i];
		}
	}


	cout << ivec[apple][plate] << endl;
	return 0;
}
/*
//变形的快排，对字符串分别排序其奇数下标字符、偶数下标字母
int PartQuickSort(string &str, int pos1, int pos2) {
		char pivot = str[pos1];
		int low = pos1, high = pos2;
		while (high - low > 1) {
			while (high - low > 1 && str[high] >= pivot)
				high -= 2;
			str[low] = str[high];
			while (high - low > 1&& str[low] <= pivot)
				low += 2;
			str[high] = str[low];
		}
		str[low] = pivot;
		return low;
}

void QuickSort(string &str, int pos1, int pos2) {
	if (pos2 - pos1 > 1) {
		int part = PartQuickSort(str, pos1, pos2);
		QuickSort(str, pos1, part - 2);
		QuickSort(str, part + 2, pos2);
	}
}

//按照题目要求对特定字符翻转其二进制位
void process_str(string &str) {
	char ch1, ch2 = 0;
	bool flag = true;
	int i;
	for (i = 0; i < str.size(); i++) {
		flag = true;
		if (str[i] >= '0' && str[i] <= '9')
			ch1 = str[i] - '0';
		else if (str[i] >= 'a' && str[i] <= 'f')
			ch1 = str[i] - 'a' + 10;
		else if (str[i] >= 'A' && str[i] <= 'F')
			ch1 = str[i] - 'A' + 10;
		else
			flag = false;
		if (flag) {
			//本题要注意这里将二进制位翻转的做法。
			//例如11的二进制为1011，翻转后为1101
			ch2 = 0;
			ch2 |= (ch1 & (1 << 0)) << 3;
			ch2 |= (ch1 & (1 << 1)) << 1;
			ch2 |= (ch1 & (1 << 2)) >> 1;
			ch2 |= (ch1 & (1 << 3)) >> 3;
			if (ch2 < 10) {
				str[i] = '0' + ch2;
				//cout << str[i] << endl;
			}
			else {
				str[i] =  'A' + ch2 - 10;
				//cout << str[i] << endl;
			}
		}
	}
}

int main() {
	string str, str1, str2;
	getline(cin, str);
	stringstream stream(str);
	stream >> str1 >> str2;
	str1 += str2;
	str2 = str1;

	//分别对字符串的偶数下标、奇数下标排序
	if (str1.size() % 2 != 0) {
		QuickSort(str1, 0, str1.size() - 1);
		QuickSort(str1, 1, str1.size() - 2);
	}
	else {
		QuickSort(str1, 0, str1.size() - 2);
		QuickSort(str1, 1, str1.size() - 1);
	}

	process_str(str1);
	cout << str1 << endl;
}
/*
bool prime(int n) {
	for (int i = 3; i <= (int)sqrt((double)n); i += 2) {
		if (n % i == 0)
			return false;
	}
	return true;
}

int main() {
	int even;
	cin >> even;
	if (even % 2 != 0 || even <= 5 || even > 10000)
		return 0;
	int i, j;
	int min = even;
	int pos1 = 0;
	for (i = even - 1; i > 0;i = i - 2) {
		if (prime(i)) {
			int test = even - i;
			if (test > 0 && prime(test)) {
				if (abs(even - 2 * i) < min) {
					min = abs(even - 2 * i);
					pos1 = i;
				}
			}
		}
	}
	if (pos1 < even - pos1) {
		cout << pos1 << endl;
		cout << even - pos1 << endl;
	}
	else {
		cout << even - pos1 << endl;
		cout << pos1 << endl;
	}
}
/*
//矩阵乘法
int main() {
	int a, b, c;
	cin >> a >> b >> c;
	vector<vector<int> > veca(a, vector<int>(b));
	vector<vector<int> > vecb(b, vector<int>(c));
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			int data;
			cin >> veca[i][j];
		}
	}

	for (int i = 0; i < b; i++) {
		for (int j = 0; j < c; j++) {
			int data;
			cin >> vecb[i][j];
		}
	}

	vector<vector<int> > vec_result(a, vector<int>(c, 0));
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			for (int k = 0; k < b; k++) {
				vec_result[i][j] += veca[i][k] * vecb[k][j];
			}
		}
	}

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < c; j++) {
			if (j != c - 1)
				cout << vec_result[i][j] << " ";
			else
				cout << vec_result[i][j];
		}
		cout << endl;
	}
}
/*
int main()
{
	char str[1000];
	int i,j,k;
	int len = 0;
	char tmp;
	gets(str);
	len = strlen(str);
	for(i = 0; i < len-1; ++i)
	{
		for(j = 0; j < len-1-i; ++j)
		{
			k = j;
			//如果str[j]是一个字母，那么就寻找其后的第一个字母a
			//找到了,并且a大于str[j]那么就将它们交换
			if(isalpha(str[j]))
			{
				while(!isalpha(str[k+1]) && k < len-i-1)
					k++;

				if(isalpha(str[k+1]))
					if(tolower(str[j]) > tolower(str[k+1]))
					{
						tmp = str[j];
						str[j] = str[k+1];
						str[k+1] = tmp;
					}
			}
		}

	}
	puts(str);
	return 0;
}
/*
//DNA序列
//使用substr得到子序列很方便！！！！！！
int main()  
{  
	string dna,temp;  
	int n=0,count=0,max=0;  
	cin>>dna;  
	cin>>n;  
	if(n>dna.size())  
	{  
		return 0;  
	}  
	else  
	{  
		for(int i=0;i<=dna.size()-n;++i)  
		{  
			for(int k=0;k<n;++k)  
			{  
				if(dna.substr(i,n)[k]=='G' || dna.substr(i,n)[k]=='C')  
				{  
					count++;  
				}  
			}  
			if(count>max)//这里如果改成大于等于，那么就默认输出最后一段字串  
			{  
				max=count;  
				temp=dna.substr(i,n);  
			}  
			count=0;  
		}  
		cout<<temp<<endl;  
	}  
	return 0;  
}  
/*
int main() {
	string str;
	getline(cin, str);
	if (str == "")
		return 0;
	int k;
	for (k = 0; k < str.length(); k++) {
		if (str[k] != 'G' && str[k] != 'C' && str[k] != 'A' && str[k] != 'T')
			return 0;
	}
	int substr_len;
	cin >> substr_len;
	if (str.length() < substr_len)
		return 0;
	int max_count = 0;
	int count = 0;
	int pos = 0;
	int i, j;

	for (i = 0; i <= str.length() - substr_len ; i++) {
		int count = 0;
		j = i;
		while (j < i + substr_len) {
			if (str[j] == 'G' || str[j] == 'C') {
				++count;
			}
			++j;
		}
		if (max_count < count) {
			max_count = count;
			pos = j;
		}
	}


	if (max_count == 0) {
		cout << endl;
	}
	else {
		for(i = 0; i < substr_len; i++) {
			cout << str[pos - substr_len + i];
		}
		cout << endl;
	}
	return 0;
}
/*
//求最长公共字串（连续）
int LCS_length(const string &str1, const string &str2, vector<vector<int> > &veca) {  
	int i, j;  
	int biggest = 0;  
	if (str1 == "" || str2 == "")  
		return 0;  
	for (i = 0; i <= str1.length(); i++) {  
		veca[i].resize(str2.length() + 1, 0);  
	}  
	for (j = 0; j <= str2.length(); j++) {  
		veca[0][j] = 0;  
	}  
	for (i = 1; i <= str1.length(); i++) {  
		for (j = 1; j <= str2.length(); j++) {  
			if (tolower(str1[i - 1]) == tolower(str2[j - 1])) {  
				veca[i][j] = veca[i - 1][j - 1] + 1;  
				if (veca[i][j] > biggest)  
					biggest = veca[i][j];  
			}  
			else  
				veca[i][j] = 0;  

		}  
	}  
	return biggest;  
}  

int main() {  
	string input;  
	getline(cin, input);  
	stringstream ss(input);  
	string str1;  
	ss >> str1;  
	string str2;  
	ss >> str2;  
	vector<vector<int> > veca(str1.length() + 1);  
	cout << LCS_length(str1, str2, veca) << endl;  
	return 0;  
}  
/*
set<string> all_lcs;//注意这里要用set去除重复的LCS
//最长公共子串（LCS）
//二维数组veca[i][j]记录的是两个字符串Xi和Yj的LCS长度
int LCS_length(const string &str1, const string &str2, vector<vector<int> > &veca) {
	int i, j;
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
			}
			else {
				if (veca[i - 1][j] >= veca[i][j - 1])
					veca[i][j] = veca[i - 1][j];
				else
					veca[i][j] = veca[i][j-1];
			}
		}
	}
	return veca[str1.length()][str2.length()];
}

//该函数找出所有的LCS的序列，并将其存在vector中
void PrintAllLCS(string &str1, string &str2, int i, int j, 
	             vector<vector<int> > &veca, string lcs_str) {
//注意这里形参lcs_str不可以为引用，这里需要每次调用lcs_str都重新生成一个对象
	while (i > 0 && j > 0) {
		if (str1[i - 1] == str2[j - 1]) {
			lcs_str = str1[i - 1] + lcs_str; //逆向存放
			--i;
			--j;
		}
		else {
			if (veca[i - 1][j] > veca[i][j - 1]) //向左走
				--i;
			else if (veca[i - 1][j] < veca[i][j - 1]) //向上走
				--j;
			else { //此时向上向右均为LCS的元素
				PrintAllLCS(str1, str2, i - 1, j, veca, lcs_str);
				PrintAllLCS(str1, str2, i, j - 1, veca, lcs_str);
				return;
			}
		}
	}
	cout << "   " << lcs_str << endl;
	all_lcs.insert(lcs_str);
}
int main() {
	string input;
	getline(cin, input);
	stringstream ss(input);
	string str1, str2;
	ss >> str1;
	ss >> str2;
	//将veca初始化为一个二维数组,其行列值分别为str1和str2的长度加1
	//二维数组veca记录的是两个字符串Xi和Yj的LCS长度
	vector<vector<int> > veca(str1.length() + 1, vector<int>(str2.length() + 1));
	cout << LCS_length(str1, str2, veca) << endl;

	string lcs_str;
	PrintAllLCS(str1, str2, str1.length(), str2.length(), veca, lcs_str);
	set<string>::iterator iter = all_lcs.begin();
	while (iter != all_lcs.end()) {
		cout << *iter++ << endl;
	}
	return 0;
}
*/
/*
//输出最长公共子串（LCS）
//二维数组veca记录的是两个字符串Xi和Yj的LCS长度
int LCS_length(const string &str1, const string &str2, 
	            vector<vector<int> > &veca, vector<vector<int> > &vecb) {
	int i, j;
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
			//如果Xi-1 == Yj-1，那么最长子序列为veca[i - 1][j - 1] + 1
			//此时将vecb[i][j] = 1表明str1[i-1]是子问题LCS的一个元素
			if (str1[i - 1] == str2[j - 1]) {
				veca[i][j] = veca[i - 1][j - 1] + 1;
				vecb[i][j] = 1;
			}
			else {
				if (veca[i - 1][j] >= veca[i][j - 1]) {
					veca[i][j] = veca[i - 1][j];
					vecb[i][j] = 2;
				}
				else {
					veca[i][j] = veca[i][j-1];
					vecb[i][j] = 3;
				}
			}
		}
	}
	return veca[str1.length()][str2.length()];
}

//该函数用于输出一个LCS的序列
//这里输出的顺序是先向上寻找，再向左寻找
void PrintOneLCS(vector<vector<int> > &vecb, string &str1, int i, int j) {
	if (i == 0 || j == 0)
		return;
	if (vecb[i][j] == 1) {
		PrintOneLCS(vecb, str1, i - 1, j - 1);
		cout << str1[i - 1] << " ";
	}
	else if (vecb[i][j] == 2)
		PrintOneLCS(vecb, str1, i -1, j);
	else
		PrintOneLCS(vecb, str1, i, j - 1);
}

int main() {
	string input;
	getline(cin, input);
	stringstream ss(input);
	string str1, str2;
	ss >> str1;
	ss >> str2;
	//将veca初始化为一个二维数组,其行列值分别为str1和str2的长度加1
	//二维数组veca记录的是两个字符串Xi和Yj的LCS长度
	//二维数组vecb[i][j]记录veca[i][j]时所选择的子问题的最优解
	vector<vector<int> > veca(str1.length() + 1, vector<int>(str2.length() + 1));
	vector<vector<int> > vecb(str1.length() + 1, vector<int>(str2.length() + 1));
	cout << LCS_length(str1, str2, veca, vecb) << endl;
	//PrintOneLCS(vecb, str1, str1.length(), str2.length());
	return 0;
}

/*
int main() {
	int num;
	cin >> num;
	int i = 0;
	map<string, int> m;
	while (i < num) {
		string name;
		cin >> name;
		m.insert(make_pair(name, 0));
		++i;
	}

	int num2;
	cin >> num2;
	i = 0;
	int invalid = 0;
	while (i < num2) {
		string nameToVote;
		cin >> nameToVote;
		map<string, int>::iterator iter = m.find(nameToVote);
		if (iter != m.end()) {
			++(iter->second);
			++invalid;
		}
		++i;
	}

	map<string, int>::iterator it = m.begin();
	while (it != m.end()) {
		cout << it->first << " : " << it->second << endl;
		++it;
	}
	cout << "Invalid : " << num2 - invalid << endl;
	return 0;
}
/*
//"求最大连续bit数"
//求一个int数的二进制表示中最大的连续1的个数
int main() {
	int n;
	cin >> n;
	int max_count = 0;
	int count = 0;
	bool flag = false;
	unsigned int num = 1;
	while (num) {
		if (n & num) {
			if (flag == true) {
				++count;
			}
			else {
				count = 1;
			}
			flag = true;
		}
		else {
			flag = false;
			count = 0;
		}
		if (count > max_count)
			max_count = count;
		num = num << 1;
	}
	cout << max_count << endl;
	return 0;
}
/*
using namespace std;

int f[11000] = {-1};

int main() {
	int test_num, res_num, c, v, kinds_food;
	int bot, top;
	int max_enjoy;
	cin >> test_num;
	while (test_num--) {
		cin >> res_num >> bot >> top;
		max_enjoy = -1;
		while (res_num--) {
			cin >> kinds_food;
			int i;
			memset(f, -1, sizeof(f));
			f[0] = 0;
			for (i = 0; i < kinds_food; i++) {
				cin >> c >> v;
				int j;
				for (j = top; j >= c; j--) {
					if (f[j - c] != -1)
						f[j] = max(f[j], f[j - c] + v);
				}
			}
			for (i = bot; i <= top; i++) {
				max_enjoy = max(max_enjoy, f[i]);
			}
		}
		if (max_enjoy == -1)
			cout << "0";
		else
			cout << max_enjoy << endl;
	}
}
*/
/*
//连续输入两个字符串，请按长度为8拆分每个字符串后输出到新的字符串数组；
//长度不是8整数倍的字符串请在后面补数字0，空字符串不处理。
int main() {
	int n = 2;
	int i = 0;
	vector<string> svec;
	while (i < n) {
		string str;
		cin >> str;
		svec.push_back(str);
		i++;
	}
	vector<string>::iterator  iter = svec.begin();
	while (iter != svec.end()) {
		int strLen = (*iter).length();
		int k = strLen / 8;
		int i = 0, j = 0;
		int m = 0;
		for (i = 0; i < k; i++) {
			for (j = m; j < m + 8; ++j)
				cout << (*iter)[j];
			cout << endl;
			m += 8;
		}
		for (j = m; j < m + 8; ++j) {
			if (j < strLen)
				cout << (*iter)[j];
			else
				cout << 0;
		}
		cout << endl;
		iter++;
	}

	return 0;
}
*/
/*
//！！！！！！！！！！！“取近似值”
int Clculate(double input)
{
	int n;
	if (input>=0)
	{
		n=int(input+0.5);
	}
	else
	{
		n=int(input-0.5);
	}
	return n;
}

void main()
{
	double f_num;
	cin>>f_num;
	cout<<Clculate(f_num)<<endl;
}
*/
/*
int main() {
	string num;
	cin >> num;
	string sub_num = "";
	int pos = 0;
	bool before_point = true;
	bool negative = false;
	int i;
	int count_point = 0;
	if ('-' == num[0]) {
		negative = true;
	}
	else if ('0' >= num[0] && '9' <= num[0]) {
		sub_num[0] = num[0];
	}
	else
		return 0;
	
	for (i = 1; i < num.length(); i++) {
		if (num[i] < '0' && num[i] > '9')
			return 0;
		if (num[i] == '.') {
			pos = i + 1;
			count_point++;
			before_point = false;
		}
		if (true == before_point) {
			sub_num += num[i];
		} 
		if (count_point > 1)
			return 0;
	}
	char temp;
	if (pos < num.length())
		temp = num[pos];
	else
		return 0;
	int sub_result = 0;
	for (i = 0; i < sub_num.length(); i++) {
		sub_result = sub_result * 10 + sub_num[i] - '0';
	}
	if (temp >= '5' && temp <= '9') {
		sub_result += 1;
	}
	if (negative)
		cout << -sub_result << endl;
	else
		cout << sub_result << endl;
	return 0;
}
*/
/*
//纯指针操作：【id:1990】在字符串中找出连续最长的数字串
int Continumax(char *& outputstr, char *inputstr) {
	//要改变outputstr的值并返回，需要用引用
	int len = 0;
	int maxlen = 0;
	char *p = inputstr;
	char *q;
	while (*p != '\0') {
		while ((*p < '0' || *p > '9') && *p != '\0')
			p++;
		len = 0;
		if (*p != '\0')
			q = p;
		while (*p >= '0' && *p <= '9' && *p != '\0') {
			len++;
			p++;
		}
		if (len > maxlen) {
			outputstr = q;
			maxlen = len;
		}
	}
	return maxlen;
}

int main() {
	char str[1000] = {'\0'};
	gets(str);
	char *outputstr;
	int n = Continumax(outputstr, str);
	if ( n > 0)
		cout << outputstr << "," << n;
	else
		cout << 0;
	return 0;
}
*/
/*
//【id:1990】在字符串中找出连续最长的数字串
unsigned int Continumax(char **pOutputstr, char *intputstr) {
	char *result = (char *)malloc(sizeof(char) * 1000);
	memset(result, 0, sizeof(result));

	char *temp = (char *)malloc(sizeof(char) * 1000);
	memset(temp, 0, sizeof(temp));

	if (intputstr == "" || intputstr == NULL) {
		result[0] = '\0';
		*pOutputstr = result;
		return 0;
	}

	int count = 0;
	int tempc = 0;
	int i;
	for (i = 0; i < strlen(intputstr); i++) {
		if (intputstr[i] >= '0' && intputstr[i] <= '9') {
			temp[count] = intputstr[i];
			count++;
		}
		else {
			if (count >= tempc) {
				memset(result, 0, sizeof(result));
				tempc = count;
				temp[count] = '\0';
				int j;
				for (j = 0; j < count; j++)
					result[j] = temp[j];
				result[count] = '\0';
			}
			count = 0;
			memset(temp, 0, sizeof(temp));
		}
	}

	if (temp != "") {
		if (count >= tempc) {
			memset(result, 0, sizeof(result));
			tempc = count;
			temp[count] = '\0';
			int j;
			for (j = 0; j < count; j++) {
				result[j] = temp[j];
			}
			result[count] = '\0';
		}
		count = 0;
		memset(temp, 0, sizeof(temp));
	}
	if (tempc == 0) {
		result[0] = '\0';
		*pOutputstr = result;
		return 0;
	}
	else {
		*pOutputstr = result;
		return tempc;
	}
	free(result);
	free(temp);
}
int main() {
	char str[1000] = {'\0'};
	gets(str);
	char *outputstr;
	int n = Continumax(&outputstr, str);
	if ( n > 0)
		cout << outputstr << "," << n;
	else
		cout << 0;
	return 0;
}
*/
/*
int main() {
	int hash[10] = {0};
	int a;
	cin >> a;
	if (a == 0) {
		cout << 0;
		return 0;
	}
	bool have_cout = 0;
	while (a > 0) {
		int n = a % 10;
		if (hash[n] == 0) {
	 	    hash[n] = 1;
			if (n != 0) {
				cout << n;
				have_cout = 1;
			}
			else {
				if (have_cout == 1) {
					cout << n;
				}
			}

		}
		a /= 10;
	}
	cout << endl;
}
/*
//!!!!!!!!!!!【id:1969】!!!!!!!!!!!
int main() {
	string str;
	getline(cin, str);
	int hash[128] = {0};
	int i = 0;
	for (i = 0; i < str.length(); i++) {
		if ((str[i] >= 'A' && str[i] <= 'Z') ||
			 (str[i] >= 'a' && str[i] <= 'z') ||
			 (str[i] == ' ') || 
			 (str[i] >= '0' && str[i] <= '9') 
			) {
				 hash[str[i]]++;
		}
	}
	map<int, set<int> > m;
	for (i = 0; i < 128; i++) {
		if (hash[i] > 0) {
			//m.insert(make_pair(hash[i], set<int>().insert(1)));
			m[hash[i]].insert(i);
		}
	}
	map<int, set<int> >::reverse_iterator iter = m.rbegin();
	while (iter != m.rend()) {
		set<int>::iterator set_iter = iter->second.begin();
		while (set_iter != iter->second.end()) {
			cout << (char)(*set_iter++);
		}
		iter++;
	}
	cout << endl;
}*/
/*
//翻转字符串：
//输入：abc efd 12
//输出：12 efd abc
string str;
void reverse_string(int a, int b) {
	while (a < b) {
		char temp = str[a];
		str[a] = str[b];
		str[b] = temp;
		a++;
		b--;
	}
}

void main_reverse(int strLen) {
	int start = 0;
	int end = start;
	while (start < strLen) {
		end = str.find(' ', start);
		if (end == string::npos) {
			reverse_string(start, str.length() - 1);
			break;
		}
		else if (end) {
			reverse_string(start, --end);
			end += 2;
			start = end;
		}
	}
}

int main() {
	getline(cin, str);
	int i = 0;
	int strLen = str.length();
	reverse_string(0, strLen - 1);
	main_reverse(strLen);
	cout << str ;
}
*/
/*
int main() {
	string str;
	getline(cin, str);
	int hash[128] = {0};
	int i = 0;
	while (i < str.length()) {
		if (str[i] >= 0 && str[i] <= 127)
			hash[str[i]]++;
		i++;
	}
	int sum = 0;
	for (i = 0; i < 128; i++) {
		if (hash[i])
			sum++;
	}
	cout << sum;
}
*/
/*
int main() {
	int n;
	cin >> n;
	int i = 0;
	vector<string> svec;
	while (i < n) {
		string str;
		cin >> str;
		svec.push_back(str);
		i++;
	}
	vector<string>::iterator  iter = svec.begin();
	while (iter != svec.end()) {
		int strLen = (*iter).length();
		int k = strLen / 8;
		int i = 0, j = 0;
		int m = 0;
		for (i = 0; i < k; i++) {
			for (j = m; j < m + 8; ++j)
				cout << (*iter)[j];
			cout << endl;
			m += 8;
		}
		int last = strLen % 8;
		for (j = m; j < m + 8; ++j) {
			if (j < strLen)
				cout << (*iter)[j];
			else
				cout << 0;
		}
		cout << endl;
		iter++;
	}
	
	return 0;
}
*/
/*
//!!!!!!!!!ip地址合法性查看！！！！！！
int main()
{ 
	int a[4]={-1,-1,-1,-1},i=0;
	char temp='.';
	while(temp=='.') { 
		cin >> a[i++];
		temp=getchar();
	}
	for(i=0;i<4;i++) { 
		if (a[i]>=0 && a[i]<=255)
			continue;
		else { 
			cout<<"NO";
			break;
		}
	}
	if(i==4)
		cout<<"YES";
	return 0;
}
*/
/*
int main() {
	int a, b;
	cin >> a >> b;
	int aa = a, bb = b;
	if (a <= 0 || b <= 0)
		return -1;
	int temp;
	if (a < b) {
		temp = b;
		b = a;
		a = temp;
	}
	while (b != 0) {
		temp = a % b;
		a = b;
		b = temp;
	}
	cout << aa * bb / a << endl;
	return 0;
}
*/
/*
int main() {
	string str;
	getline(cin, str);
	int i;
	int count = 0;
	for (i = 0; i < str.length(); i++) {
		if (str[0] >= ('a' - 97) && str[0] < ('a' - 97 + 128))
			++count;
	}
	cout << count << endl;
}
*/
/*
int main() {
	string str, result = "";
	getline(cin, str);
	if (str.length() == 0) {
		cout << "";
		return 0;
	}
	bool start = true;
	string::iterator iter = str.begin();
	for (; iter != str.end(); ++iter) {
		if (start == true) {
			if (isdigit(*iter)) {
				result = result + "*" + *iter;
				start = false;
			}
			else {
				result = result + *iter;
			}
		}
		else {
			if (isdigit(*iter)) {
				result = result + *iter;
			}
			else {
				result = result + "*" + *iter;
				start = true;
			}
		}
	}
	if (start == false)
		result += "*";
	cout << result << endl;
	return 0;
}
*/
//int main() {
//	int n;
//	scanf("%d", &n);
//	char str[32] = {'\0'};
//	if (n == 0)
//		str[0] = '0';
//	while (n > 0) {
//		int a = n % 10;
//		str[strlen(str)] = '0' + a;
//		n /= 10;
//	}
//	printf("%s", str);
//}
//int main() {
//	string str;
//	getline(cin, str);
//	char ch;
//	cin >> ch;
//	int i = 0;
//	int count = 0;
//	string::iterator iter = str.begin();
//	while (iter != str.end()) {
//		if (*iter++ == ch)
//			++count;
//	}
//	cout <<count;
//}
/*
//http://www.itmian4.net/forum.php?mod=viewthread&tid=3412&highlight=%BB%AA%CE%AA
void stringFilter(const char *pInputStr, long InputLen, char *pOutputStr) {
	bool hash[26] = {false};
	int i = 0, j = 0;
	for (i = 0; i < InputLen; i++) {
		if (false == hash[pInputStr[i] - 'a']) {
			hash[pInputStr[i] - 'a'] = true;
			pOutputStr[j++] = pInputStr[i];
		}
	}
	pOutputStr[j] = '\0';
}

void stringZip(const char *pInputStr, long InputLen, char *pOutStr) {
	int i, j, k, num;
	char buffer[20];
	for (i = 0, k = 0; i < InputLen; i++) {
		num = 0;
		for (j = i + 1; j < InputLen; j++) {
			if (pInputStr[j] == pInputStr[i])
				++num;
			else
				break;
		}
		if (0 != num) {  //重复的字符可能是多位数
			memset(buffer, 0, sizeof(buffer));
			itoa(num + 1, buffer, 10);
			strncpy(pOutStr + k, buffer, sizeof(buffer));
			k += strlen(buffer);
		}
		pOutStr[k++] = pInputStr[i];
		i = i + num + 1;
	}
	pOutStr[k] = '\0';
}
*/
//void arithmetic(const char *pInput, long InputLen, char *pOutput) {
//	int sum1 = 0, sum2 = 0, flag = 1, result = 0;
//	int i = 0, k, j;
//	int haveplus = 0, haveminus = 0;
//	
//	//求第一个数（100以内）
//	for (i = 0; pInput[i] != ' '; i++) {
//		if (pInput[i] >= '0' && pInput[i] <= '9' && i <= 2)
//			sum1 = sum1 * 10 + (pInput[i] - '0');
//		else {
//			pOutput[0] = '0';
//			pOutput[1] = '\0';
//			return;
//		}
//	}
//
//	while (pInput[i++] == ' ') {} //跳过第一个数和运算符之间的空格
//	for ( ; i < InputLen; i++) { //判断符号是否符合要求
//		switch (pInput[i]) {
//		case '+':
//			++haveplus;
//			break;
//		case '-':
//			++haveminus;
//			break;
//		}
//		if (!(((haveplus == 1) && (haveminus == 0)) ||
//			 ((haveminus ==1) && (haveplus == 0)))) {
//				 pOutput[0] = '0';
//				 pOutput[1] = '\0';
//				 return;
//		}
//	}
//
//	while (pInput[i++] == ' ') {} //跳过运算符和第二个数之间的空格
//	for ( ; i < InputLen; i++)
//
//}

//int main() {
//	char inputStr[] = "+a111abbbaaaacdAAAeef-";
//	char output[100];
//	//stringFilter(inputStr, sizeof(inputStr)/sizeof(char), output);
//	stringZip(inputStr, sizeof(inputStr)/sizeof(char), output);
//	printf("%s\n", output);
//}
/*
//http://www.itmian4.net/forum.php?mod=viewthread&tid=3714&highlight=%BB%AA%CE%AA
int huiwen_aux(int num) {
	int re_num = 0;
	while (num > 0) {
		re_num = re_num * 10 + num % 10;
		num = num / 10;
	}
	return re_num;
}
int huiwen(int num) {
	int re_num = 0, result = num;
	int i;
	for (i = 0; i < 7; i++) {
		re_num = huiwen_aux(num);
		result = num + re_num;
		num = result;
	}
	if (result == huiwen_aux(result))
		return 1;
	else
		return 0;
}

//十进制转任意进制
void jinzhi(int num, int n) {
	if (n <= 1) //必须是二进制以及二进制以上的进制
		return;
	int i = 0, j = 0;
	int result[32] = {-1};
	while (num != 0) {
		result[j] = num % n;
		num /= n;
		j++;
	}
	for (i = j - 1; i >= 0; i--) {
		printf("%d", result[i]);
	}
}
*/
/*
//http://www.itmian4.net/forum.php?mod=viewthread&tid=3247&highlight=%BB%AA%CE%AA
void Encryption(char *inputStr, int inputLen) {
	if (inputStr == NULL)
		return;
	int i = inputLen / 2;
	printf("%d", i);
	int j;
	if (i) {
		for (j = 0; j < i; j++) {
			inputStr[j] = (inputStr[j] - 'a' - 1) % 26 + 'a';
		}
		for (j = i + 1; j < inputLen; j++)
			inputStr[j] = (inputStr[j] - 'a' + 1) % 26 + 'a';
	}
	printf("%s\n", inputStr);
}
*/
/*
//输入字符串，按照字母的ascii码顺序排序，其他非字母字符在字符串中位置不变
//如，输入Wor#d，输出Wdo#r
//快速排序实现
void QuickStrSort(char str[], int left, int right) {
	char pivot = str[left];
	int i = left, j = right;
	if (left < right) {
		while (i < j) {
			//j从右向左找第一个小于枢纽的字母，如果遇到不是字母的继续向前找
			while (i < j && 
				     (
				       (isalpha(str[j]) && str[j] >= pivot) || (!isalpha(str[j]))
				     )
				  )
				j--;
			str[i] = str[j];
			//i从左向右找第一个大于枢纽的字母，遇到不是字母继续向后找
			while (i < j && 
				((isalpha(str[i]) && str[i] <= pivot) || (!isalpha(str[i])))
				)
				i++;
			str[j] = str[i];
		}
		str[i] = pivot;
		QuickStrSort(str, left, i - 1);
		QuickStrSort(str, i + 1, right);
	}
}
int main() {
	char str[102];
	while (1) {
		cin >> str;
		QuickStrSort(str, 0, strlen(str) - 1);
		cout << str << endl << endl;;
	}
	return 0;
}
/*
int Str2Int(char *str) {
	int num = 0;
	while (str == NULL)
		break;
	int flag = 1;
	while (*str != '\0') {
		if (*str == '-') {
			flag = -1;
			++str;
		}
		if (*str >= '0' && *str <= '9') {
			num = num * 10 + *str - '0';
			++str;
		}
		else
			break;
	}
	return num;
}

//int main() {
//	char str[100];
//	cin >> str;
//	Str2Int(str);
//	cout << str << endl;
//}

//int main() {
//	char c;
//	while (c = getc(stdin)) {
//		if (isupper(c)) {
//			printf("%c\n", (c - 'A' + 1) % 26 + 'A');
//		}
//		if (islower(c)) {
//			printf("%c\n", (c - 'a' - 1 + 26) % 26 + 'a');
//		}
//	}
//}
*/