#include "Cpplib.h"

// Ignore's any characters except from numbers.
String Concat_Numbers(String str)
{
	// without perioud and negative sign
	static String non_letters = "!@#$%^&*()_+=~`[]{}:;'|<>,?/";

	// To stop the dog from barking. Adds backslash
	const char newline[2] = "\n";
	non_letters += newline[0];

	bool has_letter     = false;
	bool has_non_letter = false;

	String valid_number = "0";

	for (int i = 0; i < str.size(); i++)
	{
		// Has no letter
		if ( ((int)str[i] >= int('a') && (int)str[i] <= int('z') ||
			  (int)str[i] >= int('A') && (int)str[i] <= int('Z')) )
		{
			has_letter = true;
		}
		else
			has_letter = false;

		// Check is has non letter
		for (int j = 0; j < non_letters.size(); j++)
		{
			if (str[i] == non_letters[j])
			{
				has_non_letter = true;
			}
		}

		// Final verif
		if (not(has_letter) && not(has_non_letter))
		{
			valid_number += str[i];
		}


		has_letter     = false;
		has_non_letter = false;
	}

	return valid_number;
}
int To_Int(String str)
{
	return std::stoi(Concat_Numbers(str));
}
float To_Float(String str)
{
	return std::stof(Concat_Numbers(str));
}
double To_Double(String str)
{
	return std::stod(Concat_Numbers(str));
}


String  Word_In_String(const String& str, size_t n)
{
	size_t first_space = 0;
	size_t words = 0;
	String word_str;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			word_str = str.substr(first_space, i-first_space);

			// return prev
			if (words == n)
			{
				return word_str;
			}

			words++;
			first_space = i+1;
		}
		else if (i == str.size()-1) // to end
		{
			word_str = str.substr(first_space, (i-first_space)+1);

			// return prev
			return word_str;
		}
	}

	return "Not Found: Word_In_String()";
}
size_t  Words_Ammount(const String& str)
{
	size_t words = 1;
	for (int i = 0; i < str.size(); i++)
	{
		// Still have space left
		if ((str[i] == ' ') && (i + 1 < str.size()) )
		{
			words++;
		}
	}

	return words;
}
