#include <iostream>

#include "IniFile.hpp"

int main(void)
{
	IniFile Config = IniFile("Config.ini");
	Config.save("SavingTest.ini");
	return 0;
}
