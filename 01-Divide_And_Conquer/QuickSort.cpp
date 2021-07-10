/*快速排序*/

#include<stdio.h>//标准输入输出库
#define LENGTH 10

class SortableList
{
	private:
		//。。。。。。
		int* l;//数组指针 
		int maxSize;
		int n;//已有个数 
		void Swap(int i, int j); //交换下标为 i 和 j 的数组元素
		void QuickSort(int left, int right);
		int Partition(int left, int right);//快速排序_分划 

	public:
		//构造函数 
		SortableList(int mSize) {
			maxSize = mSize;
			l = new int[maxSize];
			n = 0; //数组中已有元素个数
		}
		//析构函数 
		~SortableList() {
			delete[]l;
		}
		void Input();//输入待排序序列 ！！！！！ 
		void Output();//输出排序序列 ！！！！！ 
		void QuickSort();//调用快速排序 
		//。。。。。。

};

void SortableList::Input() {
	printf("Please enter the list:\n");
	for (n = 0; n < maxSize; n++) scanf("%d", l+n);
	//test
	for (int i = 0; i < maxSize; i++) printf("%d ", *(l+i));
	printf("\n");
	//
	//merge
	QuickSort();
}

void SortableList::Output() {
	for (int i = 0; i < maxSize; i++) printf("%d ", *(l+i));
}

void SortableList::Swap(int i, int j) {
	int c = l[i];
	l[i] = l[j];
	l[j] = c;
}

int SortableList::Partition(int left, int right) {
	int i = left, j = right + 1;
	do {
		do i++; while (l[i] < l[left] && i <= right);//增加判断条件，防止无限循环 ,与pdf所给方法不同 
		do j--; while (l[j] > l[left] && j >= left);//如果不增加也不会错，因为大于数组长度之后相当于遍历随机值，总有使循环停下的值出现 
		if (i < j) Swap(i, j);
	} while (i < j);
	Swap(left, j);
	return j;
}

void SortableList::QuickSort(int left, int right) {
	if (left < right) {
		int j = Partition(left, right);
		QuickSort(left, j - 1);
		QuickSort(j + 1, right);
	}
}

void SortableList::QuickSort() {
	QuickSort(0, n - 1);
}

int main() {
	printf("LENGTH %d\n", LENGTH);
	SortableList list1(LENGTH);
	list1.Input();
	list1.Output();
	return 0; 
}

