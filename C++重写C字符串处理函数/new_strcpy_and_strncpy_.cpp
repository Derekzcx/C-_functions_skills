/*
	本程序用于重写，strcpy 和 strncpy 函数，使得这两个函数更安全 
	strcpy(char* dest, const char *str); 
		//将 str复制给dest，但是没有是否超出界限的检查，无限拷贝至溢出报错 
	
	strncpy(char* dest, const char *str, size_t len);
		 // 将 str 复制长度为 len 字符串给 dest，当dest长度远大于src时，由于strncpy会对多余的空间都填0，会造成性能损失。 
		 
	针对此等问题进行修改 
*/ 
#include<cstring>
// or #include<string.h>
#include<iostream>
using namespace std;
/*
	dest: 目标字符串，不需要初始化，在本函数中有初始化代码
	destlen: 目标字符串 dest 占用的内存大小 ，使用sizeof 
	str: 原字符串
	返回值：目标字符串的起始地址
	注意：超出dest容量的内存将被丢弃掉 
*/
char *strcpy_new(char* dest, const size_t destlen, const char* str){
	if(dest==0) return 0; //判断是不是为空指针
	memset(dest,0,destlen); // 初始化 dest; ,这里不能使用 sizeof(dest) ，在64位系统中，sizeof(dest)用于是8，就是一个指针的大小
	
	if(str == 0) return dest;
	if(strlen(str) > destlen-1) strncpy(dest, str, destlen-1); // -1 是取出字符串截止符\0的影响，因为sizeof 会把 \0 计算进去 ，而strlen不会 
	else strcpy(dest,str);
	 
	return dest;
}

/*
	dest : 目标字符串，不需要初始化，本函数中有初始化代码
	destlen : 目标字符串 dest 占用的内存大小， 使用 sizeof
	str: 原字符串
	n: 待复杂的字节数 
	返回值： 目标字符串的起始地址
	注意：超出dest 容量的内存将被丢弃
*/ 
char *strncpy_new(char* dest, const size_t destlen, const char* str, size_t n){
	if(dest== 0) return 0;
	memset(dest,0,destlen); // 初始化 dest; ,这里不能使用 sizeof(dest) 
	
	if(str==0) return dest; 
	if(n > destlen-1) strncpy(dest, str, destlen-1);
	else strncpy(dest,str,n);
	
	return dest;
}

// 测试 
int main(){
	const char* str = "jianjian is yyds";
	char str2[] = "jianjian is right";
	char dest[20];
	
	// strcpy_new 的测试 
	strcpy_new(dest, sizeof(dest), str);
	printf("%s \n", dest);
	
	// strncpy_new 的测试
	strncpy_new(dest, sizeof(dest), str2, 30); 
	printf("%s \n", dest);
	
	return 0;
}
 
 

