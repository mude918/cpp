#include<iostream>
#include<sstream>
#include<string>

using namespace std;

struct Node{
    string val;
    Node* left;
    Node* right;
    Node(string v,Node* l,Node* r):val(v),left(l),right(r){}
};

int  main(){
    Node* n1= new Node("a",NULL,NULL);
    Node n2=Node{"b",NULL,NULL};
    cout<<n1->val<<","<<n2.val<<endl;
	
	stringstream s;
	int i=1234;
	string str;
	s<<i;
	s>>str;
	cout<<str<<endl;

    return 0;
}
