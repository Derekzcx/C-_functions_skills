#include<cstring>
#include<iostream>
using namespace std;


int main(){
	//�Ƽ���ʼ����ϵͳ���Զ��ں����'\0'���� a[3]='\0',���Ը������Ԫ�ظ����� 4 ��
	char str4[]="abc";
 	// strlen ���Ὣ \0 ���㵽������ȥ�� 
 	// sizeof �Ὣ \0 �����ȥ 
 	printf("%d \n", strlen(str4)) ;
 	printf("%d \n", sizeof(str4)) ;
 	
 	return 0;
	
} 


