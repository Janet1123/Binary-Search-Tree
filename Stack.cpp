#include <iostream>
#include "Stack.h"


bool Stack::empty() {
	return list.empty();
}


int Stack::size() {
	return list.size();
}


bool Stack::push(type newItem) {
	return list.insert(1, newItem);
}


bool Stack::pop(type &container) {
	if (!list.get(1, container)) return false;
	return list.remove(1);
}