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
	virtual void Foo() = 0;
	virtual void Buz() = 0;
};

class InterfaceObserver {
public:
	virtual void GetMessage() = 0;
};

class InterfaceObservable {
public:
	virtual void Subscribe(InterfaceObserver* observer) = 0;
	virtual void Unsubscribe(InterfaceObserver* observer) = 0;
};


class ClassB : public InterfaceB {
public:
	void Foo() {
		std::cout << "calling Foo!" << std::endl;
		if (watcher_ != nullptr) {
			watcher_-> GetMessage();
		}
	}
	
	void Buz() {
		std::cout << "calling Buz!" << std::endl;
		if (watcher_ != nullptr) {
			watcher_-> GetMessage();
		}
	}
	
	void becomeWatcher(InterfaceObserver *watcher) {
		watcher_ = watcher;
	}
	
private:
	InterfaceObserver *watcher_ = nullptr;
};

template <Roles T> class C {};

template <>
class C<Roles::Observer> : public InterfaceObservable, public InterfaceObserver {
public:
	C(ClassB* classB) {
		classB->becomeWatcher(this);
	}
	
	void Subscribe(InterfaceObserver* observer) {
		list_of_watchers_.push_back(observer);
	}
	
	void Unsubscribe(InterfaceObserver* observer) {
		list_of_watchers_.push_back(observer);
	}
	
	void GetMessage() {
		for (auto &&observer_ptr : list_of_watchers_) {
			observer_ptr->GetMessage();
		}
	}
	
private:
	std::vector<InterfaceObserver *> list_of_watchers_;
};


template <>
class C <Roles::Proxy> : public InterfaceB {
public:
	C(InterfaceB* object_ptr) : object_ptr_(object_ptr) {};
	
	void Foo() {
		object_ptr_->Foo();
	}
	
	void Buz() {
		object_ptr_->Buz();
	}
	
private:
	InterfaceB* object_ptr_;
};


template <>
class C<Roles::Mediator> : public InterfaceB {
public:
	C(std::vector <ClassB*> &ptr_array) : ptr_array_(ptr_array) {};
	
	void Foo() {
		ptr_array_[random() % ptr_array_.size()]->Foo();
	}
	
	void Buz() {
		ptr_array_[random() % ptr_array_.size()]->Buz();
	}
	
private:
	std::vector <ClassB*> ptr_array_;
};

class ClassA : public InterfaceB, public InterfaceObserver {
public:
	ClassA(const std::string& name) : name_(name) {};
	
	ClassA(InterfaceB *object_ptr) : object_ptr_(object_ptr) {}
	
	void Foo() {
		object_ptr_ -> Foo();
	}
	
	void Buz() {
		object_ptr_ -> Buz();
	}
	
	void GetMessage() {
		std::cout << "message recieved by " << name_<< std::endl;
	}
	
private:
	InterfaceB* object_ptr_;
	const std::string name_;
};

#endif /* classes_h */
