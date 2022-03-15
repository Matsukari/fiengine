#pragma once
#define FILE_H
#define TFILE_TEXT_NOT_FOUND "Not_Found"

#include "Cpplib.h"
#include "Math.h"
#include "Log.h"

// range is from position of words and not letter. Combined with Text_File
String File_To_String(const char* path, int startpos);
String File_To_String(const char* path);

Vector<String> File_To_Vector(const char* path, IRange range);
Vector<String> File_To_Vector(const char* path);

template<typename T> typename Vector<T>::iterator Index_To_Itr(Vector<T>& vec, size_t pos);
template<typename T> size_t Itr_To_Index(Vector<T>& vec, typename Vector<T>::iterator pos);
template<typename T> size_t Vector_Find(const Vector<T>& vec, T id); // Find using == operator. Returns index.

#include "File_Templates.h"

// Convert string to other types on your own
class Text_File
{
public:
	Text_File();
	Text_File(String      p_path);
	Text_File(const char* p_path);
	~Text_File();

	// Loader
	// Extract text files contents in vector. (any read and write in text file will not save 
	// because you are interfering with the copied vector. )
	bool Open(String      p_path);
	bool Open(const char* p_path);


	// Clear previous contents of text file before making any changes, and save the current changes.
	// Any extra spaces and newlines prior to changes will get discarded after closing.
	void Close();

	void Cursor_Backward(int n = 1);
	void Cursor_Forward(int n  = 1);

	void Set_Cursor_On(String p_id);
	void Set_Cursor_After(String p_id);
	void Set_Cursor_Before(String p_id);

	size_t Get_Index(String p_id) const;

	// Input
	const Vector<String>& Read_All() const;

	String Read_Before(String p_id) const;
	String Read_After(String p_id)  const;

	String Read_Begin() const;
	String Read_End() 	const;
	String Read_Current();

	// Output
	void Insert_Before(String p_id, String p_item);
	void Insert_After(String p_id, String p_item);

	void Insert_Begin(String p_item);
	void Insert_End(String p_item);
	void Insert_Current(String p_item);

	// Manipulations
	void Delete_Before(String p_id);
	void Delete_After(String p_id);

	void Delete_Begin();
	void Delete_End();
	void Delete_Current();

	String path;

private:
	// All contents of file to be string.
	Vector<String> m_content;
	size_t         m_current_index{ 0 };
};
