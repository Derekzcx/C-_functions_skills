/*
	������������д��strcpy �� strncpy ������ʹ����������������ȫ 
	strcpy(char* dest, const char *str); 
		//�� str���Ƹ�dest������û���Ƿ񳬳����޵ļ�飬���޿������������ 
	
	strncpy(char* dest, const char *str, size_t len);
		 // �� str ���Ƴ���Ϊ len �ַ����� dest����dest����Զ����srcʱ������strncpy��Զ���Ŀռ䶼��0�������������ʧ�� 
		 
	��Դ˵���������޸� 
*/ 
#include<cstring>
// or #include<string.h>
#include<iostream>
using namespace std;
/*
	dest: Ŀ���ַ���������Ҫ��ʼ�����ڱ��������г�ʼ������
	destlen: Ŀ���ַ��� dest ռ�õ��ڴ��С ��ʹ��sizeof 
	str: ԭ�ַ���
	����ֵ��Ŀ���ַ�������ʼ��ַ
	ע�⣺����dest�������ڴ潫�������� 
*/
char *strcpy_new(char* dest, const size_t destlen, const char* str){
	if(dest==0) return 0; //�ж��ǲ���Ϊ��ָ��
	memset(dest,0,destlen); // ��ʼ�� dest; ,���ﲻ��ʹ�� sizeof(dest) ����64λϵͳ�У�sizeof(dest)������8������һ��ָ��Ĵ�С
	
	if(str == 0) return dest;
	if(strlen(str) > destlen-1) strncpy(dest, str, destlen-1); // -1 ��ȡ���ַ�����ֹ��\0��Ӱ�죬��Ϊsizeof ��� \0 �����ȥ ����strlen���� 
	else strcpy(dest,str);
	 
	return dest;
}

/*
	dest : Ŀ���ַ���������Ҫ��ʼ�������������г�ʼ������
	destlen : Ŀ���ַ��� dest ռ�õ��ڴ��С�� ʹ�� sizeof
	str: ԭ�ַ���
	n: �����ӵ��ֽ��� 
	����ֵ�� Ŀ���ַ�������ʼ��ַ
	ע�⣺����dest �������ڴ潫������
*/ 
char *strncpy_new(char* dest, const size_t destlen, const char* str, size_t n){
	if(dest== 0) return 0;
	memset(dest,0,destlen); // ��ʼ�� dest; ,���ﲻ��ʹ�� sizeof(dest) 
	
	if(str==0) return dest; 
	if(n > destlen-1) strncpy(dest, str, destlen-1);
	else strncpy(dest,str,n);
	
	return dest;
}

// ���� 
int main(){
	const char* str = "jianjian is yyds";
	char str2[] = "jianjian is right";
	char dest[20];
	
	// strcpy_new �Ĳ��� 
	strcpy_new(dest, sizeof(dest), str);
	printf("%s \n", dest);
	
	// strncpy_new �Ĳ���
	strncpy_new(dest, sizeof(dest), str2, 30); 
	printf("%s \n", dest);
	
	return 0;
}
 
 

