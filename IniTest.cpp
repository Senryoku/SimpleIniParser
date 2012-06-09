#include <iostream>

#include "IniFile.hpp"

int main(void)
{
	IniFile Config = IniFile("Config.ini");
	Config.addKey("Section2", "NewKey", "WithValue!");
	Config.save("SavingTest.ini");
	return 0;
}
