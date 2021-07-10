#include<iostream>
#include<string.h>

//备忘录方法：修改LCSLength()和CLCS()方法

using namespace std;

#define MAXLENGTH 11

class LCS
{
private:
	int** c, ** s; //修改
	int m, n;
	char* a, * b;
	void CLCS(int i, int j) const; //求取序列
	int LCSLength(int i, int j); //求取最优值解

public:
	LCS(int nx, int ny, char* x, char* y) //构造函数，对数据成员m、n、a、b、c、s初始化
	{
		m = nx;
		n = ny;

		a = new char[m + 2]; // 初始化，其中“+2”的原因：从1开始放置字符串、考虑字符串结束标记"\0"
		b = new char[n + 2]; // 下标0置0有利于与矩阵对应；

		memset(a, 0, sizeof(*a) * (m + 2)); //将a数组前m（即全部）初始化为'\0'
		memset(b, 0, sizeof(*b) * (n + 2));

		/*
		* 关于memeset()
		* memset(void* ptr, int value, size_t num)三个参数分别表示:要操作的内存指针ptr，要设置的值value，ptr的前num个字节，其中size_t即unsigned int
		* 参数 value 虽声明为 int，但必须是 unsigned char，所以范围在0 到255 之间。（只修改二进制后八位，对于char类型，则将这八位转换成为ascll码，特别的，'\0'的acall码对应0）
		* 此函数在头文件<string.h>包含
		* 一般第三个参数会使用sizeof()来确定，注意，sizeof()内不能是指针，否则在32位下统一表示为指针大小：4字节，而不是表示元素的大小
		* 参考：http://c.biancheng.net/cpp/html/157.html
		* 参考：https://baike.baidu.com/item/memset#2
		*
		*memset的正规用法是只能用来初始化char类型的数组的，也就是说，它只接受0x00-0xFF的赋值
		*memset初始化int数组的value时候只有-1和0才会如预期，具体原理请读者自行查阅，不再赘述。
		*而对于也常用的int类型，int是4个字节，当memset(,1,sizeof());时，1相当于ASSCII码的1，1转为二进制00000001，当做一字节，一字节8位，int为4字节，所以初始化完每个数为00000001000000010000000100000001 = 16843009；
		*参考：https://blog.csdn.net/lyj2014211626/article/details/65481630?utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromMachineLearnPai2~default-2.vipsorttest&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromMachineLearnPai2~default-2.vipsorttest
		*
		* 注意，动态生成的二维数组内存空间不一定连续，而memset()的原理是直接对内存进行操作，所以遇到这种情况不能用memset
		*
		* 不能对已经赋值的 char* 指针进行memset()操作，因为 char*（字符串）一旦赋值后在内存是只读的， char[]（字符数组）才可以修改
		* 参考：https://stackoverflow.com/questions/1704407/what-is-the-difference-between-char-s-and-char-s
		*/
		* a = '#';//从1开始防止字符串，得先令0处被初始化为'\0'的先被赋值，否则无法直接通过cout<<a;输出
		*b = '#';
		memcpy(a + 1, x, sizeof(*a) * (m));//将x和y中的字符写入一维数组a中
		memcpy(b + 1, y, sizeof(*b) * (n));

		/*
		* 关于memcpy
		* memcpy(void* toPtr, int fromPtr, size_t num) 将fromPtr指针指向的数组内存中内容复制到toPtr指针指向的数组，复制num个字段
		* 注意：复制的内容长度不能等于或超过目标指针指向数组的长度，由于复制的内容中不含'\0'，粘贴时会使得数组不含'\0'甚至溢出，这会导致输出时产生乱码（无法识别到终止符）
		*/

		c = new int* [m + 1]; //动态创建并初始化二维数组（矩阵）每一个元素为0，不含标记符'\0'
		for (int i = 0; i < (m + 1); i++) {
			*(c + i) = new int[n + 1];
			memset(*(c + i), 0, sizeof(**(c + i)) * (n + 1));
		}
		s = new int* [m + 1];
		for (int i = 0; i < (m + 1); i++) {
			*(s + i) = new int[n + 1];
			memset(*(s + i), 0, sizeof(**(s + i)) * (n + 1));
		}
	}

	int LCSLength(); //调用函数求取最优值解

	void CLCS();//调用私有成员函数CLCS(int,int)，求取序列

	void getc() {
		cout << ' ' << b << endl;
		for (int i = 0; i <= m; i++) {
			cout << a[i];
			for (int j = 0; j <= n; j++) {
				cout << *(*(c + i) + j);
			}
			cout << endl;
		}
	}
	void gets() {
		cout << ' ' << b << endl;
		for (int i = 0; i <= m; i++) {
			cout << a[i];
			for (int j = 0; j <= n; j++) {
				cout << *(*(s + i) + j);
			}
			cout << endl;
		}
	}
};

int LCS::LCSLength(int i, int j)
{
	if (i == 0 || j == 0) return 0;
	if (c[i][j] != 0) return c[i][j];
	else
		if (a[i] == b[j])
		{
			c[i][j] = LCSLength(i - 1, j - 1) + 1; s[i][j] = 1;
		}
		else
			if (LCSLength(i - 1, j) >= LCSLength(i, j - 1))
			{
				c[i][j] = LCSLength(i - 1, j); s[i][j] = 2;
			}
			else
			{
				c[i][j] = LCSLength(i, j - 1); s[i][j] = 3;
			}
	return c[i][j];
}
int LCS::LCSLength() {
	return LCSLength(m, n);
}

void LCS::CLCS(int i, int j) const
{
	if (i == 0 || j == 0) return;
	if (a[i] == b[j])
	{
		CLCS(i - 1, j - 1);
		cout << a[i];
	}
	else
		if (c[i - 1][j] >= c[i][j - 1]) CLCS(i - 1, j);
		else CLCS(i, j - 1);
}
void LCS::CLCS() {
	CLCS(m, n);
}

int main()
{
	int nx = 0, ny = 0;
	char* x = new char[MAXLENGTH], * y = new char[MAXLENGTH];	//初始化数组x,y

	//Enter
	cout << "Please input string x !(max length allowed to enter: " << MAXLENGTH - 1 << ")" << endl;
	cin >> x;
	for (int i = 0; i < MAXLENGTH; i++) {
		if (*(x + i) == '\0') {
			nx = i;
			break; //i只有从0开始退出的时候nx才表示不含'#'的长度
		}
	}
	cout << "Please input string y !" << endl;
	cin >> y;
	for (int i = 0; i <= MAXLENGTH; i++) {
		if (*(y + i) == '\0') {
			ny = i;
			break;
		}
	}

	//Input
	LCS lcs(nx, ny, x, y);//数组x，y以及他们的长度nx，ny

	cout << endl;
	cout << "length: " << lcs.LCSLength() << endl;

	cout << "c[] = " << endl;
	lcs.getc();

	cout << endl;
	cout << "s[] = " << endl;
	lcs.gets();

	cout << endl;
	cout << "lcs: ";
	lcs.CLCS();

	//Clean
	delete[]x;
	delete[]y;

	return 0;
}

