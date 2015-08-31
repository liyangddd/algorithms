#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <string>
#include <exception>
using namespace std;

size_t strlen1(const char *str) {
	assert(str != NULL);
	unsigned int length = 0;
	while ((*str++) != '\0')
		++length;
	return length;
}

size_t strlen2(const char *str) {
	assert(str != NULL);
	const char *end = str;
	while (*end++) ;
	return ((int)(end - str - 1));
}

//strstr有两个版本：const和非const
//const char *strstr1(const char *str, const char *substr);
//char *strstr1(char *str, const char *substr);
char *strstr1(char *str, const char *substr) {
	if (str == NULL || substr ==  NULL)
		return NULL;

	char *p_str = str;
	const char *p_substr = substr;
	for ( ; *str != '\0'; ++str) {
		p_str = str;
		p_substr = substr;
		for ( ; *p_substr != '\0' && *p_str == *p_substr; ++p_str, ++p_substr)
			;
		if (*p_substr == '\0')
			return str;
	}
	return NULL;
}

char *strcat1(char *destination, const char *source) {
	assert (destination != NULL && source != NULL);
	char *cp = destination;
	while (*cp)
		++cp;
	while (*cp++ = *source++) ;
	return destination;
}

char* strncat1(char *destination, const char *source, size_t count) {
	assert (destination != NULL && source != NULL);
	char *cp = destination;
	while (*cp)
		++cp;
	while (count-- && *source != '\0')
		*cp++ = *source++;
	*cp = '\0';
	return destination;
}

char *strcpy(char *destination, const char *source) {
	assert(destination != NULL && source != NULL);

	if (destination == source)
		return destination;

	char *cp = destination;
	while ((*cp++ = *source++) != '\0')
		;
	return destination;
}

char *strncpy1(char *destination, const char *source, size_t count) {
	assert(destination != NULL && source != NULL);

	if (destination == source)
		return destination;

	char *cp = destination;
	while (count-- && *source != '\0')
		*cp++ = *source++;
	*cp = '\0';
	return destination;
}

