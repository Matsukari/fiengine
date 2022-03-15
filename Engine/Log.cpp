#include "Log.h"

String Get_Log_Categ_Str(LOG_CATEGORY category)
{
	String str = "";
	switch (category)
	{
		case LOG_ERROR: str = "Error:";   break;
		case LOG_WARN:  str = "Warning:"; break;
		case LOG_MSG:   str = "Message:"; break;
	}

	return str;
}
void Pre_Message(String msg)
{
	printf("\nPre-Message: %s", msg.c_str());
}


ELog::ELog()
{
	log[LOG_ERROR] = {};
	log[LOG_WARN] = {};
	log[LOG_MSG] = {};
}
ELog::~ELog()
{
}

void ELog::Add(String p_str, LOG_CATEGORY p_category)
{
	std::cout << "\n" << Get_Log_Categ_Str(p_category) << " " << p_str;
	Get_Log(p_category).push_back(p_str);
}
void ELog::Print(LOG_CATEGORY p_category)
{
	for (auto i : Get_Log(p_category))
	{
		std::cout << "\n" << i;
	}
}


Vector<String>& ELog::Get_Log(LOG_CATEGORY p_category)
{
	switch (p_category)
	{
		case LOG_ERROR: return log[LOG_ERROR];  break;
		case LOG_WARN:  return log[LOG_WARN];   break;
		case LOG_MSG:   return log[LOG_MSG];    break;
		default:  Pre_Message("Unidentified argument from ELog::Get_Category(). Possibly LOG_ALL.");
	}

	return log[LOG_MSG];
}

void ELog_Runtime(String msg, LOG_CATEGORY category)
{
	static ELog log;
	
	log(msg, category);
}