#include<cstring>
#include<iostream>
using namespace std;


int main(){
	//推荐初始化，系统会自动在后面加'\0'，即 a[3]='\0',所以该数组的元素个数是 4 个
	char str4[]="abc";
 	// strlen 不会将 \0 计算到长度里去。 
 	// sizeof 会将 \0 计算进去 
 	printf("%d \n", strlen(str4)) ;
 	printf("%d \n", sizeof(str4)) ;
 	
 	return 0;
	
} 


