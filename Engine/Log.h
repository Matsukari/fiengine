#pragma once
#define LOG_H
#define OS_FILE 1
#define IS_FILE 2
#define OF_FILE 3
#define IF_FILE 4

// Independent File //

#include "Cpplib.h"
#include <fstream>

enum LOG_CATEGORY
{
	LOG_ERROR,
	LOG_WARN,
	LOG_MSG,
	LOG_ALL,
	LOG_TOTAL
};


String Get_Log_Categ_Str(LOG_CATEGORY category);
void   Pre_Message(String msg);

class ELog
{
public:
	ELog();
	~ELog();

	void operator()(String p_str, LOG_CATEGORY p_category) { Add(p_str, p_category); }
	void Add(String p_str, LOG_CATEGORY p_category);

	void Print(LOG_CATEGORY p_category);

	void Init();
	void Destroy();

	friend std::ofstream& operator<<(std::ofstream& p_file, const ELog& p_log)
	{
		// For eaxh Vector
		for (int i = 0; i < p_log.log.size(); i++)
		{
			p_file << Get_Log_Categ_Str(static_cast<LOG_CATEGORY>(i)) << "\n";
			// For Each Strings in Vector.
			for (auto msgs : p_log.log[i])
			{
				p_file << msgs << "\n";
			}
		}

		Pre_Message("ELog Saved to a File.");
		return p_file;
	}

	Vector<Vector< String >> log{ LOG_TOTAL };

private:
	Vector<String>&  Get_Log(LOG_CATEGORY p_category);
};
// Static member is not a choice.
void  ELog_Runtime(String msg, LOG_CATEGORY category);