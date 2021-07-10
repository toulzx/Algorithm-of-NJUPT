#include <iostream>//��׼���������
#include <math.h>
using namespace std;

#define R 5
#define K 4
#define LENGTH 10
#define MAXSIZE 10

class SortableList
{
	private:
		int* l;//����ָ��
		int n;//���и��� 
		int k;//���Ҵ�С�����k����
		void Swap(int i, int j); //�����±�Ϊ i �� j ������Ԫ��
		int Partition(int left, int right);//�ֻ�
		void InsertSort(int left, int right);
		void InsertSort(int* mid, int rn);
		int Select(int k, int left, int right, int r);

	public:
		//���캯�� 
		SortableList(int mSize, int i) {
			l = new int[mSize];
			n = 0;
			k = i;
		}
		//�������� 
		~SortableList() {
			delete[]l;
		}
		void Input();//������������� ���������� 
		void Output();//����������� ����������
};

void SortableList::Input() {
	int temp;
	cout << "Please enter the list:\n";
	cout << "Attention! If you enter -9999, the input will be end." << endl;
	for (n = 0; n < MAXSIZE; n++) {
		cin >> temp;
		if (temp == -9999) break;
		else *(l + n) = temp;
	}
	//test
	cout << "list: " << endl;
	for (int i = 0; i < n; i++) cout << *(l + i);
	cout << endl << "Input() successsfully!" << endl;
	//
}

void SortableList::Output() {
	cout << endl << endl << "The " << k << "^th figure is " << Select(k, 0, n - 1, R) << endl << endl;
	//test
	cout << "Output() successfully!" << endl;
	cout << "list: " << endl;
	for (int i = 0; i < n; i++) cout << *(l + i) << " ";
	//
}

void SortableList::Swap(int i, int j) {
	int c = *(l+i);
	*(l+i) = *(l+j);
	*(l+j) = c;
}

int SortableList::Partition(int left, int right) {
	int i = left, j = right + 1;
	do {
		do i++; while (l[i] < l[left]);
		do j--; while (l[j] > l[left]);
		if (i < j) Swap(i, j);
	} while (i < j);
	Swap(left, j);
	return j;
}

void SortableList::InsertSort(int left, int right) {
	cout << "InsertSort() come in" << endl;
	int j;
	int temp;
	for (int i=left + 1; i <= right; i++) {
		temp = *(l+i);
		//test
		//cout << "InsertSort()'s temp:" << temp << endl;
		//
		for (j = i - 1; j >= left; j--) 
			if (temp < *(l + j)) {
				//test
				//cout << "exchange" << *(l + j + 1) << "and" << *(l + j)<<endl;
				//
				*(l + j + 1) = *(l + j);
			}else break;
		*(l+j+1) = temp;
	}
	return;
}

void SortableList::InsertSort(int* mid, int rn) {
	cout << "mid's InsertSort() come in" << endl;
	int j;
	int temp, temp_mid; //temp��¼mid��Ӧ��l�е�ֵ�� temp_mid��¼l�е��±�
	for (int i = 1; i <= rn - 1; i++) {
		temp = *(l + *(mid + i));
		temp_mid = *(mid + i);
		for (j = i - 1; j >= 0; j--)
			if (temp < *(l + *(mid + j))) *(mid + j + 1) = *(mid + j);
			else break;
		*(mid + j + 1) = temp_mid;
	}
}

//�������˺���ʵ����ʵ����ʾ�г���
//�ο���https://blog.csdn.net/zhao2018/article/details/82828733?utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control&dist_request_id=1328740.39861.16170057144613973&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control

