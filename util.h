#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<sstream>
#include<string>
#include<cstring>
#include<queue>
#include<cstdio>

using namespace std;

struct Node{
	string val;
	Node* left;
	Node* right;
	Node(string v,Node* l,Node* r):val(v),left(l),right(r){}
	Node(string v):val(v),left(NULL),right(NULL){}
};

class MyString{
	private:
		char* mdata;
	public:
		MyString():mdata(new char[1]){
			*mdata = '\0';			
		}
		MyString(const char* s){
			mdata = new char[strlen(s)+1];
			strcpy(mdata,s);
		}
		MyString(const MyString &rhs):mdata(new char[strlen(rhs.mdata)+1]){
			strcpy(mdata,rhs.mdata);
		}
		~MyString(){
			delete []mdata;
		}
		size_t size(){
			return strlen(mdata);
		}
		char operator[](int i){
			if(i>0&&i<strlen(mdata))
				return mdata[i];
		}
		MyString& operator=(const MyString &str);
		friend ostream& operator<<(ostream &os,const MyString &s);
};

class URL:public MyString{
	public:
		URL(const char *s):MyString(s){}
		//URL(const char *s){}
		~URL(){}
};

int calDepth(Node* r);
string printTree(Node* r);
bool operator<(const Node &n1,const Node &n2);
bool operator>(const Node &n1,const Node &n2);
#endif
