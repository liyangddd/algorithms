#include "3doubly_list_c++.h"
#include "test.h"

template <typename Object>
void PrintAllElements(List<Object> lst) {
	if (lst.empty()) {
		cout << "the list is empty." << endl;
		return;
	}
	List<Object>::iterator iter = lst.begin();
	while (iter != lst.end()) {
		cout << *iter << " ";
		iter++;
	}
	cout << endl;
}

/*
int main() {
	List<int> lst;
	int i;
	if (lst.empty()) {
		cout << "empty" << endl;
	}
	lst.push_back(3);
	for (i = 0; i < 10; ++i)
		lst.insert(lst.end(), i);
	PrintAllElements(lst);

	List<string> lst_str;
	lst_str.push_back("test1");
	lst_str.push_back("test2");
	PrintAllElements(lst_str);

	List<int> lst_copy = lst;
	PrintAllElements(lst_copy);

	cout << *lst.begin() << endl;
	lst.pop_front();
	lst.pop_back();
	lst.pop_back();
	lst.erase(lst.begin(), lst.end());
	PrintAllElements(lst);
	cout << lst.size() << endl;

	return 0;
}
*/