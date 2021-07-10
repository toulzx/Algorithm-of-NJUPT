#include <iostream>
#include <math.h> 
#include <string.h> //memeset() 
using namespace std;

#define N 8
#define INF 1061109567



bool Place(int k,int i,int *x,int *y)	//�ж������ʺ��Ƿ���ͬһ�л���ͬһб����
{
	for (int j=0;j<k;j++) if((x[j]==i)||(abs(x[j]-i)==abs(j-k))) return false;
	return true;
}


bool AvailablePlace(int m, int *x, int *y) {
	int t = N-1;
	int i;
	for(int p=0; p*N<INF; p++) {
		if(y[p*N+0]==-1) break;
		//˳ʱ��1�� 
		for(i=0; i<N; i++) if(y[p*N + x[0+i]]!=t-(0+i)) break; 
		if(i == N) return false;
		//˳ʱ��2�� 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)]!=t-x[0+i]) break; 
		if(i == N) return false;
		//˳ʱ��3�� 
		for(i=0; i<N; i++) if(y[p*N + t-x[0+i]] != 0+i) break; 
		if(i == N) return false;
		//���¶Գ� 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)] != x[0+i]) break; 
		if(i == N) return false;
		//���ҶԳ� 
		for(i=0; i<N; i++) if(y[p*N + (0+i)] != t - x[0+i]) break; 
		if(i == N) return false;
	}
	//���¶Գ�+��ת
	//�� ���ҶԳ�+��ת ��Ч����һ���� 
	for(int p=0; p*N<INF; p++) {
		if(y[p*N+0]==-1) break;
		int*z = new int[N];
		memcpy(z,x,sizeof(*z)*N);
		//�������¶ԳƵ�z 
		for(i=0; i<(N/2); i++){
			int temp = z[i];
			z[i] = z[t-i];
			z[t-i] = temp; 
		}
		//��z˳ʱ��1�� 
		for(i=0; i<N; i++) if(y[p*N + z[0+i]]!=t-(0+i)) break; 
		if(i == N) return false;
		//��z˳ʱ��2�� 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)]!=t-z[0+i]) break; 
		if(i == N) return false;
		//��z˳ʱ��3�� 
		for(i=0; i<N; i++) if(y[p*N + t-z[0+i]] != 0+i) break; 
		if(i == N) return false;
	} 
	return true;
}
//��ת(˳ʱ��)�� y[i]=x[i]  ->  y[x[i]]=t-i  ->  y[t-i]=t-x[i]  ->  y[t-x[i]]=i

int Find(int n, int* x, int k, int *y)
{
	int i = x[k];
	for (i++; i < n; i++) if(Place(k, i, x, y)) return i;     //��k+1���ҵ��ɷ��ûʺ����,���ظ���
	return -1;   //��k+1��û���ҵ��ɷ��ûʺ����
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

void NQueens(int k,int n,int *x,int *y)	//�ݹ麯��(��� n �ʺ�����)
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
		if (k == 0)//������������һ��
		{
			x[k] = x[k] + 1;   //��̽��һ��
			if (x[k] > max_col) break;    //����max_col��֦�����nΪ����,��һ�е�n/2+1����̽��Ϻ���ֹ������n/2����̽��Ϻ���ֹ //��max_col = n-1 ��û��AvailablePlace()Լ���¾���ȫ�����92�� 
			k++;    //��̽��һ��
		}
		else
		{
			int i = Find(n, x, k, y);
			if(i  == -1)//k+1��û���ҵ��ɷ��ûʺ��λ��
			{
				x[k] = -1;          //��Ҫ������
				k--;                //����
			}
			else
			{
				x[k] = i;  //��k+1���ҵ���λ�ø���x[k]
				if (k != (n - 1)) k++;  //�ʺ�û��ȫ��������� //��̽��һ��
				else if(AvailablePlace(m, x, y))  //�ʺ�ȫ�����óɹ����ж��Ƿ��ظ��� 
				{
					cout<<endl<<"The "<<m+1<<" solution: "; //�����1��ʼ
					//Output(n, x);    //�����ģ�� 
					for(int i=0;i<n;i++) {
						cout<<x[i]+1<<" ";  //�����
						y[m*n+i] = x[i]; //�洢���x[i]=j��y[m*n+i]=j   //m��0��ʼ
					}
					m++;  //�ƴδ�0��ʼ
					//cout<<endl;	
					//exit(0); //��ϣ��ֻ����״ο��н� 
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

