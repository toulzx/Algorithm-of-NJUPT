//���ߣ�naturerun
//���ӣ�https://www.zhihu.com/question/325980883/answer/694887889
//��Դ��֪��
//����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������

#include <stdio.h>
#include <malloc.h>
#include <math.h>
int place(int i, int k, int* p);  //���k+1��i���ܷ���ûʺ�,�ܷ���1�����򷵻�0
int find(int n, int* p, int k, bool n_is_odd);   //��k+1���������Է��ûʺ��λ�ã��ҵ�λ�ú󷵻��б꣬���򷵻�0
void output(int n, int* p);   //���n�ʺ������һ����

int main()
{
	int k, n;
	int m;
	int* p;  //���Ǵ�1��ʼ�Ƶ� 

	printf("you want to solve n queens problem\n");
	printf("n=");
	scanf("%d", &n);                   //���������ģ

	p = (int*)malloc(n * sizeof(int));   //p[k]��ʾk+1�лʺ�������
	for (k = 0; k < n; k++)	p[k] = 0;    //��ʼ������p        

	k = 0;       //��ʼ��Ϊ��һ��
	m = 0;      //��¼��ĸ���������ʼ��
	
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
			p[k] = p[k] + 1;   //��̽��һ��

			if (p[k] > max_col)    //����max_col��֦�����nΪ����,��һ�е�n/2+1����̽��Ϻ���ֹ������n/2����̽��Ϻ���ֹ
			{
				break;
			}

			k++;    //��̽��һ��
		}
		else
		{
			int temp;
			if ((temp = find(n, p, k, n_is_odd)) == 0)    //k+1��û���ҵ��ɷ��ûʺ��λ��
			{
				p[k] = 0;             //��Ҫ������
				k--;                //����
			}
			else
			{
				p[k] = temp;     //��k+1���ҵ���λ�ø���p[k]
				if (k != (n - 1))     //�ʺ�û��ȫ���������
				{
					k++;          //��̽��һ��
				}
				else        //�ʺ�ȫ�����óɹ����ҵ���
				{
					m++;
					printf("The %dnd solution\n", m);
					for(int i=0;i<n;i++) printf("%d ",p[i]);  //����� 
					printf("\n");
					output(n, p);    //�����
				}
			}
		}
	}

	printf("There are %d solutions in total\n", m);   //�����ĸ���
  return 0;
}

int place(int i, int k, int* p)
{
	for (int m = 0; m < k; m++)
	{
		if ((p[m] == i) || (abs(m - k) == abs(p[m] - i)))   //k+1��i�в��ǺϷ�λ��
			return 0;
	}

	return 1;   //k+1��i���ǺϷ�λ��    
}

int find(int n, int* p, int k, bool n_is_odd)
{
	int i = p[k];

	int max_col = n;
	if (k == 1 && n_is_odd && p[0] == n / 2 + 1)  //�����ǰ��Ϊ�ڶ�����nΪ������ͬʱ��һ�лʺ�λ��Ϊ���м䣬��ڶ��������̽��n/2����ֹ
	{
		if (i + 1 < n / 2) return i + 1;
		else return 0;
	}

	for (i++; i <= max_col; i++)
	{
		if (place(i, k, p) == 1)  //��k+1���ҵ��ɷ��ûʺ����
			return i;    //���ظ���
	}
	return 0;   //��k+1��û���ҵ��ɷ��ûʺ����
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
