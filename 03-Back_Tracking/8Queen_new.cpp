#include <iostream>
#include <math.h> 
#include <string.h> //memeset() 
using namespace std;

#define N 8
#define INF 1061109567


bool Place(int k,int i,int *x,int *y)	
{
	int t = N - 1;
	//�ж������ʺ��Ƿ���ͬһ�л���ͬһб����
	for (int j=0;j<k;j++){
		if((x[j]==i)||(abs(x[j]-i)==abs(j-k))) {
			return false;
		}
	}
	//new���ų�����ת�Գ���� 
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
//	//��������ʼ����ʱ���� 
//	int* count = new int[5]{0};
//	//˳ʱ����ת1�� 
//	for(int i=0; i<=t; i++){
//		if(y[x[i]][t-i] == y[i][x[i]]) count[0]++;
//		else break;
//	}
//	//˳ʱ����ת2�� 
//	for(int i=0; i<=t; i++){
//		if(y[t-i][t-x[i]] == y[i][x[i]]) count[1]++;
//		else break;
//	}
//	//˳ʱ����ת3�� 
//	for(int i=0; i<=t; i++){
//		if(y[t-x[i]][i] == y[i][x[i]]) count[2]++;
//		else break;
//	}
//	//���¶Գ�
//	for(int i=0; i<=t; i++){
//		if(y[t-i][x[i]] == y[i][x[i]]) count[3]++;
//		else break;
//	}
//	//���ҶԳ� 
//	for(int i=0; i<=t; i++){
//		if(y[i][t-x[i]] == y[i][x[i]]) count[4]++;
//		else break;
//	}
//	if(count[0]==t+1 || count[1]==t+1 || count[2]==t+1 || count[3]==t+1 || count[4]==t+1) return false;
//	else return true;
//}
//x[i]=j��i��j�б�ʹ��,tΪn-1 ������±� 
//��ת(˳ʱ��)�� (i,j)->(j,t-i)->(t-i,t-j)->(t-j,i)
//�Գƣ�(i,j)->(2*t/2-i,j)->(i,2*t/2-j) 
//���ڵݹ�Ĺ�ϵ��ÿ�ν���໥�޹�����ֻ����ȡ��ά����y[i][j]�洢ÿһ�εĽ������ɸѡ���ε��ظ���� 
//�������ˣ� û�д�����ĽǶȳ�����������ÿ��Ԫ�ص�Լ����������ת�Գ�ǿ���������壡
//����1����ʱ��ά���飬���������ת���ԳƵĽ���������Ƚϡ� 

//void NQueens(int k,int n,int *x,int **y)	//�ݹ麯��(��� n �ʺ�����)
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
		//˳ʱ��2�� 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)]!=t-z[0+i]) break; 
		if(i == N) return false;
		//˳ʱ��3�� 
		for(i=0; i<N; i++) if(y[p*N + t-z[0+i]] != 0+i) break; 
		if(i == N) return false;
		//���¶Գ� 
		for(i=0; i<N; i++) if(y[p*N + t-(0+i)] != z[0+i]) break; 
		if(i == N) return false;
		//���ҶԳ� 
		for(i=0; i<N; i++) if(y[p*N + (0+i)] != t - z[0+i]) break; 
		if(i == N) return false;
	} 
	return true;
}
//��ת(˳ʱ��)�� y[i]=x[i]  ->  y[x[i]]=t-i  ->  y[t-i]=t-x[i]  ->  y[t-x[i]]=i

int Find(int n, int* x, int k, int *y)
{
	int i = x[k];
//	bool n_is_odd;
//	if (n % 2 != 0)	n_is_odd = true;
//	else n_is_odd = false;
//	if (k == 1 && n_is_odd && x[0] == n / 2 + 1)  //�����ǰ��Ϊ�ڶ�����nΪ������ͬʱ��һ�лʺ�λ��Ϊ���м䣬��ڶ��������̽��n/2����ֹ
//	{
//		if (i + 1 < n / 2) return i + 1;
//		else return -1;
//	}

	for (i++; i < n; i++)
	{
		if (Place(k, i, x, y))  //��k+1���ҵ��ɷ��ûʺ����
			return i;    //���ظ���
	}
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
		if (k == 0)   //������������һ��
		{
			x[k] = x[k] + 1;   //��̽��һ��

			if (x[k] > n-1)    //����max_col��֦�����nΪ����,��һ�е�n/2+1����̽��Ϻ���ֹ������n/2����̽��Ϻ���ֹ
			{
				break;         //max_col = n-1 ����ȫ�����92�� 
			}

			k++;    //��̽��һ��
		}
		else
		{
			int temp;
			if ((temp = Find(n, x, k, y)) == -1)    //k+1��û���ҵ��ɷ��ûʺ��λ��
			{
				x[k] = -1;           //����
				k--;                //����
			}
			else
			{
				x[k] = temp;     //��k+1���ҵ���λ�ø���x[k]
				if (k != (n - 1))     //�ʺ�û��ȫ���������
				{
					k++;          //��̽��һ��
				}
				else if(AvailablePlace(m, x, y))  //�ʺ�ȫ�����óɹ����ҵ��⣬�ж��Ƿ��ظ��� 
				{
					printf("The %dnd solution\n", m+1); //������1��ʼ 
					//Output(n, x);    //�����ģ�� 
					for(int i=0;i<n;i++){
						cout<<x[i]+1<<" ";  //�����
						y[m*n+i] = x[i];//�洢���x[i]=j��y[m*n+i]=j   //m��0��ʼ
					}
					m++;  //�ƴδ�0��ʼ 
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
//The 1nd solution�� 
//1 5 8 6 3 7 2 4
//The 2nd solution�� 
//1 6 8 3 7 4 2 5

//The 3nd solution 
//1 7 4 6 8 2 5 3
//The 4nd solution 
//1 7 5 8 2 4 6 3
//The 5nd solution
//2 4 6 8 3 1 7 5

//The 6nd solution�� 
//2 5 7 1 3 8 6 4
//The 7nd solution�� 
//2 5 7 4 1 8 6 3
//The 8nd solution�� 
//2 6 1 7 4 8 3 5
//The 9nd solution�� 
//2 6 8 3 1 4 7 5
//The 10nd solution�� 
//2 7 3 6 8 5 1 4
//The 11nd solution�� 
//2 7 5 8 1 4 6 3
//

//2 8 6 1 3 5 7 4 ???

//The 12nd solution
//3 1 7 5 8 2 4 6
//
//The 13nd solution�� 
//3 5 2 8 1 7 4 6
//The 14nd solution�� 
//3 5 8 4 1 7 2 6
//The 15nd solution�� 
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
