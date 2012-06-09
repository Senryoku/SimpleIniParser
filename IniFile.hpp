#ifndef _INIFILE_HPP_
#define _INIFILE_HPP_

#include <map>
#include <fstream>

class IniFile
{
	public:
		typedef std::pair<std::string, std::string>	Pair;
		typedef std::map<std::string, std::string>	Section;

		/** @brief Default constructor */
		IniFile();
		IniFile(std::string Path);
		/** @brief Default destructor */
		~IniFile();

		bool load();
		bool load(std::string Path);
		bool save();
		bool save(std::string Path);

		Section getSection(std::string Name);
		std::string getValue(std::string Name, std::string Key);

	private:
		std::string myPath;
		std::map<std::string, Section> mySections;

};

#endif // _INIFILE_HPP_
