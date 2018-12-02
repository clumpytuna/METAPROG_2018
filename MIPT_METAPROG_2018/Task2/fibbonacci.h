// Автор: Михаил Анухин
// Описание: Класс CFibonacci, хранит числа Фибоначии.

#ifndef fibbonacci_h
#define fibbonacci_h

//Класс - "функция". Позволяет вычислять числа Фибоначчи на этапе компиляции.

template<int n>
class CFibonacci {
public:
	static const int number = CFibonacci<n - 1>::number + CFibonacci<n - 2>::number;
};

template<>
class CFibonacci<0> {
public:
	static const int number = 1;
};

template<>
class CFibonacci<1> {
public:
	static const int number = 1;
};

#endif /* fibbonacci_h */
