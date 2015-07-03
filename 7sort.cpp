#include "test.h"

/*
插入排序的C实现。
平均情形为O(N^2)。
一共进行n-1趟排序，第i趟排序时保证前i个(0到i-1)是排好序的
*/
void InsertionSort(int array[], int n) {
	int i, j;
	int tmp;
	for (i = 1; i < n; i++) { 
		/*
		这里实现了数组元素移动而没有明显使用交换。
		位置i上的元素存储在tmp中，而位置i之前的所有更大的元素
		都被向右移动一个位置；然后tmp被放置在正确的位置上。
		这个技巧与实现二叉堆所用的技巧相同（可以减少交换次数，加快速度）。
		*/
		tmp = array[i];
		for (j = i; j > 0 && array[j - 1] > tmp; j--)
			array[j] = array[j - 1];
		array[j] = tmp;
	}
}


template<typename T>
void ShellSort(vector<T>& unorder) {  //希尔排序
	int gap;
	int i;
	for (gap = unorder.size() / 2; gap > 0; gap /= 2)
		for (i = gap; i < unorder.size(); i++) {
			T tmp = unorder[i];
			int j = i;
			for (; j >= gap && tmp < unorder[j - gap]; j -= gap)
				unorder[j] = unorder[j - gap];
			unorder[j] = tmp;
		}
}

template<typename T>
void PrintValue(vector<T>& a) {
	vector<T>::iterator iter = a.begin();
	while (iter != a.end()) {
		cout << *iter++ << " ";
	}
	cout << endl;
}

/*
（大根）堆排序，花费O(NlogN)。
对于小根堆来说，一般的思路是每次删除最小值，执行N次删除；
每次将删除的元素拷贝到一个新的数组，那么新数组将按照从小到大的
顺序排列。这里的主要问题是空间的：使用新数组，使存储空间增加了一倍。
一个技巧是：每次删除一个堆元素，堆大小会减少1。那么位于堆最后的
那个空间可以用来存放刚刚被删除的元素。按照这种思路，不用额外的空间
即可完成排序。对小根堆，该方式排序完的数组是递减的，
那么，如果我们建立堆时用大根堆，则该方式得到的排序结果是递增的。
*/
template<typename T>
void HeapSort(vector<T>& a) {
	int i;
	//先建立大根堆，该操作花费O(N)
	for (i = a.size() / 2; i >= 0; --i) {
		AdjustHeap(a, i, a.size());
	}
	//将要删除的元素放入堆末尾的空间（交换根元素和尾元素），
	//这样不需要额外的空间。
	for (i = a.size() - 1; i > 0; --i) {
		T tmp = a[i];
		a[i] = a[0];
		a[0] = tmp;
		/*
		每次删除时，根元素与根末尾元素交换了，在位置0处下滤。
		由于不断从堆中删除，因此堆大小不断减小，为i
		*/
		AdjustHeap(a, 0, i);
	}
}

//该函数是堆操作中的下滤操作
template<typename T>
void AdjustHeap(vector<T>&a, int pos, int n) {
	int pos_child;
	T tmp;
	for (tmp = a[pos]; (pos * 2 + 1) < n; pos = pos_child) {
		pos_child = 2 * pos + 1;
		if (pos_child != n -1 && a[pos_child] < a[pos_child + 1])
			pos_child++;
		if (tmp < a[pos_child])
			a[pos] = a[pos_child];
		else
			break;
	}
	a[pos] = tmp;
}

