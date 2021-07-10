#include <iostream>
#include <math.h> 
#include <string.h> //memeset() 
using namespace std;

#define N 8
#define INF 1061109567


bool Place(int k,int i,int *x,int *y)	
{
	int t = N - 1;
	//判定两个皇后是否在同一列或在同一斜线上
	for (int j=0;j<k;j++){
		if((x[j]==i)||(abs(x[j]-i)==abs(j-k))) {
			return false;
		}
	}
	//new，排除可旋转对称情况 
//	if(!y[i][t-k] || !y[t-k][t-i] || !y[t-i][k] || !y[t-k][i] || !y[k][t-i]) {
//		y[k][i] = 0;
//		return false;
//	} 
//	if(x[i]==t-k || x[t-k]==t-i || x[t-i]==k || x[t-k]==i || x[k]==t-i) {
//		y[k][i] = 0;
//		return false;
//	} 
	return true;
}

//bool AvailablePlace(int m, int i, int *x, int *y){
//	int t = N - 1;
//	//创建并初始化临时数组 
//	int* count = new int[5]{0};
//	//顺时针旋转1次 
//	for(int i=0; i<=t; i++){
//		if(y[x[i]][t-i] == y[i][x[i]]) count[0]++;
//		else break;
//	}
//	//顺时针旋转2次 
//	for(int i=0; i<=t; i++){
//		if(y[t-i][t-x[i]] == y[i][x[i]]) count[1]++;
//		else break;
//	}
//	//顺时针旋转3次 
//	for(int i=0; i<=t; i++){
//		if(y[t-x[i]][i] == y[i][x[i]]) count[2]++;
//		else break;
//	}
//	//上下对称
//	for(int i=0; i<=t; i++){
//		if(y[t-i][x[i]] == y[i][x[i]]) count[3]++;
//		else break;
//	}
//	//左右对称 
//	for(int i=0; i<=t; i++){
//		if(y[i][t-x[i]] == y[i][x[i]]) count[4]++;
//		else break;
//	}
//	if(count[0]==t+1 || count[1]==t+1 || count[2]==t+1 || count[3]==t+1 || count[4]==t+1) return false;
//	else return true;
//}
//x[i]=j即i行j列被使用,t为n-1 即最大下标 
//旋转(顺时针)： (i,j)->(j,t-i)->(t-i,t-j)->(t-j,i)
//对称：(i,j)->(2*t/2-i,j)->(i,2*t/2-j) 
//由于递归的关系，每次结果相互无关联，只能另取二维数组y[i][j]存储每一次的结果，以筛选往次的重复结果 
//犯错误了， 没有从整体的角度出发，光想着每个元素的约束条件，旋转对称强调的是整体！
//新增1个临时二维数组，用来存放旋转、对称的结果，以作比较。 

//void NQueens(int k,int n,int *x,int **y)	//递归函数(求解 n 皇后问题)
//{
//	for (int i=0;i<n;i++){
//		if(Place(k,i,x,y)) {
//			x[k]=i;
//			y[k][i] = 1; //new
//			if (k==n-1){
//				if(AvailablePlace(k,i,x,y)) {
//					for(i=0;i<n;i++) cout<<x[i]<<" ";
//					cout<<endl;	
//				//test
////				cout<<endl;
////				for(int i=0;i<N;i++) {
////					for(int j=0;j<N;j++) cout << "\t" << y[i][j] << " ";
////				cout<<endl;
////				}
//				}
//			}else NQueens(k+1,n,x,y);
//		}
//	}
//}


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
		//顺时针2次 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)]!=t-z[0+i]) break; 
		if(i == N) return false;
		//顺时针3次 
		for(i=0; i<N; i++) if(y[p*N + t-z[0+i]] != 0+i) break; 
		if(i == N) return false;
		//上下对称 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)] != z[0+i]) break; 
		if(i == N) return false;
		//左右对称 
		for(i=0; i<N; i++) if(y[p*N + (0+i)] != t - z[0+i]) break; 
		if(i == N) return false;
	} 
	return true;
}
//旋转(顺时针)： y[i]=x[i]  ->  y[x[i]]=t-i  ->  y[t-i]=t-x[i]  ->  y[t-x[i]]=i

