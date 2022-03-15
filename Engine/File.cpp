#include "File.h"


// Read aall contents of text file including white space and newlines/
String File_To_String(const char* path, int startpos)
{
	std::ifstream file(path);

	// store the file's content here
	std::string   content = "";

	// Go until the the minimum position.
	for (int i = 0; i < startpos; i++)
	{
		String name;
		file >> name;
	}

	// Main
	if (file.is_open())
	{
		for (int i = 0; not(file.eof()); i++)
		{
			content = content + " "; // add 1 cell(space) to store next content. EXTRA space in the end.
			file >> std::noskipws >> content[i];
		}
	}
	else
		std::cout << std::string{"In File_To_String(). File: "} + path + std::string{" name given does not exist or cannot be readed."};

	content.pop_back();
	file.close();

	return content;
}
String File_To_String(const char* path)
{
	std::ifstream file(path);

	// store the file's content here
	std::string   content = "";

	if (file.is_open())
	{
		for (int i = 0; not(file.eof()); i++)
		{
			content = content + " "; // add 1 cell(space) to store next content. EXTRA space in the end.
			file >> std::noskipws >> content[i];
		}
	}
	else
		std::cout << std::string{"In File_To_String(). File: "} + path + std::string{" name given does not exist or cannot be readed."};

	content.pop_back();
	file.close();

	return content;
}

// Ignore spaces, read all words denoted by a space.
Vector<String> File_To_Vector(const char* path, IRange range)
{
	std::ifstream  file(path);
	Vector<String> content;


	// Go until the minimum.
	for (int i = 0; i < range.min; ++i)
	{
		String name;
		file >> name;
	}

	// Main
	if (file.is_open())
	{
		for (int i = 0; not(file.eof()); i++)
		{
			content.push_back(String());
			file >> content[i];
		}
	}
	else
		std::cout << std::string{"In File_To_Vector(). File: "} + path + String{" name given does not exist or cannot be readed."};

	file.close();

	return content;
}


// Ignore spaces, read all words denoted by a space.
Vector<String> File_To_Vector(const char* path)
{
	std::ifstream  file(path);
	Vector<String> content;

	if (file.is_open())
	{
		for (int i = 0; not(file.eof()); i++)
		{
			content.push_back(String());
			file >> content[i];
		}
	}
	else
		std::cout << std::string{"In File_To_Vector(). File: "} + path + String{" name given does not exist or cannot be readed."};

	file.close();

	return content;
}





// Text_File________________________________________________________________________________________________________________________
Text_File::Text_File()
{
	
}

Text_File::Text_File(String p_path)
{
	Open(p_path);
}
Text_File::Text_File(const char* p_path)
{
	Open(p_path);
}
Text_File::~Text_File()
{
	
}
// Loader___________________________________________________________________________________________________________________________
bool Text_File::Open(String p_path)
{
	return (Open(p_path.c_str()));
}
bool Text_File::Open(const char* p_path)
{
	// Check if there is file already existed.
	std::ifstream test(p_path);

	// If Input file not located then create one. Note:: Output file create file if not existed and trucates it.
	if (not(test.is_open()))
	{
		std::ofstream new_file(p_path, std::ios::out | std::ios::trunc);
		new_file.close();
	}
	test.close();


	path      = p_path;
	m_content = File_To_Vector(p_path);

	if (m_content.size() == 0)
	{
		return false;
	}
	return true;
}
void Text_File::Close()
{
	// Overwite the last opened file.
	std::ofstream file(path, std::ios::out | std::ios::trunc);

	int i = 0;
	for (auto words : m_content)
	{
		file << words << "\n";


		++i;
		// For reading sakes.
		if (i == 2)
		{
			file << "\n";
			i = 0;
		}
	}
	ELog_Runtime((String)"Closed File:" + path, LOG_MSG);
	file.close();
}


