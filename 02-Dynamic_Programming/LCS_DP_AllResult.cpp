#include<iostream>
#include<string.h>
#include<stack>

using namespace std;

#define MAXLENGTH 11
#define N 20




class LCS
{
private:
	int** c, ** s; //�޸�
	int m, n;
	char* a, * b;
	int CLCS(int i, int j, int t, int q, bool tf) const; //��ȡ����
	char** ch; //�洢��� 
	int ch_n; //��¼�ж�������� 
	int ch_l; //��¼�����г��� 
	void Output();

public:
	LCS(int nx, int ny, char* x, char* y) //���캯���������ݳ�Աm��n��a��b��c��s��ʼ��
	{
		ch_n = -1;
		ch_l = -1;
		m = nx;
		n = ny;
		
		a = new char[m + 2]; // ��ʼ�������С�+2����ԭ�򣺴�1��ʼ�����ַ����������ַ����������"\0"
		b = new char[n + 2]; // �±�0��0������������Ӧ��

		memset(a, 0, sizeof(*a) * (m + 2)); //��a����ǰm����ȫ������ʼ��Ϊ'\0'
		memset(b, 0, sizeof(*b) * (n + 2));

		*a = '#';//��1��ʼ��ֹ�ַ�����������0������ʼ��Ϊ'\0'���ȱ���ֵ�������޷�ֱ��ͨ��cout<<a;���
		*b = '#';
		memcpy(a + 1, x, sizeof(*a) * (m));//��x��y�е��ַ�д��һά����a��
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
		ch = new char* [N + 1];//��̬��������ʼ����ά����ÿһ��Ԫ��Ϊ#��������Ƿ�'\0'
		for (int i = 0; i < (N + 1); i++) {
			*(ch + i) = new char[MAXLENGTH + 1];
			memset(*(ch + i), '#', sizeof(**(ch + i)) * (MAXLENGTH + 1));
		}
		
	}

	int LCSLength(); //��ȡ����ֵ��

	void CLCS();//����˽�г�Ա����CLCS(int,int)����ȡ����

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
				s[i][j] = 1; //s�д洢������̣�1��ʾ�ҵ���ͬ�3��ʾ������������ϣ�4��ʾ��=�ϣ�2��ʾ����
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
	ch_l = c[m][n]; //��¼���Ž� 
	return ch_l; //�������Ž�ֵ
}

int LCS::CLCS(int i, int j, int t, int q, bool tf) const //��¼t��������У���������q����ĸ λ�� 
{
	if (i == 0 || j == 0 || s[i][j] == 0) return t;
	if (s[i][j] == 1)  //����a[i] == b[j]
	{
		ch[t][q] = a[i]; //�洢��ch���飨���� 
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
			if(ch[i][j] == '#') //�������ط�û��ֵ�������������һ�У���#���ַ�Խ�������ȼ�Խ�� 
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
	char* x = new char[MAXLENGTH], * y = new char[MAXLENGTH];	//��ʼ������x,y

	//Enter
	cout << "Please input string x !(max length allowed to enter: " << MAXLENGTH-1 << ")" << endl;
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