int strcmp1(const char *str1, const char *str2) {
	assert(str1 != NULL && str2 != NULL);

	int result = 0;
	while ( !(result = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2) {
		++str1;
		++str2;
	}

	if (result < 0)
		return -1;
	else if (result > 0)
		return 1;
	return result;
}

int strncmp1(const char *str1, const char *str2, size_t count) {
	assert(str1 != NULL && str2 != NULL);

	int result = 0;
	//下一行必须将count--写在前边，否则count等于0时还会计算一个ret
	while (count-- && (!(result = *(unsigned char*)str1 - *(unsigned char*)str2)) && *str2) {
		++str1;
		++str2;
	}

	if (result < 0)
		return -1;
	else if (result > 0)
		return 1;
	return result;
}

/*
Returns a pointer to the first occurrence in str1 of any of the 
characters that are part of str2, or a null pointer if there are no matches.
The search does not include the terminating null-characters
该函数也是两个版本：const和非const版本
*/
char *strpbrk1(char *str1, const char *str2) {     
	assert((str1 != NULL) && (str2 != NULL));     
	const char *s;     
	while (*str1 != '\0') {     
		s = str2;     
		while (*s != '\0'){     
			if (*str1 == *s)     
				return str1;     
			++ s;     
		}     
		++ str1;     
	}     
	return NULL;     
}     

void *memcpy1(void *destination, const void *source, size_t count) {
	assert (destination != NULL && source != NULL);

	void *address = destination;
	while (count--) {
		*(char*)destination = *(char*)source;
		destination = (char *)destination + 1;
		source = (char *)source + 1;
	}
	return address;
}

void *memmove1(void *destination, const void *source, size_t count) {
	assert (destination != NULL && source != NULL);

	char *pdest = (char*)destination;
	char *psrc = (char*)source;
	//pdest在psrc后面，且两者距离小于count，从尾部开始移动，
	//其他情况从头部开始移动
	if ((pdest > psrc) && (pdest - psrc < count)) {
		while (count--)
			*(pdest + count) = *(psrc + count);
	}
	else {
		while (count--)
			*pdest++ = *psrc++;
	}
	return destination;
}

void *memset1(void *str, int value, size_t count) {
	if (str == NULL)
		return NULL;

	void *p = str;
	while (count--) {
		*(char*)p = (char)value;
		p = (char *)p + 1;
	}
	return str;
}

//两个版本：
//const void * memchr ( const void * ptr, int value, size_t num );
//void * memchr (void * ptr, int value, size_t num );
void *memchr1(void *str, int value, size_t count) {
	if (str == NULL)
		return NULL;
	while (count--) {
		if (*(char*)str == value)
			return (void*)str;
		str = (char*)str + 1;
	}
	return NULL;
}

//strtok：
//static char *last保存没有处理完的字串。    
char *strtok1(char *strToken, const char *str) {    
	assert(str != NULL);    
	static char *last;    

	//如果strToken等于NULL并且last记录的部分也为NULL证明处理完，返回NULL
	if (strToken == NULL && (strToken = last) == NULL)    
		return (NULL);    

	char *s = strToken;    
	const char *t = str;    
	while (*s != '\0') {    
		t = str;    
		while (*t != '\0') {    
			if (*s == *t) {    
				last = s + 1; 
				//跳过str中的字符，继续向strTok后匹配
				if (s - strToken == 0) {    
					strToken = last;    
					break;    
				}    
				*(strToken + (s - strToken)) = '\0';    
				return strToken;    
			}    
			++t;    
		}    
		++s;    
	}    
	return NULL;    
}   

//strtok1函数调用方式：
//第一次调用strtok函数设置两个参数，第一次分割的结果
//，返回串中第一个','之前的字符串“abc”；
//第二次调用strtok第一个参数设置为NULL，返回分割后面串
//的结果：123，第三次返回ddd。
int main() {
	char str[] = "abc,  123,   ddd,   ";
	char *p = strtok1(str, ", ");  //第一次调用
	while (p) {
		cout << p << endl;
		p = strtok1(NULL, ", ");  //之后的调用
	}
}


//int main() {
//	int data = 33;
//	int *aa = &data;
//	int *bb = new int;
//	//cout << *(int*)memcpy1(bb, aa, 8) << *(int*)memcpy(bb, aa, 8)<< endl;
//
//	char a[10] = "abcd";
//	char *b = a + 2;
//	cout << strcpy(a, b) << endl;
//	/*cout << strcmp1(a, b )<< endl;
//	cout << strcmp(a, b) << endl;*/
//	//cout << strncpy1(b, a, 2);
//	//cout << strncat(b, a, 5);
//}

void GetNext(char* pattern,int next[]) {  
	int length_pattern = strlen(pattern);  
	next[0] = -1;  
	int k = -1;  
	int j = 0;  
	while (j < length_pattern - 1) {  
		//p[k]表示前缀，p[j]表示后缀  
		if (k == -1 || pattern[j] == pattern[k]) {  
			++k;  
			++j;  
			next[j] = k;  
		}  
		else
			k = next[k];
	}  
}

int KmpSearch(char* text, char* pattern) {  
	int i = 0;  
	int j = 0;  
	int length_text = strlen(text);  
	int length_pattern = strlen(pattern);
	int *next = new int[length_pattern];
	GetNext(pattern, next);

	for (int i = 0; i < length_pattern; ++i) 
		cout << next[i] << " ";
	cout << endl;

	while (i < length_text && j < length_pattern) {  
		//①如果j = -1,或者当前字符匹配成功(即text[i] == pattern[j]),令i++，j++      
		if (j == -1 || text[i] == pattern[j]) {  
			++i;
			++j;
		}
		else
			//②如果j != -1,且当前字符匹配失败(即text[i] != pattern[j]),
			//则令i不变,j = next[j]，next[j]即为j所对应的next值        
			j = next[j]; 
	}  
	delete[] next;
	if (j == length_pattern)  
		return i - j;  
	else  
		return -1;  
}  

int main() {
	char str[100] = {'\0'};
	char substr[100] = {'\0'};
	scanf("%s %s", str, substr);
	cout << KmpSearch(str, substr) << endl;
}
