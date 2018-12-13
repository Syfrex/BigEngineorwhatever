#pragma once
#include <string>
#include <fstream>

namespace Big
{

	class LogFile
	{
	public:
		LogFile();
		~LogFile();
		enum LogType
		{
			Info,
			Warning,
			Error
		};

		bool Create(const std::string& Filename, bool DoSupressFileOutput = false, bool DoLogTimeStamp = true);
		void Destroy();

		void DoLog(const std::string Message, LogType logType = Info);


	private:
		LogFile(const LogFile& logFile);
		LogFile& operator=(const LogFile&) {};

		std::string URI;
		bool SupressFileOutput = false;
		bool LogTimestamps = true;

		std::ofstream FileStream;
	};
}

