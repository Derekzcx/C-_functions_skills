/*
	* 本程序用于实现对文件最后一行的读取方法实现
	* 包括自上而下读取，和 直接定位最后一行进行读取 
	* 作者：Derek_jian 

*/ 

#include<iostream>
#include<string>
#include<fstream>

// 正着读最后一行 
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

// 倒着读最后一行 
bool Read_from_down_context(const char *pathname, std::string &result){
	char ch;// 偏移单位 
	std::ifstream File(pathname, std::ios::in);// 采用默认方式打开 
	if(!File){
		printf("open file failed ! \n"); 
		return false;
	}
	File.seekg(-sizeof(ch), File.end); // 先定位到文件末尾 但在eof前 
	while(File.peek() != File.widen('\n') && File.peek() != File.widen('\r')){ // 应对Windows 和 linux 的不同 
		if(File.tellg() <=1) { // 当文件只有一行时 
			File.seekg(0, File.beg);
			getline(File,result);
			return true;
		}
		File.seekg(-sizeof(ch),File.cur); // 注意char是两个字节 
	}
	File.seekg(1,std::ios::cur); // 向前移动一个字节到最后一行 
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
// 知识点补充 
/*
	* 文件操作函数说明
	*  ofstream & seekp (int offset, int mode);  // 写指针定位 
	* ifstream & seekg (int offset, int mode);   //  读指针定位 
	-- offset 偏移量，mode为 ios::beg（文件头）\ios::cur（当前位置）\ios::end（文件尾部）  
	-- ios::cur 模式下 offset 可为正负，负向前，正向后
	-- ios::beg offset 只可正，ios::end 只可负 
	
	* 文件流类成员函数 
	* std::fstream::pos_type tellg();	// 返回从文件头开始到当前读指针的文件长度 ，返回为字节个数 
	* std::fstream::pos_type tellp();  // 返回写指针的 
	// pos_type 类似于 int，如果tellg() 或  tellp() 返回失败是 std::fstream::pos_type(-1) 
	
	* 文件流类成员函数
	*  peek() 表示预读取下一个字符
	*  get(char) 读取当前指针所指字符
	*  eof() 判断当前指针是否知道文件尾部，bool类型 
	* good() 判断文件打开是否成功
	* bad()	 判断文件打开是否失败 
	
	* Linux操作系统：LF，对应 \n
	* Windows操作系统：CR LF，对应 \r \n
	* Mac操作系统：CR，对应 \r
	
	* 成员函数 char widen(char c) const; 只是用于扩宽字符以此与当前操作的字节流一致 
*/ 
