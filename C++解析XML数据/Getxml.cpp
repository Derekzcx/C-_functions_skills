/*
*	本程序 用于实现 对xml数据的解析，属于通用功能模块 
*	作者：Derek_jian 
*/ 

#include<iostream>
#include<cstring>
#include<stdarg.h>

using namespace std;

// 删除字符串左边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteLChar(char *str,const char chr)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;
  char strTemp[strlen(str)+1];
  int iTemp=0;
  
  memset(strTemp,0,sizeof(strTemp));
  strcpy(strTemp,str);
  while ( strTemp[iTemp] == chr )  iTemp++;
  memset(str,0,strlen(str)+1);
  strcpy(str,strTemp+iTemp);
  
  return;
}

// 删除字符串右边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteRChar(char *str,const char chr)
{
  if (str == 0) return;
  if (strlen(str) == 0) return;
  int istrlen = strlen(str);

  while (istrlen>0){
    if (str[istrlen-1] != chr) break;
    str[istrlen-1]=0;
    istrlen--;
  }
}

// 删除字符串左右两边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符。
void DeleteLRChar(char *str,const char chr)
{
  DeleteLChar(str,chr);
  DeleteRChar(str,chr);
}


// 安全的snprintf函数。
/*
* int snprintf ( char * str, size_t size, const char * format, ... );
* 用于格式化输出字符串，并将结果写入到指定的缓冲区, snprintf有输出长度限制，sprintf没有 ，作用类似于 printf，只是输出字符串到指定区 
*/
// 将可变参数(...)按照fmt描述的格式输出到dest字符串中。
// dest：输出字符串，不需要初始化，在SNPRINTF函数中会对它进行初始化。
// destlen：输出字符串dest占用内存的大小，如果格式化后的字符串内容的长度大于destlen-1，后面的内容将丢弃。
// n：把格式化后的字符串截取n-1存放到dest中，如果n>destlen，则取destlen-1。
// fmt：格式控制描述。
// ...：填充到格式控制描述fmt中的参数。
// 返回值：格式化后的内容的长度，程序员一般不关心返回值。
int SNPRINTF(char *dest,const size_t destlen,size_t n,const char *fmt,...)
{
  if (dest==0) return -1;    // 判断空指针。
  memset(dest,0,destlen);
  
  int len=n;
  if (n>destlen) len=destlen;

  va_list arg;
  va_start(arg,fmt);
  int ret=vsnprintf(dest,len,fmt,arg );
  va_end(arg);

  return ret;
}
// 读取为字符串形式
/*
* xmlbuffer：从xml文件中读取的数据
* fieldname: 需要提取的标签名字
* value:	 提出后的标签内容，使用数组存储 value[len+1]接收 
* len：		 字符长度 
*/ 
bool Get_XML_Data(const char* xmlbuffer, const char *fieldname, char* value, const int len){
	if(value == 0) return false;// 避免value为空指针，value为数组
	if(len>0) memset(value, 0, len+1); // 调用者必须保证 value 的空间足够，否则会导致内存溢出
	char* start=0;
	char* end = 0;
	char m_sfieldname[51];
	char m_efieldname[51];
	int m_namelen = strlen(fieldname);
	
	SNPRINTF(m_sfieldname, sizeof(m_sfieldname), 50, "<%s>", fieldname); // 标签头 
	SNPRINTF(m_efieldname, sizeof(m_efieldname), 50, "</%s>", fieldname); // 标签尾
	
	start = (char*)strstr(xmlbuffer, m_sfieldname); // 采用 C++ 的find，得到的是子串第一次出现的位置 
	if(start != 0){
		end = (char*)strstr(xmlbuffer, m_efieldname);
	} 
	if((start == 0) || (end == 0)){
		return false;
	}
	int m_value_len = end - start - m_namelen - 2;
	if(m_value_len <= len || len == 0){
		strncpy(value,start+m_namelen+2,m_value_len);
		value[m_value_len] = 0;// 可加可不加 ，转C的话要加给\0留位置 
	}else{
		strncpy(value,start+m_namelen+2,len);
		value[len] = 0; // 
	}
	//最后再加一个出去两边空格的处理
	DeleteLRChar(value,' ');	
} 

/************************** 测试 ***********************************/ 
int main(){
	const char* xmlbuffer = "<arg1>0x0 </arg1><arg2>1x1</arg2>";
	char result[101];
	Get_XML_Data(xmlbuffer, "arg1", result, 100);
	printf("%s %d\n", result, strlen(result));
	const char* dex = result;
	printf("%s", dex);
	return 0;
}
