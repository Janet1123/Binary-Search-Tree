#ifndef Stack_type
#define Stack_type

#include	"List.h"
#include	"Node.h"

//typedef char type;

//using type = char;

struct Stack {
	
		List list;
		bool empty();
		int size();
		bool push(type);  // insert item
		bool pop(type&);	// remove item
};



#endif