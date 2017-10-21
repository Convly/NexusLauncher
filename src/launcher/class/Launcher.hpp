#ifndef NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_
#define NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_

#include "SystemTpl.hpp"
#include "UISystem.hpp"

#include <memory>
#include <vector>

namespace nx {
	class Launcher
	{
	public:
		Launcher();
		~Launcher();

	public:
		const std::vector<std::shared_ptr<nx::SystemTpl>>& getSystems(void) const;
		const std::shared_ptr<nx::SystemTpl>& getSystemByName(const std::string&) const;

	private:
		std::vector<std::shared_ptr<nx::SystemTpl>>	_systems;

	};
}

#endif // !NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_
