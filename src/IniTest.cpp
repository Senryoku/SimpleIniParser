#include <iostream>

#include "IniFile.hpp"

int main(void)
{
	IniFile Config = IniFile("Config.ini");
	for(IniFile::const_iterator it = Config.begin();
		it != Config.end(); it++)
	{
		std::cout << "[" << (*it)->getName() << "]" << std::endl;
		for(Ini::Section::const_iterator it2 = (*it)->begin();
			it2 != (*it)->end(); it2++)
			{
			Ini::Pair P = static_cast<Ini::Pair>(*it2);
			std::cout << " " << P.getKey() << " = " << P.getValue() << std::endl;
			}
	}
	Config.addKey("Section2", "NewKey", "WithValue!");
	Config.save("SavingTest.ini");
	return 0;
}
