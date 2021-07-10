#include<iostream>
#include<string.h>
#define MAXLENGTH 11

using namespace std;
 
class LCS
{
	private:
		char* a, * b; //l存放较长序列 
		int *c1,*c2;
		int l,s; //l存放较长序列的长度，s存放较短序列的长度。
		
	public:
	LCS(int nx,int ny,char *x,char *y)
	{ 
		if (nx>ny) {
			l = nx;
			s = ny;
		} else { 
			char* t = x;
			x = y;
			y = t;
			l = ny; 
			s = nx;
		}
		
		c1=new int[s+1]; //“+1”是因为从1开始 
		c2=new int[s+1];
		memset(c1, 0, sizeof(*c1) * (s+1)); //初始化c1、c2           //为c1、c2赋初值
		memset(c2, 0, sizeof(*c2) * (s+1));
		
		a = new char[l + 2]; // 初始化，其中“+2”的原因：从1开始放置字符串、考虑字符串结束标记"\0"
		b = new char[s + 2]; // 下标0置0有利于与矩阵对应；

		memset(a, 0, sizeof(*a) * (l + 2)); //将a数组前m（即全部）初始化为'\0'
		memset(b, 0, sizeof(*b) * (s + 2));

		*a = '#';//从1开始防止字符串，得先令0处被初始化为'\0'的先被赋值，否则无法直接通过cout<<a;输出
		*b = '#';
		memcpy(a + 1, x, sizeof(*a) * (l));//将x和y中的字符写入一维数组a中
		memcpy(b + 1, y, sizeof(*b) * (s));
			
	}
	int LCSLength();
};

int LCS::LCSLength()
{
	int *temp;
	for (int i = 1; i <= l; i++){
		for (int j = 1; j <= s; j++){
			if (a[i] == b[j])   c2[j] = c1[j - 1] + 1;
			else if (c1[j] >= c2[j - 1]) c2[j] = c1[j];
			else c2[j] = c2[j - 1];
		}
		//test
		for (int i = 1; i <= s; i++) cout << c2[i] << " ";
		cout << endl;
		//交换c1、c2 
		temp = c1;
		c1 = c2;
		c2 = temp;
	}
	return c1[s]; //返回最优解值
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
	
	cout<<"最长公共子序列长度值（最优解值）："<<lcs.LCSLength()<<endl;
	
	delete []x;
	delete []y;
	return 0; 
}

