#pragma once

/******************************************************************************/
/*! \mainpage SimpleIniParser
 * A really simple .ini file parser
 *
 * Does not support comments, formating is minimalistic
 * Typical use :
 * @code
 * IniFile Config = IniFile("Config.ini");
 * // Do something with the values :
 * Option  = Config["SectionName"]["Key1"]; 
 * Option2 = Config("SectionName", "Key2"); // There is different ways to get values
 * Option3 = Config.get("UniqueKey");
 * // Modify some values
 * Config.set("SectionName", "Key1", Option); // Update Ini
 * // Save the result on disc
 * Config.save();
 * \endcode
 *
 * Started on 08 June 2012
 *
 * Senryoku <maretverdant@gmail.com>
 *
 * https://github.com/Senryoku/SimpleIniParser
 ******************************************************************************/

#include <map>
#include <fstream>

/** 
 * Class representing a ini file in memory.
 * Typical use :
 * @code
 * IniFile Config = IniFile("Config.ini");
 * // Do something with the values :
 * Option  = Config["SectionName"]["Key1"]; 
 * Option2 = Config("SectionName", "Key2"); // There is different ways to get values
 * Option3 = Config.get("UniqueKey");
 * // Modify some values
 * Config.set("SectionName", "Key1", Option); // Update Ini
 * // Save the result on disc
 * Config.save();
 * \endcode
**/
class IniFile
{
	public:
		/** Section Class
		 * Contains (Key, Value) pairs
		**/
		class Section : public std::map<std::string, std::string>
		{
			private:
				std::string _name; ///< Section's name (identifier)
			public:
				/** Constructor
				 * @param Name Name (Identifier) of the section
				**/
				Section(const std::string& Name) : _name(Name) {}
				
				/** @return Section's name **/
				inline const std::string& getName() const { return _name; }
				/** 
				 * @param Key Valid Key
				 * @return Value associated to Key
				**/
				inline const std::string& get(const std::string& Key) const 
				{ return at(Key); }
				/** Sets the value associated to Key
				 * @param Key Key
				 * @param Value associated to Key
				**/
				inline void set(const std::string& Key, 
								const std::string& Value)
				{ std::map<std::string, std::string>::operator[](Key) = Value; }
				/** 
				 * @param Key Valid Key
				 * @return Value associated to Key
				**/
				inline const std::string& operator[](const std::string& Key) const 
				{ return get(Key); }
				/** 
				 * @param Key Key
				 * @return True if Key is a valid (existing) key, false otherwise
				**/
				inline bool isKey(const std::string& Key) const 
				{ return count(Key) > 0; }
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
		
		/// Copy Constructor
		IniFile(const IniFile&);
		/// Move Constructor
		IniFile(IniFile&&) =default;
		
		/// Copy assigment
		IniFile& operator=(const IniFile&);
		/// Move assigment
		IniFile& operator=(IniFile&&) =default;
		
		/** @brief Destructor */
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

		/** @brief Adds/Modifies a value
		 *
		 * Creates Section if doesn't exist
		 * If [Section]Key is already specified, replace associated value.
		 * @param Name Section's name
		 * @param Key Key
		 * @param Value Value
		**/
		void set(const std::string& Name, const std::string& Key, 
					  const std::string& Value = "");

		/** @brief Returns section "Name"
		 *
		 * @param Name Section's name
		 * @return Section
		**/
		const Section& getSection(const std::string& Name) const;
		/// Syntactic sugar for getSection()
		inline const Section& operator[](const std::string& Name) const 
		{ return getSection(Name); }

		/** @brief Search for a value in any Section (the first found is returned)
		 *
		 * @param Key Key
		 * @return Value
		**/
		const std::string& get(const std::string& Key) const throw(std::out_of_range);
		
		/** @brief Search for a value
		 *
		 * @param Section Valid section's name
		 * @param Key Key
		 * @return Value
		**/
		const std::string& get(const std::string& Section, 
							   const std::string& Key) const;
		
		/** Syntactic sugar for get(Section, Name);
		 * @param Section Valid section's name 
		 * @param Key Valid Key
		**/
		inline const std::string& operator()(const std::string& Section, 
											 const std::string& Key) const 
		{ return getSection(Section).get(Key); }

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
		 * \endcode
		 * @see getEnd()
		**/
		Map::iterator begin() { return _data.begin(); }
		/// Const version of begin
		Map::const_iterator cbegin() const { return _data.cbegin(); }

		/** @brief Used to iterate on Sections (End test)
		 *
		**/
		Map::iterator end() { return _data.end(); }
		/// Const version of end
		Map::const_iterator cend() const { return _data.cend(); }

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
		
		Map			_data; ///< Actual data (Packed into Sections)
};
