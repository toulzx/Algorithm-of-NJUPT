#include <iostream>//标准输入输出库
#include <math.h>
using namespace std;

#define R 5
#define K 4
#define LENGTH 10
#define MAXSIZE 10

class SortableList
{
	private:
		int* l;//数组指针
		int n;//已有个数 
		int k;//查找从小到大第k个数
		void Swap(int i, int j); //交换下标为 i 和 j 的数组元素
		int Partition(int left, int right);//分划
		void InsertSort(int left, int right);
		void InsertSort(int* mid, int rn);
		int Select(int k, int left, int right, int r);

	public:
		//构造函数 
		SortableList(int mSize, int i) {
			l = new int[mSize];
			n = 0;
			k = i;
		}
		//析构函数 
		~SortableList() {
			delete[]l;
		}
		void Input();//输入待排序序列 ！！！！！ 
		void Output();//输出排序序列 ！！！！！
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
	int temp, temp_mid; //temp记录mid对应的l中的值， temp_mid记录l中的下标
	for (int i = 1; i <= rn - 1; i++) {
		temp = *(l + *(mid + i));
		temp_mid = *(mid + i);
		for (j = i - 1; j >= 0; j--)
			if (temp < *(l + *(mid + j))) *(mid + j + 1) = *(mid + j);
			else break;
		*(mid + j + 1) = temp_mid;
	}
}

//声明：此函数实现与实验提示有出入
//参考：https://blog.csdn.net/zhao2018/article/details/82828733?utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control&dist_request_id=1328740.39861.16170057144613973&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control

int SortableList::Select(int k, int left, int right, int r) {//寻找第k个，每组有r个
	//共有组数，不含不完整的部分：(right-left)/r
	//提取每一组中值 -> 插入排序后选择
	if (left < right) {
		int rn = (right - left +1) / r;
		int temp_mid = 0;
		int* mid = new int[rn];//存储各满组的中值的下标

		if (rn >= 1) {
			for (int i = 0; i < rn; i++) {//每一组
				////test
				for (int m = 0; m < n; m++) cout << *(l + m) << " ";
				cout << endl;
				cout << "InsertSort(" << left + i * r << "," << left + (i + 1) * r - 1 << ")" << endl;
				////
				InsertSort(left + i * r, left + (i + 1) * r - 1);//插入排序
				//test
				for (int m = 0; m < n; m++) cout << *(l + m) << " ";
				cout << endl;
				////
				*(mid + i) = left + i * r + r / 2;//中值若遇偶数r取较大的
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
				InsertSort(mid, rn);//对中值下标数组mid的排序
				//test
				//cout << "afterSort mid array: " << endl;
				//for (int i = 0; i < rn; i++) cout << "mid[" << i << "]=" << *(mid + i) << "; l[" << *(mid + i) << "]=" << *(l + *(mid + i)) << " " << endl;
				//cout << endl;
				//
				temp_mid = *(mid + (rn - 1) / 2 + 1);//在中值中找出他们的中值，得到在l中下标,同样，中值若遇偶数r取较大的
			}
			else if (rn == 1) temp_mid = *mid;
			////test
			for (int m = 0; m < n; m++) cout << *(l + m) << " ";
			cout << endl;
			////


			////test
			//cout << "temp_mid:" << temp_mid << endl;
			////
			Swap(left, temp_mid);//放到列首，以便划分
			////test
			cout << "after Swap(" << left << "," << temp_mid << ")" << endl;
			for (int m = 0; m < n; m++) cout << *(l + m) << " ";
			cout << endl;
			////
			temp_mid = Partition(left, right);//划分后更新下标
			////test
			cout << "after Partition()";
			//cout << "'s temp_mid:" << temp_mid << endl;
			for (int i = 0; i < n; i++)
				if (i == 0) cout << endl;
				else if (i == temp_mid) cout <<  " #" << *(l + i) << "#";
				else cout << " " << *(l + i);
			cout << endl << endl << endl;
			////

			if (k < temp_mid + 1) Select(k, left, temp_mid - 1, r);//如果k在前一部分，接下来不用管后一部分
			else if (k > temp_mid + 1) Select(k, temp_mid + 1, right, r);//反之亦然
			else return *(l + temp_mid);//如果这么巧...
		}
		else if (rn == 0) {
			InsertSort(left, right);
			return *(l + k - 1);//这下真找到了，不过第k个的下标需要-1
		}
		else {
			cout << "!!!WRONG!!!";
			exit(0);
		}
	}
	/*
		//每个分组r个元素，寻找第k小元素
		int n=right-left+1;
		if (n<=r) //若问题足够小，使用直接插入排序
		{
			InsertSort(left,right);
			return left+k-1; //取其中的第k小元素，其下标为left+k-1
		}
		for (int i=1;i<=n/r;i++)
		{
			InsertSort(left+(i-1)*r,left+i*r-1);
			//二次取中规则求每组的中间值
			Swap(left+i-1,left+(i-1)*r+(int)ceil((double)r/2)-1);
			//将每组的中间值交换到子表前部集中存放
		}
		int j=Select((int)ceil((double)n/r/2),left,left+(n/r)-1,r);
		//求二次中间值，其下标为j
		Swap(left,j); //二次中间值为枢纽元，并换至left处
		j=Partition(left,right);//对表（子表）进行分划操作
		if (k==j-left+1) return j; //返回第k小元素下标
		else if (k<j-left+1) 
			return Select(k,left,j-1,r);//在左子表求第k小元素
 		else
			return Select(k-(j-left+1),j+1,right,r);
		//在右子表求第k-(j-left+1)小元素
		*/
}


int main() {
	SortableList list1(LENGTH, K);
	list1.Input();
	list1.Output();
}

