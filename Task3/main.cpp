//
//  main.cpp
//  MIPT_METAPROG_2018
//
//  Created by Clumpy Tuna on 26/12/2018.
//  Copyright © 2018 Clumpy Tuna. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "reader.h"
#include "typelist.h"

int main () {
	std::ofstream file_to_read_from("file", std::ios::out | std::ios::binary);
	
	char char_ = 'a';
	file_to_read_from.write(reinterpret_cast<char*>(&char_), sizeof(int));
	file_to_read_from.close();
	
	std::ifstream file("file", std::ios::in | std::ios::binary);
	
	Reader<TYPELIST_1( char )> reader;
	char* result = (char *)reader.readNextLine(file);
	
	std::cout << "Result: " << result[0] << std::endl;
	
	delete(result);
	file.close();
	
	return 0;
}
