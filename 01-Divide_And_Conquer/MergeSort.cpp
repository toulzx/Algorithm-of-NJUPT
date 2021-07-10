/*两路合并排序*/ 

#include<stdio.h>//标准输入输出库

#define LENGTH 10

class SortableList
{
	private:
		//。。。。。。
		int* l;//数组指针 
		int maxSize;
		int n;//已有个数 
		void MergeSort(int left, int right);//两路合并排序 
		void Merge(int left, int mid, int right);//两路合并排序_子序列合并 

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
		void MergeSort();//调用两路合并排序


};

void SortableList::Input() {
	printf("Please enter the list:\n");
	for (n = 0; n < maxSize; n++) scanf("%d", l+n);
	//test
	//for (int i = 0; i < maxSize; i++) printf("%d ", *(l+i));
	MergeSort();
}

void SortableList::Output() {
	for (int i = 0; i < maxSize; i++) printf("%d ", *(l+i));
}

void SortableList::MergeSort() {
	MergeSort(0, n - 1);
}

void SortableList::MergeSort(int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		MergeSort(left, mid);
		MergeSort(mid + 1, right);
		Merge(left, mid, right);
	}
}

void SortableList::Merge(int left, int mid, int right) {
	int* temp = new int[right - left + 1];
	int i = left, j = mid + 1, k = 0;
	//对划分的每一部分进行排序，方法是从第一和中间分别开始互相比，比赢了就先存入临时数组（排序结果），再前进一格
	while ((i <= mid) && (j <= right))
		if (l[i] <= l[j]) temp[k++] = l[i++];
		else temp[k++] = l[j++];
	//当两部分中有一部分已经前进完了，另一部分中剩余部分数要依次写入，剩余部分的顺序不用担心是因为两路排序后这两部分各自有序
	while (i <= mid) temp[k++] = l[i++];
	while (j <= right) temp[k++] = l[j++];
	//将临时数组的有序数列取出
	for (i = 0, k = left; k <= right;) l[k++] = temp[i++];
}


int main() {
	printf("LENGTH %d\n", LENGTH);
	SortableList list1(LENGTH);
	list1.Input();
	list1.Output();
	return 0; 
}

