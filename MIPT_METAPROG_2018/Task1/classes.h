//
//  classes.h
//  MIPT_METAPROG_2018
//
//  Created by Clumpy Tuna on 17.10.2018.
//  Copyright © 2018 Clumpy Tuna. All rights reserved.
//
#include <iostream>
#include <vector>


#ifndef classes_h
#define classes_h

enum class Roles {
	Proxy,
	Mediator,
	Observer,
};

class InterfaceB {
public:
	virtual void foo() = 0;
	virtual void buz() = 0;
};

class ClassB : public InterfaceB {
public:
	void foo() {
		std::cout << "calling foo!" << std::endl;
	}
	
	void buz() {
		std::cout << "calling buz!" << std::endl;
	}
};


template <Roles T> class C {};

template <>
class C <Roles::Proxy> : public InterfaceB {
public:
	C(ClassB* object_ptr) : object_ptr_(object_ptr) {};
	
	void foo() {
		object_ptr_ -> foo();
	}
	
	void buz() {
		object_ptr_ -> buz();
	}
	
private:
	ClassB* object_ptr_;
};


template <>
class C<Roles::Mediator> : public InterfaceB {
public:
	C(std::vector <ClassB*> &ptr_array) : ptr_array_(ptr_array) {};
	
	void foo() {
		ptr_array_[random() % ptr_array_.size()]->foo();
	}
	
	void buz() {
		ptr_array_[random() % ptr_array_.size()]->buz();
	}
	
private:
	std::vector <ClassB*> ptr_array_;
};

class ClassA : public InterfaceB {
public:
	ClassA(InterfaceB *object_ptr) : object_ptr_(object_ptr) {}
	
	void foo() {
		object_ptr_ -> foo();
	}
	
	void buz() {
		object_ptr_ -> buz();
	}
	
private:
	InterfaceB* object_ptr_;
};

#endif /* classes_h */
