#include<stdio.h>
int w=1;
int check(int m);
void put(void);
int check3(void);
int check2(void);
void firstdiagonal();
void seconddiagonal();
void updown();
void leftright();
void Queen(int r);
void PRINTF(void);
int k=0,a[100]={0},n,b[100][100]={0};//数组b用来存放满足条件的棋盘

#define n 8
void Queen(int r){
	int i;
	for(i=1;i<=n;i++){
		a[n-r+1]=i;
		if(check(n-r+1)){
			if(r>1)
			Queen(r-1);
			else{ 
			if(check2()==0)
			put();} 
		}
	}
}
int check(int r){//检查皇后位置是否合法
	int i;
	for(i=1;i<r;i++){
		if(a[i]==a[r])return 0;
		if(a[i]-i==a[r]-r)return 0;
		if(a[i]+i==a[r]+r)return 0;
	}
	return 1;
}
void leftright(){//左右对称 
	int i,c[100];
	for(i=1;i<=n;i++){
		c[n-i+1]=a[i]; 
	}
	for(i=1;i<=n;i++){
		a[i]=c[i];
	}
} 
void updown(){//上下对称 
	int i,c[100];
	for(i=1;i<=n;i++){
		c[i]=n+1-a[i]; 
	}
	for(i=1;i<=n;i++){
		a[i]=c[i];
	}
} 
void seconddiagonal(){//副对角线对称 
	int i,j,c[100];
	for(i=1;i<=n;i++){
		j=a[i];
		c[j]=i;
	}
	for(i=1;i<=n;i++){
		a[i]=c[i];
	}
} 
void firstdiagonal(){//主对角线对称； 
	int i,j,c[100];
	for(i=1;i<=n;i++){
		j=a[i];
		c[n+1-j]=n+1-i;
	}
	for(i=1;i<=n;i++){
		a[i]=c[i];
	}
} 
int check2(void){//检查是否和之前的摆法有本质区别
	int i;
	leftright();
	if(check3()){
		leftright();//特别注意！由于a数组为全局变量，变换完后要变换回去。
		return 1;
	}
	else{
		leftright();
	}
	updown();
	if(check3()){
		updown();
	return 1;
	}
	else{
		updown();
	}
	seconddiagonal();
	if(check3()){
		seconddiagonal();
		return 1;
	}
	else{
		seconddiagonal();
	}
	firstdiagonal();
	if(check3()){
		firstdiagonal();
		return 1;
		}
	else{
		firstdiagonal();
	}
	firstdiagonal();//顺时针旋转 90° 
	updown();
	if(check3()){
		updown();
		firstdiagonal();
		return 1;
	}
	else{
		updown();
		firstdiagonal();
	} 
	seconddiagonal();//逆时针旋转90° 
	leftright();
	if(check3()){
		leftright();
		seconddiagonal(); 
		return 1;
	}
	else{
		leftright();
		seconddiagonal();
	}
	updown();//顺时针旋转180° 
	leftright();
	if(check3()){
		leftright();
		updown();
		return 1;
	}
	else{
		leftright();
		updown();
	}
	seconddiagonal();
	updown(); 
	if(check3()){
		updown(); 	
		seconddiagonal();
		return 1;
	}
	else{
		updown(); 	
		seconddiagonal();
	}
	return 0;//无重复	
}
int check3(void){//一个用来检查变化后的a是否与b中元素相同的函数
	int i,j,flag=0;
	for(i=1;i<=w;i++){
		for(j=1;j<=n;j++){
		if(a[j]==b[i][j])
		flag++;
		}
		if(flag==n)
		return 1;//有重复 
		else
		flag=0;
	}

	return 0;
}
void put(void){//将满足条件的棋盘存入b中
	int i;
	for(i=1;i<=n;i++)
	b[w][i]=a[i];
	w++;
} 
void PRINTF(void){//打印
	int i,j;
	for(i=1;i<w;i++){
		printf("No%d:",i);
		for(j=1;j<=n;j++){
		printf("%d ",b[i][j]);
		}
		if(i!=w-1)printf("\n");
	}
}
int main(void){
	Queen(n);
	PRINTF();
	return 0;
}

//No1: 1 5 8 6 3 7 2 4
//No2: 1 6 8 3 7 4 2 5
//No3: 2 4 6 8 3 1 7 5
//No4: 2 5 7 1 3 8 6 4
//No5: 2 5 7 4 1 8 6 3
//No6: 2 6 1 7 4 8 3 5
//No7: 2 6 8 3 1 4 7 5
//No8: 2 7 3 6 8 5 1 4
//No9: 2 7 5 8 1 4 6 3
//No10:3 5 2 8 1 7 4 6
//No11:3 5 8 4 1 7 2 6
//No12:3 6 2 5 8 1 7 4
//————————————————
//版权声明：本文为CSDN博主「Curly hair male」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/qq_51741975/article/details/111306700
