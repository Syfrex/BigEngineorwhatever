#include "StringHelper.h"
#include <algorithm>

bool Big::StringHelper::StringToBool(const std::string& value)
{

	if(value.compare("true") || value.compare("1"))
		return true;
	return false;
}

int Big::StringHelper::StringToInt(const std::string& value)
{
	return std::stoi(value);

}

void Big::StringHelper::BoolToString(bool value,std::string& outValue)
{
	if (value)
	{
		outValue = '1';
	}
	else
	{
		outValue = '0';
	}
}

void Big::StringHelper::IntToString(int value, std::string& outValue)
{
	outValue = std::to_string(value);
}

Big::StringHelper::StringHelper()
{
}


Big::StringHelper::~StringHelper()
{
}
