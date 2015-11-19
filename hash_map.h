#ifndef HASH_MAP_H
#define HASH_MAP_H
#include "util.h"

const int TABLE_SIZE = 128;

template <class K,class V>
class HashNode{
	private:
		K key;
		V val;
	public:
		HashNode(K k,V v):key(k),val(v){}
		K getKey(){
			return key;
		}

		V getValue(){
			return val;
		}
};

template <class K,class V>
class HashMap{
	private:
		HashNode<K,V> **table;
		int size;
	public:
		HashMap(){
			//memset(table,0,sizeof(HashNode<K,V>*)*TABLE_SIZE);
			table = new HashNode<K,V>*[TABLE_SIZE];
			for(int i=0; i < TABLE_SIZE; i++){
				table[i] = NULL;
			}
			size = 0;
		}

		~HashMap(){
			for(int i=0; i < TABLE_SIZE; i++){
				if(table[i]!=NULL)
					delete table[i];
			}

			delete []table;
			size = 0;
		}
		V get(K key){
			int hash = key % TABLE_SIZE;
			while(table[hash]!=NULL&&table[hash]->getKey()!=key){
				hash = (hash + 1) % TABLE_SIZE;
			}

			if(table[hash] != NULL)
				return table[hash]->getValue();
		}

		void put(K key,V val){
			if(size >= TABLE_SIZE)
				return ;
			int hash = key % TABLE_SIZE;
			while(table[hash]!=NULL&&table[hash]->getKey()!=key){
				hash = (hash + 1) % TABLE_SIZE;
			}

			if(table[hash]!=NULL){
				delete table[hash];
				size -= 1;
			}
			table[hash] = new HashNode<K,V>(key, val);
			size += 1;
		}

		int getSize(){
			return size;
		}
};

#endif