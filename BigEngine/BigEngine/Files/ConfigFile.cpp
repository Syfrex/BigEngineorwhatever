#include "ConfigFile.h"
#include "..\third\tixml2ex.h"
#include <assert.h>
#include "..\Helpers\StringHelper.h"

Big::ConfigFile::ConfigFile()
{}
Big::ConfigFile::~ConfigFile()
{}

bool Big::ConfigFile::Create(const std::string& fileWithPath, bool parseNow /*= true*/)
{
	uri = fileWithPath;
	if (parseNow)
		return Parse();

	return false;
}

void Big::ConfigFile::Destroy()
{
	if (document)
	{
		delete document;
		document = nullptr;
	}
}

bool Big::ConfigFile::Parse()
{
	if (document)
	{
		delete document;
	}
	document = new tinyxml2::XMLDocument();
	tinyxml2::XMLError error = document->LoadFile(uri.c_str());
	if (error != tinyxml2::XML_SUCCESS)
	{
		//todo todo, do do do do do dodododoooooooooooooooooooo
		return false;
	}
	return true;
}

bool Big::ConfigFile::Save()
{
	assert(document != nullptr);
	tinyxml2::XMLError error = document->SaveFile(uri.c_str());

	if (error == tinyxml2::XML_SUCCESS)
		return true;

	return false;
}

bool Big::ConfigFile::GetString(const std::string& uri, std::string& outValue, const std::string& defaultValue)
{
	assert(document != nullptr);
	
	size_t attributposition = uri.find_last_not_of('/');
	const tinyxml2::XMLElement* element = tinyxml2::find_element(document->RootElement(), uri.substr(0, attributposition).c_str());
	if (element)
	{
		outValue = element->Attribute(uri.substr(attributposition + 1).c_str());
		return true;
	}
	outValue = defaultValue;
	return false;
}
