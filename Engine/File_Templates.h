#include "File.h"

template<typename T>
typename Vector<T>::iterator Index_To_Itr(Vector<T>& vec, size_t pos)
{
	typename Vector<T>::iterator it = vec.begin() + pos;
	return it;
}
template<typename T>
size_t Itr_To_Index(Vector<T>& vec, typename Vector<T>::iterator pos)
{
	return pos - vec.begin();
}

// Find uusing == operator
template<typename T>
size_t Vector_Find(const Vector<T>& vec, T id)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (id == vec[i])
		{
			return i;
		}
	}
	return -1;
}