/*
归并排序
*/
/*该函数用于合并两个已经排序的数组。如果对Merge的每个递归调用都声明一个临时数组，那么任一时刻可能
会有logN个临时数组处于活动期,这对小内存机器是致命的。另一方面，如果Merge动态分配并释放最小量临时空间，
那么由malloc占用的时间会很多。由于Merge位于MSort的最后一行，可以在MergeSort中建立该临时数组。
因此在任一时刻只需要一个临时数组活动，而且可以使用该临时数组的任意部分；我们将使用和输入数组array相同的部分。
*/
void Merge(int array[], int tmp_array[], int left_pos, int right_pos, int right_end) {
	int i, left_end, num_elements, tmp_pos;
	left_end = right_pos - 1;
	tmp_pos = left_pos;
	num_elements = right_end - left_pos + 1;

	while (left_pos <= left_end && right_pos <= right_end)
		if (array[left_pos] <= array[right_pos])
			tmp_array[tmp_pos++] = array[left_pos++];
		else
			tmp_array[tmp_pos++] = array[right_pos++];
	while (left_pos <= left_end)
		tmp_array[tmp_pos++] = array[left_pos++];
	while (right_pos <= right_end)
		tmp_array[tmp_pos++] = array[right_pos++];
	for (i = 0; i < num_elements; i++, right_end--)
		array[right_end] = tmp_array[right_end];
}

void MSort(int array[], int tmp_array[], int left, int right) {
	int center;
	if (left < right) {
		center = (left + right) / 2;
		MSort(array, tmp_array, left, center);
		MSort(array, tmp_array, center + 1, right);
		Merge(array, tmp_array, left, center + 1, right);
	}
}

void MergeSort(int array[], int n) {
	int *tmp_array;
	tmp_array = (int *)malloc(n * sizeof(int));
	if (tmp_array != NULL) {
		MSort(array, tmp_array, 0, n - 1);
		free(tmp_array);
	}
	else
		cout << "malloc failed" << endl;
}

//快速排序版本一
template<typename T>
int PartionQuickSort1(vector<T> &vec, int left, int right) {
	T pivot = vec[left];//设置枢纽
	int low = left;
	int high = right;
	while (low < high) {//注意两个内层while的顺序不能换
		while (low < high && vec[high] >= pivot) //这里是>=不能使>，否则当数组元素等于枢纽时会死循环
			high--;
		vec[low] = vec[high];//将找到的小于于枢纽的元素存到high所指的空穴
		while (low < high && vec[low] <= pivot) //这里是<=不能使<，否则当数组元素等于枢纽时会死循环
			low++;
		vec[high] = vec[low];//将找到的大于枢纽的元素存到high所指的空穴
	}
	vec[low] = pivot;
	cout << low << endl;
	return low;  //返回枢纽的位置
}
template<typename T>
void QuickSort1(vector<T> &vec, int left, int right) {
	if (left < right) {
		int partion = PartionQuickSort1(vec, left, right);
		QuickSort1(vec, left, partion - 1);
		QuickSort1(vec, partion + 1, right);
	}
}

//快速排序的非递归算法，以第一个元素为枢纽
//非递归算法用一个stack辅助数据结构，栈存放下一次要排序的两个下标
template<typename T>
void QuickSort1NoRecursion(vector<T>& vec, int left, int right) {
	stack<int> st;
	//注意每次入栈都将较大的下标先入栈，那么
	//每次出栈相反：较大的小标会后出栈
	st.push(right);
	st.push(left);
	int maxsize = 0;
	while (!st.empty()) {
		if (st.size() > maxsize)
			maxsize = st.size();
		int low = st.top();  st.pop();
		int high = st.top(); st.pop();
		//cout << low << " " << high << endl;
		int mid = PartionQuickSort1(vec, low, high);
		if (mid - 1 > low) {
			st.push(mid - 1);
			st.push(low);
		}
		if (mid + 1 < high) {
			st.push(high);
			st.push(mid + 1);
		}
	}
	//cout << "max stack size: " << maxsize << endl;
	return;
}

