#include "IniFile.hpp"

IniFile::IniFile()
{
}

IniFile::IniFile(const std::string& Path)
{
	load(Path);
}

IniFile::IniFile(const IniFile& I) :
	_path(I._path)
{
	for(auto S : I._data)
		_data[S.first] = new Section(*S.second);
}

IniFile& IniFile::operator=(const IniFile& I)
{
	clear();
	_path = I._path;
	for(auto S : I._data)
		_data[S.first] = new Section(*S.second);
	return *this;
}

IniFile::~IniFile()
{
	clear();
}

bool IniFile::load()
{
	return load(_path);
}

bool IniFile::load(const std::string& Path)
{
	std::ifstream File(Path.c_str());
	if(File)
	{
		clear();
		Section *CurrentSection;
		std::string line, key, value;
		while(std::getline(File, line))
		{
			if(line[0] == '[')
			{
				CurrentSection = new Section(line.substr(1, line.find_first_of("]") - 1));
				_data.insert(std::make_pair(CurrentSection->getName(), CurrentSection));
			} else if(line != "" && line != "\n") {
				key = line.substr(line.find_first_not_of(" "));
				key = line.substr(0, line.find_first_of(" ="));
				if(line.find_first_of("=") + 1>= line.length())
				{
					value = "";
				} else  {
					value = line.substr(line.find_first_of("=") + 1);
					if(value.find_first_not_of(" ") > value.length())
						value = "";
					else
						value = value.substr(value.find_first_not_of(" "));
				}
				CurrentSection->insert(std::make_pair(key, value));
			}
		}
		File.close();
		_path = Path;
		return true;
	} else { return false; }
}

bool IniFile::save()
{
	return save(_path);
}

bool IniFile::save(const std::string& Path)
{
	std::ofstream File(Path.c_str());
	if(File)
	{
		for(auto it = _data.begin();
			it != _data.end(); it++)
		{
			File << "[" << it->first << "]" << std::endl;
			for(Section::iterator it2 = it->second->begin();
				it2 != it->second->end(); it2++)
				File << it2->first << " = " << it2->second << std::endl;
			File << std::endl;
		}
		File.close();
		return true;
	} else { return false; }
}

void IniFile::clear()
{
	for(auto it = _data.begin();
		it != _data.end(); it++)
		delete it->second;
	_data.clear();
}

void IniFile::addSection(const std::string& Name)
{
	if(!isSection(Name))
	{
		_data.insert(std::make_pair(Name, new Section(Name)));
	}
}

void IniFile::addValue(const std::string& Name, const std::string& Key, const std::string& Value)
{
	addSection(Name);
	Section *S = _data[Name];
	if(!isKey(Name, Key))
	{
		S->insert(std::make_pair(Key, Value));
	} else {
		(*S)[Key] = Value;
	}
}

const IniFile::Section& IniFile::getSection(const std::string& Name) const
{
	return *_data.at(Name);
}

const std::string& IniFile::getValue(const std::string& Key) const throw(std::out_of_range)
{
	for(auto& s : _data)
		if(s.second->isKey(Key)) return s.second->getValue(Key);
	throw std::out_of_range("IniFile : Key not found !");
}

const std::string& IniFile::getValue(const std::string& Name, const std::string& Key) const
{
	return (*_data.at(Name)).at(Key);
}

bool IniFile::isSection(const std::string& Name) const
{
	return _data.count(Name) > 0;
}

bool IniFile::isKey(const std::string& Key) const
{
	for(auto& s : _data)
		if(s.second->isKey(Key)) return true;
	return false;
}

bool IniFile::isKey(const std::string& Name, const std::string& Key) const
{
	return isSection(Name) && _data.at(Name)->count(Key);
}