int Find(int n, int* x, int k, int *y)
{
	int i = x[k];
//	bool n_is_odd;
//	if (n % 2 != 0)	n_is_odd = true;
//	else n_is_odd = false;
//	if (k == 1 && n_is_odd && x[0] == n / 2 + 1)  //如果当前行为第二行且n为奇数，同时第一行皇后位置为正中间，则第二行最多试探到n/2列终止
//	{
//		if (i + 1 < n / 2) return i + 1;
//		else return -1;
//	}

	for (i++; i < n; i++)
	{
		if (Place(k, i, x, y))  //在k+1行找到可放置皇后的列
			return i;    //返回该列
	}
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
		if (k == 0)   //进入或回溯至第一行
		{
			x[k] = x[k] + 1;   //试探下一列

			if (x[k] > n-1)    //利用max_col剪枝，如果n为奇数,第一行第n/2+1列试探完毕后终止，否则n/2列试探完毕后终止
			{
				break;         //max_col = n-1 就是全部情况92种 
			}

			k++;    //试探下一行
		}
		else
		{
			int temp;
			if ((temp = Find(n, x, k, y)) == -1)    //k+1行没有找到可放置皇后的位置
			{
				x[k] = -1;           //清理
				k--;                //回溯
			}
			else
			{
				x[k] = temp;     //在k+1行找到的位置赋予x[k]
				if (k != (n - 1))     //皇后没有全部放置完毕
				{
					k++;          //试探下一行
				}
				else if(AvailablePlace(m, x, y))  //皇后全部放置成功，找到解，判断是否重复解 
				{
					printf("The %dnd solution\n", m+1); //报数从1开始 
					//Output(n, x);    //输出解模型 
					for(int i=0;i<n;i++){
						cout<<x[i]+1<<" ";  //输出解
						y[m*n+i] = x[i];//存储结果x[i]=j到y[m*n+i]=j   //m从0开始
					}
					m++;  //计次从0开始 
					cout<<endl;	
				}
			}
		}

	}
}

void NQueens(int n,int *x)
{	
	//new
	int* y = new int[INF];
	memset(y, -1, sizeof(*y)*INF);

	NQueens(0,n,x,y);
	
	////test
//	for(int i=0;i<INF;i++) {
//		if(y[i]==-1) break;
//		if(i%N==0) cout<<endl;
//		cout<<y[i]<<" ";
//	}
}

int main()
{
	int n=N;
	int x[n];
	for (int i=0;i<n;i++) x[i]=-1;

	NQueens(n,x);

	return 0;
}



//
//The 1nd solution√ 
//1 5 8 6 3 7 2 4
//The 2nd solution√ 
//1 6 8 3 7 4 2 5

//The 3nd solution 
//1 7 4 6 8 2 5 3
//The 4nd solution 
//1 7 5 8 2 4 6 3
//The 5nd solution
//2 4 6 8 3 1 7 5

//The 6nd solution√ 
//2 5 7 1 3 8 6 4
//The 7nd solution√ 
//2 5 7 4 1 8 6 3
//The 8nd solution√ 
//2 6 1 7 4 8 3 5
//The 9nd solution√ 
//2 6 8 3 1 4 7 5
//The 10nd solution√ 
//2 7 3 6 8 5 1 4
//The 11nd solution√ 
//2 7 5 8 1 4 6 3
//

//2 8 6 1 3 5 7 4 ???

//The 12nd solution
//3 1 7 5 8 2 4 6
//
//The 13nd solution√ 
//3 5 2 8 1 7 4 6
//The 14nd solution√ 
//3 5 8 4 1 7 2 6
//The 15nd solution√ 
//3 6 2 5 8 1 7 4
//
//The 16nd solution
//3 6 2 7 1 4 8 5
//The 17nd solution
//3 6 2 7 5 1 8 4
//The 18nd solution
//3 6 4 1 8 5 7 2
//The 19nd solution
//4 1 5 8 6 3 7 2
//The 20nd solution
//4 2 7 5 1 8 6 3
//The 21nd solution
//5 1 4 6 8 2 7 3
//The 22nd solution
//5 2 6 1 7 4 8 3
//The 23nd solution
//5 3 1 7 2 8 6 4
//The 24nd solution
//5 7 1 4 2 8 6 3
