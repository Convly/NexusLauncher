/**
 * @file Crawler.hpp
 * @author JSX
 */

#ifndef NEXUS_LAUNCHER_STANDALONE_CRAWLER
#define NEXUS_LAUNCHER_STANDALONE_CRAWLER

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <experimental/filesystem>
#include <unordered_map>
#include <functional>

namespace fs = std::experimental::filesystem;

struct EnumClassHash
{
	template <typename T>
	std::size_t operator()(T t) const
	{
		return static_cast<std::size_t>(t);
	}
};

namespace nx {

	/**
	 * @class Crawler
	 * This class allow the user to do researches in path and sort them by file type.
	 * All the researches are saved in a search history (archiveSearch()).
	 * The full list of keywords supported is available here: nx::Crawler::ENTRY_TYPE
	 */
	class  Crawler
	{
	public:
		/**
		 * @enum ENTRY_TYPE
		 * Reference all the types available for the researches
		 */
		enum ENTRY_TYPE
		{
			ANY = 0,
			BLOCK_FILE,
			CHARACTER_FILE,
			DIRECTORY,
			FIFO,
			OTHER,
			REGULAR,
			SOCKET,
			SYMLINK
		};
	
		/**
		 * This variable act as a linker.<br>
		 * It will, when a type is given in key, return a check function which will verify if the path given in argument is of the right type.<br><br>
		 * <i><b>eg</b>:<br>
		 * entryTypeModifier[nx::Crawler::ENTRY_TYPE::DIRECTORY](pathToMyHomeDir) will return true,<br>
		 * entryTypeModifier[nx::Crawler::ENTRY_TYPE::DIRECTORY](pathToMyBinary) will return false</i>
		 */
		std::unordered_map<nx::Crawler::ENTRY_TYPE, std::function<bool(fs::path)>, EnumClassHash> entryTypeModifier = 
		{
			{nx::Crawler::ENTRY_TYPE::ANY,              [](const fs::path& p) {return fs::exists(p);}},
			{nx::Crawler::ENTRY_TYPE::BLOCK_FILE,       [](const fs::path& p) {return fs::is_block_file(p);}},
			{nx::Crawler::ENTRY_TYPE::CHARACTER_FILE,   [](const fs::path& p) {return fs::is_character_file(p);}},
			{nx::Crawler::ENTRY_TYPE::DIRECTORY,        [](const fs::path& p) {return fs::is_directory(p);}},
			{nx::Crawler::ENTRY_TYPE::FIFO,             [](const fs::path& p) {return fs::is_fifo(p);}},
			{nx::Crawler::ENTRY_TYPE::OTHER,            [](const fs::path& p) {return fs::is_other(p);}},
			{nx::Crawler::ENTRY_TYPE::REGULAR,          [](const fs::path& p) {return fs::is_regular_file(p);}},
			{nx::Crawler::ENTRY_TYPE::SOCKET,           [](const fs::path& p) {return fs::is_socket(p);}},
			{nx::Crawler::ENTRY_TYPE::SYMLINK,          [](const fs::path& p) {return fs::is_symlink(p);}}
		};

	public:
		/**
		 * Default constructor for Crawler class
		 * 
		 * @param path The root path of the crawler. Default value: "."
		 * @param log Enable/Disable the ability to log debug messages. Default value: false
		 */
		Crawler(const std::string& path = ".", const bool log = false);
		/**
		 * Default destructor
		 */
		virtual ~Crawler();

	public:
		/**
		 * Setter for nx::Crawler::_path<br>
		 * When called, also trigger the update() function<br>
		 * 
		 * @param std::string path, the new path for the crawler
		 */
		void setPath(const std::string&);
		
		/**
		 * Getter for nx::Crawler::_path
		 * 
		 * @return a const reference to nx::Crawler::_path
		 */
		const std::string& getPath(void) const;
		
		/**
		 * Getter for nx::Crawler::_entries
		 * 
		 * @return a const reference to nx::Crawler::_entries
		 */
		const std::vector<fs::path>& getEntries(void);
		
