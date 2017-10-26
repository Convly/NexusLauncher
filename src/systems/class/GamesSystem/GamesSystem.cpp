#include "GamesSystem.hpp"
#include "Launcher.hpp"

nx::GamesSystem::GamesSystem(nx::Launcher& root)
:
	SystemTpl(root, "games"),
	_binaryPath(fs::absolute(fs::path(root.getArgv()[0]).parent_path())),
	_crawler(this->_binaryPath)
{

}

nx::GamesSystem::~GamesSystem()
{

}

void nx::GamesSystem::init()
{
	auto ret = this->is_launcherArchValid();
	if (!ret.first) {
		throw nx::SystemInitException(this->getName(), std::string("Cannot find 'games' directory in ") + this->_binaryPath);
	}

	this->_gamesPath = ret.second;
	this->update();
}

int nx::GamesSystem::run()
{
	// TODO: UPDATE GAME LIST ONE TIME
	return 0;
}

const std::vector<nx::GameInfos>& nx::GamesSystem::getGames() const
{
	return this->_games;
}

const std::vector<nx::GameInfos>& nx::GamesSystem::update()
{
	this->_games.clear();

	auto dirs = this->_crawler.getDirectoriesListByPath(this->_gamesPath);

	for (const auto it : dirs) {
		auto ret = this->is_validGameDirectory(it);
		if (ret.first) {
			try {
				this->_games.push_back(nx::GameInfos(ret.second));
			} catch (const nx::BadFormatGameJSONException e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}

	return this->_games;
}

const std::pair<bool, fs::path> nx::GamesSystem::is_launcherArchValid()
{
	auto dirs = this->_crawler.getDirectoriesList();

	auto it = std::find_if(dirs.begin(), dirs.end(), [&](auto & item){return item.filename() == NX_GAMES_DIR;});
	bool valid = (it != dirs.end());

	return std::pair<bool, fs::path>(valid, (valid)? *it: "");
}

const std::pair<bool, fs::path> nx::GamesSystem::is_validGameDirectory(const std::string& dir)
{
	auto entries = this->_crawler.getEntriesListByTypeAndPath(nx::Crawler::ENTRY_TYPE::REGULAR, dir);

	auto it = std::find_if(entries.begin(), entries.end(), [&](auto & item){return item.filename() == NX_GAMES_CONF_FILE;});
	bool valid = (it != entries.end());
	
	if (!valid)
		return std::pair<bool, fs::path>(false, "");

	return std::pair<bool, fs::path>(valid, *it);
}