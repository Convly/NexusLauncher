#include "Crawler.hpp"

nx::Crawler::Crawler(const std::string& path, const bool log)
:
	_path(path),
	_log(log)
{
	this->update();
}

nx::Crawler::~Crawler()
{

}

const std::string& nx::Crawler::getPath() const
{
	return this->_path;
}

const std::vector<fs::path>& nx::Crawler::getEntries()
{
	return this->getEntriesListByType(nx::Crawler::ENTRY_TYPE::ANY);
}

const std::vector<fs::path>& nx::Crawler::getSearch() const
{
	return this->_search;
}

const std::vector<std::pair<nx::Crawler::ENTRY_TYPE, std::vector<fs::path>>>& nx::Crawler::getSearchHistory() const
{
	return this->_searchHistory;
}

const std::vector<fs::path>& nx::Crawler::update()
{
	this->_entries.clear();

	for (const fs::path & p : fs::directory_iterator(this->_path)) {
		this->_entries.push_back(p);
	}

	return this->_entries;
}

bool nx::Crawler::archiveSearch(const nx::Crawler::ENTRY_TYPE type)
{
	if (this->_search.size() > 0) {
		this->_searchHistory.push_back(std::pair<nx::Crawler::ENTRY_TYPE, std::vector<fs::path>>(type, _search));
		this->_search.clear();
		return true;
	}
	return false;
}

void nx::Crawler::displayEntriesList(const std::vector<fs::path>& entries, const std::string& header) const
{
	if (!this->_log) return;
	std::cout << header << std::endl;
	for (auto & path : entries) {
		std::cout << ">>> " << path << std::endl;
	}
	std::cout << std::endl;
}


const std::vector<fs::path>& nx::Crawler::getEntriesListByType(const nx::Crawler::ENTRY_TYPE type)
{
	return this->getEntriesListByTypeAndPath(type, this->_path);
}

const std::vector<fs::path>& nx::Crawler::getDirectoriesList()
{
	return this->getEntriesListByTypeAndPath(nx::Crawler::ENTRY_TYPE::DIRECTORY, this->_path);
}

const std::vector<fs::path>& nx::Crawler::getDirectoriesListByPath(const std::string& path)
{
	return this->getEntriesListByTypeAndPath(nx::Crawler::ENTRY_TYPE::DIRECTORY, path);
}

const std::vector<fs::path>& nx::Crawler::getEntriesListByTypeAndPath(const nx::Crawler::ENTRY_TYPE type, const std::string& path)
{
	this->archiveSearch(type);

	for (const fs::path & path : this->_entries)
	{
		if (nx::Crawler::entryTypeModifier[type](path)) {
			this->_search.push_back(path);
		}
	}

	this->displayEntriesList(this->_search, "NEW SEARCH");

	return this->_search;
}