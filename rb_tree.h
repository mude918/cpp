#ifndef RB_TREE_H
#define RB_TREE_H
#include "util.h"

enum RBTColor
{
	RED,
	BLACK
};

template <class T> 
struct RBNode{
	T val;
	RBTColor color;
	RBNode *left,*right,*parent;
	RBNode(T v):val(v),color(RED),left(NULL),right(NULL),parent(NULL){}
	RBNode(T v,RBTColor c):val(v),color(c),left(NULL),right(NULL),parent(NULL){}
	RBNode(T v,RBTColor c,RBNode<T>* l,RBNode<T>* r,RBNode<T>* p):val(v),color(c),left(l),right(r),parent(p){}
};

template <class T> 
class RBTree{
	private:
		RBNode<T> *mRoot;

	public:
		RBTree();
		~RBTree();
		RBNode<T>* search(T key) const;
		void insert(T key);
		void del(T key);
		string print() const;
		void destroy();
	private:
		RBNode<T>* search(RBNode<T>* &root,T key) const;
		string print(RBNode<T>* root)const;
		void insert(RBNode<T>* &root,RBNode<T>* &node);
		void del(RBNode<T>* &root,RBNode<T>* &node);
		void insertFixUp(RBNode<T>* &root,RBNode<T>* &node);
		void delFixUp(RBNode<T>* &root,RBNode<T>* &node,RBNode<T>* &parent);
		void destroy(RBNode<T>* &root);
		void LRote(RBNode<T>* &root,RBNode<T>* &x);
		void RRote(RBNode<T>* &root,RBNode<T>* &y);
};

#define rb_parent(r) 	((r)->parent)
#define rb_color(r) 	((r)->color)
#define rb_is_red(r) 	((r)->color == RED)
#define rb_is_black(r) 	((r)->color == BLACK)
#define rb_set_red(r) 	do {((r)->color = RED);} while(0)
#define rb_set_black(r) do {((r)->color = BLACK);} while(0)
#define rb_set_parent(r,p) do {(r)->parent = p;} while(0)
#define rb_set_color(r,c) do {(r)->color = c;} while(0)

template <class T>
RBTree<T>::RBTree():mRoot(NULL){

}

template <class T>
RBTree<T>::~RBTree(){
	destroy();
}

template <class T>
void RBTree<T>::destroy(RBNode<T>* &root){
	if(root==NULL)
		return;
	destroy(root->left);
	destroy(root->right);
	delete root;
	root = NULL;
}

template <class T>
void RBTree<T>::destroy(){
	destroy(mRoot);
}

