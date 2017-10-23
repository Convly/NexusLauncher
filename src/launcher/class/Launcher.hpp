#ifndef NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_
#define NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_

#include <memory>
#include <vector>

#include "SystemNotFoundException.hpp"
#include "SystemTpl.hpp"
#include "UISystem.hpp"

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
		void init(void);

	private:
		int&	 	_argc;
		char**		_argv;
		std::vector<std::shared_ptr<nx::SystemTpl>>	_systems;

	};
}

#endif // !NEXUS_LAUNCHER_CORE_LAUNCHER_HPP_
