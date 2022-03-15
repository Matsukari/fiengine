#ifndef SEARCHER_TEMPLATES_H
#define SEARCHER_TEMPLATES_H

// Only works for classes that have id int member variable.
template<typename T>
int  Search_ID(const int id, std::vector<T*>& array_vector, IRange search_range)
{
	if (search_range.min > array_vector.size() || search_range.max > array_vector.size()) 
	{
		printf("\nIn Search_ID(), search range exceed max size.");
		return SEARCH_ERROR;
	}

	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i]->id == id)
		{
			return i;
		}
	}

	return SEARCH_FAILED;
}
template<typename T>
std::vector<int> Give_Matching_ID(const int id, std::vector<T*>& array_vector, IRange search_range)
{
	if (search_range.min > array_vector.size() || search_range.max > array_vector.size()) 
	{
		printf("\nIn Search_ID(), search range exceed max size.");
		return {SEARCH_ERROR};
	}

	std::vector<int> matching_id = {};

	for (int i = search_range.min; i < search_range.max; i++)
	{
		if (array_vector[i]->id == id)
		{
			matching_id.push_back(i);
		}
	}

	return matching_id;
}

#endif