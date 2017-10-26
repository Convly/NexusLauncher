#include "GamesSystem.hpp"
#include "Launcher.hpp"

nx::GamesSystem::GamesSystem(nx::Launcher& root)
:
	SystemTpl(root, "games"),
	_binaryPath(fs::absolute(fs::path(root.getArgv()[0]).parent_path())),
	_crawler(this->_binaryPath, true)
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

	std::cout << "Update called" << std::endl;

	return this->_games;
}

const std::pair<bool, fs::path> nx::GamesSystem::is_launcherArchValid()
{
	auto dirs = this->_crawler.getDirectoriesList();
	auto it = std::find_if(dirs.begin(), dirs.end(), [&](auto & item){return item.filename() == "games";});
	bool valid = (it != dirs.end());
	return std::pair<bool, fs::path>(valid, (valid)? *it: "");;
}

bool nx::GamesSystem::is_validGameDirectory(const std::string& dir)
{
	return true;
}

bool nx::GamesSystem::is_validGameConfiguration(const std::string& dir)
{
	return true;
}