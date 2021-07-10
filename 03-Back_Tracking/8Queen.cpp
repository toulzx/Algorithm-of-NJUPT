#include <iostream> 
#include <math.h>
using namespace std;

bool Place(int k,int i,int *x)	//�ж������ʺ��Ƿ���ͬһ�л���ͬһб����
{
	for (int j=0;j<k;j++) 	if((x[j]==i)||(abs(x[j]-i)==abs(j-k))) return false;
	return true;
}

void NQueens(int k,int n,int *x)	//�ݹ麯��(��� n �ʺ�����)
{
	for (int i=0;i<n;i++){
		if(Place(k,i,x)) {
			x[k]=i;
			if (k==n-1){
				for(i=0;i<n;i++) cout<<x[i]<<" ";
				cout<<endl;
			}else NQueens(k+1,n,x);
		}
	}
}

void NQueens(int n,int *x)
{
	NQueens(0,n,x);
}

int main()
{
	int x[8];
	for (int i=0;i<8;i++) x[i]=-1;
	NQueens(8,x);
	return 0;
}

