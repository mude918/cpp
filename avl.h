#ifndef AVL_H
#define AVL_H
#include "util.h"

#define 	EQ(x,y)	((x)==(y))
#define 	LT(x,y)	((x)<(y))	 
const int LH = 1;
const int EH = 0;
const int RH = -1;

struct AvlNode{
	int val;
	int bf;
	AvlNode *left;
	AvlNode *right;
	AvlNode(int v):val(v),bf(0),left(NULL),right(NULL){}
	AvlNode(int v,int b):val(v),bf(b),left(NULL),right(NULL){}
	AvlNode(int v,int b,AvlNode* l,AvlNode* r):val(v),bf(b),left(l),right(r){}
}; 

int insertKeyToAvl(AvlNode* &root, int key, bool &taller);
int delKeyFromAvl(AvlNode* &root, int key, bool &taller);
void leftBalance(AvlNode* &root);
void rightBalance(AvlNode* &root);
void RRote(AvlNode* &root);
void LRote(AvlNode* &root);
string printAvl(AvlNode* &root);

#endif
