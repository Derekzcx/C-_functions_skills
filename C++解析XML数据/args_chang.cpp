/*
*	������������ʾ�ɱ����������ʾ�� 
*	��Ҫ �õ���val_list va_start va_arg va_end �꺯��
*   va_list���������� ��va_list args;��������args�����Կ���Ϊһ������ָ��
*	va_start(args, formt)����argsָ��formt��һ������
*	va_arg(args, ��������)��argsָ����һ������, ��������args��ͷ�Ĳ��������;���������� 
*	va_end(args)����args��Ϊ��Ч 
*/
//
#include <stdarg.h> 
#include <iostream>
 
void fun(int fmt,...){
    va_list arg;
    int n=1;
    va_start(arg,fmt);
    do{
        printf("�� %d ������ =%d\n",n++,fmt);
        fmt=va_arg(arg,int);
    }while (fmt!=0);
    va_end(arg);
}
int main()
{
    fun(20,40,60,80,0);
    return 0;
}

