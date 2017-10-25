#ifndef NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_
#define NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_

#include <memory>
#include <vector>
#include <iostream>

#include "SystemNotFoundException.hpp"
#include "SystemInitException.hpp"
#include "SystemTpl.hpp"
#include "UISystem.hpp"
#include "GamesSystem.hpp"

namespace nx {
	class Launcher
	{
	public:
		Launcher(int, char**);
		~Launcher();

	public:
		const std::vector<std::shared_ptr<nx::SystemTpl>>& getSystems(void) const;
		const std::shared_ptr<nx::SystemTpl>& getSystemByName(const std::string&) const;
		int run(void);
		int& getArgc(void) const;
		char** getArgv(void) const;

	private:
		bool init(void);

	private:
		int&	 	_argc;
		char**		_argv;
		std::vector<std::shared_ptr<nx::SystemTpl>>	_systems;

	};
}

#endif // !NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_
