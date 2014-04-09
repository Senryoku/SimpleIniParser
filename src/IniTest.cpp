#include <iostream>

#include "IniFile.hpp"

int main(void)
{
	IniFile Config = IniFile("Config.ini");
	for(auto it = Config.begin();
		it != Config.end(); it++)
	{
		std::cout << "[" << it->first << "]" << std::endl;
		for(auto it2 = it->second->begin();
			it2 != it->second->end(); it2++)
		{
			// You will never use it this way !
			std::cout << " " << it2->first << " = " << it2->second << std::endl;
		}
	}
	std::cout << "Section1 : S1Key1 = " << Config.getSection("Section1").getValue("S1Key1") << std::endl;
	std::cout << "Section1 : S1Key1 = " << Config["Section1"]["S1Key1"] << std::endl;
	
	Config.addKey("Section2", "NewKey", "WithValue!");
	std::cout << "Section2 : NewKey = " << Config("Section2", "NewKey") << std::endl;
	
	Config.save("SavingTest.ini");
	return 0;
}
