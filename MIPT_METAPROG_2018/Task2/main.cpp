#include <iostream>

#include "typelist.h"
#include "fibbonacci.h"
#include "genLinearHierarchyFib.h"
#include "genScatterHierarchyFib.h"

template<class T, class Root>
class Unit : public Root {
public:
	T a;
};

int main() {
	std::cout << CFibonacci<5>::number << std::endl;
	
	typedef CGenScatterHierarchyFib<TYPELIST_2( double, double ), Unit, 0> Type;
	
	Type awesome;
	
	return 0;
}
