#include "Symbtab.h"

Symbtab::Symbtab()
{
}


Symbtab::~Symbtab()
{
	Symb* item = root;
	if (item != NULL)
	{
		while (item->next != NULL){
			item = item->next;
			delete root;
			root = item;
		}
		delete root;
	}
}

Symb* Symbtab::symblook(std::string varName)
{
	
	if (root == NULL)
	{
		root = new Symb();
		root->name = varName;
		root->scope = actualScope;
		root->type = SYMB_UNDEFINED;
		return root;
	}
	Symb* item = root;
	while (item->name != varName)
	{
		if (item->next == NULL)
		{
			item->next = new Symb();
			item->next->name = varName;
			item->next->scope = actualScope;
			item->next->type = SYMB_UNDEFINED;
			return item->next;
		}
		item = item->next;
	}
	return item;
}

void Symbtab::quitScope()
{
	Symb* item = root;
	Symb* itemToDelete;
	if (actualScope != 0)
	{
		actualScope--;
		while (item != NULL)
		{
			if (item->scope > actualScope){
				itemToDelete = item;
				item = item->next;
				delete itemToDelete;

			}
		}
	}
}

void Symbtab::addScope()
{
	actualScope++;
}
