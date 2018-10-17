//
//  main.cpp
//  MIPT_METAPROG_2018
//
//  Created by Clumpy Tuna on 17.10.2018.
//  Copyright © 2018 Clumpy Tuna. All rights reserved.
//

#include <iostream>
#include <vector>

#include "classes.h"

void Proxy() {
	ClassB b;
	C<Roles::Proxy> c(&b);
	ClassA A(&c);
	
	A.Foo();
	A.Buz();
}

void Mediator() {
	std::vector<ClassB *> ptr_array;
	
	ClassB first;
	ClassB second;
	
	ptr_array.push_back(&first);
	ptr_array.push_back(&second);
	
	C<Roles::Mediator> c(ptr_array);
	
	ClassA A(&c);
	
	A.Foo();
	A.Buz();
}

void Observer() {
	ClassB observable;
	
	C<Roles::Observer> C(&observable);
	
	ClassA Frist("First");
	ClassA Second("Second");
	
	C.Subscribe(&Frist);
	C.Subscribe(&Second);
	
	observable.Buz();
}

int main(int argc, const char * argv[]) {
	
	// first case
	Proxy();
	
	// second case
	Mediator();
	
	//third case
	Observer();
	
	return 0;
}
