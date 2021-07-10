//作者：naturerun
//链接：https://www.zhihu.com/question/325980883/answer/694887889
//来源：知乎
//著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

#include <stdio.h>
#include <malloc.h>
#include <math.h>
int place(int i, int k, int* p);  //检查k+1行i列能否放置皇后,能返回1，否则返回0
int find(int n, int* p, int k, bool n_is_odd);   //在k+1行搜索可以放置皇后的位置，找到位置后返回列标，否则返回0
void output(int n, int* p);   //输出n皇后问题的一个解

int main()
{
	int k, n;
	int m;
	int* p;  //这是从1开始计的 

	printf("you want to solve n queens problem\n");
	printf("n=");
	scanf("%d", &n);                   //输入问题规模

	p = (int*)malloc(n * sizeof(int));   //p[k]表示k+1行皇后所在列
	for (k = 0; k < n; k++)	p[k] = 0;    //初始化数组p        

	k = 0;       //初始化为第一行
	m = 0;      //记录解的个数变量初始化
	
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
			p[k] = p[k] + 1;   //试探下一列

			if (p[k] > max_col)    //利用max_col剪枝，如果n为奇数,第一行第n/2+1列试探完毕后终止，否则n/2列试探完毕后终止
			{
				break;
			}

			k++;    //试探下一行
		}
		else
		{
			int temp;
			if ((temp = find(n, p, k, n_is_odd)) == 0)    //k+1行没有找到可放置皇后的位置
			{
				p[k] = 0;             //必要的清理
				k--;                //回溯
			}
			else
			{
				p[k] = temp;     //在k+1行找到的位置赋予p[k]
				if (k != (n - 1))     //皇后没有全部放置完毕
				{
					k++;          //试探下一行
				}
				else        //皇后全部放置成功，找到解
				{
					m++;
					printf("The %dnd solution\n", m);
					for(int i=0;i<n;i++) printf("%d ",p[i]);  //输出解 
					printf("\n");
					output(n, p);    //输出解
				}
			}
		}
	}

	printf("There are %d solutions in total\n", m);   //输出解的个数
  return 0;
}

int place(int i, int k, int* p)
{
	for (int m = 0; m < k; m++)
	{
		if ((p[m] == i) || (abs(m - k) == abs(p[m] - i)))   //k+1行i列不是合法位置
			return 0;
	}

	return 1;   //k+1行i列是合法位置    
}

int find(int n, int* p, int k, bool n_is_odd)
{
	int i = p[k];

	int max_col = n;
	if (k == 1 && n_is_odd && p[0] == n / 2 + 1)  //如果当前行为第二行且n为奇数，同时第一行皇后位置为正中间，则第二行最多试探到n/2列终止
	{
		if (i + 1 < n / 2) return i + 1;
		else return 0;
	}

	for (i++; i <= max_col; i++)
	{
		if (place(i, k, p) == 1)  //在k+1行找到可放置皇后的列
			return i;    //返回该列
	}
	return 0;   //在k+1行没有找到可放置皇后的列
}

void output(int n, int* p)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (j == p[i])
				printf("1 ");
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}
