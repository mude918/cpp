#include<iostream>
#include<sstream>
#include<string>
#include<queue>

using namespace std;

struct Node{
	string val;
	Node* left;
	Node* right;
	Node(string v,Node* l,Node* r):val(v),left(l),right(r){}
	Node(string v):val(v),left(NULL),right(NULL){}
};

int calDepth(Node* r){
	if(r==NULL)
		return 0;
	queue<Node*> q;
	q.push(r);
	q.push(NULL);
	int h=0;
	Node* t;
	while(q.size()>0){
		t = q.front();
		q.pop();
		if(t==NULL){
			h++;
			if(q.size()>0)
				q.push(NULL);
		} else {
			if(t->left!=NULL)
				q.push(t->left);
			if(t->right!=NULL)
				q.push(t->right);
		}
	}
	return h;
}

//like:a(b,c(d,e))
string printTree(Node* r){
	if(r==NULL)
		return "";
	else if(r->left==NULL&&r->right==NULL)
		return r->val;
	else{
		string lv = printTree(r->left);
		string rv = printTree(r->right);
		return r->val+"("+lv+","+rv+")";
	}
}

int main(){
	Node* n1 = new Node("a");
	Node* n2 = new Node("b");
	//Node n2 = Node{"b",NULL,NULL};
	Node* n3 = new Node("c",n1,n2);
	cout<<n1->val<<","<<n2->val<<endl;
	cout<<calDepth(n3)<<","<<calDepth(n1)<<endl;
	cout<<printTree(n3)<<","<<printTree(n1)<<endl;
	stringstream s;
	int i=1234;
	string str;
	s<<i;
	s>>str;
	cout<<str<<endl;

	return 0;
}
