#include "Launcher.hpp"

nx::Launcher::Launcher(int ac, char** av)
	:
	_argc(ac),
	_argv(av),
	_systems({
		std::make_shared<nx::UISystem>(*this)
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

void nx::Launcher::init()
{
	for (auto& it : this->_systems) {
		it->init();
	}
}

int nx::Launcher::run()
{
	this->init();

	for (auto & it : this->_systems) {
		if (it->getName() != "ui") {
			it->run();
		}
	}

	return this->getSystemByName("ui")->run();
}