#include "LogHandler.h"
#include <assert.h>
#include "GLFW/glfw3.h"

Big::LogHandler* Big::LogHandler::instance = nullptr;
Big::LogFile* Big::LogHandler::defaultLog = nullptr;


	Big::LogHandler* Big::LogHandler::InstancePtr()
	{
		assert(instance != nullptr);
		return instance;
	}
	Big::LogHandler& Big::LogHandler::InstanceRef()
	{
		assert(instance != nullptr);
		return *instance;
	}

	Big::LogHandler* Big::LogHandler::CreateInstance(const std::string& folderPath)
	{
		if (!instance)
		{
			// Todo::Create folder if not exist;
			instance = new Big::LogHandler(folderPath);
			glfwSetErrorCallback(glfwErrorCallback);
		}
		return instance;
	}

	void Big::LogHandler::DestroyInstance()
	{
		if (instance)
		{
			for (std::map<std::string, LogFile*>::iterator itr = instance->logs.begin(); itr != instance->logs.end(); ++itr )
			{
				itr->second->Destroy();
				delete itr->second;
				itr->second = nullptr;
			}
			defaultLog = nullptr;
			delete instance;
			instance = nullptr;
		}
	}

	bool Big::LogHandler::CreateLog(const std::string logName, bool DoSupressFileOutput, bool doLogTimestamps)
	{
		if (logs.find(logName) == logs.end())
		{
			LogFile* log = new LogFile();
			if (log->Create(basePath + logName, DoSupressFileOutput, doLogTimestamps))
			{
				if (logs.empty())
				{
					defaultLog = log;
				}
				logs.insert(std::make_pair(logName, log));
				return true;
			}
			delete log;
			log = nullptr;
		}
		return false;
	}

	void Big::LogHandler::DoLog(const std::string& logName, const std::string& message, LogFile::LogType logType /*= LogFile::LogType::Info*/)
	{
		std::map<std::string, LogFile*>::iterator itr = logs.find(logName);
		if (itr != logs.end())
		{
			itr->second->DoLog(message, logType);
		}
	}

	void Big::LogHandler::DoLog(const std::string& message, LogFile::LogType logType /*= LogFile::LogType::Info*/)
	{
		assert(defaultLog != nullptr);
		defaultLog->DoLog(message,logType);
	}

	Big::LogHandler::LogHandler()
	{
	}


	void Big::LogHandler::glfwErrorCallback(int error, const char* description)
	{
		DoLog(description, LogFile::LogType::Error);
	}

	Big::LogHandler::LogHandler(const LogHandler&)
	{

	}

	Big::LogHandler::LogHandler(const std::string& pathToFiles) : basePath(pathToFiles)
	{

	}

	Big::LogHandler::~LogHandler()
	{
	}



