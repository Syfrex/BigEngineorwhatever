#include "LogFile.h"
#include <time.h>
#include <iomanip>


Big::LogFile::LogFile()
{

}

Big::LogFile::~LogFile()
{

}

bool Big::LogFile::Create(const std::string& Filename, bool DoSupressFileOutput, bool DoLogTimeStamp)
{
	URI = Filename;
	SupressFileOutput = DoSupressFileOutput;
	LogTimestamps = DoLogTimeStamp;

	if (!SupressFileOutput)
	{
		FileStream.open(URI);
		return FileStream.is_open();
	}
	return true;
}

void Big::LogFile::Destroy()
{
	if (SupressFileOutput == false)
	{
		FileStream.close();
	}
}

void Big::LogFile::DoLog(const std::string Message, LogType logType)
{
	if (!SupressFileOutput)
	{
		if (LogTimestamps)
		{
			time_t rawTime;
			tm timeInfo;
			time(&rawTime);
			localtime_s(&timeInfo, &rawTime);

			FileStream << std::setw(2)
				<< std::setfill('0') << timeInfo.tm_hour << ":" << std::setw(2)
				<< std::setfill('0') << timeInfo.tm_min << ":" << std::setw(2)
				<< std::setfill('0') << timeInfo.tm_sec << " - ";
		}
		switch (logType)
		{
		case Big::LogFile::Info:
		{
			FileStream << "Info: ";
			break;
		}
		case Big::LogFile::Warning:
		{
			FileStream << "Warning: ";
			break;
		}
		case Big::LogFile::Error:
		{
			FileStream << "Error: ";
			break;
		}
		default:
			break;
		}
		FileStream << Message << std::endl;
		FileStream.flush();
	}
}

Big::LogFile::LogFile(const LogFile& logFile)
{

}


