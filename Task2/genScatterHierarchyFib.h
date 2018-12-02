// Автор: Михаил Анухин
// Описание: Класс CGenScatterHierarchyFib, генерирует иерархию, особого типа.

#ifndef genScatterHierarchyFib_h
#define genScatterHierarchyFib_h

#include "fibbonacci.h"
#include "genLinearHierarchyFib.h"
#include "typelist.h"

// Класс - "функция". Генерирует "scattered" - иерархию классов, веткой,
// которой является линейная иерархия, классов указанных в CTypeList.

template <class CTypeList, template <class, class> class Unit, int number=0>
class CGenScatterHierarchyFib;

template <class H, class T, template <class, class> class Unit, int number>
class CGenScatterHierarchyFib<CTypeList<H, T>, Unit, number> :
	public CGenLinearHierarchyFib<CTypeList<H, T>, Unit, CFibonacci<number>::number>,
	public CGenScatterHierarchyFib<typename Slice<CTypeList<H, T>, CFibonacci<number>::number >::Result, Unit, number + 1> {};

template <template <class, class> class Unit, int number>
class CGenScatterHierarchyFib<NullType, Unit, number> {};


#endif /* genScatterHierarchyFib_h */
