#ifndef SYMBTAB_H
#define SYMBTAB_H

#include <string>
#define NULL 0
#define SYMB_ARRAY 10
#define SYMB_FLOAT 11
#define SYMB_MATRIX 12
#define SYMB_UNDEFINED 13

struct Symb{
	std::string name;
	int type;
	int scope;
	Symb* next = NULL;
};

class Symbtab
{
public:
	Symbtab();
	~Symbtab();
	int actualScope = 0;
	Symb* root;
	Symb* symblook(std::string varName);
	void addScope();
	void quitScope();
};

#endif