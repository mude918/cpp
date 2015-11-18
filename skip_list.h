#ifndef SKIP_LIST_H
#define SKIP_LIST_H
#include "util.h"

const float P = 0.5;
const int MAX_LEVEL = 6;

template <class T>
struct SkipNode{
	T val;
	SkipNode<T> **fwd;

	SkipNode(int level,const T &val){
		fwd = new SkipNode<T>*[level+1];
		memset(fwd,0,sizeof(SkipNode<T>*)*(level+1));
		this->val = val;
	}
	~SkipNode(){
		delete []fwd;
	}
};

template <class T>
struct SkipList{
	SkipNode<T> *head;
	int level;

	SkipList(){
		head = new SkipNode<T>(MAX_LEVEL,T());
		level = 0;
	}
	~SkipList(){
		delete head;
	}

	void print() const;
	bool contains(const T &) const;
	void insert(const T &);
	void del(const T &);
};

float frand(){
	return float(rand())/RAND_MAX;
}

int randomLevel(){
	static bool first = true;

	if(first){
		srand((unsigned)time(NULL));
		first = false;
	}

	int lvl = (int)(log(frand())/log(1.-P));

	return lvl < MAX_LEVEL?lvl:MAX_LEVEL;
}

template <class T>
void SkipList<T>::print() const {
	const SkipNode<T> *x = head->fwd[0];
	cout<<"{";
	while(x!=NULL){
		cout<<x->val;
		x = x->fwd[0];
		if(x!=NULL)
			cout<<", ";
	}
	cout<<"}\n";
}

template <class T>
bool SkipList<T>::contains(const T &key) const {
	const SkipNode<T> *x = head;
	for(int i = level; i >= 0; i--){
		while(x->fwd[i]!=NULL&&x->fwd[i]->val < key){
			x = x->fwd[i];
		}
	}
	x = x->fwd[0];

	return x != NULL && x->val == key; 
}

template <class T>
void SkipList<T>::insert(const T &key){
	SkipNode<T> *x = head;
	SkipNode<T> *update[MAX_LEVEL+1];
	memset(update,0,sizeof(SkipNode<T>*)*(MAX_LEVEL+1));

	for (int i = level; i >= 0; i--)
	{
		while(x->fwd[i]!=NULL && x->fwd[i]->val < key){
			x = x->fwd[i];
		}

		update[i] = x;
	}

	x = x->fwd[0];

	if(x==NULL || x->val != key){
		int lvl = randomLevel();
		if(lvl > level){
			for(int i=level+1;i<=lvl;i++){
				update[i] = head;
			}
			level = lvl;
		}

		x = new SkipNode<T>(lvl,key);

		for(int i=0;i<=lvl;i++){
			x->fwd[i] = update[i]->fwd[i];
			update[i]->fwd[i] = x;
		}

	}
}

template <class T>
void SkipList<T>::del(const T &key){
	SkipNode<T> *x = head;
	SkipNode<T> *update[MAX_LEVEL+1];
	memset(update,0,sizeof(SkipNode<T>*)*(MAX_LEVEL+1));

	for(int i=level;i>=0;i--){
		while(x->fwd[i]!=NULL&&x->fwd[i]->val<key){
			x = x->fwd[i];
		}
		update[i] = x;
	}

	x = x->fwd[0];

	if(x!=NULL&&x->val==key){
		for(int i=0;i<=level;i++){
			if(update[i]->fwd[i]!=x)
				break;
			update[i]->fwd[i] = x->fwd[i]; 
		}

		delete x;

		while(level>0 && head->fwd[level]==NULL){
			level--;
		}
	}
}

#endif