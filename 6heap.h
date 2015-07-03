#ifndef TEST_HEAP_H
#define TEST_HEAP_H

#include "test.h"

/*
这里建立的是小根堆，元素存在vector容器中，根从下标为1的元素开始
*/
template <typename T>
class BinaryHeap {
public:
	explicit BinaryHeap(int capacity = 100)
		:array(capacity + 1), current_size(0) {}
	explicit BinaryHeap(const vector<T>& items)
		:array(items.size() + 10), current_size(items.size()) {
		int i;
		for (i = 0; i < items.size(); i++)
			array[i + 1] = items[i];
		BuildHeap();
	}

	bool IsEmpty() const {
		return current_size == 0;
	}

	const T& FindMin() const {
		if (IsEmpty())
			cout << "No items in binary heap" << endl;
		return array[1];
	}

	/*
	堆的插入操作是“上滤”的过程。最坏时间为O(logN)，平均时间为O(logN)。
	先在堆的下一个空闲位置上建立一个空穴，如果这样不破坏堆的性质，那么插入完成。
	否则，将空穴父节点的元素移入空穴，这样空穴上升了一层，到达父节点的位置。
	继续该过程，直到插入值可以放入空穴为止。
	*/
	void Insert(const T& value)	{
		if (current_size == array.size() - 1) //空间不够，重分配
			array.resize(array.size() * 2);
		int hole = ++current_size; //在堆的下一个空闲位置建立一个空穴
		/* 
		在空穴没上滤到根部并且插入值小于空穴父节点时，
		将父节点移入空穴，空穴位置上升一层 
		*/
		for ( ; hole > 1 && value < array[hole / 2]; hole /= 2)
			array[hole] = array[hole / 2];
		array[hole] = value; //将值插入到合适位置
    }

	/*
	删除操作最坏时间为O(logN)，平均时间为O(logN)。
	删除最小值时，根成空穴，且堆要少一个元素，
	因此原堆的最后一个元素X将要放到堆的某个位置；
	如果X可以放到空穴中则完成；否则要将空穴的儿子中较小的元素放入空穴，空穴
	下移，重复该过程直到X可以放入空穴。
	*/
	void DeleteMin();
	/*{
		if (IsEmpty())
			cout << "No items in binary heap" << endl;
		array[1] = array[current_size--];
		PercolateDown(1);
	}*/

	void DeleteMin(T& min_item) {
		if (IsEmpty())
			cout << "No items in binary heap" << endl;
		min_item = array[1];
		array[1] = array[current_size--];
		PercolateDown(1);
	}

	void MakeEmpty() {
		current_size = 0;
	}

	void PrintItems() {
		cout << "Items: ";
		int i = 1;
		while (i <= current_size) {;
			cout << array[i++] << " "
		}
		cout << endl;
	}

private:
	int current_size;
	vector<T> array;
	/*
	建立堆的操作最坏时间为O(NlogN)，平均时间为O(N)
	建立堆的过程就是堆排序的过程
	*/
	void BuildHeap() {
		int i;
		for (i = current_size / 2; i > 0; i--)
			PercolateDown(i);
	}

	/*
	该函数完成“下滤”过程。
	删除堆的过程就是要下滤的。
	而堆排序用到了删除堆的操作，因此，堆排序也是要下滤的。
	对任意输入序列建立堆也要下滤。
	该函数的做法是将插入值置入沿着从根开始
	包含最小儿子的一条路径上的正确位置
	*/
	void PercolateDown(int hole) {
		int pos_child;
		T tmp = array[hole];
		//当空穴位置没有到达堆的尾部前，循环向下层找空穴位置
		for ( ; hole * 2 <= current_size; hole = pos_child) {
			pos_child = 2 * hole;
			/*
			下边语句是要将较小孩子的下标移入空穴，将空穴移入下一层。
			下边的pos_child != current_size条件是控制当堆的节点为偶数时情况，
			当堆节点为偶数时，最后一个非叶节点只有一个左孩子，则此时要找的
			较小孩子的下标就是左孩子的下标，即不用执行下边第一个if
			*/
			if (pos_child != current_size && array[pos_child + 1] < array[pos_child])
				pos_child++;
			if (array[pos_child] < tmp)  //如果较小孩子比父节点小，则空穴下移一层
				array[hole] = array[pos_child];
			else
				break;
		}
		array[hole] = tmp;
	}
};
#endif