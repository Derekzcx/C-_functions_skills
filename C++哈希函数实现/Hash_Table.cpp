/*
*	该哈希表采用 链地址法 
*	哈希表 就是 可根据关键值直接访问数据的数据结构，关键值时通过哈希函数映射到表对应位置的 
* 	这里采用的 哈希函数是 time33 算法 
* 	版本：0.0.1
*/
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

/******** 构建哈希表 ********/
#define HASHSIZE 5

struct Node{
	char* key;
	char* value;
	Node* next;
	Node(char* k, char* v):key(k),value(v),next(NULL){}
};

/************ 哈希表管理类 ******************/
class HashTable{
private:
	Node* node[HASHSIZE];
	size_t hash(const char* key);					// 哈希函数映射 
	Node* lookup(const char* key);					// 哈希表查询返回 节点 
	
public:
	HashTable();
	~HashTable();
	
	bool insert(const char* key,const char* value);	//  哈希表插入 
	char* get(const char* key);						// 	哈希表下标查询 
	void display();									// 	遍历函数 
};
/************** 成员函数实现 ****************************/ 
HashTable::HashTable(){
	memset(node,0,sizeof(node));//初始化数组 
}

HashTable::~HashTable(){
	for(int i=0; i<HASHSIZE; i++){
		Node* ptr = node[i];
		while(ptr != NULL){
			Node* tmp = ptr->next;
			delete ptr;
			ptr = tmp; 
		}
	}
}

// 定义哈希函数 采用 time33 算法 
size_t HashTable::hash(const char* key){
	size_t hash = 0;
	while(*key){
		hash += (hash << 5) + (*key++);
	}
	return hash % HASHSIZE;
}

// 定义查找方式：根据key返回结果
Node* HashTable::lookup(const char* key){
	size_t index = hash(key);
	for(Node* np = node[index]; np != NULL; np=np->next){
		if(strcmp(key, np->key) == 0){
			return np;
		}
	}
	return NULL;
} 

// 定义插入方式: 首先是查看该key值的结点是否存在，如果存在则更改value值就好，如果不存在，则插入新结点。
bool HashTable::insert(const char* key,const char* value){
	// 常变量转换成非常变量 
	char* key_tmp = const_cast<char*>(key); 
	char* value_tmp = const_cast<char*>(value);
	Node* np = lookup(key);
	if(!np){ // 不存在 
		size_t index = hash(key);
		np = new Node(key_tmp, value_tmp);
		if(np == nullptr) return false;
		np->next = node[index];
		node[index] = np;
	}else{
		np->value = value_tmp;
	}
	return true;
}

// 打印哈希表
void HashTable::display(){
	for(int i=0; i < HASHSIZE; i++){
		if(node[i] == NULL) printf("[]\n");
		else{
			printf("[");
			Node* ptr = node[i];
			while(ptr!=NULL){
				printf("[%s,%s]",ptr->key,ptr->value);
				ptr = ptr->next;
			}
			printf("]\n");
		}
	}
} 

char* HashTable::get(const char* key){
	Node* np = lookup(key);
	if(np != NULL) return np->value;
	return NULL;
}

/******************** 哈希表测试 **********************/ 
void testHash(HashTable *_hash_){
    const char* key[]={"a","b","c","d","e","f","x"};
    const char* value[]={"value1","value2","value3","value4","value5","value6","value7"};
    for (int i = 0; i < 7; ++i){
        _hash_->insert(key[i],value[i]);
    }
}

int main(){
	HashTable ha;
	testHash(&ha);
	ha.display();
	printf("%s",ha.get("a"));
	return 0;
	
}
