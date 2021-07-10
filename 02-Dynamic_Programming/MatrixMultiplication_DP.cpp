#include<iostream>
#include<string.h>

using namespace std;

void MatrixChain(int n, int* p, int** m, int** s) //n���������ˣ���i�����������*(p+i)������i-1����������������һ�����������*(p+n+1)����Ai�������˵�Aj��������ٴ�����¼��m��ά���飬���ٴ���ʱ�õĽص��¼��s����
{
	for (int i = 1; i <= n; i++) m[i][i] = 0; //��ʼ���Խ���Ԫ�أ�����0���1��ʼ
	for (int r = 2; r <= n; r++) //һ��n��б�У����Խ��ߣ������
		for (int i = 1; i <= n - r + 1; i++) //����б���ϵ�i������������������n-r+1��
		{
			int j = i + r - 1; //��ø�λ�õ�����j
			m[i][j] = m[i + 1][j] + p[i] * p[i + 1] * p[j + 1]; //ʡ����m[i][i]=0��ص�һ����ʣ�ಿ�ֵ����
			s[i][j] = i;
			for (int k = i + 1; k < j; k++) //�ɽ�����k=i���ҽ�������ɾ����������һ��
			{
				int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
				if (t < m[i][j])
				{
					m[i][j] = t;
					cout << "����m[" << i << "][" << j << "]��ֵΪ��" << t << endl;
					s[i][j] = k;
					cout << "����s[" << i << "][" << j << "]��ֵΪ��" << k << endl;
				}
			}
			cout << "���������m[" << i << "][" << j << "]��ֵΪ��" << m[i][j] << endl;
		}
}
void Traceback(int i, int j, int** s) //�����˼��ð�
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
	
	
	//����һ�����յ�memset()�¼��ܳ�ʼ�������~
	int* p = new int[n + 2];
	memset(p, 0, sizeof(*p) * (n + 2));
	*p = -1; //��0��洢
	
	int** m = new int*[n + 1];
	for (int i = 0; i < n + 1; i++) {
		*(m + i) = new int[n + 1];
		//���³�ʼ��
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
		//���³�ʼ������m����ĳ�ʼ��ԭ��һ����ֻ��������ʹ����Ŀ������򻯹���
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
