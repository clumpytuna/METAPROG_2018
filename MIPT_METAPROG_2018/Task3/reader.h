#ifndef MIPT_METAPROG_READER_H
#define MIPT_METAPROG_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "typelist.h"



// Класс получает на вход TypeList с описанием строки в файле, открывает этот файл
// и позволяет с помощью метода void* readNextLine() читать по очереди все строки в файл.
// Возвращаемое значение функции – указатель на область памяти, где последовательно
// записаны считанные элементы строки.

template<class Types>
class Reader;


template<>
class Reader<NullType>
{
public:
	static void readNextElement(std::ifstream& stream, char* position) {}
};

template<class Head, class Tail>
class Reader<CTypeList<Head, Tail>>
{
public:
	Reader() = default;
	
	static void readNextElement(std::ifstream& stream, char* position) {
		stream.read(position, sizeof(Head));
		position = (char*)(((Head*)position) + 1);
		Reader<Tail>::readNextElement(stream, position);
	}
	
	void* readNextLine(std::ifstream& stream) {
		char* result = (char *)operator new(SizeOf<CTypeList<Head, Tail>>::result);
		readNextElement(stream, result);
		return result;
	}
};

#endif //MIPT_METAPROG_READER_H
