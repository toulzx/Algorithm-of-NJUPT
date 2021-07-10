/*��������*/

#include<stdio.h>//��׼���������
#define LENGTH 10

class SortableList
{
	private:
		//������������
		int* l;//����ָ�� 
		int maxSize;
		int n;//���и��� 
		void Swap(int i, int j); //�����±�Ϊ i �� j ������Ԫ��
		void QuickSort(int left, int right);
		int Partition(int left, int right);//��������_�ֻ� 

	public:
		//���캯�� 
		SortableList(int mSize) {
			maxSize = mSize;
			l = new int[maxSize];
			n = 0; //����������Ԫ�ظ���
		}
		//�������� 
		~SortableList() {
			delete[]l;
		}
		void Input();//������������� ���������� 
		void Output();//����������� ���������� 
		void QuickSort();//���ÿ������� 
		//������������

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
		do i++; while (l[i] < l[left] && i <= right);//�����ж���������ֹ����ѭ�� ,��pdf����������ͬ 
		do j--; while (l[j] > l[left] && j >= left);//���������Ҳ�������Ϊ�������鳤��֮���൱�ڱ������ֵ������ʹѭ��ͣ�µ�ֵ���� 
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

