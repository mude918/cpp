#include "util.h"

bool operator<(const Node &n1,const Node &n2){
	return n1.val < n2.val;
}

bool operator>(const Node &n1,const Node &n2){
	return n1.val > n2.val;
}

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
