/*
*	本程序用于演示可变参数函数的示例 
*	主要 用的了val_list va_start va_arg va_end 宏函数
*   va_list：复合类型 即va_list args;声明变量args，可以看作为一个参数指针
*	va_start(args, formt)：将args指向formt第一个参数
*	va_arg(args, 参数类型)：args指向下一个参数, 返回是以args开头的参数，类型就是入参类型 
*	va_end(args)：将args置为无效 
*/
//
#include <stdarg.h> 
#include <iostream>
 
void fun(int fmt,...){
    va_list arg;
    int n=1;
    va_start(arg,fmt);
    do{
        printf("第 %d 个参数 =%d\n",n++,fmt);
        fmt=va_arg(arg,int);
    }while (fmt!=0);
    va_end(arg);
}
int main()
{
    fun(20,40,60,80,0);
    return 0;
}

