#include<iostream>
#include<string.h>

//����¼�������޸�LCSLength()��CLCS()����

using namespace std;

#define MAXLENGTH 11

class LCS
{
private:
	int** c, ** s; //�޸�
	int m, n;
	char* a, * b;
	void CLCS(int i, int j) const; //��ȡ����
	int LCSLength(int i, int j); //��ȡ����ֵ��

public:
	LCS(int nx, int ny, char* x, char* y) //���캯���������ݳ�Աm��n��a��b��c��s��ʼ��
	{
		m = nx;
		n = ny;

		a = new char[m + 2]; // ��ʼ�������С�+2����ԭ�򣺴�1��ʼ�����ַ����������ַ����������"\0"
		b = new char[n + 2]; // �±�0��0������������Ӧ��

		memset(a, 0, sizeof(*a) * (m + 2)); //��a����ǰm����ȫ������ʼ��Ϊ'\0'
		memset(b, 0, sizeof(*b) * (n + 2));

		/*
		* ����memeset()
		* memset(void* ptr, int value, size_t num)���������ֱ��ʾ:Ҫ�������ڴ�ָ��ptr��Ҫ���õ�ֵvalue��ptr��ǰnum���ֽڣ�����size_t��unsigned int
		* ���� value ������Ϊ int���������� unsigned char�����Է�Χ��0 ��255 ֮�䡣��ֻ�޸Ķ����ƺ��λ������char���ͣ������λת����Ϊascll�룬�ر�ģ�'\0'��acall���Ӧ0��
		* �˺�����ͷ�ļ�<string.h>����
		* һ�������������ʹ��sizeof()��ȷ����ע�⣬sizeof()�ڲ�����ָ�룬������32λ��ͳһ��ʾΪָ���С��4�ֽڣ������Ǳ�ʾԪ�صĴ�С
		* �ο���http://c.biancheng.net/cpp/html/157.html
		* �ο���https://baike.baidu.com/item/memset#2
		*
		*memset�������÷���ֻ��������ʼ��char���͵�����ģ�Ҳ����˵����ֻ����0x00-0xFF�ĸ�ֵ
		*memset��ʼ��int�����valueʱ��ֻ��-1��0�Ż���Ԥ�ڣ�����ԭ����������в��ģ�����׸����
		*������Ҳ���õ�int���ͣ�int��4���ֽڣ���memset(,1,sizeof());ʱ��1�൱��ASSCII���1��1תΪ������00000001������һ�ֽڣ�һ�ֽ�8λ��intΪ4�ֽڣ����Գ�ʼ����ÿ����Ϊ00000001000000010000000100000001 = 16843009��
		*�ο���https://blog.csdn.net/lyj2014211626/article/details/65481630?utm_medium=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromMachineLearnPai2~default-2.vipsorttest&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~BlogCommendFromMachineLearnPai2~default-2.vipsorttest
		*
		* ע�⣬��̬���ɵĶ�ά�����ڴ�ռ䲻һ����������memset()��ԭ����ֱ�Ӷ��ڴ���в��������������������������memset
		*
		* ���ܶ��Ѿ���ֵ�� char* ָ�����memset()��������Ϊ char*���ַ�����һ����ֵ�����ڴ���ֻ���ģ� char[]���ַ����飩�ſ����޸�
		* �ο���https://stackoverflow.com/questions/1704407/what-is-the-difference-between-char-s-and-char-s
		*/
		* a = '#';//��1��ʼ��ֹ�ַ�����������0������ʼ��Ϊ'\0'���ȱ���ֵ�������޷�ֱ��ͨ��cout<<a;���
		*b = '#';
		memcpy(a + 1, x, sizeof(*a) * (m));//��x��y�е��ַ�д��һά����a��
		memcpy(b + 1, y, sizeof(*b) * (n));

		/*
		* ����memcpy
		* memcpy(void* toPtr, int fromPtr, size_t num) ��fromPtrָ��ָ��������ڴ������ݸ��Ƶ�toPtrָ��ָ������飬����num���ֶ�
		* ע�⣺���Ƶ����ݳ��Ȳ��ܵ��ڻ򳬹�Ŀ��ָ��ָ������ĳ��ȣ����ڸ��Ƶ������в���'\0'��ճ��ʱ��ʹ�����鲻��'\0'�����������ᵼ�����ʱ�������루�޷�ʶ����ֹ����
		*/

		c = new int* [m + 1]; //��̬��������ʼ����ά���飨����ÿһ��Ԫ��Ϊ0��������Ƿ�'\0'
		for (int i = 0; i < (m + 1); i++) {
			*(c + i) = new int[n + 1];
			memset(*(c + i), 0, sizeof(**(c + i)) * (n + 1));
		}
		s = new int* [m + 1];
		for (int i = 0; i < (m + 1); i++) {
			*(s + i) = new int[n + 1];
			memset(*(s + i), 0, sizeof(**(s + i)) * (n + 1));
		}
	}

	int LCSLength(); //���ú�����ȡ����ֵ��

	void CLCS();//����˽�г�Ա����CLCS(int,int)����ȡ����

	void getc() {
		cout << ' ' << b << endl;
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
		for (int i = 0; i <= m; i++) {
			cout << a[i];
			for (int j = 0; j <= n; j++) {
				cout << *(*(s + i) + j);
			}
			cout << endl;
		}
	}
};

int LCS::LCSLength(int i, int j)
{
	if (i == 0 || j == 0) return 0;
	if (c[i][j] != 0) return c[i][j];
	else
		if (a[i] == b[j])
		{
			c[i][j] = LCSLength(i - 1, j - 1) + 1; s[i][j] = 1;
		}
		else
			if (LCSLength(i - 1, j) >= LCSLength(i, j - 1))
			{
				c[i][j] = LCSLength(i - 1, j); s[i][j] = 2;
			}
			else
			{
				c[i][j] = LCSLength(i, j - 1); s[i][j] = 3;
			}
	return c[i][j];
}
int LCS::LCSLength() {
	return LCSLength(m, n);
}

void LCS::CLCS(int i, int j) const
{
	if (i == 0 || j == 0) return;
	if (a[i] == b[j])
	{
		CLCS(i - 1, j - 1);
		cout << a[i];
	}
	else
		if (c[i - 1][j] >= c[i][j - 1]) CLCS(i - 1, j);
		else CLCS(i, j - 1);
}
void LCS::CLCS() {
	CLCS(m, n);
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

	//Clean
	delete[]x;
	delete[]y;

	return 0;
}