		/**
		 * Getter for nx::Crawler::_search
		 * 
		 * @return a const reference to nx::Crawler::_search
		 */
		const std::vector<fs::path>& getSearch(void) const;
		
		/**
		 * Getter for nx::Crawler::_searchHistory
		 * 
		 * @return a const reference to nx::Crawler::_searchHistory
		 */
		const std::vector<std::pair<nx::Crawler::ENTRY_TYPE, std::vector<fs::path>>>& getSearchHistory(void) const;


	public:
		/**
		 * Update the stored entries (nx::Crawler::_entries)<br>
		 * When called:<br>
		 * 1. nx::Crawler::_entries::clear() is called<br>
		 * 2. nx::Crawler::_entries is filled with the list of files and directories in nx::Crawler::_path
		 * 
		 * @return std::vector<fs::path>& nx::Crawler::_entries
		 */
		const std::vector<fs::path>& update(void);
		
	public:
		/**
		 * Get the list of directories in the current root path.<br>
		 * This method use getEntriesListByTypeAndPath()
		 * @return a const reference to nx::Crawler::_search
		 */
		const std::vector<fs::path>& getDirectoriesList(void);
		
		/**
		 * Get the list of entries in the current root path, sorted by a file type.<br>
		 * This method use getEntriesListByTypeAndPath()
		 * 
		 * @param type The type used for the sort
		 * @return a const reference to nx::Crawler::_search
		 */
		const std::vector<fs::path>& getEntriesListByType(const nx::Crawler::ENTRY_TYPE);
		
		/**
		 * Get the list of directories, given a specific path.<br>
		 * This method use getEntriesListByTypeAndPath()
		 * 
		 * @param path The path used for the research
		 * @return a const reference to nx::Crawler::_search
		 */
		const std::vector<fs::path>& getDirectoriesListByPath(const std::string&);
		
		/**
		 * Get the list of entries, given a specific type and sorted by a type<br>
		 * 
		 * When called, this method act like this:<br>
		 * 1. The current search (nx::Crawler::_search) is archived thanks to archiveSearch()
		 * 2. nx::Crawler::_search is filled with the entries of the right type located at the path given in parameters.
		 * 3. If nx::Crawler::_log is enable, the current search will be displayed with displayEntriesList()
		 *
		 * @param type The type used for the sort
		 * @param path The path used for the research
		 * @return a const reference to nx::Crawler::_search
		 */
		const std::vector<fs::path>& getEntriesListByTypeAndPath(const nx::Crawler::ENTRY_TYPE, const std::string&);

	private:
		/**
		 * This method archive the current search (if not empty) into the search history.
		 * After being archived, the current search will be cleared.
		 * 
		 * @param nx::Crawler::ENTRY_TYPE the type associated to the research
		 * @return true if the current search has been saved
		 * @return false if the current search do not contain any result
		 */
		bool archiveSearch(const nx::Crawler::ENTRY_TYPE = nx::Crawler::ENTRY_TYPE::ANY);

		/**
		 * If nx::Crawler::_log is enable, display a list of entries and its informations in a pretty format
		 * 
		 * @param entries The list of entries
		 * @param type The type used for the research
		 * @param path The path used for the research
		 * @param header An alterable header message which will be print above the rest
		 */
		void displayEntriesList(const std::vector<fs::path>& entries, const nx::Crawler::ENTRY_TYPE& type, const fs::path& path, const std::string& header = "NEW ENTRIES LIST") const;

	private:
		bool																	_log; /**< Boolean which enable/disable the ability to display debug messages */
		std::string		                   										_path; /**< The crawler root path. All researches start there. */
		std::vector<fs::path>                                            		_search; /**< The results of the last research  */
		std::vector<std::pair<nx::Crawler::ENTRY_TYPE, std::vector<fs::path>>>  _searchHistory; /**< The container which store all researches ordered to the crawler */
		std::vector<fs::path>               									_entries; /**< The list of entries from nx::Crawler::_path */

	};
}

#endif // !NEXUS_LAUNCHER_STANDALONE_CRAWLER