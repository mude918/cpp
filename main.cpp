#include "util.h"

int main(){
	Node* n1 = new Node("c");
	Node* n2 = new Node("a");
	//Node n2 = Node{"b",NULL,NULL};
	Node* n3 = new Node("b",n1,n2);
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
	
	//priority_queue<Node,vector<Node>,greater<Node> >q2;
	priority_queue<Node,vector<Node>,less<Node> >q2;
	q2.push(*n1);
	q2.push(*n2);
	q2.push(*n3);

	while(q2.size()>0){
		cout<<q2.top().val<<endl;
		q2.pop();
	}
	
	string s4 = "hello";
	MyString *s5 = new MyString(s4.c_str());	
	URL *s6 = new URL(s4.c_str());	
	cout<<s5->size()<<endl;
	cout<<s6->size()<<endl;
	return 0;
}
