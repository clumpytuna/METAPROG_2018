// Автор: Михаил Анухин
// Описание: Класс CTypeList, хранит типы в явном виде.

#ifndef TypeList_h
#define TypeList_h

// Список типов. Класс предназначен для хранения типов в явном виде
template <class H, class T>
class CTypeList {
public:
	typedef H head;
	typedef T tail;
};

// Обертки для более удобного использования списка типов.
// Использовать следующим образом (пример для списка длины два):
// TYPELIST_2( int, double )
#define TYPELIST_1( T1 ) CTypeList<T1, NullType>
#define TYPELIST_2( T1, T2 ) CTypeList<T1, TYPELIST_1( T2 ) >
#define TYPELIST_3( T1, T2, T3 ) Typelist<T1, TYPELIST_2( T2, T3 ) >

/////////////////////////////////////////////////////////////////////////////////////

// Пустой элемент списка, также можно использовать как пустой список
class NullType {};

/////////////////////////////////////////////////////////////////////////////////////

// Класс - "функция". Предназначен для получения элементов списка типов по индексу.
// Первым параметром в шаблон передается CTypeList, вторым передается индекс элемента,
// третьим всегда передается тип, возращаемый в случае если индекс вне границ списка.
// Пример использования:
// typedef typename GetTypeAt<TypeList, 0, NullType>::Result FirstParameterType;
template <class TList, unsigned int index, typename DefaultType = NullType>
class GetTypeAt {
public:
	typedef DefaultType Result;
};

// Специализация класса GetTypeAt. Предназначена для получения первого элемента списка типов
template <class Head, class Tail, typename DefaultType>
class GetTypeAt<CTypeList<Head, Tail>, 0, DefaultType> {
public:
	typedef Head Result;
};

// Специализация класса GetTypeAt. Предназначена для получения i-го элемента
// списка типов. Если индекс выходит за границу списка, то возвращается DefaultType.
// Работает за O(n), однако все операции выполняются во время компиляции.
template <class Head, class Tail, unsigned int i, typename DefaultType>
class GetTypeAt<CTypeList<Head, Tail>, i, DefaultType> {
public:
	typedef typename GetTypeAt<Tail, i - 1, DefaultType>::Result Result;
};

///////////////////////////////////////////////////////////////////////////////////

// Класс - "функция". Предназначен для получения длины тайплиста.

template<class Type>
class Length {
public:
	enum { value = 0 };
};

template<class Head, class Tail>
class Length<CTypeList<Head, Tail> > {
public:
	enum { value = 1 + Length<Tail>::value };
};




// Класс - "функция". Предназначен для удаления элементов из списка типов по индексу.
// typedef typename Erase<TypeList, T>::Result
// где Result - новый typelist
template <class TList, class T> class Erase;


// Если TypeList состоит из NullType, то Result = NullType
template <class T>
class Erase<NullType, T> {
public:
	typedef NullType Result;
};

// Иначе, если T == TList::Head, то Result = TList::Tail
template <class T, class Tail>
class Erase<CTypeList<T, Tail>, T> {
public:
	typedef Tail Result;
};


// Иначе Result = { TList::Head, Erase<TList::Tail, T> }
template <class Head, class Tail, class T>
class Erase<CTypeList<Head, Tail>, T> {
public:
	typedef CTypeList<Head, typename Erase<Tail, T>::Result> Result;
};


#endif // TypeList_h
