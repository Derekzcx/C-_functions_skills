/*
*	�ù�ϣ����� ����ַ�� 
*	��ϣ�� ���� �ɸ��ݹؼ�ֱֵ�ӷ������ݵ����ݽṹ���ؼ�ֵʱͨ����ϣ����ӳ�䵽���Ӧλ�õ� 
* 	������õ� ��ϣ������ time33 �㷨 
* 	�汾��0.0.1
*/
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

/******** ������ϣ�� ********/
#define HASHSIZE 5

struct Node{
	char* key;
	char* value;
	Node* next;
	Node(char* k, char* v):key(k),value(v),next(NULL){}
};

/************ ��ϣ������� ******************/
class HashTable{
private:
	Node* node[HASHSIZE];
	size_t hash(const char* key);					// ��ϣ����ӳ�� 
	Node* lookup(const char* key);					// ��ϣ���ѯ���� �ڵ� 
	
public:
	HashTable();
	~HashTable();
	
	bool insert(const char* key,const char* value);	//  ��ϣ����� 
	char* get(const char* key);						// 	��ϣ���±��ѯ 
	void display();									// 	�������� 
};
/************** ��Ա����ʵ�� ****************************/ 
HashTable::HashTable(){
	memset(node,0,sizeof(node));//��ʼ������ 
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

// �����ϣ���� ���� time33 �㷨 
size_t HashTable::hash(const char* key){
	size_t hash = 0;
	while(*key){
		hash += (hash << 5) + (*key++);
	}
	return hash % HASHSIZE;
}

// ������ҷ�ʽ������key���ؽ��
Node* HashTable::lookup(const char* key){
	size_t index = hash(key);
	for(Node* np = node[index]; np != NULL; np=np->next){
		if(strcmp(key, np->key) == 0){
			return np;
		}
	}
	return NULL;
} 

// ������뷽ʽ: �����ǲ鿴��keyֵ�Ľ���Ƿ���ڣ�������������valueֵ�ͺã���������ڣ�������½�㡣
bool HashTable::insert(const char* key,const char* value){
	// ������ת���ɷǳ����� 
	char* key_tmp = const_cast<char*>(key); 
	char* value_tmp = const_cast<char*>(value);
	Node* np = lookup(key);
	if(!np){ // ������ 
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

// ��ӡ��ϣ��
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

/******************** ��ϣ����� **********************/ 
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
