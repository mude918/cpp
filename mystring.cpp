#include "util.h"

MyString& MyString::operator=(const MyString &str){
	if(this!=&str){
		delete []this->mdata;
		if(!str.mdata){
			this->mdata = 0;
		}else{
			this->mdata = new char[strlen(str.mdata)+1];
			strcpy(this->mdata,str.mdata);
		}
	}
	return *this;
}
ostream& operator<<(ostream &os,const MyString &s){
	os<<s.mdata;
	return os;
}
