#include "ConfigHandler.h"
#include <assert.h>
#include "ConfigFile.h"

Big::ConfigHandler* Big::ConfigHandler::instance = nullptr;


Big::ConfigHandler* Big::ConfigHandler::InstancePtr()
{
	assert(instance != nullptr);
	return instance;
}
Big::ConfigHandler& Big::ConfigHandler::InstanceRef()
{
	assert(instance != nullptr);
	return *instance;
}

Big::ConfigHandler* Big::ConfigHandler::CreateInstance(const std::string& folderPath)
{
	if (!instance)
	{
		instance = new Big::ConfigHandler(folderPath);
	}
	return instance;
}

void Big::ConfigHandler::DestroyInstance()
{
	if (instance)
	{
		for (std::map<std::string, ConfigFile*>::iterator itr = instance->configlog.begin(); itr != instance->configlog.end(); ++itr)
		{
			itr->second->Destroy();
			delete itr->second;
			itr->second = nullptr;
		}
		delete instance;
		instance = nullptr;
	}
}


bool Big::ConfigHandler::LoadConfig(const std::string& ConfigName, bool parseNow, ConfigFile** outConfigFile /*= nullptr*/)
{
	if (configlog.find(ConfigName) == configlog.end())
	{
		ConfigFile* config = new ConfigFile();
		if (config->Create(basePath + ConfigName, parseNow))
		{
			configlog.insert(std::make_pair(ConfigName, config));
			*outConfigFile = config;
			return true;
		}
		return false;
	}
	return false;
}

bool Big::ConfigHandler::SaveConfigFile(const std::string& name)
{
	std::map<std::string, ConfigFile*>::iterator itr = configlog.find(name);
	if (itr != configlog.end())
	{
		return itr->second->Save();
	}
	return false;
}

Big::ConfigFile* Big::ConfigHandler::GetConfigFile(const std::string& name)
{
	std::map<std::string, ConfigFile*>::iterator itr = configlog.find(name);
	if (itr != configlog.end())
	{
		return itr->second;
	}
	return nullptr;
}

Big::ConfigHandler::ConfigHandler()
{
}


Big::ConfigHandler::ConfigHandler(const ConfigHandler&)
{

}

Big::ConfigHandler::ConfigHandler(const std::string& pathToFiles) : basePath(pathToFiles)
{

}

Big::ConfigHandler::~ConfigHandler()
{
}


