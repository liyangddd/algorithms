//KMP算法
void GetNext(char* p,int next[]) {  
	int pLen = strlen(p);  
	next[0] = -1;  
	int k = -1;  
	int j = 0;  
	while (j < pLen - 1) {  
		//p[k]表示前缀，p[j]表示后缀  
		if (k == -1 || p[j] == p[k]) {  
			++k;  
			++j;  
			next[j] = k;  
		}  
		else {  
			k = next[k];  
		}  
	}  
}  
int KmpSearch(char* s, char* p) {  
	int i = 0;  
	int j = 0;  
	int sLen = strlen(s);  
	int pLen = strlen(p);
	int *next = new int[pLen];
	GetNext(p, next);
	while (i < sLen && j < pLen) {  
		//①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++      
		if (j == -1 || s[i] == p[j]) {  
			i++;  
			j++;  
		}  
		else {  
			//②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]      
			//next[j]即为j所对应的next值        
			j = next[j];  
		}  
	}  
	delete[] next;
	if (j == pLen)  
		return i - j;  
	else  
		return -1;  
}  

//int main() {
//	char str[100] = {'\0'};
//	char substr[100] = {'\0'};
//	scanf("%s %s", str, substr);
//	cout << KmpSearch(str, substr) << endl;
//}
