//Trie树的简单小例子，仅考虑小写字母，且对非法输入没做检测

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <cstring>
#include <iostream>
#define MAXBRANCH 26
using namespace std;

struct TrieNode {
	TrieNode * next_branch[MAXBRANCH];
	bool exist;
};

TrieNode* CreateTrieNode() {
	TrieNode *node = (TrieNode*)malloc(sizeof(TrieNode));
	node->exist = false;
	memset(node->next_branch, 0, sizeof(node->next_branch));
	return node;
}


void TrieInsert(TrieNode* root, char* word) {
	TrieNode* node = root;
	int id;
	while (*word) {
		id = *word - 'a';
		if (node->next_branch[id] == NULL)
			node->next_branch[id] = CreateTrieNode();
		node = node->next_branch[id];
		++word;
	}
	node->exist = true; //到达字符串结尾，将其标记为一个串
}

//在Trie树中查找word是否存在，存在返回true
//如果查找word是否是某个字符串的前缀，只要将
//返回值值改为return node;即可
bool TrieSearch(TrieNode* root, char *word) {
	TrieNode *node = root;
	int id;
	while (*word && node) {
		id = *word - 'a';
		node = node->next_branch[id];
		++word;
	}
	return (node && node->exist);
}

void DestroyTrieTree(TrieNode *root) {
	for (int i = 0; i < MAXBRANCH; i++) {
		if (root->next_branch[i])
			DestroyTrieTree(root->next_branch[i]);
	}
	free(root);
}

int main() {
	TrieNode * root = CreateTrieNode();
	char str[100];
	cout << "输入Trie中单词：" << endl;
	while (scanf("%s", str) && strcmp(str, "end") != 0) {
		TrieInsert(root, str);
	}

	cout << "输入待匹配的单词：" << endl;
	while (scanf("%s", str) != EOF) {
		if (TrieSearch(root, str))
			cout << "found" << endl;
		else
			cout << "not found" << endl;
	}
}
