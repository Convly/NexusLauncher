#include "Launcher.hpp"

nx::Launcher::Launcher()
	:
	_systems({
		std::make_shared<nx::UISystem>()
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
}
