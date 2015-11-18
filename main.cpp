#include "util.h"
#include "avl.h"
#include "rb_tree.h"
#include "skip_list.h"

void testShuffle();
void testStringStream();
void testCalTreeDepth();
void testPriorityQueue();
void testMyString();
void testAvlTree();
void testRBTree();
void testSkipList();

void ref(int& i){
	cout<<"((LF:)())"<<i<<endl;
}

void ref(int&& i){
	ref(i);
}

template <class T> struct A{
	T t;
	void printType(){
		cout<<typeid(t).name()<<endl;
	}
};

int main(){
	//testStringStream();
	//testCalTreeDepth();
	//testPriorityQueue();
	//testMyString();
	//testShuffle();
	//testRBTree();
	//testAvlTree();
	testSkipList();

	A<int> a1;
	A<char> a2;
	A<string> a3;
	a1.printType();
	a2.printType();
	a3.printType();

	int a=1;
	
	ref(a);
	ref(1);
	ref(std::move(a));
	cout<<a<<endl;


	return 0;
}

void testSkipList(){
	/*
	for(int i=0;i<40;i++){
		int rd = rand();
		float frd = float(rd)/RAND_MAX;
		int lvl = (int)(log(frd)/log(1.-P));
		cout<<rd<<", "<<frd<<", "<<lvl<<endl;
	}
	*/
	SkipList<int> sl;
	sl.print();
	sl.insert(6);
	sl.print();
	sl.insert(4);
	sl.insert(1);
	sl.insert(7);
	sl.print();
	if(sl.contains(6))
		cout<<"has 6,haha!\n";
	sl.del(6);
	if(!sl.contains(6))
		cout<<"haha,6 has gone\n";
	sl.del(4);
	sl.print();
}

void testAvlTree(){
	AvlNode *r = new AvlNode(0);
	bool taller = false;
	for(int i=1;i<10;i++){
		insertKeyToAvl(r, i, taller);		
		cout<<printAvl(r)<<endl;
	}
	for(int i=1;i<10;i++){
		delKeyFromAvl(r, i, taller);		
		cout<<printAvl(r)<<endl;
	}
}

void testRBTree(){
	RBTree<int> *root = new RBTree<int>(); 
	for(int i= 0;i<10;i++){
		root->insert(i);
		cout<<root->print()<<endl;
	}
	for (int i = 1; i < 10; ++i)
	{
		root->del(i);
		cout<<root->print()<<endl;
	}
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
	cout<<s6[3]<<endl;
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
