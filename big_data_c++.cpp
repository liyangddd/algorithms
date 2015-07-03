#include "test.h"

const int maxn = 1001;
class BigData {
	int len;
	int data[maxn];
	BigData Sub(const BigData& a, const BigData& b) {
		int i;
		BigData result;
		int flag = 0;
		for (i = 0; i < a.len; ++i) {
			int this_sub = a.data[i] - flag;
			result.data[i] = this_sub - b.data[i];
			if (result.data[i] >= 0)
				flag = 0;
			else {
				flag = 1;
				result.data[i] += 10;
			}
			result.len = a.len;
		}
		result.clean();
		return result;
	}

	void clean() {
		while (len > 1 && !data[len - 1])
			len--;
	}

	string str() const {
		string res = "";
		int i;
		for (i = 0; i < len; i++)
			res = (char)(data[i] + '0') + res;
		if (res.empty())
			res = "0";
		return res;
	}

public:
	BigData() {
		memset(data, 0, sizeof(data));
		len = 1;
	}

	BigData(int num) {
		*this = num;
	}

	BigData(const char* num) {
		*this = num;
	} 

	BigData& operator=(int num) {
		char data[maxn];
		sprintf(data, "%d", num);
		*this = data;
		return *this;
	}

	BigData& operator=(const char *num) {
		len = strlen(num);
		int i;
		for (i = 0; i < len; ++i)
			data[i] = num[len - i - 1] - '0';
		return *this;
	}

	BigData operator+(const BigData& b) const {
		BigData c;
		c.len = 0;
		int i, flag = 0;
		int max_len = len > b.len ? len : b.len;
		for (i = 0; i < max_len; ++i) {
			int sum = (flag + data[i] + b.data[i]);
			c.data[c.len++] = sum % 10;
			flag = sum / 10;
		}
		if (flag != 0)
			c.data[c.len++] = 1;
		c.clean();
		return c;
	}

	BigData& operator+=(const BigData& b) {
		*this = *this + b;
		return *this;
	}

	BigData& operator-=(const BigData& b) {
		*this = *this - b;
		return *this;
	}

	bool operator<(const BigData& b) const {
		if (len != b.len)
			return len < b.len;
		int i;
		for (i = len - 1; i >= 0; --i) {
			if (data[i] != b.data[i])
				return data[i] < b.data[i];
		}
		return false;
	}

	bool operator>(const BigData& b) const {
		return b < *this;
	}

	bool operator<=(const BigData& b) const {
		return !(*this > b);
	}

	bool operator>=(const BigData& b) const {
		return !(*this < b);
	}

	bool operator==(const BigData& b) const {
		return !(*this > b) && !(*this < b);
	}

	BigData operator-(const BigData& b) {
		BigData c;
		c.len = 0;
		if (*this == b) {
			c.data[++c.len] = 0;
			return c;
		}
		else if (*this > b) {
			c = Sub(*this, b);
		}
		else {
			c = Sub(b, *this);
			c.data[c.len++] = '-' - '0';
		}
		return c;
	}

	BigData operator*(const BigData& b) {
		int i, j, flag;
		BigData result;
		for (i = 0; i < len; ++i) {
			for (j = 0; j < b.len; ++j) {
				result.data[i + j] = data[i] * b.data[j];
			}
		}
		result.len = len + b.len;
		for (i = 0; i <result.len; ++i) {
			result.data[i + 1] += result.data[i] / 10;
			result.data[i] %= 10;
		}
		result.clean();
		return result;
	}

	friend ostream& operator<<(ostream& out, const BigData& bd) {
		out << bd.str();
		return out;
	}

	friend istream& operator>>(istream& in, BigData& bd) {
		string s;
		in >> s;
		bd = s.c_str();
		return in;
	}
};

//int main() {
//	BigData a, b;
//	cin >> a >> b;
//	cout << "a: " << a << endl;
//	cout << "b: " << b << endl;
//	cout << "a+b: " << a + b<< endl;
//	cout << "a-b: " << a - b << endl;
//	cout << "a*b: " << a * b << endl;
//	a += b;
//	cout << "a += b: " << a << endl;
//	a -= b;
//	cout << "a -= b: " << a << endl;
//	return 0;
//}

string Mutiplication(const string data1, const string data2) {
	if (data1 == "" || data2 == "") //非法输入
		return "";

	string result;
	int length_data1 = data1.size();
	int length_data2 = data2.size();

	vector<int> result_number(length_data1 +  length_data2 - 1, 0);

	//处理有负数的情况，data1为负数则data1_end等于1，data2为负数则data2_end等于1
	int data1_end = 0, data2_end = 0;
	if (data1[0] - '-' == 0 && data2[0] - '-' == 0) {
		data1_end = 1;
		data2_end = 1;
	}
	else if (data1[0] - '-' == 0)
		data1_end = 1;
	else if (data2[0] - '-' == 0)
		data2_end = 1;
	else {}

	for (int i = length_data2 - 1; i >= data2_end; --i) {
		for (int j = length_data1 - 1; j >= data1_end; --j) {
			if (!isdigit(data1[j]) || !isdigit(data2[i])) {
				cerr << "invalid number";
				return "";
			}
			//result_number记录乘法过程中每一位
			result_number[i + j] += (data2[i] - '0') * (data1[j] - '0');
		}
	}

	//处理进位并将结果存到字符串result
	int carry = 0;
	for (int i = result_number.size() - 1; i >= 0; --i) {
		result_number[i] += carry;
		carry = result_number[i] / 10;
		result = string(1, result_number[i] % 10 + '0') + result;
	}

	if (carry > 0) //最高位的进位
		result = string(1, carry + '0') + result;

	//下面几行处理有乘数为0的情况，如果不处理，会出现：
	//1234 * 0 = 0000的情况
	string::iterator iter = result.begin();
	//如果乘法结果的前n - 1位为0，则将其删除，只保留最后一位
	while (*iter - '0' == 0 && iter < result.end() - 1) {
		iter = result.erase(iter);
	}

	//如果结果为负数则在结果字符串中添加负号
	if (data1_end ^ data2_end)
		result = "-" + result;
	return result;
}

//int main() {
//	string a;
//	string b;
//	while (cin >> a >> b)
//		cout << "result: " << Mutiplication(a, b) << endl;
//}
