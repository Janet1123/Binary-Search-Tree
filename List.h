#ifndef List_type
#define List_type

#include	"Node.h"


//typedef char type;

//using type = int;

struct List
{
	int count;
	Node *head;
	Node *find(int);
	List();
	bool empty();
	int size();
	bool get(int, type&);
	bool set(int, type);
	bool insert(int, type);  // insert item according to the specified position
	bool remove(int);
	bool insert(type);  // insert item into ascending order - work for primitve type only
};


#endif