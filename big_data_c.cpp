#include "test.h"

const int maxn = 1001;
void BigdataAdd() {
	char data1_str[maxn], data2_str[maxn];
	int data1[maxn] = {0}, data2[maxn]  = {0}, data_sum[maxn]  = {0};
	int len_data1, len_data2, i;
	scanf("%s", data1_str);
	len_data1 = strlen(data1_str);
	for (i = 0; i < len_data1; ++i)
		data1[i] = data1_str[len_data1 - i - 1] - '0';
	scanf("%s", data2_str);
	len_data2 = strlen(data2_str);
	for (i = 0; i < len_data2; i++)
		data2[i] = data2_str[len_data2 - i - 1] - '0';
	int max_len = len_data1 > len_data2 ? len_data1 : len_data2;
	int flag = 0;              // flag标志进位的值
	for (i = 0; i < max_len; ++i) {
		data_sum[i] = (data1[i] + data2[i] + flag) % 10;
		flag = (data1[i] + data2[i] + flag) / 10;
	}
	printf("Sum: ");
	if (flag != 0) {
		data_sum[max_len] = 1;
		printf("%d", data_sum[max_len]);
	}
	for (i = max_len - 1; i >= 0; --i)
		printf("%d", data_sum[i]);
	printf("\n");
}

void BigdataSubtraction() {
	char data1_str[maxn], data2_str[maxn];
	int data1[maxn] = {0}, data2[maxn] = {0}, data_sub[maxn] = {0};
	int len_data1, len_data2;
	scanf("%s", data1_str);
	scanf("%s", data2_str);	
	len_data1 = strlen(data1_str);
	len_data2 = strlen(data2_str);
	int bigdata;
	if (len_data1 > len_data2)
		bigdata = 1;
	else if (len_data1 < len_data2)
		bigdata = -1;
	else
		bigdata = strcmp(data1_str, data2_str);
	int i;
	if (bigdata >= 0) {
		for (i = 0; i < len_data1; ++i)
			data1[i] = data1_str[len_data1 - i - 1] - '0';
		for (i = 0; i < len_data2; i++)
			data2[i] = data2_str[len_data2 - i - 1] - '0';
	}
	else {
		for (i = 0; i < len_data2; ++i)
			data1[i] = data2_str[len_data2 - i - 1] - '0';
		for (i = 0; i < len_data1; i++)
			data2[i] = data1_str[len_data1 - i - 1] - '0';
	}

	int flag = 0;             //flag表示借位
	int max_len = len_data1 >= len_data2 ? len_data1 : len_data2;
	for (i = 0; i < max_len; ++i) {
		int this_sub = data1[i] - flag;
		data_sub[i] = this_sub - data2[i];
		if (data_sub[i] >= 0) {
			flag = 0;
		}
		else {
			flag = 1;
			data_sub[i] += 10;
		}
	}
	printf("Subtraction: ");
	if (bigdata < 0)
		printf("-");
	while (max_len > 1 && !data_sub[max_len - 1])
		max_len--;
	for (i = max_len - 1; i >= 0; --i)
		printf("%d", data_sub[i]);
	printf("\n");
}


void BigdataMutiply() {
	char data1_str[maxn], data2_str[maxn];
	int data1[maxn] = {0}, data2[maxn]  = {0}, data_result[maxn]  = {0};
	int len_data1, len_data2;
	scanf("%s", data1_str);
	len_data1 = strlen(data1_str);
	int i;
	for (i = 0; i < len_data1; ++i)
		data1[i] = data1_str[len_data1 - i - 1] - '0';
	scanf("%s", data2_str);
	len_data2 = strlen(data2_str);
	for (i = 0; i < len_data2; i++)
		data2[i] = data2_str[len_data2 - i - 1] - '0';
	int j, flag;
	int len_data_result = len_data1 + len_data2;
	for (i = 0; i < len_data2; ++i) {
		for (j = 0; j < len_data1; ++j) {
			data_result[j + i] = data2[i] * data1[j];
		}
	}
	for (i = 0; i < len_data_result; ++i) {
		data_result[i + 1] += data_result[i] / 10;
		data_result[i] %= 10;
	}
	while (len_data_result > 1 && !data_result[len_data_result - 1])
		--len_data_result;
	printf("Result: ");
	for (i = len_data_result - 1; i >= 0; --i)
		printf("%d", data_result[i]);
	printf("\n");

}

/*
int main() {
	BigdataAdd();
	return 0;
}
*/