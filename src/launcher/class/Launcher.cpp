#include "Launcher.hpp"

nx::Launcher::Launcher(int ac, char** av)
	:
	_argc(ac),
	_argv(av),
	_systems({
		std::make_shared<nx::UISystem>(*this),
		std::make_shared<nx::GamesSystem>(*this)
	})
{
}

nx::Launcher::~Launcher()
{
}

const std::vector<std::shared_ptr<nx::SystemTpl>>& nx::Launcher::getSystems(void) const
{
	return this->_systems;
}

const std::shared_ptr<nx::SystemTpl>& nx::Launcher::getSystemByName(const std::string & target) const
{
	for (auto & it : this->_systems) {
		if (it->getName() == target)
			return it;
	}

	throw nx::SystemNotFoundException(target + std::string(" not found"));
}

int& nx::Launcher::getArgc() const
{
	return this->_argc;
}

char** nx::Launcher::getArgv() const
{
	return this->_argv;
}

bool nx::Launcher::init()
{
	for (auto& it : this->_systems) {
		try {
			it->init();
		} catch (const nx::SystemInitException e) {
			std::cerr << e.what() << std::endl;
			return false;
		}
	}
	return true;
}

int nx::Launcher::run()
{
	if (!this->init())
		return EXIT_FAILURE;

	for (auto & it : this->_systems) {
		if (it->getName() != "ui") {
			it->run();
		}
	}

	return this->getSystemByName("ui")->run();
}