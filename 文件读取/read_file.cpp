/*
	* ����������ʵ�ֶ��ļ����һ�еĶ�ȡ����ʵ��
	* �������϶��¶�ȡ���� ֱ�Ӷ�λ���һ�н��ж�ȡ 
	* ���ߣ�Derek_jian 

*/ 

#include<iostream>
#include<string>
#include<fstream>

// ���Ŷ����һ�� 
bool Read_from_head_context(const char *pathname, std::string &result){
	
	std::ifstream File(pathname);
	if(!File){
		printf("open file failed ! \n"); 
		return false;
	}
	
	std::string oneline;
	while(std::getline(File,oneline)){
		result = oneline;
	}
	return true;
} 

// ���Ŷ����һ�� 
bool Read_from_down_context(const char *pathname, std::string &result){
	char ch;// ƫ�Ƶ�λ 
	std::ifstream File(pathname, std::ios::in);// ����Ĭ�Ϸ�ʽ�� 
	if(!File){
		printf("open file failed ! \n"); 
		return false;
	}
	File.seekg(-sizeof(ch), File.end); // �ȶ�λ���ļ�ĩβ ����eofǰ 
	while(File.peek() != File.widen('\n') && File.peek() != File.widen('\r')){ // Ӧ��Windows �� linux �Ĳ�ͬ 
		if(File.tellg() <=1) { // ���ļ�ֻ��һ��ʱ 
			File.seekg(0, File.beg);
			getline(File,result);
			return true;
		}
		File.seekg(-sizeof(ch),File.cur); // ע��char�������ֽ� 
	}
	File.seekg(1,std::ios::cur); // ��ǰ�ƶ�һ���ֽڵ����һ�� 
	getline(File,result);
	File.close();
	return true;
}

int main(){
	
	std::string str = "";
	Read_from_down_context("test.txt",str);
	printf("%s\n", str.c_str());
	return 0;
}
// ֪ʶ�㲹�� 
/*
	* �ļ���������˵��
	*  ofstream & seekp (int offset, int mode);  // дָ�붨λ 
	* ifstream & seekg (int offset, int mode);   //  ��ָ�붨λ 
	-- offset ƫ������modeΪ ios::beg���ļ�ͷ��\ios::cur����ǰλ�ã�\ios::end���ļ�β����  
	-- ios::cur ģʽ�� offset ��Ϊ����������ǰ�������
	-- ios::beg offset ֻ������ios::end ֻ�ɸ� 
	
	* �ļ������Ա���� 
	* std::fstream::pos_type tellg();	// ���ش��ļ�ͷ��ʼ����ǰ��ָ����ļ����� ������Ϊ�ֽڸ��� 
	* std::fstream::pos_type tellp();  // ����дָ��� 
	// pos_type ������ int�����tellg() ��  tellp() ����ʧ���� std::fstream::pos_type(-1) 
	
	* �ļ������Ա����
	*  peek() ��ʾԤ��ȡ��һ���ַ�
	*  get(char) ��ȡ��ǰָ����ָ�ַ�
	*  eof() �жϵ�ǰָ���Ƿ�֪���ļ�β����bool���� 
	* good() �ж��ļ����Ƿ�ɹ�
	* bad()	 �ж��ļ����Ƿ�ʧ�� 
	
	* Linux����ϵͳ��LF����Ӧ \n
	* Windows����ϵͳ��CR LF����Ӧ \r \n
	* Mac����ϵͳ��CR����Ӧ \r
	
	* ��Ա���� char widen(char c) const; ֻ�����������ַ��Դ��뵱ǰ�������ֽ���һ�� 
*/ 
