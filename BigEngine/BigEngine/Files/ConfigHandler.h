#pragma once
#include <string>
#include <map>
namespace Big
{
	class ConfigFile;
	class ConfigHandler
	{
	public:
		static ConfigHandler* InstancePtr();
		static ConfigHandler& InstanceRef();

		ConfigHandler* CreateInstance(const std::string& folderPath);
		void DestroyInstance();

		bool LoadConfig(const std::string& ConfigName, bool parseNow, ConfigFile** outConfigFile = nullptr);
		bool SaveConfigFile(const std::string& name);
		ConfigFile* GetConfigFile(const std::string& name);
	private:
		ConfigHandler();
		ConfigHandler(const std::string& pathToFiles);
		ConfigHandler(const ConfigHandler&);
		~ConfigHandler();
		ConfigHandler& operator =(const ConfigHandler&) {};

		std::string basePath;
		std::map<std::string, ConfigFile*> configlog;
		static ConfigHandler* instance;
	};
}

