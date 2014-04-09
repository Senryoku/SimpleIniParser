#ifndef _INIFILE_HPP_
#define _INIFILE_HPP_

#include <map>
#include <fstream>

/*******************************************************************************
 * SimpleIniParser
 * A really simple .ini file parser
 *
 * Does not support comments, formating is minimalistic
 *
 * Started on 08 June 2012
 * Senryoku <maretverdant@gmail.com>
 * https://github.com/Senryoku/SimpleIniParser
 ******************************************************************************/

class IniFile
{
	public:
		class Section : public std::map<std::string, std::string>
		{
			private:
				std::string _name;
			public:
				Section(const std::string& Name) : _name(Name) {}

				inline const std::string& getName() const { return _name; }
				inline const std::string& getValue(const std::string& Key) const { return at(Key); }
				inline std::string& operator[](const std::string& Key) { return std::map<std::string, std::string>::operator[](Key); }
				inline const std::string& operator[](const std::string& Key) const { return getValue(Key); }
				inline bool isKey(const std::string& Key) const { return count(Key) > 0; }
		};
		
		using Map = std::map<std::string, Section*>;
		
		/** @brief Default constructor */
		IniFile();
		/** @brief Constructor with file
		 *
		 * Loads the given file
		 * @param Path Path to an existing .ini file
		**/
		IniFile(const std::string& Path);
		
		IniFile(const IniFile&);
		IniFile(IniFile&&) =default;
		
		IniFile& operator=(const IniFile&);
		IniFile& operator=(IniFile&&) =default;
		
		/** @brief Default destructor */
		~IniFile();

		/** @brief Return current file */
		const std::string& getPath() const { return _path; }
		/** @brief Sets path used by save() and load() */
		void setPath(const std::string& Path) { _path = Path; }

		/** @brief Re-Loads current file */
		bool load();
		/** @brief Loads given file, update internal Path
		 *
		 * @param Path File to load
		**/
		bool load(const std::string& Path);
		/** @brief Saves current file */
		bool save();
		/** @brief Saves content into given file
		 *
		 * @param Path Ini File
		**/
		bool save(const std::string& Path);

		/** @brief Frees current data **/
		void clear();

		/** @brief Add a section
		 *
		 * @param Name New section's name
		**/
		void addSection(const std::string& Name);

		/** @brief Add/Modify a value
		 *
		 * Creates Section if doesn't exist
		 * If [Section]Key is already specified, replace associated value.
		 * @param Name Section's name
		 * @param Key Key
		 * @param Value Value
		**/
		void addValue(const std::string& Name, const std::string& Key, 
					  const std::string& Value = "");
		inline void addKey(const std::string& Name, const std::string& Key, 
						   const std::string& Value = "") 
		{ addValue(Name, Key, Value); }

		/** @brief Returns section "Name"
		 *
		 * @param Name Section's name
		 * @return Section
		**/
		const Section& getSection(const std::string& Name) const;
		inline const Section& operator[](const std::string& Name) const 
		{ return getSection(Name); }
		
		inline const std::string& operator()(const std::string& Section, 
											 const std::string& Key) const 
		{ return getSection(Section).getValue(Key); }

		/** @brief Search for a value in any Section (the first found is returned)
		 *
		 * @param Key Key
		 * @return Value
		**/
		const std::string& getValue(const std::string& Key) const throw(std::out_of_range);
		
		/** @brief Search for a value
		 *
		 * @param Name Section's name
		 * @param Key Key
		 * @return Value
		**/
		const std::string& getValue(const std::string& Name, const std::string& Key) const;

		/** @brief Returns sections count
		 *
		 * @return Sections count
		**/
		size_t getSectionCount() const { return _data.size(); }

		/** @brief Used to iterate on Sections
		 *
		 * Example :
		 * @code
		 * for(auto it = Config.begin();
		 * it != Config.end(); it++)
		 * 	std::cout << "[" << it->first << "]" << std::endl;
		 * @see getEnd()
		**/
		Map::iterator begin() { return _data.begin(); }
		Map::const_iterator begin() const { return _data.cbegin(); }

		/** @brief Used to iterate on Sections (End test)
		 *
		**/
		Map::iterator end() { return _data.end(); }
		Map::const_iterator end() const { return _data.cend(); }

		/** @brief Tests if a section exists
		 *
		 * @param Name Section's name
		 * @return true if section exists
		**/
		bool isSection(const std::string& Name) const;
		
		/** @brief Tests if a key (in any section) exists
		 *
		 * @param Key Key
		 * @return true if section/key exists
		**/
		bool isKey(const std::string& Key) const;
		
		/** @brief Tests if a key (in a given section) exists
		 *
		 * @param Name Section's name
		 * @param Key Key
		 * @return true if section/key exists
		**/
		bool isKey(const std::string& Name, const std::string& Key) const;

	private:
		std::string _path; ///< Current File
		
		Map			_data;
};

#endif // _INIFILE_HPP_