/*
该算法需要注意的是在PartionQuickSort1函数中两个内层while的顺序不能交换，否则会覆盖元素。如果两个内层while循环交换，
例如在上边的演示中，首先low指针右移，找到9，则要将a[low] = 9 存入a[high] = 7的位置，这样7还没被保存，那么该值就丢失了。
算法中之所以可以在循环中赋值是因为枢纽元素值已经保存在了pivot中。
*/
//下面算法与上边第一个版本类似，只是将枢纽设为待排序数组最右侧的元素了。
//如果将待排序数组的最右侧元素设为枢纽，那么则内层while循环需要交换，如下程序：
template<typename T>
int PartionQuickSort12(vector<T> &vec, int left, int right) {
	T pivot = vec[right]; //设置枢纽
	int low = left;
	int high = right;
	while (low < high) {//注意两个内层while的顺序不能换
		while (low < high && vec[low] <= pivot)
			low++;
		vec[high] = vec[low];
		while (low < high && vec[high] >= pivot)
			high--;
		vec[low] = vec[high];
	}
	vec[low] = pivot;
	return low;
}
template<typename T>
void QuickSort12(vector<T> &vec, int left, int right) {
	if (left < right) {
		int partion = PartionQuickSort1(vec, left, right);
		QuickSort12(vec, left, partion - 1);
		QuickSort12(vec, partion + 1, right);
	}
}


//快速排序版本二
//Hore版本，不产生空穴，直接交换
template<typename T>
int PartionQuickSort2(vector<T> &vec, int left, int right) {
	T pivot = vec[left];
	int low = left - 1;
	int high = right  + 1;
	for (; ;) {
		do {
			high--;
		}while (vec[high] > pivot);
		do {
			low++;
		}while (vec[low] < pivot);
		/*这里的循环是错误的，当某元素等于pivot时会死循环
		while (vec[high] > pivot)
			high--;
		while (vec[low] < pivot)
			low++;
		*/
		if (low < high)
			SwapQuickSort(vec[low], vec[high]);
		else
			return high;
	}
}
template<typename T>
void QuickSort2(vector<T> &vec, int left, int right) {
	if (left < right) {
		int partion = PartionQuickSort2(vec, left, right);
		QuickSort2(vec, left, partion);
		/*
		注意上一行与版本一不同，不是QuickSort2(vec, left, partion - 1)
		因为版本一中每次排序后会将枢纽pivot放在最终的位置上，但是该算法
		只保证每次排序后枢纽位于待排序数组的有半部分，不保证pivot在最终
		的位置上，因此要将Partion所指的位置加入下一次排序
		*/
		QuickSort2(vec, partion + 1, right);
	}
}

//快速排版本三，算法导论上
template<typename T>
void SwapQuickSort(T &a, T &b) {
	T temp = a;
	a = b;
	b = temp;
}
template<typename T>
int PartionQuickSort3(vector<T> &vec, int left, int right) {
	int low = left - 1;
	int high;
	T pivot = vec[right];
	for (high = left; high < right; high++) {
		if (vec[high] <= pivot) { //将找到的小于枢纽的元素移到左边
			low++;//low++后low指向了数组第一个大于枢纽的位置
			//将low所指的、第一个大于枢纽的元素与high所指的小于枢纽的元素交换
			SwapQuickSort(vec[low], vec[high]);
		}
	}
	SwapQuickSort(vec[low + 1], vec[right]);
	return low + 1;
}
template<typename T>
void QuickSort3(vector<T>& vec, int left, int right) {
	if (left < right) {
		int partion = PartionQuickSort3(vec, left, right);
		QuickSort3(vec, left, partion - 1);
		QuickSort3(vec, partion + 1, right);
	}
}

//和版本三类似，这里以left为枢纽，编程珠玑112页
template<typename T>
void QuickSort33(vector<T>& vec, int left, int right) {
	if (right <= left)
		return;;
	int low = left;
	int high;
	for (high = left + 1; high <= right; high++) {
		if (vec[high] < vec[left]) //如果high找到一个小于枢纽的，将其移动到左侧
			SwapQuickSort(vec[++low], vec[high]);
	}
	SwapQuickSort(vec[left], vec[low]);
	QuickSort32(vec, left, low - 1);
	QuickSort32(vec, low + 1, right);
}

