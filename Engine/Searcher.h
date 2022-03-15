#pragma once
#define SEARCHER_H
#define SEARCH_FAILED -1
#define MATCHING_NONE 0
#define SEARCH_ERROR -2

#include "Cpplib.h"
#include "Math.h"

// Returns false at fail. Int returning function returns SEARCH_FAILED at fail.
// First to search.
bool   Search_Char  (const char  to_search, const std::vector<char>&   array_vector, IRange search_range);
bool   Search_Int   (const int   to_search, const std::vector<int>&    array_vector, IRange search_range);
bool   Search_Float (const float to_search, const std::vector<float>&  array_vector, IRange search_range);
bool   Search_Bool  (const bool  to_search, const std::vector<bool>&   array_vector, IRange search_range);
bool   Search_String(const std::string to_search, const std::vector<std::string>& vector, IRange search_range);

// Search with Matching results. Return index in success in "results"
bool Search_Char  (const char  to_search, const std::vector<char>&   array_vector, IRange search_range, Vector<int>& result);
bool Search_Int   (const int   to_search, const std::vector<int>&    array_vector, IRange search_range, Vector<int>& result);
bool Search_Float (const float to_search, const std::vector<float>&  array_vector, IRange search_range, Vector<int>& result);
bool Search_Bool  (const bool  to_search, const std::vector<bool>&   array_vector, IRange search_range, Vector<int>& result);
bool Search_String(const std::string to_search, const std::vector<std::string>& vector, IRange search_range, Vector<int>& result);

// For all. std::find().

bool   Search_Odd();
bool   Search_Even();
bool   Search_Prime();

// Only works for classes that have 'id' int member variable.
template<typename T>
int  			    Search_ID(const int id, std::vector<T*>& array_vector, IRange search_range);
template<typename T>
std::vector<int>	Give_Matching_ID(const int id, std::vector<T*>& array_vector, IRange search_range);

#include "Searcher_Templates.h"