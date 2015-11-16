#include "avl.h"
#include "util.h"

int insertKeyToAvl(AvlNode* &root, int key, bool &taller){
	if(root==NULL){
		root = new AvlNode(key);
		taller = true;
	}
	else{
		if(EQ(root->val,key)){
			taller = false;
			return 0;
		}
		else if(LT(key,root->val)){
			if(!insertKeyToAvl(root->left,key,taller))
				return 0;

			if(taller){
				switch(root->bf){
					case LH:
						leftBalance(root); taller=false; break;
					case EH:
						root->bf = LH; taller=true; break;
					case RH:
						root->bf = EH; taller=false; break;
				}	
			}
		}
		else {
			if(!insertKeyToAvl(root->right,key,taller))
				return 0;

			if(taller){
				switch(root->bf){
					case LH:
						root->bf=EH; taller=false; break;
					case EH:
						root->bf=RH; taller=true; break;
					case RH:
						rightBalance(root); taller=false; break;
				}	
			}
		}
	}

	return 1;
}

void leftBalance(AvlNode* &root){
	AvlNode* &lc = root->left;
	AvlNode* &lrc = root->left->right;
	switch(lc->bf){
		case LH:
		   	root->bf = lc->bf = EH;
			RRote(root);
		   	break;
		case EH:
			lc->bf = RH; root->bf = LH;
			RRote(root); 
			break;
		case RH:
			switch(lrc->bf){
				case LH:
					lc->bf = EH; root->bf = RH; break;
				case EH:
					lc->bf = root->bf = EH; break;
				case RH:
					lc->bf = LH; root->bf = EH; break;
			}
			lrc->bf = EH;
			LRote(lc);
			RRote(root);
			break;
	}
		
}

void rightBalance(AvlNode* &root){
	AvlNode* &rc = root->right;
	AvlNode* &rlc = root->right->left;
	switch(rc->bf){
		case LH:
			switch(rlc->bf){
				case LH:
					rc->bf = RH; root->bf = EH; break;
				case EH:
					rc->bf = root->bf = EH; break;
				case RH:
					rc->bf = EH; root->bf = LH; break;
			}
			rlc->bf = EH;
			RRote(rc);
			LRote(root);
			break;
		case EH:
			rc->bf = LH; root->bf = RH;
			LRote(root);
			break;
		case RH:
			rc->bf = root->bf = EH;
			LRote(root);
			break;	
	}
}

int delKeyFromAvl(AvlNode* &root,int key,bool &lower){
	AvlNode* p;
	int retFlag = 0,delFlag = 0;
	if(root==NULL){
		return 0;
	}

	if(EQ(key,root->val)){
		lower = true;
		if(root->right==NULL){
			p = root;
			root = root->left;
			delete p;
			return 1;
		}
		else{
			p=root->right;
			while(p->left!=NULL){
				p = p->left;
			}
			root->val = p->val;
			retFlag = delKeyFromAvl(root->right,p->val,lower);
			delFlag = RH;
		}
	}else if(LT(key,root->val)){
		retFlag = delKeyFromAvl(root->left,key,lower);
		delFlag = LH;
	}else{
		retFlag = delKeyFromAvl(root->right,key,lower);
		delFlag = RH;
	}

	if(lower==true){
		if(delFlag==LH){
			switch(root->bf){
				case LH:
					root->bf = EH;lower=true;break;
				case EH:
					root->bf = RH;lower=false;break;
				case RH:
					rightBalance(root);lower=true;break;
			}
		}
		else{
			switch(root->bf){
				case LH:
					leftBalance(root);lower=true;break;
				case EH:
					root->bf = LH;lower=false;break;
				case RH:
					root->bf = EH;lower=true;break;
			}
		}
	}

	return retFlag;
}

void LRote(AvlNode* &root){
	AvlNode *rc;
	rc = root->right;
	root->right = rc->left;
	rc->left = root;
	root = rc;
}

void RRote(AvlNode* &root){
	AvlNode *lc;
	lc = root->left;
	root->left = lc->right;
	lc->right = root;
	root = lc;
}

string printAvl(AvlNode* &root){
	string ret="";
	if(root!=NULL){
		stringstream ss;
		ss<<root->val;
		ret = ss.str();
		if(root->left==NULL&&root->right==NULL){
			return ret;
		}
		string lv = printAvl(root->left);
		string rv = printAvl(root->right);
		return ret +"("+lv+","+ rv + ")";
	}

	return ret;
}


