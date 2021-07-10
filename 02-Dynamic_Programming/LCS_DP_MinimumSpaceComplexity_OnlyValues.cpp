#include<iostream>
#include<string.h>
#define MAXLENGTH 11

using namespace std;
 
class LCS
{
	private:
		char* a, * b; //l��Žϳ����� 
		int *c1,*c2;
		int l,s; //l��Žϳ����еĳ��ȣ�s��Ž϶����еĳ��ȡ�
		
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
		
		c1=new int[s+1]; //��+1������Ϊ��1��ʼ 
		c2=new int[s+1];
		memset(c1, 0, sizeof(*c1) * (s+1)); //��ʼ��c1��c2           //Ϊc1��c2����ֵ
		memset(c2, 0, sizeof(*c2) * (s+1));
		
		a = new char[l + 2]; // ��ʼ�������С�+2����ԭ�򣺴�1��ʼ�����ַ����������ַ����������"\0"
		b = new char[s + 2]; // �±�0��0������������Ӧ��

		memset(a, 0, sizeof(*a) * (l + 2)); //��a����ǰm����ȫ������ʼ��Ϊ'\0'
		memset(b, 0, sizeof(*b) * (s + 2));

		*a = '#';//��1��ʼ��ֹ�ַ�����������0������ʼ��Ϊ'\0'���ȱ���ֵ�������޷�ֱ��ͨ��cout<<a;���
		*b = '#';
		memcpy(a + 1, x, sizeof(*a) * (l));//��x��y�е��ַ�д��һά����a��
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
		//����c1��c2 
		temp = c1;
		c1 = c2;
		c2 = temp;
	}
	return c1[s]; //�������Ž�ֵ
}


int main()
{ 
	
	int nx = 0, ny = 0;
	char* x = new char[MAXLENGTH], * y = new char[MAXLENGTH];	//��ʼ������x,y

	//Enter
	cout << "Please input string x !(max length allowed to enter: " << MAXLENGTH - 1 << ")" << endl;
	cin >> x;
	for (int i = 0; i < MAXLENGTH; i++) {
		if (*(x + i) == '\0') {
			nx = i;
			break; //iֻ�д�0��ʼ�˳���ʱ��nx�ű�ʾ����'#'�ĳ���
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
	LCS lcs(nx, ny, x, y);//����x��y�Լ����ǵĳ���nx��ny
	
	cout<<"����������г���ֵ�����Ž�ֵ����"<<lcs.LCSLength()<<endl;
	
	delete []x;
	delete []y;
	return 0; 
}

