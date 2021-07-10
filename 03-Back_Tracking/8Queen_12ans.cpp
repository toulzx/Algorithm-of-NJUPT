#include <iostream>
#include <math.h> 
#include <string.h> //memeset() 
using namespace std;

#define N 8
#define INF 1061109567



bool Place(int k,int i,int *x,int *y)	//判定两个皇后是否在同一列或在同一斜线上
{
	for (int j=0;j<k;j++) if((x[j]==i)||(abs(x[j]-i)==abs(j-k))) return false;
	return true;
}


bool AvailablePlace(int m, int *x, int *y) {
	int t = N-1;
	int i;
	for(int p=0; p*N<INF; p++) {
		if(y[p*N+0]==-1) break;
		//顺时针1次 
		for(i=0; i<N; i++) if(y[p*N + x[0+i]]!=t-(0+i)) break; 
		if(i == N) return false;
		//顺时针2次 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)]!=t-x[0+i]) break; 
		if(i == N) return false;
		//顺时针3次 
		for(i=0; i<N; i++) if(y[p*N + t-x[0+i]] != 0+i) break; 
		if(i == N) return false;
		//上下对称 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)] != x[0+i]) break; 
		if(i == N) return false;
		//左右对称 
		for(i=0; i<N; i++) if(y[p*N + (0+i)] != t - x[0+i]) break; 
		if(i == N) return false;
	}
	//上下对称+旋转
	//和 左右对称+旋转 的效果是一样的 
	for(int p=0; p*N<INF; p++) {
		if(y[p*N+0]==-1) break;
		int*z = new int[N];
		memcpy(z,x,sizeof(*z)*N);
		//构造上下对称的z 
		for(i=0; i<(N/2); i++){
			int temp = z[i];
			z[i] = z[t-i];
			z[t-i] = temp; 
		}
		//对z顺时针1次 
		for(i=0; i<N; i++) if(y[p*N + z[0+i]]!=t-(0+i)) break; 
		if(i == N) return false;
		//对z顺时针2次 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)]!=t-z[0+i]) break; 
		if(i == N) return false;
		//对z顺时针3次 
		for(i=0; i<N; i++) if(y[p*N + t-z[0+i]] != 0+i) break; 
		if(i == N) return false;
	} 
	return true;
}
//旋转(顺时针)： y[i]=x[i]  ->  y[x[i]]=t-i  ->  y[t-i]=t-x[i]  ->  y[t-x[i]]=i

int Find(int n, int* x, int k, int *y)
{
	int i = x[k];
	for (i++; i < n; i++) if(Place(k, i, x, y)) return i;     //在k+1行找到可放置皇后的列,返回该列
	return -1;   //在k+1行没有找到可放置皇后的列
}


void Output(int n, int* x)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == x[i])
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}

void NQueens(int k,int n,int *x,int *y)	//递归函数(求解 n 皇后问题)
{
	int m = 0;
	bool n_is_odd;
	if (n % 2 != 0)	n_is_odd = true;
	else n_is_odd = false;

	int max_col;
	if (n_is_odd) max_col = n / 2 + 1;
	else max_col = n / 2;
	
	while (true)
	{
		if (k == 0)//进入或回溯至第一行
		{
			x[k] = x[k] + 1;   //试探下一列
			if (x[k] > max_col) break;    //利用max_col剪枝，如果n为奇数,第一行第n/2+1列试探完毕后终止，否则n/2列试探完毕后终止 //若max_col = n-1 在没有AvailablePlace()约束下就是全部情况92种 
			k++;    //试探下一行
		}
		else
		{
			int i = Find(n, x, k, y);
			if(i  == -1)//k+1行没有找到可放置皇后的位置
			{
				x[k] = -1;          //必要的清理
				k--;                //回溯
			}
			else
			{
				x[k] = i;  //在k+1行找到的位置赋予x[k]
				if (k != (n - 1)) k++;  //皇后没有全部放置完毕 //试探下一行
				else if(AvailablePlace(m, x, y))  //皇后全部放置成功后，判断是否重复解 
				{
					cout<<endl<<"The "<<m+1<<" solution: "; //报序从1开始
					//Output(n, x);    //输出解模型 
					for(int i=0;i<n;i++) {
						cout<<x[i]+1<<" ";  //输出解
						y[m*n+i] = x[i]; //存储结果x[i]=j到y[m*n+i]=j   //m从0开始
					}
					m++;  //计次从0开始
					//cout<<endl;	
					//exit(0); //若希望只输出首次可行解 
				}
			}
		}
	}
}

void NQueens(int n,int *x)	//new
{
	int* y = new int[INF];
	memset(y, -1, sizeof(*y)*INF);
	NQueens(0,n,x,y);
}

int main()
{
	int n=N;
	int x[n];
	for (int i=0;i<n;i++) x[i]=-1;
	NQueens(n,x);
	return 0;
}

