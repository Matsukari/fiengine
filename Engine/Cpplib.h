#pragma once
#define CPPLIB_H

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

typedef std::string String;
template<typename T> using Vector = std::vector<T>;


#define FOUND_NO_NUMBER "100101"
// Ignore's any characters except from numbers.
String 	Concat_Numbers(String str);

int 	To_Int(String str);
float 	To_Float(String str);
double 	To_Double(String str);

String  Word_In_String(const String& str, size_t n);
size_t  Words_Ammount(const String& str);