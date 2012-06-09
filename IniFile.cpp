#include "IniFile.hpp"

IniFile::IniFile()
{
}

IniFile::IniFile(std::string Path) : myPath(Path)
{
	std::ifstream FileStream(myPath.c_str(), std::ifstream::in);
	FileStream.close();
}

IniFile::~IniFile()
{
}

bool IniFile::load()
{
}

bool IniFile::load(std::string Path)
{
}

bool IniFile::save()
{
}

bool IniFile::save(std::string Path)
{
}

IniFile::Section IniFile::getSection(std::string Name)
{
	return mySections[Name];
}

std::string IniFile::getValue(std::string Name, std::string Key)
{
	return (mySections[Name])[Key];
}

