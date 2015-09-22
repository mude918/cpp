#ifndef UTIL_H
#define UTIL_H
#include<iostream>
#include<sstream>
#include<string>
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

int calDepth(Node* r);
string printTree(Node* r);
bool operator<(const Node &n1,const Node &n2);
bool operator>(const Node &n1,const Node &n2);
#endif
