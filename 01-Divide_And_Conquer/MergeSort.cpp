/*��·�ϲ�����*/ 

#include<stdio.h>//��׼���������

#define LENGTH 10

class SortableList
{
	private:
		//������������
		int* l;//����ָ�� 
		int maxSize;
		int n;//���и��� 
		void MergeSort(int left, int right);//��·�ϲ����� 
		void Merge(int left, int mid, int right);//��·�ϲ�����_�����кϲ� 

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
		void MergeSort();//������·�ϲ�����


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
	//�Ի��ֵ�ÿһ���ֽ������򣬷����Ǵӵ�һ���м�ֱ�ʼ����ȣ���Ӯ�˾��ȴ�����ʱ���飨������������ǰ��һ��
	while ((i <= mid) && (j <= right))
		if (l[i] <= l[j]) temp[k++] = l[i++];
		else temp[k++] = l[j++];
	//������������һ�����Ѿ�ǰ�����ˣ���һ������ʣ�ಿ����Ҫ����д�룬ʣ�ಿ�ֵ�˳���õ�������Ϊ��·������������ָ�������
	while (i <= mid) temp[k++] = l[i++];
	while (j <= right) temp[k++] = l[j++];
	//����ʱ�������������ȡ��
	for (i = 0, k = left; k <= right;) l[k++] = temp[i++];
}


int main() {
	printf("LENGTH %d\n", LENGTH);
	SortableList list1(LENGTH);
	list1.Input();
	list1.Output();
	return 0; 
}

