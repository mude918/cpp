#include "util.h"

void testShuffle();
void testStringStream();
void testCalTreeDepth();
void testPriorityQueue();
void testMyString();

void ref(int&& i){
	cout<<"RF:"<<i<<endl;
}

void ref(int& i){
	cout<<"LF:"<<i<<endl;
}

void pre(int&& i){
	ref(i);
}

void move(int& a){
	cout<<"move"<<endl;
}

int main(){
	//testStringStream();
	//testCalTreeDepth();
	//testPriorityQueue();
	//testMyString();
	//testShuffle();	

	int a=1;
	
	ref(1);
	pre(1);
	move(a);
	ref(std::move(a));
	
	cout<<a<<endl;
	return 0;
}


void testMyString(){
	string s4 = "hello";
	MyString *s5 = new MyString(s4.c_str());	
	MyString s7 = MyString(s4.c_str());	
	MyString s8=s7;
	//s8=s7;
	URL *s6 = new URL(s4.c_str());	
	cout<<(*s5)[2]<<endl;
	cout<<(*s6)[2]<<endl;
	cout<<s7<<endl;
	cout<<s8[2]<<endl;
	//cout<<s6[3]<<endl;
}

void testPriorityQueue(){
	priority_queue<int,vector<int>,greater<int> > q1;
	q1.push(3);
	q1.push(2);
	q1.push(6);
	q1.push(9);

	while(q1.size()>0){
		cout<<q1.top()<<endl;
		q1.pop();
	}
}

void testCalTreeDepth(){
	Node* n1 = new Node("c");
	Node* n2 = new Node("a");
	//Node n2 = Node{"b",NULL,NULL};
	Node* n3 = new Node("b",n1,n2);
	cout<<n1->val<<","<<n2->val<<endl;
	cout<<calDepth(n3)<<","<<calDepth(n1)<<endl;
	cout<<printTree(n3)<<","<<printTree(n1)<<endl;

	//priority_queue<Node,vector<Node>,greater<Node> >q2;
	priority_queue<Node,vector<Node>,less<Node> >q2;
	q2.push(*n1);
	q2.push(*n2);
	q2.push(*n3);

	while(q2.size()>0){
		cout<<q2.top().val<<endl;
		q2.pop();
	}
}

void testStringStream(){
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
}

void testShuffle(){
	int A[54];
	for(int i=0;i < 54;i++){
		A[i] = i;
	}
	
	int n,t;
	for(int i=53;i > 0;i--){
		srand((unsigned)time(NULL));
		n = rand()%(i+1);
		if(i!=n){
			t = A[i];
			A[i] = A[n];
			A[n] = t;
		}
		cout<<A[i]<<' ';
	}
	cout<<endl;
}
