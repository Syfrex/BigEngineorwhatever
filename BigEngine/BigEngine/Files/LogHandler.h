#pragma once
#include <string>
#include <map>
#include "LogFile.h"


namespace Big
{
	class LogHandler
	{
	public:
		static LogHandler* InstancePtr();
		static LogHandler& InstanceRef();

		static LogHandler* CreateInstance(const std::string& folderPath);
		static void DestroyInstance();

		bool CreateLog(const std::string logName, bool DoSupressFileOutput = false, bool doLogTimestamps = true);
		void DoLog(const std::string& logName, const std::string& message, LogFile::LogType logType = LogFile::LogType::Info);
		static void DoLog(const std::string& message, LogFile::LogType logType = LogFile::LogType::Info);
	private:
		LogHandler();
		~LogHandler();
		LogHandler(const std::string& pathToFiles);
		LogHandler(const LogHandler&);
		LogHandler& operator =(const LogHandler&) {};

		static void glfwErrorCallback(int error, const char* description);

		std::string basePath;
		std::map<std::string, LogFile*> logs;
		static LogHandler* instance;
		static LogFile* defaultLog;
	};
}

