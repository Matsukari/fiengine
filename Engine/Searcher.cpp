#include "Searcher.h"

// _______________________________________________________________________________________________________________________________

bool Search_Char(const char to_search, const std::vector<char>& array_vector, IRange search_range)
{
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			return true;
		}
	}
	return false;
}
bool Search_Int(const int   to_search, const std::vector<int>&  array_vector, IRange search_range)
{
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			return true;
		}
	}
	return false;
}
bool Search_Float(const float to_search, const std::vector<float>&  array_vector, IRange search_range)
{
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			return true;
		}
	}
	return false;
}
bool Search_Bool(const bool to_search, const std::vector<bool>& array_vector, IRange search_range)
{
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			return true;
		}
	}
	return false;
}
bool Search_String(const std::string to_search, const std::vector<std::string>& array_vector, IRange search_range)
{
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			return true;
		}
	}
	return false;
}


// _______________________________________________________________________________________________________________________________

bool Search_Char(const char to_search, const std::vector<char>& array_vector, IRange search_range, Vector<int>& result)
{
	bool found_one = false;
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			result.push_back(i);
			found_one = true;
		}
	}
	return found_one;
}
bool Search_Int(const int   to_search, const std::vector<int>&  array_vector, IRange search_range, Vector<int>& result)
{
	bool found_one = false;
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			result.push_back(i);
			found_one = true;
		}
	}
	return found_one;
}
bool Search_Float(const float to_search, const std::vector<float>&  array_vector, IRange search_range, Vector<int>& result)
{
	bool found_one = false;
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			result.push_back(i);
			found_one = true;
		}
	}
	return found_one;
}
bool Search_Bool(const bool to_search, const std::vector<bool>& array_vector, IRange search_range, Vector<int>& result)
{
	bool found_one = false;
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			result.push_back(i);
			found_one = true;
		}
	}
	return found_one;
}
bool Search_String(const std::string to_search, const std::vector<std::string>& array_vector, IRange search_range, Vector<int>& result)
{
	bool found_one = false;
	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i] == to_search)
		{
			result.push_back(i);
			found_one = true;
		}
	}
	return found_one;
}

// _______________________________________________________________________________________________________________________________


bool Search_Odd()
{
	return false;
}
bool Search_Even()
{
	return false;
}
bool Search_Prime()
{
	return false;
}
// _______________________________________________________________________________________________________________________________