int SortableList::Select(int k, int left, int right, int r) {//Ѱ�ҵ�k����ÿ����r��
	//���������������������Ĳ��֣�(right-left)/r
	//��ȡÿһ����ֵ -> ���������ѡ��
	if (left < right) {
		int rn = (right - left +1) / r;
		int temp_mid = 0;
		int* mid = new int[rn];//�洢���������ֵ���±�

		if (rn >= 1) {
			for (int i = 0; i < rn; i++) {//ÿһ��
				////test
				for (int m = 0; m < n; m++) cout << *(l + m) << " ";
				cout << endl;
				cout << "InsertSort(" << left + i * r << "," << left + (i + 1) * r - 1 << ")" << endl;
				////
				InsertSort(left + i * r, left + (i + 1) * r - 1);//��������
				//test
				for (int m = 0; m < n; m++) cout << *(l + m) << " ";
				cout << endl;
				////
				*(mid + i) = left + i * r + r / 2;//��ֵ����ż��rȡ�ϴ��
				////test
				//cout << "i=" << i << endl;
				//cout << "mid[" << i << "]= " << *(mid + i) << endl << "l[" << *(mid + i) << "]= " << *(l + *(mid + i));
				//cout << endl << endl;
				////
			}
			////test
			//for (int m = 0; m < n; m++) cout << *(l + m) << " ";
			//cout << endl << "rn=" << rn << endl;
			////
			if (rn > 1) {
				//test
				//cout << "origin mid array: " << endl;
				//for (int i = 0; i < rn; i++) cout << "mid[" << i << "]=" << *(mid + i) << "; l[" << *(mid + i) << "]=" << *(l + *(mid + i)) << " " << endl;
				//cout << endl;
				//
				InsertSort(mid, rn);//����ֵ�±�����mid������
				//test
				//cout << "afterSort mid array: " << endl;
				//for (int i = 0; i < rn; i++) cout << "mid[" << i << "]=" << *(mid + i) << "; l[" << *(mid + i) << "]=" << *(l + *(mid + i)) << " " << endl;
				//cout << endl;
				//
				temp_mid = *(mid + (rn - 1) / 2 + 1);//����ֵ���ҳ����ǵ���ֵ���õ���l���±�,ͬ������ֵ����ż��rȡ�ϴ��
			}
			else if (rn == 1) temp_mid = *mid;
			////test
			for (int m = 0; m < n; m++) cout << *(l + m) << " ";
			cout << endl;
			////


			////test
			//cout << "temp_mid:" << temp_mid << endl;
			////
			Swap(left, temp_mid);//�ŵ����ף��Ա㻮��
			////test
			cout << "after Swap(" << left << "," << temp_mid << ")" << endl;
			for (int m = 0; m < n; m++) cout << *(l + m) << " ";
			cout << endl;
			////
			temp_mid = Partition(left, right);//���ֺ�����±�
			////test
			cout << "after Partition()";
			//cout << "'s temp_mid:" << temp_mid << endl;
			for (int i = 0; i < n; i++)
				if (i == 0) cout << endl;
				else if (i == temp_mid) cout <<  " #" << *(l + i) << "#";
				else cout << " " << *(l + i);
			cout << endl << endl << endl;
			////

			if (k < temp_mid + 1) Select(k, left, temp_mid - 1, r);//���k��ǰһ���֣����������ùܺ�һ����
			else if (k > temp_mid + 1) Select(k, temp_mid + 1, right, r);//��֮��Ȼ
			else return *(l + temp_mid);//�����ô��...
		}
		else if (rn == 0) {
			InsertSort(left, right);
			return *(l + k - 1);//�������ҵ��ˣ�������k�����±���Ҫ-1
		}
		else {
			cout << "!!!WRONG!!!";
			exit(0);
		}
	}
	/*
		//ÿ������r��Ԫ�أ�Ѱ�ҵ�kСԪ��
		int n=right-left+1;
		if (n<=r) //�������㹻С��ʹ��ֱ�Ӳ�������
		{
			InsertSort(left,right);
			return left+k-1; //ȡ���еĵ�kСԪ�أ����±�Ϊleft+k-1
		}
		for (int i=1;i<=n/r;i++)
		{
			InsertSort(left+(i-1)*r,left+i*r-1);
			//����ȡ�й�����ÿ����м�ֵ
			Swap(left+i-1,left+(i-1)*r+(int)ceil((double)r/2)-1);
			//��ÿ����м�ֵ�������ӱ�ǰ�����д��
		}
		int j=Select((int)ceil((double)n/r/2),left,left+(n/r)-1,r);
		//������м�ֵ�����±�Ϊj
		Swap(left,j); //�����м�ֵΪ��ŦԪ��������left��
		j=Partition(left,right);//�Ա��ӱ����зֻ�����
		if (k==j-left+1) return j; //���ص�kСԪ���±�
		else if (k<j-left+1) 
			return Select(k,left,j-1,r);//�����ӱ����kСԪ��
 		else
			return Select(k-(j-left+1),j+1,right,r);
		//�����ӱ����k-(j-left+1)СԪ��
		*/
}


int main() {
	SortableList list1(LENGTH, K);
	list1.Input();
	list1.Output();
}