template <class T> 
void RBTree<T>::insert(RBNode<T>* &root,RBNode<T>* &node){
	RBNode<T> *y = NULL;
	RBNode<T> *x = root;

	while(x!=NULL){
		y = x;
		if(node->val<x->val)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if(y!=NULL){
		if(node->val < y->val)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	node->color = RED;

	insertFixUp(root,node);
}

template <class T> 
void RBTree<T>::insert(T key){
	RBNode<T>* node = NULL;
	if((node = new RBNode<T>(key,BLACK,NULL,NULL,NULL)) == NULL)
		return;
	insert(mRoot,node);
}

template <class T>
void RBTree<T>::insertFixUp(RBNode<T>* &root,RBNode<T>* &node){
	RBNode<T> *parent,*gparent;
	while((parent=rb_parent(node))&&rb_is_red(parent)){
		gparent = rb_parent(parent);

		if(parent == gparent->left){
			{
				//case 1 uncle is red
				{	
					RBNode<T>* uncle = gparent->right;
					if(uncle && rb_is_red(uncle)){
						rb_set_black(parent);
						rb_set_black(uncle);
						rb_set_red(gparent);
						node = gparent;
						continue;
					}
				}
				//case 2 uncle is black and node is right child
				if(parent->right == node){
					RBNode<T> *tmp;
					LRote(root,parent);
					tmp = parent;
					parent = node;
					node = tmp;
				}
				//case 3 uncle is black and node is left
				rb_set_black(parent);
				rb_set_red(gparent);
				RRote(root,gparent);
			}
		}
		else
		{
			//case 1 uncle is red
			{
				RBNode<T> *uncle = gparent->left;
				if(uncle&&rb_is_red(uncle)){
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			//case 2 uncle is black and node is left child
			if(parent->left == node){
				RBNode<T> *tmp;
				RRote(root,parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			//case 3 uncle is black and node is right child
			rb_set_black(parent);
			rb_set_red(gparent);
			LRote(root,gparent);
		}
	}

	rb_set_black(root);
}

template <class T>
void RBTree<T>::del(RBNode<T>* &root,RBNode<T>* &node){
	RBNode<T> *parent,*child;
	RBTColor color;

	if(node->left!=NULL&&node->right!=NULL){
		RBNode<T> *replace = node;
		replace = replace->right;

		while(replace->left!=NULL)
			replace = replace->left;

		if(rb_parent(node)){
			if(node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			root = replace;

		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if(parent==node){
			parent = replace;
		}
		else
		{
			if(child)
				rb_set_parent(child,parent);
			parent->left = child;
			replace->right = node->right;
			rb_set_parent(node->right,replace);
		}

		replace->parent = node->parent;
		replace->left = node->left;
		replace->color = node->color;
		node->left->parent = replace;

		if(color == BLACK)
			delFixUp(root,child,parent);

		delete node;
		return;
	}

	if(node->left!=NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;

	if(child)
		child->parent = parent;

	if(parent){
		if(parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;
	if(color == BLACK)
		delFixUp(root,child,parent);
	delete node;
}


template <class T>
void RBTree<T>::del(T key){
	RBNode<T> *node;
	if((node = search(mRoot, key)) != NULL)
		del(mRoot,node);
}

template <class T>
void RBTree<T>::delFixUp(RBNode<T>* &root,RBNode<T>* &node,RBNode<T>* &parent){

	RBNode<T> *brother;
	while(node==NULL||rb_is_black(node) && node != root){
		if(parent->left==node){
			brother = parent->right;
			//case 1 node's brother is red
			if(rb_is_red(brother)){
				rb_set_black(brother);
				rb_set_red(parent);
				LRote(root,parent);
				brother = parent->right;
			}
			//case 2 node's brother is black and its children are black
			if(!brother->left||rb_is_black(brother->left)&&!brother->right||rb_is_black(brother->right)){
				rb_set_red(brother);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{	//case 3 node's brother is black,its left child red and right child is black
				if(!brother->right||rb_is_black(brother->right)){
					rb_set_black(brother->left);
					rb_set_red(brother);
					RRote(root,brother);
					brother = parent->right;
				}
				//case 4 node's brother is black, its right child is red and left child not matter
				rb_set_color(brother,rb_color(parent));
				rb_set_black(parent);
				rb_set_black(brother->right);
				LRote(root,brother);
				node = root;
				break;
			}
		}
		else
		{
			brother = parent->left;
			if(rb_is_red(brother)){
				rb_set_black(brother);
				rb_set_red(parent);
				RRote(root,parent);
				brother = parent->left;
			}
			if(!brother->left||rb_is_black(brother->left)&&!brother->right||rb_is_black(brother->right)){
				rb_set_red(brother);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if(!brother->left||rb_is_black(brother->left)){
					rb_set_black(brother->right);
					rb_set_red(brother);
					LRote(root,brother);
					brother = parent->right;
				}

				rb_set_color(brother,rb_color(parent));
				rb_set_black(parent);
				rb_set_black(brother->left);
				RRote(root,brother);
				node = root;
				break;
			}
		}
	}

	if(node)
		rb_set_black(node);
}

template <class T>
RBNode<T>* RBTree<T>::search(RBNode<T>* &root,T key) const {
	if(!root)
		return NULL;
	else if(root->val == key)
		return root;
	else if(root->val<key)
		return search(root->left,key);
	else
		return search(root->right,key);
}

template <class T>
RBNode<T>* RBTree<T>::search(T key) const {
	return search(mRoot,key);
}


template <class T>
string RBTree<T>::print(RBNode<T>* mRoot) const {
	string ret="";
	if(mRoot!=NULL){
		stringstream ss;
		ss<<mRoot->val;
		ret = ss.str();
		if(rb_is_black(mRoot))
			ret += "(B)";
		else
			ret += "(R)";
		if(mRoot->left==NULL&&mRoot->right==NULL){
			return ret;
		}
		string lv = print(mRoot->left);
		string rv = print(mRoot->right);
		return ret +"("+lv+","+ rv + ")";
	}

	return ret;
}

template <class T>
string RBTree<T>::print() const {
	return print(mRoot);
}

template <class T> 
void RBTree<T>::LRote(RBNode<T>* &root,RBNode<T>* &x){
	RBNode<T>* y = x->right;
	x->right = y->left;
	if(y->left!=NULL){
		y->left->parent = x;
	}

	if(x->parent==NULL){
		root = y; 
	}
	else {
		if(x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	y->parent = x->parent;
	x->parent = y;
}

template <class T> 
void RBTree<T>::RRote(RBNode<T>* &root,RBNode<T>* &y){
	RBNode<T> *x= y->left;
	y->left = x->right;
	if(x->right!=NULL){
		x->right->parent = y;
	}

	if(y->parent==NULL){
		root = x;
	}
	else {
		if(y->parent->left == y)
			y->parent->left = x;
		else
			y->parent->right = x;
	}

	x->right = y;
	x->parent = y->parent;
	y->parent = x;
}

#endif