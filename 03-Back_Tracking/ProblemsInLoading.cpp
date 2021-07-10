#include<iostream>
#include<string.h> //ʹmemset()���� 
using namespace std;

#define N 5
#define C1 60
#define C2 40

template <class T> class Loading
{
	private:
		int n;	//��װ����
		int* x;	//��ǰ��
		int* bestx; //��ǰ��һ�Ҵ������Ž�
		T c1; //��һ���ִ��ĺ˶������� 
		T c2; //�ڶ����ִ��ĺ˶�������
		T* w; //��װ����������
		//T total;	//���м�װ������֮��
		T cw;	//��ǰ��һ�Ҵ��������������̱���������ͳ�� 
		T bestw; //��ǰ��һ�Ҵ�������������
		T r;	//ÿ��ڵ㴦ʣ�༯װ�������������̱���������ͳ�� 

	public:
		Loading(T* w)	//���캯��
		{
			n=N;
			x=new int[n+1];
			bestx=new int[n+1]; 
			c1=C1;
			c2=C2;
			this->w = w;
			cw=0;
			bestw=0;
			r=0;
			//��ʼ��x,bestx
			memset(x,-1,sizeof(*x)*(n+1));
			memset(bestx,-1,sizeof(*bestx)*(n+1));
			//��ʼ��r
			for(int i=1;i<=n;i++) r+=w[i];
		}
		
		~Loading()	//��������
		{
			delete []x;
			delete []bestx; 
		}
		
		void Backtrack(int i); //�ҵ���ӽ���һ���ִ�����c1�����װ�ط���, 
		//��������ֵbestw�����Ž�����bestx�� 
		
		void Show();//�������װ�ط���
};
		
		
template <class T> void Loading<T>::Backtrack(int i)
{	//������i����
	if (i>n)
	{//����Ҷ�ڵ�
 		if(cw>bestw)
		{
			for (int j=1;j<=n;j++) bestx[j]=x[j]; 
			bestw=cw;
		}
		return;
	}
	
	//��������
	r-=w[i];
	if (cw+w[i]<=c1)	//x[i]=1ʱ�Ŀ��н�Լ������
	{//����������
		x[i]=1;
		cw+=w[i];
		Backtrack(i+1);
		cw-=w[i];
	}
	if (cw+r>bestw)	//x[i]=0ʱ���ӵ�Լ����������ȥ�������Ž�ķ�֦
	{//����������
		x[i]=0;
		Backtrack(i+1);
	}
	r+=w[i];//�б�Ҫ��ԭ������ 
}

template <class T> void Loading<T>::Show()
{
	//test
//	cout << "n: " << n << endl << "cw: " << cw << endl ;
//	cout << "bestw: " << bestw << endl << "c1: " << c1 << endl ;
//	cout << "c2: " << c2 << endl << "r: " << r << endl;
//	
//	cout << endl << "x" << endl;
//	for( int i = 0 ; i <= n ; i ++) cout << *(x+i) << " ";
//	cout << endl << "bestx" << endl;
//	for( int i = 0 ; i <= n ; i ++) cout << *(bestx+i) << " ";
	
	cout << endl;
	
	//formal
	cout<<"�ִ����������ֱ�Ϊ��"<<endl;
	cout<<"c(1)="<<c1<<",c(2)="<<c2<<endl;
 
	cout<<"��װ��װ�������ֱ�Ϊ��"<<endl;
	cout<<"w(i)=";
	for (int i=1;i<=n;i++)
	{
		cout<<w[i]<<" ";
	}
	cout<<endl;
 
	cout<<"����ѡ����bestx[]=";
	for (int i=1;i<=n;i++) cout<<bestx[i]<<",";
	cout<<"\b "<<endl;
	cout<<"��һ�Ҵ�����������Ϊbestw="<<bestw<<endl;
	cout<<"�伯װ�����Ϊ��";
	for (int i=1;i<=n;i++) if(bestx[i]) cout<<"��"<<i<<"��"<<w[i]<<" ";
	cout<<endl;
 	cout<<"ʣ�༯װ��������Ϊ(r-bestw)="<<r-bestw; 
	if((r-bestw)>c2) cout<<">"<<c2<<",����c2�������ֵ��ԭ�����޽⣡"<<endl;
	else {
		cout << endl << "������c2�ļ�װ�����Ϊ��";
		for (int i=1;i<=n;i++) if(!bestx[i]) cout<<"��"<<i<<"��"<<w[i]<<" ";
	} 
}


int main()
{
	//int* w=new int[N+1]{0,22,35,24,19,4};
	int* w=new int[N+1]{0,22,35,24,15,4};
	//int* w=new int[N+1]{0,22,35,24,15,3};
	Loading<int> ld(w);
	ld.Backtrack(1);
	ld.Show();
	system("pause");
	return 0;
}


//�ο����� 
//https://blog.csdn.net/liufeng_king/article/details/8762073
//�˸������ȷʹ�� 
//https://blog.csdn.net/lfod1997/article/details/99617431?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162181777216780265416264%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=162181777216780265416264&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-99617431.pc_search_result_hbase_insert&utm_term=cout+%E9%80%80%E6%A0%BC&spm=1018.2226.3001.4187
