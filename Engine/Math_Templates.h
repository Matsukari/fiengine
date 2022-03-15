#ifndef MATH_EXTEND_TEMPLATES_H
#define MATH_EXTEND_TEMPLATES_H
// Part of Math.h

template<typename T>
IRange  Range_Equal(const std::vector<T>& array_vector)
{
	// all contents 0 - length
	return IRange{ 0, static_cast<int>(array_vector.size()) };
}

#endif