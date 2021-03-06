#include<iostream>
#include<string.h> //使memset()可用 
using namespace std;

#define N 5
#define C1 60
#define C2 40

template <class T> class Loading
{
	private:
		int n;	//集装箱数
		int* x;	//当前解
		int* bestx; //当前第一艘船的最优解
		T c1; //第一艘轮船的核定载重量 
		T c2; //第二艘轮船的核定载重量
		T* w; //集装箱重量数组
		//T total;	//所有集装箱重量之和
		T cw;	//当前第一艘船的载重量，过程变量，不作统计 
		T bestw; //当前第一艘船的最优载重量
		T r;	//每层节点处剩余集装箱总重量，过程变量，不作统计 

	public:
		Loading(T* w)	//构造函数
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
			//初始化x,bestx
			memset(x,-1,sizeof(*x)*(n+1));
			memset(bestx,-1,sizeof(*bestx)*(n+1));
			//初始化r
			for(int i=1;i<=n;i++) r+=w[i];
		}
		
		~Loading()	//析构函数
		{
			delete []x;
			delete []bestx; 
		}
		
		void Backtrack(int i); //找到最接近第一艘轮船载重c1的最佳装载方案, 
		//最优载重值bestw，最优解数组bestx。 
		int Left(int i);
		int Right(int i);
		void Show();//输出整个装载方案
};
	
template <class T> int Loading<T>::Left(int i){
	//搜索左子树
	r-=w[i];
	cw+=w[i];
	x[i]=1;
	return ++i;
}	

template <class T> int Loading<T>::Right(int i){//搜索右子树
		i--;
		while (i>0 && x[i]==0)
		{ 
			r+=w[i];
			i--;
		}
		if(i==0) return 0;
		cw-=w[i];
		x[i]=0;
		return ++i;
}	
		
template <class T> void Loading<T>::Backtrack(int i)
{
	while(true){
		while(i<=n && cw+w[i]<=c1){i=Left(i);} 	//x[i]=1时的可行解约束条件
		if(cw>bestw && i>n) //抵达叶节点 
			for (int j=1;j<i;j++)
			{
				bestx[j]=x[j]; //new 动态更新 bestx[] 
				bestw=cw;
			}
		else //未抵达叶节点，进入右子树前进入下一层 i++
		{          
			r-=w[i];
			x[i]=0;
			i++;
		}
		while(cw+r<=bestw){i=Right(i);} 	//x[i]=0时增加的约束函数，剪去不含最优解的分枝 //统一先返回上一层--i
		if(i==0) return;
	}
}

template <class T> void Loading<T>::Show()
{

	cout << endl;
	
	//formal
	cout<<"轮船的载重量分别为："<<endl;
	cout<<"c(1)="<<c1<<",c(2)="<<c2<<endl;
 
	cout<<"待装集装箱重量分别为："<<endl;
	cout<<"w(i)=";
	for (int i=1;i<=n;i++)
	{
		cout<<w[i]<<" ";
	}
	cout<<endl;
 
	cout<<"回溯选择结果bestx[]=";
	for (int i=1;i<=n;i++) cout<<bestx[i]<<",";
	cout<<"\b "<<endl;
	cout<<"第一艘船最优载重量为bestw="<<bestw<<endl;
	cout<<"其集装箱组成为：";
	for (int i=1;i<=n;i++) if(bestx[i]) cout<<"【"<<i<<"】"<<w[i]<<" ";
	cout<<endl;
 	cout<<"剩余集装箱总重量为(r-bestw)="<<r-bestw; 
	if((r-bestw)>c2) cout<<">"<<c2<<",超过c2承载最大值，原问题无解！"<<endl;
	else {
		cout << endl << "承载于c2的集装箱组成为：";
		for (int i=1;i<=n;i++) if(!bestx[i]) cout<<"【"<<i<<"】"<<w[i]<<" ";
	} 
}


int main()
{
	//int* w=new int[N+1]{0,22,35,24,19,4};
	//int* w=new int[N+1]{0,22,35,24,15,4};
	int* w=new int[N+1]{0,22,35,24,15,3};
	Loading<int> ld(w);
	ld.Backtrack(1);
	ld.Show();
	system("pause");
	return 0;
}


//参考资料 
//https://blog.csdn.net/liufeng_king/article/details/8762073
//退格符的正确使用 
//https://blog.csdn.net/lfod1997/article/details/99617431?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162181777216780265416264%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=162181777216780265416264&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-1-99617431.pc_search_result_hbase_insert&utm_term=cout+%E9%80%80%E6%A0%BC&spm=1018.2226.3001.4187
//迭代参考
//https://blog.csdn.net/liufeng_king/article/details/8762073?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522162083144216780269871709%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=162083144216780269871709&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-8762073.first_rank_v2_pc_rank_v29&utm_term=%E8%A3%85%E8%BD%BD%E9%97%AE%E9%A2%98%E5%9B%9E%E6%BA%AF%E6%B3%95 
