/*
*	������ ����ʵ�� ��xml���ݵĽ���������ͨ�ù���ģ�� 
*	���ߣ�Derek_jian 
*/ 

#include<iostream>
#include<cstring>
#include<stdarg.h>

using namespace std;

// ɾ���ַ������ָ�����ַ���
// str����������ַ�����
// chr����Ҫɾ�����ַ���
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

// ɾ���ַ����ұ�ָ�����ַ���
// str����������ַ�����
// chr����Ҫɾ�����ַ���
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

// ɾ���ַ�����������ָ�����ַ���
// str����������ַ�����
// chr����Ҫɾ�����ַ���
void DeleteLRChar(char *str,const char chr)
{
  DeleteLChar(str,chr);
  DeleteRChar(str,chr);
}


// ��ȫ��snprintf������
/*
* int snprintf ( char * str, size_t size, const char * format, ... );
* ���ڸ�ʽ������ַ������������д�뵽ָ���Ļ�����, snprintf������������ƣ�sprintfû�� ������������ printf��ֻ������ַ�����ָ���� 
*/
// ���ɱ����(...)����fmt�����ĸ�ʽ�����dest�ַ����С�
// dest������ַ���������Ҫ��ʼ������SNPRINTF�����л�������г�ʼ����
// destlen������ַ���destռ���ڴ�Ĵ�С�������ʽ������ַ������ݵĳ��ȴ���destlen-1����������ݽ�������
// n���Ѹ�ʽ������ַ�����ȡn-1��ŵ�dest�У����n>destlen����ȡdestlen-1��
// fmt����ʽ����������
// ...����䵽��ʽ��������fmt�еĲ�����
// ����ֵ����ʽ��������ݵĳ��ȣ�����Աһ�㲻���ķ���ֵ��
int SNPRINTF(char *dest,const size_t destlen,size_t n,const char *fmt,...)
{
  if (dest==0) return -1;    // �жϿ�ָ�롣
  memset(dest,0,destlen);
  
  int len=n;
  if (n>destlen) len=destlen;

  va_list arg;
  va_start(arg,fmt);
  int ret=vsnprintf(dest,len,fmt,arg );
  va_end(arg);

  return ret;
}
// ��ȡΪ�ַ�����ʽ
/*
* xmlbuffer����xml�ļ��ж�ȡ������
* fieldname: ��Ҫ��ȡ�ı�ǩ����
* value:	 �����ı�ǩ���ݣ�ʹ������洢 value[len+1]���� 
* len��		 �ַ����� 
*/ 
bool Get_XML_Data(const char* xmlbuffer, const char *fieldname, char* value, const int len){
	if(value == 0) return false;// ����valueΪ��ָ�룬valueΪ����
	if(len>0) memset(value, 0, len+1); // �����߱��뱣֤ value �Ŀռ��㹻������ᵼ���ڴ����
	char* start=0;
	char* end = 0;
	char m_sfieldname[51];
	char m_efieldname[51];
	int m_namelen = strlen(fieldname);
	
	SNPRINTF(m_sfieldname, sizeof(m_sfieldname), 50, "<%s>", fieldname); // ��ǩͷ 
	SNPRINTF(m_efieldname, sizeof(m_efieldname), 50, "</%s>", fieldname); // ��ǩβ
	
	start = (char*)strstr(xmlbuffer, m_sfieldname); // ���� C++ ��find���õ������Ӵ���һ�γ��ֵ�λ�� 
	if(start != 0){
		end = (char*)strstr(xmlbuffer, m_efieldname);
	} 
	if((start == 0) || (end == 0)){
		return false;
	}
	int m_value_len = end - start - m_namelen - 2;
	if(m_value_len <= len || len == 0){
		strncpy(value,start+m_namelen+2,m_value_len);
		value[m_value_len] = 0;// �ɼӿɲ��� ��תC�Ļ�Ҫ�Ӹ�\0��λ�� 
	}else{
		strncpy(value,start+m_namelen+2,len);
		value[len] = 0; // 
	}
	//����ټ�һ����ȥ���߿ո�Ĵ���
	DeleteLRChar(value,' ');	
} 

/************************** ���� ***********************************/ 
int main(){
	const char* xmlbuffer = "<arg1>0x0 </arg1><arg2>1x1</arg2>";
	char result[101];
	Get_XML_Data(xmlbuffer, "arg1", result, 100);
	printf("%s %d\n", result, strlen(result));
	const char* dex = result;
	printf("%s", dex);
	return 0;
}
