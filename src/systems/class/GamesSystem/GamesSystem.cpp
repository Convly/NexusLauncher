#include "GamesSystem.hpp"
#include "Launcher.hpp"

nx::GamesSystem::GamesSystem(nx::Launcher& root)
:
	SystemTpl(root, "games")
{

}

nx::GamesSystem::~GamesSystem()
{

}

void nx::GamesSystem::init()
{
	// TODO: GET ALL RESSOURCES AND CHECK ALL (EG: CHECK IF DIRECTORY GAMES IS HERE)
	// eg in error: throw nx::SystemInitException(this->getName(), "Cannot find 'Games' directory in /home/convly/tamer");
}

int nx::GamesSystem::run()
{
	// TODO: START A THREAD WHICH CRAWL DIRECTORIES
	return 0;
}