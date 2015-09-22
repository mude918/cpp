#include "util.h"

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
	
	char s2[20];
	sprintf(s2,"i:%d",i);
	string s3(s2);
	cout<<s3<<" "<<s3.size()<<endl;	
	
	priority_queue<int,vector<int>,greater<int> > q1;
	q1.push(3);
	q1.push(2);
	q1.push(6);
	q1.push(9);

	while(q1.size()>0){
		cout<<q1.top()<<endl;
		q1.pop();
	}

	return 0;
}