void Text_File::Cursor_Backward(int n)
{
	m_current_index -= n;

	if (m_current_index <= 0)
	{
		m_current_index = 0;
	}
}
void Text_File::Cursor_Forward(int n)
{
	m_current_index += n;

	if (m_current_index >= m_content.size())
	{
		// revert from 0 again after exceeding limit.
		m_current_index = (m_current_index - m_content.size());
	}
}
void Text_File::Set_Cursor_On(String p_id)
{
	Vector<String>::iterator found_pos = std::find(m_content.begin(), m_content.end(), p_id);

	if (found_pos == m_content.end())
	{
		ELog_Runtime(String("Cannot Find: ") + p_id, LOG_ERROR);
		return;
	}

	m_current_index = Itr_To_Index(m_content, found_pos);
}
void Text_File:: Set_Cursor_After(String p_id)
{
	Vector<String>::iterator found_pos = std::find(m_content.begin(), m_content.end(), p_id);

	if (found_pos == m_content.end())
	{
		ELog_Runtime(String("Cannot Find: ") + p_id, LOG_ERROR);
		return;
	}

	m_current_index = Itr_To_Index(m_content, found_pos) - 1;
}
void Text_File::Set_Cursor_Before(String p_id)
{
	Vector<String>::iterator found_pos = std::find(m_content.begin(), m_content.end(), p_id);

	if (found_pos == m_content.end())
	{
		ELog_Runtime(String("Cannot Find: ") + p_id, LOG_ERROR);
		return;
	}
	m_current_index = Itr_To_Index(m_content, found_pos) + 1;
}

size_t Text_File::Get_Index(String p_id) const
{
	size_t found_pos = Vector_Find(m_content, p_id);
	return found_pos;
}

// Input____________________________________________________________________________________________________________________________
const Vector<String>& Text_File::Read_All() const
{
	return m_content;
}


String Text_File::Read_Before(String p_id) const
{
	size_t found_pos = Vector_Find(m_content, p_id);

	if (found_pos == -1 || found_pos == 0)
	{
		return TFILE_TEXT_NOT_FOUND;
	}

	return m_content[found_pos - 1];
}
String Text_File::Read_After(String p_id) const
{
	size_t found_pos = Vector_Find(m_content, p_id);

	if (found_pos == -1 || found_pos == m_content.size()-1)
	{
		return TFILE_TEXT_NOT_FOUND;
	}

	return m_content[found_pos + 1];
}

String Text_File::Read_Begin() const
{
	return m_content.front();
}
String Text_File::Read_End() const
{
	return m_content.back();
}
String Text_File::Read_Current()
{
	String word = m_content[m_current_index];
	Cursor_Forward();

	return word;
}


// Output___________________________________________________________________________________________________________________________
void Text_File::Insert_Before(String p_id, String p_item)
{
	Vector<String>::iterator found_pos = std::find(m_content.begin(), m_content.end(), p_id);

	if (found_pos == m_content.end())
	{
		ELog_Runtime(String("Cannot Find: ") + p_id, LOG_ERROR);
		return;
	}

	m_content.insert(found_pos - 1, p_item);
}
void Text_File::Insert_After(String p_id, String p_item)
{
	Vector<String>::iterator found_pos = std::find(m_content.begin(), m_content.end(), p_id);

	if (found_pos == m_content.end())
	{
		ELog_Runtime(String("Cannot Find: ") + p_id, LOG_ERROR);
		return;
	}

	m_content.insert(found_pos + 1, p_item);
}
void Text_File::Insert_Begin(String p_item)
{
	m_content.insert(m_content.begin(), p_item);
	Cursor_Forward();
}
void Text_File::Insert_End(String p_item)
{
	m_content.insert(m_content.end(), p_item);
}
void Text_File::Insert_Current(String p_item)
{
	m_content.insert(Index_To_Itr(m_content, m_current_index), p_item);
	Cursor_Forward();
}
// Manipulations_________________________________________________________________________________________________________________
void Text_File::Delete_Before(String p_id)
{
	Vector<String>::iterator found_pos = std::find(m_content.begin(), m_content.end(), p_id);

	if (found_pos == m_content.end())
	{
		ELog_Runtime(String("Cannot Find: ") + p_id, LOG_ERROR);
		return;
	}

	m_content.erase(found_pos - 1);
}
void Text_File::Delete_After(String p_id)
{
	Vector<String>::iterator found_pos = std::find(m_content.begin(), m_content.end(), p_id);

	if (found_pos == m_content.end())
	{
		ELog_Runtime(String("Cannot Find: ") + p_id, LOG_ERROR);
		return;
	}

	if (m_content.size() > 0)
	{
		m_content.erase(found_pos + 1);
	}
}
void Text_File::Delete_Begin()
{
	if (m_content.size() > 0)
	{
		m_content.erase(m_content.begin());
		Cursor_Backward();
	}
}
void Text_File::Delete_End()
{
	if (m_content.size() > 0)
	{
		m_content.erase(m_content.end());

		// If in the end, then get back
		if (m_current_index >= m_content.size())
		{
			m_current_index--;
		}
	}
}
void Text_File::Delete_Current()
{
	if (m_content.size() > 0)
	{
		m_content.erase(Index_To_Itr(m_content, m_current_index));
		Cursor_Backward();
	}
}


