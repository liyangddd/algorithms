#include "3avl_tree_c++.h"
#include "test.h"
//int main() {
//	AvlTree<int> tree;
//	int i = 0;
//	while (i != 9) {
//		tree.insert(i++);
//	}
//	tree.printTree();
//
//	cout << endl << "删除11但11不存在：" << endl;
//	tree.remove(11);
//	tree.printTree();
//
//    cout << endl << "删除 5和8：" << endl;
//	tree.remove(5);
//	tree.remove(8);
//	tree.printTree();
//	return 0;
//}


//template <class Elem>
//class FreeList
//{
//private:
//	static FreeList<Elem> *freelist;
//public:
//	Elem element;
//	FreeList *next;
//	FreeList(const Elem& elemval, FreeList* nextval =NULL)
//	{
//		element = elemval;
//		next = nextval;
//	}
//	FreeList(FreeList *nextval =NULL)
//	{
//		next = nextval;
//	}
//	void* operator new(size_t);
//	void operator delete(void*);
//};
//
//template <class Elem>
//FreeList<Elem>* FreeList<Elem>::freelist = NULL;
//
//template <class Elem>
//void* FreeList<Elem>::operator new(size_t)
//{
//	if(NULL == freelist)
//		return ::new FreeList;
//	FreeList<Elem>* temp = freelist;
//	freelist = freelist->next;
//	return temp;
//}
//
//template<class Elem>
//void FreeList<Elem>::operator delete(void* ptr)
//{
//	((FreeList<Elem>*)ptr)->next = freelist;
//	freelist = (FreeList<Elem>*)ptr;
//}