//版本四,随机的枢纽，使用版本一的方法
int Rand(int left, int right) {
	int size = right - left + 1;
	return left + rand() % size;
}
template<typename T>
int PartionQuickSort4(vector<T> &vec, int left, int right) {
	srand((unsigned int)time(0));  
	SwapQuickSort(vec[Rand(left, right)], vec[right]);//将随机的枢纽交换到right位置处
	T pivot = vec[right]; //设置枢纽
	int low = left;
	int high = right;
	while (low < high) {//注意两个内层while的顺序不能换
		while (low < high && vec[low] <= pivot)
			low++;
		vec[high] = vec[low];
		while (low < high && vec[high] >= pivot)
			high--;
		vec[low] = vec[high];
	}
	vec[low] = pivot;
	return low;
}
template<typename T>
void QuickSort4(vector<T> &vec, int left, int right) {
	if (left < right) {
		int partion = PartionQuickSort1(vec, left, right);
		QuickSort4(vec, left, partion - 1);
		QuickSort4(vec, partion + 1, right);
	}
}

//版本五，取中间值为枢纽
template <typename T>
const T & median( vector<T> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    if( a[ center ] < a[ left ] )
        swap( a[ left ], a[ center ] );
    if( a[ right ] < a[ left ] )
        swap( a[ left ], a[ right ] );
    if( a[ right ] < a[ center ] )
        swap( a[ center ], a[ right ] );
    swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

template <typename T>
void QuickSort5( vector<T> & a, int left, int right )
{
	if (left + 10 <= right) {
		T pivot = median( a, left, right );
		int i = left, j = right - 1;
		for( ; ; )
		{
			while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
				swap( a[ i ], a[ j ] );
			else
				break;
		}
		swap( a[ i ], a[ right - 1 ] );
		QuickSort5( a, left, i - 1 );
		QuickSort5( a, i + 1, right );
	}
	else {
		InsertionSortQuickSort(a, left, right);
	}
}

template <typename T>
void InsertionSortQuickSort( vector<T> & a, int left, int right )
{
    for( int p = left + 1; p <= right; p++ )
    {
        T tmp = a[ p ];
        int j;

        for( j = p; j > left && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}
void Swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void SelectSort(int a[], int size) {
	int i;
	for (i = 0; i < size; ++i) {
		int min_index = i;
		int j;
		for (j = i + 1; j < size; ++j)
			if (a[j] < a[min_index])
				min_index = j;

		Swap(a[i], a[min_index]);
	}
}

void printVector(vector<int> &ivec) {
	cout << ivec.size() << " " << ivec.capacity() << endl;
}

//int main() {
	/*vector<int> ivec;
	printVector(ivec);

	ivec.push_back(1);
	printVector(ivec);

	ivec.push_back(2);
	printVector(ivec);

	int a[] = {34,1,1,3, 111, 11};
	SelectSort(a, sizeof(a) / sizeof(int));
	int i;
	for (i = 0; i < sizeof(a) / sizeof(int); ++i)
	cout << a[i] << " ";
	cout << endl;*/
	
	////vec_time用于记录所有算法的十次耗时
	////每个元素表示一种算法
	//vector< vector<int> > vec_time(10);
	////进行十次测试
	//for (int a = 0; a < 10; ++a) {
	//	int max = 100; //每次测试的都是随机的一百万个数 
	//	int i = 0;
	//	vector<int> ivec1, ivec1_none, ivec12, ivec2, ivec3, ivec4, ivec5;
	//	for (i = 0; i < 3000; i++) {
	//		int value = i;
	//		ivec1.push_back(value);
	//		ivec1_none.push_back(value);
	//		ivec12.push_back(value);
	//		ivec2.push_back(value);
	//		ivec3.push_back(value);
	//		ivec4.push_back(value);
	//		ivec5.push_back(value);
	//	}
	//	/*srand((unsigned int)time(0));
	//	while (i < max) {
	//		i++;
	//		int value = rand();
	//		ivec1.push_back(value);
	//		ivec1_none.push_back(value);
	//		ivec12.push_back(value);
	//		ivec2.push_back(value);
	//		ivec3.push_back(value);
	//		ivec4.push_back(value);
	//		ivec5.push_back(value);
	//	}*/



	//	clock_t time1 = clock();
	//	QuickSort1(ivec1, 0, ivec1.size() - 1);
	//	clock_t time2 = clock();
	//	//cout << "版本一（左侧枢纽）:" << time2 - time1 << endl;
	//	vec_time[0].push_back(time2 - time1);
	//	//PrintValue(ivec1);

	//	clock_t time_none1 = clock();
	//	QuickSort1NoRecursion(ivec1_none, 0, ivec1_none.size() - 1);
	//	clock_t time_none2 = clock();
	//	//cout << "版本一（非递归法）:" << time_none2 - time_none1 << endl;
	//	//PrintValue(ivec1_none);
	//	vec_time[1].push_back(time_none2 - time_none1);

	//	clock_t time31 = clock();
	//	QuickSort12(ivec12, 0, ivec12.size() - 1);
	//	clock_t time3 = clock();
	//	//cout << "版本一（右侧枢纽）:" << time3 - time31 << endl;
	//	vec_time[2].push_back(time3 - time31);

	//	clock_t time41 = clock();
	//	QuickSort2(ivec2, 0, ivec2.size() - 1);
	//	clock_t time4 = clock();
	//	//cout << "版本二（直接交换）:" << time4 - time41 << endl;
	//	vec_time[3].push_back(time4 - time41);

	//	clock_t time51 = clock();
	//	QuickSort3(ivec3, 0, ivec3.size() - 1);
	//	clock_t time5 = clock();
	//	//cout << "版本三（单向划分）:" << time5 - time51 << endl;
	//	vec_time[4].push_back(time5 - time51);

	//	clock_t time61 = clock();
	//	QuickSort4(ivec4, 0, ivec4.size() - 1);
	//	clock_t time6 = clock();
	//	//cout << "版本四（随机枢纽）:" << time6 - time61 << endl;
	//	vec_time[5].push_back(time6 - time61);

	//	clock_t time71 = clock();
	//	QuickSort5(ivec5, 0, ivec5.size() - 1);
	//	clock_t time7 = clock();
	//	//cout << "版本五（三数取中）:" << time7 - time71 << endl;
	//	vec_time[6].push_back(time7 - time71);
	//}

	////下列输出的各行依次是下列各个算法的函数
	//cout << "版本一（左侧枢纽） " << "版本一（非递归法） " << "版本一（右侧枢纽） " << endl;
	//cout <<	"版本二（直接交换） " << "版本三（单向划分） " <<  "版本四（随机枢纽） " << "版本五（三数取中）"  << endl;
	//for (int j = 0; j < 7; ++j) {
	//	int sum = 0;
	//	vector<int>::iterator iter = vec_time[j].begin();
	//	while (iter != vec_time[j].end()) {
	//		cout << *iter << "  ";
	//		sum += *iter;
	//		++iter;
	//	}
	//	cout << (double)sum / 10;
	//	cout << endl;
	//}
	
	/*
	clock_t time1 = clock();
	QuickSort1(ivec, 0, ivec.size() - 1);
	clock_t time2 = clock();
	cout << "time:" << time2 - time1 << endl;
	PrintValue(ivec);
	*/
	/*
	int a[] = {99, 8, 7, 5, 4, 2};
	MergeSort1(a, sizeof(a) / sizeof(int));
	int i = 0;
	while (i != sizeof(a) / sizeof(int))
		cout << *(a + i++) << " ";
	cout << endl;
	*/
	/*
	InsertionSort(a, 5);
	int i = 0;
	while (i != 5)
		cout << *(a + i++) << " ";
	cout << endl;
	*/
	/*
	int value;
	while (cin >> value)
		ivec5.push_back(value);
	//ShellSort<int>(ivec);
	//HeapSort<int>(ivec);
	QuickSort32(ivec5, 0, ivec5.size() - 1);
	PrintValue(ivec5);
	*/
//}


//int main() {
//	vector<int> ivec;
//	ivec.push_back(5);
//	ivec.push_back(7);
//	ivec.push_back(2);
//	ivec.push_back(3);
//	ivec.push_back(1);
//	ivec.push_back(1);
//	QuickSort1(ivec, 0, ivec.size() - 1);
//	PrintValue(ivec);
//}