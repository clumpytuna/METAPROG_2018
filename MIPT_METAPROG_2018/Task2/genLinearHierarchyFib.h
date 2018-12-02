// Автор: Михаил Анухин
// Описание: Класс CGenLinearHierarchy, генерирует линейную иерархию.

#ifndef genLinearHierarchyFib_h
#define genLinearHierarchyFib_h

#include "typelist.h"

// Класс - "функция". Генерирует линейную иерархию классов из указанного CTypeList.

template <class CTypeList, template <class AtomicType, class base> class Unit, int number>
class CGenLinearHierarchyFib;

template <class H, class T, template <class, class> class Unit, int number>
class CGenLinearHierarchyFib<CTypeList<H, T>, Unit, number> :
	public Unit<H, CGenLinearHierarchyFib<T, Unit, number - 1> > {};

template<class H, class T, template<class, class> class Unit>
class CGenLinearHierarchyFib<CTypeList<H,T>, Unit, 0> {};

template <template <class, class> class Unit, int number>
class CGenLinearHierarchyFib<NullType, Unit, number> {};


#endif /* genLinearHierarchyFib_h */
