#include<string.h>
#include<iostream>
using namespace std;


int main(){
	char c[6];
	char *t = new char[6];
	
	strcpy(c, "hello");
//	t = "hi";
	
	cout << "c -> " << c << endl;
//	cout << "t -> " << t << endl;
	
	memset(c, 33, 2); 
	cout << "memset(c, '0', 6) -> " << c << endl;
	memset(t, '0', 6);
	cout << "memset(t, '0', 6) -> " << t << endl;	

//	c[0] = 'J';
//	cout << "c -> " << c << endl;

	int in[6];
	memset(in, 1, sizeof(*in)*6);
	for(int i = 0; i < 6; i++) cout << *(in+i) << " ";

	return 0;
} 
