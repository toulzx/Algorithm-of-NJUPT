#include<iostream>
#include<string.h>

using namespace std;

void MatrixChain(int n, int* p, int** m, int** s) //n个数组连乘，第i个矩阵的行数*(p+i)（即第i-1矩阵的列数）和最后一个矩阵的列数*(p+n+1)，从Ai矩阵连乘到Aj矩阵的最少次数记录于m二维数组，最少次数时得的截点记录于s数组
{
	for (int i = 1; i <= n; i++) m[i][i] = 0; //初始化对角线元素，忽略0项，从1开始
	for (int r = 2; r <= n; r++) //一共n条斜列（含对角线）需遍历
		for (int i = 1; i <= n - r + 1; i++) //遍历斜列上第i个（即行数），共有n-r+1个
		{
			int j = i + r - 1; //获得该位置的列数j
			m[i][j] = m[i + 1][j] + p[i] * p[i + 1] * p[j + 1]; //省略了m[i][i]=0项，截第一个和剩余部分的情况
			s[i][j] = i;
			for (int k = i + 1; k < j; k++) //可将这里k=i，且将上两行删除并入下面一起
			{
				int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
				if (t < m[i][j])
				{
					m[i][j] = t;
					cout << "更新m[" << i << "][" << j << "]的值为：" << t << endl;
					s[i][j] = k;
					cout << "更新s[" << i << "][" << j << "]的值为：" << k << endl;
				}
			}
			cout << "最终求出：m[" << i << "][" << j << "]的值为：" << m[i][j] << endl;
		}
}
void Traceback(int i, int j, int** s) //这个的思想好啊
{
	if (i == j) { cout << 'A' << i; return; }
	if (i < s[i][j]) cout << '(';
	Traceback(i, s[i][j], s);
	if (i < s[i][j]) cout << ')';
	if (s[i][j] + 1 < j) cout << '(';
	Traceback(s[i][j] + 1, j, s);
	if (s[i][j] + 1 < j) cout << ')';
}

int main() {
	int n = 0;

	do {
		cout << "please enter the number of matrix: " << endl;
		cin >> n;
	} while (n > 1 ? 0 : 1);
	
	
	//用上一题掌握的memset()新技能初始化数组吧~
	int* p = new int[n + 2];
	memset(p, 0, sizeof(*p) * (n + 2));
	*p = -1; //第0项不存储
	
	int** m = new int*[n + 1];
	for (int i = 0; i < n + 1; i++) {
		*(m + i) = new int[n + 1];
		//以下初始化
		if(i == 0) memset(*(m + i), -1, sizeof(**(m + i)) * (n + 1));
		else {
			memset(*(m + i), -1, sizeof(**(m + i)) * 1);
			memset(*(m + i) + 1, 0, sizeof(**(m + i)) * n);
		}
		//for (int j = 0; j < n + 1; j++) cout << *(*(m + i) + j) << " ";
		//cout << endl;
	}
	
	int** s = new int* [n + 1];
	for (int i = 0; i < n + 1; i++) {
		*(s + i) = new int[n + 1];
		//以下初始化，和m数组的初始化原理一样，只不过这里使用三目运算符简化过程
		memset(*(s + i) + 1, i!=0?0:-1, sizeof(**(s + i)) * n);
		memset(*(s + i), -1, sizeof(**(s + i)) * 1);
		//for (int j = 0; j < n + 1; j++) cout << *(*(s + i) + j) << " ";
		//cout << endl;
	}


	cout << "Please enter p[]:" << endl;

	for (int i = 1; i <= n + 1; i++) {
		cin >> p[i];
	}
	
	//test4: 50 10 40 30 5
	//test6: 30 35 15 5 10 20 25
	//for (int i = 0; i <= n + 1; i++) cout << *(p+i) << " ";

	MatrixChain(n, p, m, s);

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) cout << "\t" << *(*(m + i) + j) << " ";
		cout << endl;
	}

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) cout << "\t" << *(*(s + i) + j) << " ";
		cout << endl;
	}

	cout << "the best chain is: " << endl;
	Traceback(1, n, s);
}
