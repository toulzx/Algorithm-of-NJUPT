#include<iostream>
#include<string.h>
#include<stack>

using namespace std;

#define MAXLENGTH 11
#define N 20




class LCS
{
private:
	int** c, ** s; //修改
	int m, n;
	char* a, * b;
	int CLCS(int i, int j, int t, int q, bool tf) const; //求取序列
	char** ch; //存储结果 
	int ch_n; //记录有多少种情况 
	int ch_l; //记录子序列长度 
	void Output();

public:
	LCS(int nx, int ny, char* x, char* y) //构造函数，对数据成员m、n、a、b、c、s初始化
	{
		ch_n = -1;
		ch_l = -1;
		m = nx;
		n = ny;
		
		a = new char[m + 2]; // 初始化，其中“+2”的原因：从1开始放置字符串、考虑字符串结束标记"\0"
		b = new char[n + 2]; // 下标0置0有利于与矩阵对应；

		memset(a, 0, sizeof(*a) * (m + 2)); //将a数组前m（即全部）初始化为'\0'
		memset(b, 0, sizeof(*b) * (n + 2));

		*a = '#';//从1开始防止字符串，得先令0处被初始化为'\0'的先被赋值，否则无法直接通过cout<<a;输出
		*b = '#';
		memcpy(a + 1, x, sizeof(*a) * (m));//将x和y中的字符写入一维数组a中
		memcpy(b + 1, y, sizeof(*b) * (n));

		c = new int* [m + 1]; 
		for (int i = 0; i < (m + 1); i++) {
			*(c + i) = new int[n + 1];
			memset(*(c + i), 0, sizeof(**(c + i)) * (n + 1));
		}
		s = new int* [m + 1];
		for (int i = 0; i < (m + 1); i++) {
			*(s + i) = new int[n + 1];
			memset(*(s + i), 0, sizeof(**(s + i)) * (n + 1));
		}
		ch = new char* [N + 1];//动态创建并初始化二维数组每一个元素为#，不含标记符'\0'
		for (int i = 0; i < (N + 1); i++) {
			*(ch + i) = new char[MAXLENGTH + 1];
			memset(*(ch + i), '#', sizeof(**(ch + i)) * (MAXLENGTH + 1));
		}
		
	}

	int LCSLength(); //求取最优值解

	void CLCS();//调用私有成员函数CLCS(int,int)，求取序列

	void getc() {
		cout << ' ' << b <<endl;
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
		for (int i = 0; i <= m; i++){
			cout << a[i];
			for (int j = 0; j <= n; j++) {
				cout << *(*(s + i) + j);
			}
			cout << endl;
		}
	}
	void getch() {
		for (int i = 0; i <= N; i++){
			for (int j = 0; j <= MAXLENGTH; j++) {
				cout << *(*(ch + i) + j);
			}
			cout << endl;
		}
	}
};

int LCS::LCSLength()
{

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			if (a[i] == b[j]) 
			{
				c[i][j] = c[i - 1][j - 1] + 1; 
				s[i][j] = 1; //s中存储计算过程，1表示找到相同项；3表示矩阵计算中左＜上，4表示左=上，2表示左＞上
			}
			else
				if (c[i - 1][j] > c[i][j - 1]) 
				{
					c[i][j] = c[i - 1][j]; 
					s[i][j] = 3; 
				} else if(c[i - 1][j] = c[i][j - 1]) {
					c[i][j] = c[i - 1][j]; 
					s[i][j] = 4; 
				} else {
					c[i][j] = c[i][j - 1]; 
					s[i][j] = 2; 
				}
	ch_l = c[m][n]; //记录最优解 
	return ch_l; //返回最优解值
}

int LCS::CLCS(int i, int j, int t, int q, bool tf) const //记录t种情况（行），倒数第q个字母 位置 
{
	if (i == 0 || j == 0 || s[i][j] == 0) return t;
	if (s[i][j] == 1)  //即：a[i] == b[j]
	{
		ch[t][q] = a[i]; //存储进ch数组（逆序） 
		CLCS(i - 1, j - 1, t, ++q, false);
		
	}
	else
		if (s[i][j] == 3) CLCS(i - 1, j, t, q, false);
		else if(s[i][j] == 4) //c[i - 1][j] = c[i][j - 1]
		{
			CLCS(i - 1, j, t, q, true);
			CLCS(i, j - 1, ++t, q, true);
		}
		else CLCS(i, j - 1, t, q, false);
}
void LCS::CLCS() {
	if(ch_l == -1) LCSLength();
	ch_n = CLCS(m, n, 1, 1, false);
	Output(); 
}

void LCS::Output() {
	cout << endl;
	for(int i = ch_n; i > 0; i--){
		for(int j = ch_l; j > 0; j--){
			int temp = 0;
			if(ch[i][j] == '#') //如果这个地方没有值，则遍历数组这一列，非#的字符越往下优先级越高 
			{
				for(int t = 1; t <= N; t++) if(ch[t][j] != '#') temp = t;
				cout << ch[temp][j];
			}else cout << ch[i][j];
		} 
		cout << endl;
	}
}

int main()
{
	int nx = 0, ny = 0;
	char* x = new char[MAXLENGTH], * y = new char[MAXLENGTH];	//初始化数组x,y

	//Enter
	cout << "Please input string x !(max length allowed to enter: " << MAXLENGTH-1 << ")" << endl;
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

//	cout << endl;
//	cout << "original ch[]: " << endl;
//	lcs.getch();

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
	
	cout << endl;
	cout << "new ch[]: " << endl;
	lcs.getch();

	


	//Clean
	delete[]x;
	delete[]y;

	return 0;
}	

